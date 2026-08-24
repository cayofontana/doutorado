import os
import numpy as np
from ai_edge_litert.interpreter import Interpreter


MODEL_PATH = "melhor_modelo_exp06_fp16.tflite"
INPUT_PATH = "benchmark_input.npy"
REFERENCE_PATH = "benchmark_output_tflite_fp16.npy"


def validar_arquivos():
    for caminho in (MODEL_PATH, INPUT_PATH, REFERENCE_PATH):
        if not os.path.exists(caminho):
            raise FileNotFoundError(f"Arquivo não encontrado: {caminho}")


def main():
    print("=" * 68)
    print("VALIDAÇÃO FP16 — PC x RASPBERRY PI ZERO 2 W")
    print("=" * 68)

    validar_arquivos()

    entrada = np.load(INPUT_PATH).astype(np.float32)
    referencia = np.load(REFERENCE_PATH).astype(np.float32)

    print("\n--- Arquivos de referência ---")
    print("Modelo:", MODEL_PATH)
    print("Entrada:", entrada.shape, entrada.dtype)
    print("Referência FP16/PC:", referencia.shape, referencia.dtype)

    print("\nCarregando modelo FP16...")
    interpreter = Interpreter(model_path=MODEL_PATH)

    input_details = interpreter.get_input_details()

    interpreter.resize_tensor_input(
        input_details[0]["index"],
        entrada.shape,
        strict=False
    )

    interpreter.allocate_tensors()

    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    print("Modelo carregado com sucesso.")
    print(
        "Entrada do modelo:",
        input_details[0]["shape"],
        input_details[0]["dtype"]
    )
    print(
        "Saída do modelo:",
        output_details[0]["shape"],
        output_details[0]["dtype"]
    )

    interpreter.set_tensor(
        input_details[0]["index"],
        entrada
    )

    print("\nExecutando inferência na Raspberry Pi...")
    interpreter.invoke()

    saida_rpi = interpreter.get_tensor(
        output_details[0]["index"]
    ).astype(np.float32)

    diferenca = (
        saida_rpi.astype(np.float64)
        - referencia.astype(np.float64)
    )
    abs_diff = np.abs(diferenca)

    max_abs_diff = float(np.max(abs_diff))
    mean_abs_diff = float(np.mean(abs_diff))
    rmse = float(np.sqrt(np.mean(diferenca ** 2)))

    allclose_1e5 = bool(
        np.allclose(
            saida_rpi,
            referencia,
            rtol=1e-5,
            atol=1e-5
        )
    )

    allclose_1e6 = bool(
        np.allclose(
            saida_rpi,
            referencia,
            rtol=1e-6,
            atol=1e-6
        )
    )

    print("\n" + "=" * 68)
    print("RESULTADOS — TFLite FP16 PC x LiteRT FP16 Raspberry Pi")
    print("=" * 68)
    print(f"Saída RPi:                  {saida_rpi.shape}")
    print(f"Máxima diferença absoluta: {max_abs_diff:.10e}")
    print(f"Média diferença absoluta:  {mean_abs_diff:.10e}")
    print(f"RMSE entre as saídas:      {rmse:.10e}")
    print(f"allclose (1e-5):           {allclose_1e5}")
    print(f"allclose (1e-6):           {allclose_1e6}")


if __name__ == "__main__":
    main()
