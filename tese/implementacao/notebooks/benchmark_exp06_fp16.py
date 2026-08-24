import os
import time
import subprocess
import resource
import numpy as np

from ai_edge_litert.interpreter import Interpreter


MODEL_PATH = "melhor_modelo_exp06_fp16.tflite"
INPUT_PATH = "benchmark_input.npy"

WARMUP_RUNS = 10
BENCHMARK_RUNS = 100
PROGRESS_INTERVAL = 10

RESULT_PATH = "benchmark_exp06_fp16_resultado.txt"


def obter_temperatura():
    resultado = subprocess.run(
        ["vcgencmd", "measure_temp"],
        capture_output=True,
        text=True,
        check=False
    )

    texto = resultado.stdout.strip()

    if not texto:
        return float("nan")

    return float(
        texto
        .replace("temp=", "")
        .replace("'C", "")
    )


def obter_throttled():
    resultado = subprocess.run(
        ["vcgencmd", "get_throttled"],
        capture_output=True,
        text=True,
        check=False
    )

    texto = resultado.stdout.strip()

    return texto if texto else "indisponivel"


def obter_memoria_processo_mb():
    uso = resource.getrusage(
        resource.RUSAGE_SELF
    ).ru_maxrss

    # Em Linux, ru_maxrss é retornado em KiB.
    return uso / 1024.0


def percentil(valores, p):
    return float(
        np.percentile(
            valores,
            p
        )
    )


def imprimir_cabecalho():
    print("=" * 64)
    print("BENCHMARK — EXPERIMENTO 06 — FP16")
    print("Raspberry Pi Zero 2 W / LiteRT")
    print("=" * 64)


def validar_arquivos():
    arquivos = [
        MODEL_PATH,
        INPUT_PATH
    ]

    ausentes = [
        arquivo
        for arquivo in arquivos
        if not os.path.exists(arquivo)
    ]

    if ausentes:
        raise FileNotFoundError(
            "Arquivos não encontrados: "
            + ", ".join(ausentes)
        )


