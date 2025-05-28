import matplotlib.pyplot as plt
import numpy as np

def parse_data(filename):
    with open(filename) as f:
        lines = f.readlines()

    data = {}
    current_func = None

    for line in lines:
        line = line.strip()
        if not line:
            continue

        if line.startswith("Function:"):
            current_func = line.split(":")[1].strip()
            data[current_func] = []
            continue

        if current_func is None:
            continue

        # Пропускаем заголовки таблиц и строки, не начинающиеся с числа
        if not line[0].isdigit():
            continue

        parts = line.split()
        if len(parts) != 4:
            continue

        try:
            n = int(parts[0])
            err_x = float(parts[1])
            err_f = float(parts[2])
            delta = float(parts[3])
            data[current_func].append((n, err_x, err_f, delta))
        except ValueError:
            continue

    return data

data = parse_data("data.txt")

fig, axs = plt.subplots(len(data), 3, figsize=(15, 4 * len(data)))
fig.suptitle("Bisection Method Analysis", fontsize=16)

for i, (func, values) in enumerate(data.items()):
    values = np.array(values)
    n = values[:, 0]
    err_x = values[:, 1]
    err_f = values[:, 2]
    delta = values[:, 3]

    axs[i][0].semilogy(n, err_x, 'o-')
    axs[i][0].set_title(f"{func}: |xₙ - x*|")
    axs[i][0].set_xlabel("n")

    axs[i][1].semilogy(n, err_f, 'o-')
    axs[i][1].set_title(f"{func}: |f(xₙ)|")
    axs[i][1].set_xlabel("n")

    axs[i][2].semilogy(n[1:], delta[1:], 'o-')  # Пропускаем первую (nan/DBL_MAX)
    axs[i][2].set_title(f"{func}: |xₙ - xₙ₋₁|")
    axs[i][2].set_xlabel("n")

plt.tight_layout(rect=[0, 0.03, 1, 0.97])
plt.show()

