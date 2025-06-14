import numpy as np

def f(x):
    return np.sin(x)

def trapezoidal(f, a, b, n):
    h = (b - a) / n
    result = 0.5 * (f(a) + f(b))
    for i in range(1, n):
        result += f(a + i * h)
    return result * h

def romberg(f, a, b, max_order):
    R = [[0] * (max_order + 1) for _ in range(max_order + 1)]

    for i in range(0, max_order + 1):
        n = 2 ** i
        R[i][0] = trapezoidal(f, a, b, n)

    for k in range(1, max_order + 1):
        for j in range(k, max_order + 1):
            R[j][k] = (4**k * R[j][k-1] - R[j-1][k-1]) / (4**k - 1)
    
    return R

a = 0
b = np.pi
max_order = 4

result = romberg(f, a, b, max_order)

print("Tabel Romberg:")
for i in range(max_order + 1):
    for j in range(i + 1):
        print(f"{result[i][j]:.10f}", end="\t")
    print()

print(f"\nHasil integrasi Romberg: {result[max_order][max_order]:.10f}")