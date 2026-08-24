import os
import time
import subprocess
import resource
import numpy as np
from ai_edge_litert.interpreter import Interpreter

MODEL_PATH = "melhor_modelo_exp06.tflite"
INPUT_PATH = "benchmark_input.npy"
RESULT_PATH = "benchmark_exp06_resultado.txt"

WARMUP_RUNS = 10
BENCHMARK_RUNS = 100
PROGRESS_INTERVAL = 10


def obter_temperatura():
    r = subprocess.run(["vcgencmd", "measure_temp"], capture_output=True, text=True)
    texto = r.stdout.strip()
    if not texto:
        return float("nan")
    return float(texto.replace("temp=", "").replace("'C", ""))


def obter_throttled():
    r = subprocess.run(["vcgencmd", "get_throttled"], capture_output=True, text=True)
    texto = r.stdout.strip()
    return texto if texto else "indisponivel"


def obter_memoria_processo_mb():
    # Linux: ru_maxrss em KiB
    return resource.getrusage(resource.RUSAGE_SELF).ru_maxrss / 1024.0


def validar_arquivos():
    ausentes = [p for p in (MODEL_PATH, INPUT_PATH) if not os.path.exists(p)]
    if ausentes:
        raise FileNotFoundError("Arquivos não encontrados: " + ", ".join(ausentes))


def main():
    print("=" * 64)
    print("BENCHMARK — EXPERIMENTO 06")
    print("Raspberry Pi Zero 2 W / LiteRT FP32")
    print("=" * 64)

    validar_arquivos()

    temperatura_inicial = obter_temperatura()
    throttled_inicial = obter_throttled()
    memoria_inicial = obter_memoria_processo_mb()

    print("\n--- Estado inicial ---")
    print(f"Temperatura: {temperatura_inicial:.1f} °C")
    print(f"Throttling: {throttled_inicial}")
    print(f"Memória máxima do processo até aqui: {memoria_inicial:.2f} MiB")

    entrada = np.load(INPUT_PATH).astype(np.float32)
    print("\n--- Entrada ---")
    print("Shape:", entrada.shape)
    print("dtype:", entrada.dtype)

    print("\nCarregando modelo TFLite...")
    inicio_carregamento = time.perf_counter()

    interpreter = Interpreter(model_path=MODEL_PATH)
    input_details = interpreter.get_input_details()
    interpreter.resize_tensor_input(input_details[0]["index"], entrada.shape, strict=False)
    interpreter.allocate_tensors()
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    tempo_carregamento = time.perf_counter() - inicio_carregamento
    print("Modelo carregado com sucesso.")
    print(f"Tempo de carregamento: {tempo_carregamento:.6f} s")

    print(f"\nExecutando {WARMUP_RUNS} inferências de warm-up...")
    for i in range(WARMUP_RUNS):
        interpreter.set_tensor(input_details[0]["index"], entrada)
        interpreter.invoke()
        print(f"Warm-up {i + 1}/{WARMUP_RUNS} concluído", flush=True)
    print("Warm-up concluído.")

    print(f"\nExecutando {BENCHMARK_RUNS} inferências medidas...")
    tempos = []
    temperatura_benchmark_inicial = obter_temperatura()
    throttled_benchmark_inicial = obter_throttled()

    for i in range(BENCHMARK_RUNS):
        interpreter.set_tensor(input_details[0]["index"], entrada)
        inicio = time.perf_counter()
        interpreter.invoke()
        tempos.append(time.perf_counter() - inicio)

        if (i + 1) % PROGRESS_INTERVAL == 0 or (i + 1) == BENCHMARK_RUNS:
            print(f"{i + 1}/{BENCHMARK_RUNS} inferências concluídas", flush=True)

    temperatura_benchmark_final = obter_temperatura()
    throttled_benchmark_final = obter_throttled()

    tempos = np.asarray(tempos, dtype=np.float64)
    media = float(np.mean(tempos))
    mediana = float(np.median(tempos))
    desvio = float(np.std(tempos, ddof=1))
    minimo = float(np.min(tempos))
    maximo = float(np.max(tempos))
    p95 = float(np.percentile(tempos, 95))
    p99 = float(np.percentile(tempos, 99))
    throughput = 1.0 / media

    temperatura_final = obter_temperatura()
    throttled_final = obter_throttled()
    memoria_final = obter_memoria_processo_mb()

    linhas = [
        "BENCHMARK EXPERIMENTO 06",
        "Raspberry Pi Zero 2 W / LiteRT FP32",
        "",
        f"Warm-up: {WARMUP_RUNS}",
        f"Inferências: {BENCHMARK_RUNS}",
        f"Tempo carregamento: {tempo_carregamento:.6f} s",
        "",
        f"Tempo médio: {media * 1000:.3f} ms",
        f"Mediana: {mediana * 1000:.3f} ms",
        f"Desvio padrão: {desvio * 1000:.3f} ms",
        f"Mínimo: {minimo * 1000:.3f} ms",
        f"Máximo: {maximo * 1000:.3f} ms",
        f"P95: {p95 * 1000:.3f} ms",
        f"P99: {p99 * 1000:.3f} ms",
        f"Throughput: {throughput:.3f} inferências/s",
        "",
        f"Memória inicial: {memoria_inicial:.2f} MiB",
        f"Memória máxima: {memoria_final:.2f} MiB",
        "",
        f"Temperatura inicial: {temperatura_inicial:.1f} °C",
        f"Temperatura início benchmark: {temperatura_benchmark_inicial:.1f} °C",
        f"Temperatura fim benchmark: {temperatura_benchmark_final:.1f} °C",
        f"Temperatura final: {temperatura_final:.1f} °C",
        "",
        f"Throttling inicial: {throttled_inicial}",
        f"Throttling início benchmark: {throttled_benchmark_inicial}",
        f"Throttling fim benchmark: {throttled_benchmark_final}",
        f"Throttling final: {throttled_final}",
    ]

    print("\n" + "=" * 64)
    print("RESULTADOS")
    print("=" * 64)
    for linha in linhas[3:]:
        print(linha)

    with open(RESULT_PATH, "w", encoding="utf-8") as f:
        f.write("\n".join(linhas) + "\n")

    print(f"\nRelatório salvo em {RESULT_PATH}")


if __name__ == "__main__":
    main()
