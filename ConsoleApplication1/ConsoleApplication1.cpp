#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

void slauOut(double** a, double* y, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << " + ";
        }
        cout << " = " << y[i] << endl;
    }
}
double* methodGauss(double** a, double* y, int n)
{
    double* x, max = 0;
    int k = 0, index = 0;
    x = new double[n];
    while (k < n)
    {
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++)
        {
            if (abs(a[i][k]) > max)
            {
                max = abs(a[i][k]);
                index = i;
            }
        }
        for (int j = 0; j < n; j++)
        {
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;

        for (int i = k; i < n; i++)
        {
            double temp = a[i][k];
            for (int j = 0; j < n; j++)
                a[i][j] /= temp;
            y[i] /= temp;
            if (i == k) continue;
            for (int j = 0; j < n; j++)
                a[i][j] -= a[k][j];
            y[i] -= y[k];
        }
        k++;
    }

    for (k = n - 1; k >= 0; k--)
    {
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] -= a[i][k] * x[k];
    }
    return x;
}
double* vectorNevyazki(double** a_temp, double* y_temp, double* x, int n) {
    double* F;
    F = new double[n];
    for (int i = 0; i < n; i++) {
        double temp = 0;
        for (int j = 0; j < n; j++) {
            temp += a_temp[i][j] * x[j];
        }
        F[i] = y_temp[i] - temp;
    }
    return F;
}
int main()
{
    setlocale(LC_ALL, "ru");
    double** a, ** a_temp, * y, * y_temp, * x, * F, * x_temp;
    int n = 3;
    a = new double* [n];
    a_temp = new double* [n];
    y = new double[n];
    y_temp = new double[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            cout << "a[" << i << "][" << j << "]= ";
            cin >> a[i][j];
        }
    }
    cout << endl << endl << "--------------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "y[" << i << "]= ";
        cin >> y[i];
    }

    cout << endl << endl << "--------------" << endl;
    slauOut(a, y, n);
    cout << endl << endl << "--------------" << endl;
    x = methodGauss(a, y, n);
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "]=" << x[i] << endl;
    cout << endl << endl << "--------------" << endl;
    for (int i = 0; i < n; i++)
    {
        a_temp[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            cout << "a_temp[" << i << "][" << j << "]= ";
            cin >> a_temp[i][j];
        }
    }
    cout << endl << endl << "--------------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "y_temp[" << i << "]= ";
        cin >> y_temp[i];
    }
    cout << endl << endl << "--------------" << endl;
    F = vectorNevyazki(a_temp, y_temp, x, n);
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "]=" << x[i] << endl;
    cout << endl << endl << "--------------" << endl;
    for (int i = 0; i < n; i++)
        cout << "F[" << i << "]=" << F[i] << endl;
    cout << endl << endl << "--------------" << endl;
    cout << "Норма вектора невязки -> " << max((abs(F[0]), abs(F[1])), abs(F[2]));
    cout << endl << endl << "--------------" << endl;
    for (int i = 0; i < n; i++) {
        y_temp[i] = x[i];
    }
    x_temp = methodGauss(a_temp, y_temp, n);
    for (int i = 0; i < n; i++)
        cout << "x_temp[" << i << "]=" << x_temp[i] << endl;
    cout << endl << endl << "--------------" << endl;
    double x_max = max((x[0], x[1]), x[2]);
    double x_temp_max = max((x_temp[0], x_temp[1]), x_temp[2]);
    double delta = abs(x_temp_max - x_max) / abs(x_max);
    cout << "delta = " << delta << endl;
    return 0;
}