#include <stdio.h>
#include <math.h>

double f(double x) {
    return x * x - 4; // Ubah fungsi di sini sesuai kebutuhan

}

double regula_falsi(double a, double b, int max_iter, double tolerance) {
    if (f(a) * f(b) >= 0) {
        printf("Fungsi harus memiliki tanda yang berbeda di a dan b.\n");
        return -1;

    }

    double c;
    int iter = 0;

    printf("Iterasi\t     a\t\t     b\t\t     c\t\t   f(c)\n");
    printf("---------------------------------------------------------------\n");

    while (iter < max_iter) {
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));
        printf("%3d\t%10.6lf\t%10.6lf\t%10.6lf\t%10.6lf\n", iter + 1, a, b, c, f(c));

        if (fabs(f(c)) < tolerance) {
            break;

        }

        if (f(a) * f(c) < 0) {
            b = c;

        } else {
            a = c;

        }

        iter++;

    }

    printf("Akar ditemukan setelah %d iterasi.\n", iter);
    return c;

}

int main() {
    double a, b;
    int max_iter;
    double tolerance;

    printf("Masukkan batas bawah interval (a): ");
    scanf("%lf", &a);
    printf("Masukkan batas atas interval (b): ");
    scanf("%lf", &b);
    printf("Masukkan jumlah maksimum iterasi: ");
    scanf("%d", &max_iter);
    printf("Masukkan toleransi error (misal 0.0001): ");
    scanf("%lf", &tolerance);

    double root = regula_falsi(a, b, max_iter, tolerance);
    if (root != -1) {
        printf("Akar fungsi adalah: %lf\n", root);

    }

    return 0;

}