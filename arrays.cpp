#include <iostream>

// There is a O(n^2) way to do this. This just involves
// nested loops and is quite straightforward.
//
// If we let
//
//  T(i) = sum(A[k], k = 0; k = i)
//  V(i,j) = T(j) - T(i-1)
//
//  then V is max when
//
//  V(j) = T(j) - Tmin
//  
//  is max.
//
//  We need to keep track of WHERE Tmin occurs for i and
//  the location of Vmax for j. When we have these things
//  we have obtained the maximum contiguous subarray
//

double maxSubArray(double a[], int len, int& i, int& j) {
    double T = a[0], Vmax = a[0];
    double Tmin = std::min(0.0, T);
    for (int k = 1; k < len; k++) {
        T += a[k];
        if (T - Tmin > Vmax) {
            Vmax = T - Tmin;
            j = k;
        }
        if (T < Tmin) {
            Tmin = T;
            i = k < j ? k : j;
        }
    }
    return Vmax;
}

void movingAverage(double a[], double B[], int len, int m) {
    double S = 0;
    for (int i = 0; i < m; i++) {
        S += a[i];
    }
    B[0] = S / m;
    for (int i = m; i < len; i++) {
        // note the performance optimisation here.
        S = S + a[i] - a[i - m];
        B[i - m + 1] = S / m;
    }
}

int main() {
    int size = 10;
    int avg = 3;
    int avgSize = size - avg;
    int i = 0, j = 0;
    double* A = new double[size];
    double* B = new double[avgSize];
    A[0] = 1;
    A[1] = -1;
    A[2] = 2;
    A[3] = 4;
    A[4] = -8;
    A[5] = 5;
    A[6] = 6;
    A[7] = 5;
    A[8] = 4;
    A[9] = -7;

    auto max = maxSubArray(A, size, i, j);
    std::cout << "max, i+1 , j" << std::endl;
    std::cout << max << " " << i + 1 << " " << j << std::endl;

    movingAverage(A, B, size, avg);
    std::cout << "moving averages" << std::endl;
    for (int i = 0; i < avgSize; i++) {
        std::cout << B[i] << std::endl;
    }

    delete A[];
    delete B[];
    return 0;
}

