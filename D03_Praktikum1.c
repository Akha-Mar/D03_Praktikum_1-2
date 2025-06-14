#include <stdio.h>
#include <math.h>

// Definisi fungsi f(x) = x^2 - 4
// Kamu bisa mengubah ini sesuai soal
double f(double x) {
    return x * x - 4;

}

// Fungsi untuk menjalankan metode Regula Falsi
double regula_falsi(double a, double b, int max_iter, double tolerance) {
    // Periksa apakah tanda f(a) dan f(b) berbeda
    if (f(a) * f(b) >= 0) {
        printf("Fungsi harus memiliki tanda yang berbeda di a dan b.\n");
        return -1;

    }

    double c;     // Titik tengah (root perkiraan)
    int iter = 0; // Penghitung iterasi

    // Header tabel hasil iterasi
    printf("Iterasi\t     a\t\t     b\t\t     c\t\t   f(c)\n");
    printf("---------------------------------------------------------------\n");

    // Proses iteratif metode Regula Falsi
    while (iter < max_iter) {
        // Rumus Regula Falsi untuk mencari titik c
        c = (a * f(b) - b * f(a)) / (f(b) - f(a));

        // Tampilkan nilai pada iterasi ini
        printf("%3d\t%10.6lf\t%10.6lf\t%10.6lf\t%10.6lf\n", iter + 1, a, b, c, f(c));

        // Periksa apakah nilai f(c) cukup dekat dengan 0 (berarti sudah cukup akurat)
        if (fabs(f(c)) < tolerance) {
            break;

        }

        // Perbarui nilai a atau b berdasarkan tanda f(c)
        if (f(a) * f(c) < 0) {
            b = c; // akar ada di antara a dan c

        } else {
            a = c; // akar ada di antara c dan b

        }

        iter++; // Tambah iterasi

    }

    printf("Akar ditemukan setelah %d iterasi.\n", iter);
    return c; // Return akar yang ditemukan

}

int main() {
    double a, b;         // Batas bawah dan atas
    int max_iter;        // Jumlah maksimum iterasi
    double tolerance;    // Toleransi error

    // Input dari pengguna
    printf("Masukkan batas bawah interval (a): ");
    scanf("%lf", &a);
    printf("Masukkan batas atas interval (b): ");
    scanf("%lf", &b);
    printf("Masukkan jumlah maksimum iterasi: ");
    scanf("%d", &max_iter);
    printf("Masukkan toleransi error (misal 0.0001): ");
    scanf("%lf", &tolerance);

    // Panggil fungsi regula_falsi
    double root = regula_falsi(a, b, max_iter, tolerance);

    // Tampilkan hasil jika berhasil
    if (root != -1) {
        printf("Akar fungsi adalah: %lf\n", root);

    }

    return 0;

}
