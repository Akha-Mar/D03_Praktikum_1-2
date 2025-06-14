#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <functional>

using namespace std;

class IntegrationMethods {
private:
    // Fungsi untuk menghitung integral dengan metode Trapezoidal
    double trapezoidalRule(function<double(double)> f, double a, double b, int n) {
        double h = (b - a) / n;
        double sum = 0.5 * (f(a) + f(b));
        
        for (int i = 1; i < n; i++) {
            sum += f(a + i * h);
        }
        
        return h * sum;
    }

public:
    // Metode Romberg Integration
    double rombergIntegration(function<double(double)> f, double a, double b, int maxLevel) {
        vector<vector<double>> R(maxLevel + 1, vector<double>(maxLevel + 1, 0.0));
        
        // Inisialisasi kolom pertama dengan aturan Trapezoidal
        for (int i = 0; i <= maxLevel; i++) {
            int n = pow(2, i);
            R[i][0] = trapezoidalRule(f, a, b, n);
        }
        
        // Hitung nilai Romberg menggunakan ekstrapolasi Richardson
        for (int j = 1; j <= maxLevel; j++) {
            for (int i = j; i <= maxLevel; i++) {
                double factor = pow(4, j);
                R[i][j] = (factor * R[i][j-1] - R[i-1][j-1]) / (factor - 1);
            }
        }
        
        // Tampilkan tabel Romberg
        cout << "\n=== TABEL ROMBERG ===" << endl;
        cout << "Level\\Col";
        for (int j = 0; j <= maxLevel; j++) {
            cout << setw(15) << "R(" << j << ")";
        }
        cout << endl;
        
        for (int i = 0; i <= maxLevel; i++) {
            cout << "Level " << i << "  ";
            for (int j = 0; j <= i; j++) {
                cout << setw(15) << fixed << setprecision(10) << R[i][j];
            }
            cout << endl;
        }
        
        return R[maxLevel][maxLevel];
    }
    
    // Metode Trapezoidal biasa dengan berbagai jumlah interval
    void compareTrapezoidalAccuracy(function<double(double)> f, double a, double b, double exactValue) {
        cout << "\n=== PERBANDINGAN AKURASI METODE TRAPEZOIDAL ===" << endl;
        cout << setw(10) << "Interval" << setw(20) << "Hasil Integral" << setw(15) << "Error" << setw(20) << "Error Relatif (%)" << endl;
        cout << string(65, '-') << endl;
        
        for (int n = 2; n <= 1024; n *= 2) {
            double result = trapezoidalRule(f, a, b, n);
            double error = abs(result - exactValue);
            double relativeError = (error / abs(exactValue)) * 100;
            
            cout << setw(10) << n 
                 << setw(20) << fixed << setprecision(10) << result
                 << setw(15) << scientific << setprecision(4) << error
                 << setw(20) << fixed << setprecision(8) << relativeError << endl;
        }
    }
    
    // Demonstrasi keunggulan Romberg
    void demonstrateRombergAdvantage(function<double(double)> f, double a, double b, double exactValue) {
        cout << "\n=== DEMONSTRASI KEUNGGULAN METODE ROMBERG ===" << endl;
        
        // Metode Trapezoidal dengan interval besar
        double trap_result = trapezoidalRule(f, a, b, 16);
        double trap_error = abs(trap_result - exactValue);
        
        // Metode Romberg dengan level yang sama
        double romberg_result = rombergIntegration(f, a, b, 4);
        double romberg_error = abs(romberg_result - exactValue);
        
        cout << "\nHasil dengan 16 interval:" << endl;
        cout << "Trapezoidal  : " << fixed << setprecision(10) << trap_result << endl;
        cout << "Error        : " << scientific << setprecision(4) << trap_error << endl;
        
        cout << "\nHasil Romberg (Level 4):" << endl;
        cout << "Romberg      : " << fixed << setprecision(10) << romberg_result << endl;
        cout << "Error        : " << scientific << setprecision(4) << romberg_error << endl;
        
        cout << "\nPeningkatan akurasi: " << fixed << setprecision(2) 
             << (trap_error / romberg_error) << " kali lebih akurat!" << endl;
    }
};

// Fungsi-fungsi untuk diintegrasikan
double func1(double x) {
    return sin(x);  // Integral dari 0 to π = 2
}

double func2(double x) {
    return exp(x);  // Integral dari 0 to 1 = e - 1
}

double func3(double x) {
    return x * x;   // Integral dari 0 to 2 = 8/3
}

double func4(double x) {
    return 1.0 / (1.0 + x * x);  // Integral dari 0 to 1 = π/4
}

int main() {
    IntegrationMethods integrator;
    
    cout << "PROGRAM DEMONSTRASI INTEGRASI ROMBERG vs TRAPEZOIDAL" << endl;
    cout << "====================================================" << endl;
    
    // Test dengan fungsi sin(x) dari 0 to π
    cout << "\n1. FUNGSI f(x) = sin(x), dari 0 to π" << endl;
    cout << "Nilai eksak: 2.0" << endl;
    
    function<double(double)> f1 = func1;
    integrator.compareTrapezoidalAccuracy(f1, 0, M_PI, 2.0);
    integrator.demonstrateRombergAdvantage(f1, 0, M_PI, 2.0);
    
    // Test dengan fungsi e^x dari 0 to 1
    cout << "\n\n2. FUNGSI f(x) = e^x, dari 0 to 1" << endl;
    cout << "Nilai eksak: " << fixed << setprecision(10) << (exp(1) - 1) << endl;
    
    function<double(double)> f2 = func2;
    integrator.compareTrapezoidalAccuracy(f2, 0, 1, exp(1) - 1);
    integrator.demonstrateRombergAdvantage(f2, 0, 1, exp(1) - 1);
    
    // Test dengan fungsi x^2 dari 0 to 2
    cout << "\n\n3. FUNGSI f(x) = x^2, dari 0 to 2" << endl;
    cout << "Nilai eksak: " << fixed << setprecision(10) << (8.0/3.0) << endl;
    
    function<double(double)> f3 = func3;
    integrator.compareTrapezoidalAccuracy(f3, 0, 2, 8.0/3.0);
    integrator.demonstrateRombergAdvantage(f3, 0, 2, 8.0/3.0);
    
    // Test dengan fungsi 1/(1+x^2) dari 0 to 1
    cout << "\n\n4. FUNGSI f(x) = 1/(1+x^2), dari 0 to 1" << endl;
    cout << "Nilai eksak: " << fixed << setprecision(10) << (M_PI/4.0) << endl;
    
    function<double(double)> f4 = func4;
    integrator.compareTrapezoidalAccuracy(f4, 0, 1, M_PI/4.0);
    integrator.demonstrateRombergAdvantage(f4, 0, 1, M_PI/4.0);
    
    cout << "\n=== KESIMPULAN ===" << endl;
    cout << "Metode Romberg mengatasi kelemahan metode Trapezoidal dengan:" << endl;
    cout << "1. Menggunakan ekstrapolasi Richardson untuk meningkatkan akurasi" << endl;
    cout << "2. Mencapai akurasi tinggi dengan interval yang lebih sedikit" << endl;
    cout << "3. Konvergensi yang lebih cepat dibanding metode Trapezoidal biasa" << endl;
    cout << "4. Error berkurang secara eksponensial dengan setiap level Romberg" << endl;
    
    return 0;
}