def main():
    imprimir_cabecalho()
    validar_arquivos()

    # -------------------------------------------------
    # Estado inicial
    # -------------------------------------------------

    temperatura_inicial = obter_temperatura()
    throttled_inicial = obter_throttled()
    memoria_inicial = obter_memoria_processo_mb()

    print("\n--- Estado inicial ---")
    print(
        f"Temperatura: {temperatura_inicial:.1f} °C"
    )
    print(
        f"Throttling: {throttled_inicial}"
    )
    print(
        f"Memória máxima do processo até aqui: "
        f"{memoria_inicial:.2f} MiB"
    )

    # -------------------------------------------------
    # Entrada
    # -------------------------------------------------

    entrada = np.load(
        INPUT_PATH
    ).astype(np.float32)

    print("\n--- Entrada ---")
    print("Shape:", entrada.shape)
    print("dtype:", entrada.dtype)

    # -------------------------------------------------
    # Carregamento do modelo
    # -------------------------------------------------

    print("\nCarregando modelo TFLite FP16...")

    inicio_carregamento = time.perf_counter()

    interpreter = Interpreter(
        model_path=MODEL_PATH
    )

    input_details = interpreter.get_input_details()

    interpreter.resize_tensor_input(
        input_details[0]["index"],
        entrada.shape,
        strict=False
    )

    interpreter.allocate_tensors()

    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    fim_carregamento = time.perf_counter()

    tempo_carregamento = (
        fim_carregamento
        - inicio_carregamento
    )

    print("Modelo carregado com sucesso.")
    print(
        f"Tempo de carregamento: "
        f"{tempo_carregamento:.6f} s"
    )

    # -------------------------------------------------
    # Warm-up
    # -------------------------------------------------

    print(
        f"\nExecutando {WARMUP_RUNS} "
        "inferências de warm-up..."
    )

    for i in range(WARMUP_RUNS):

        interpreter.set_tensor(
            input_details[0]["index"],
            entrada
        )

        interpreter.invoke()

        print(
            f"Warm-up {i + 1}/{WARMUP_RUNS} concluído",
            flush=True
        )

    print("Warm-up concluído.")

    # -------------------------------------------------
    # Benchmark
    # -------------------------------------------------

    print(
        f"\nExecutando {BENCHMARK_RUNS} "
        "inferências medidas..."
    )

    tempos = []

    temperatura_benchmark_inicial = obter_temperatura()
    throttled_benchmark_inicial = obter_throttled()

    for i in range(BENCHMARK_RUNS):

        interpreter.set_tensor(
            input_details[0]["index"],
            entrada
        )

        inicio = time.perf_counter()

        interpreter.invoke()

        fim = time.perf_counter()

        tempos.append(
            fim - inicio
        )

        if (
            (i + 1) % PROGRESS_INTERVAL == 0
            or (i + 1) == BENCHMARK_RUNS
        ):
            print(
                f"{i + 1}/{BENCHMARK_RUNS} "
                "inferências concluídas",
                flush=True
            )

    temperatura_benchmark_final = obter_temperatura()
    throttled_benchmark_final = obter_throttled()

    tempos = np.array(
        tempos,
        dtype=np.float64
    )

    # -------------------------------------------------
    # Estatísticas
    # -------------------------------------------------

    media = float(
        np.mean(tempos)
    )

    mediana = float(
        np.median(tempos)
    )

    desvio = float(
        np.std(
            tempos,
            ddof=1
        )
    )

    minimo = float(
        np.min(tempos)
    )

    maximo = float(
        np.max(tempos)
    )

    p95 = percentil(
        tempos,
        95
    )

    p99 = percentil(
        tempos,
        99
    )

    throughput = 1.0 / media

    # -------------------------------------------------
    # Estado final
    # -------------------------------------------------

    temperatura_final = obter_temperatura()
    throttled_final = obter_throttled()
    memoria_final = obter_memoria_processo_mb()

    # -------------------------------------------------
    # Relatório
    # -------------------------------------------------

    print("\n" + "=" * 64)
    print("RESULTADOS — FP16")
    print("=" * 64)

    print(
        f"Inferências de warm-up: {WARMUP_RUNS}"
    )

    print(
        f"Inferências medidas:    {BENCHMARK_RUNS}"
    )

    print(
        f"Tempo de carregamento:   "
        f"{tempo_carregamento:.6f} s"
    )

    print(
        f"\nTempo médio:             "
        f"{media * 1000:.3f} ms"
    )

    print(
        f"Mediana:                 "
        f"{mediana * 1000:.3f} ms"
    )

    print(
        f"Desvio padrão:           "
        f"{desvio * 1000:.3f} ms"
    )

    print(
        f"Mínimo:                  "
        f"{minimo * 1000:.3f} ms"
    )

    print(
        f"Máximo:                  "
        f"{maximo * 1000:.3f} ms"
    )

    print(
        f"P95:                     "
        f"{p95 * 1000:.3f} ms"
    )

    print(
        f"P99:                     "
        f"{p99 * 1000:.3f} ms"
    )

    print(
        f"Throughput:              "
        f"{throughput:.3f} inferências/s"
    )

    print(
        f"\nMemória inicial:         "
        f"{memoria_inicial:.2f} MiB"
    )

    print(
        f"Memória máxima:          "
        f"{memoria_final:.2f} MiB"
    )

    print(
        f"\nTemperatura inicial:     "
        f"{temperatura_inicial:.1f} °C"
    )

    print(
        f"Temp. início benchmark:  "
        f"{temperatura_benchmark_inicial:.1f} °C"
    )

    print(
        f"Temp. fim benchmark:     "
        f"{temperatura_benchmark_final:.1f} °C"
    )

    print(
        f"Temperatura final:       "
        f"{temperatura_final:.1f} °C"
    )

    print(
        f"\nThrottling inicial:      "
        f"{throttled_inicial}"
    )

    print(
        f"Throttling início bench: "
        f"{throttled_benchmark_inicial}"
    )

    print(
        f"Throttling fim bench:    "
        f"{throttled_benchmark_final}"
    )

    print(
        f"Throttling final:        "
        f"{throttled_final}"
    )

    # -------------------------------------------------
    # Salvar relatório
    # -------------------------------------------------

    with open(
        RESULT_PATH,
        "w",
        encoding="utf-8"
    ) as arquivo:

        arquivo.write(
            "BENCHMARK EXPERIMENTO 06 — FP16\n"
        )

        arquivo.write(
            "Raspberry Pi Zero 2 W / LiteRT\n\n"
        )

        arquivo.write(
            f"Warm-up: {WARMUP_RUNS}\n"
        )

        arquivo.write(
            f"Inferências: {BENCHMARK_RUNS}\n"
        )

        arquivo.write(
            f"Tempo carregamento: "
            f"{tempo_carregamento:.6f} s\n\n"
        )

        arquivo.write(
            f"Tempo médio: "
            f"{media * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"Mediana: "
            f"{mediana * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"Desvio padrão: "
            f"{desvio * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"Mínimo: "
            f"{minimo * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"Máximo: "
            f"{maximo * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"P95: "
            f"{p95 * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"P99: "
            f"{p99 * 1000:.3f} ms\n"
        )

        arquivo.write(
            f"Throughput: "
            f"{throughput:.3f} inferências/s\n\n"
        )

        arquivo.write(
            f"Memória inicial: "
            f"{memoria_inicial:.2f} MiB\n"
        )

        arquivo.write(
            f"Memória máxima: "
            f"{memoria_final:.2f} MiB\n\n"
        )

        arquivo.write(
            f"Temperatura inicial: "
            f"{temperatura_inicial:.1f} °C\n"
        )

        arquivo.write(
            f"Temperatura início benchmark: "
            f"{temperatura_benchmark_inicial:.1f} °C\n"
        )

        arquivo.write(
            f"Temperatura fim benchmark: "
            f"{temperatura_benchmark_final:.1f} °C\n"
        )

        arquivo.write(
            f"Temperatura final: "
            f"{temperatura_final:.1f} °C\n\n"
        )

        arquivo.write(
            f"Throttling inicial: "
            f"{throttled_inicial}\n"
        )

        arquivo.write(
            f"Throttling início benchmark: "
            f"{throttled_benchmark_inicial}\n"
        )

        arquivo.write(
            f"Throttling fim benchmark: "
            f"{throttled_benchmark_final}\n"
        )

        arquivo.write(
            f"Throttling final: "
            f"{throttled_final}\n"
        )

    print(
        f"\nRelatório salvo em {RESULT_PATH}"
    )


if __name__ == "__main__":
    main()
