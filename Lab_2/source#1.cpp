#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

using namespace std;

// Функция для вычисления наибольшего общего делителя (алгоритм Евклида)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функция для быстрого возведения в степень по модулю
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Функция для вычисления модульной обратной величины
int modInverse(int e, int phi) {
    int k = 1;
    while (true) {
        int d = (k * phi + 1) / e;
        if (d * e % phi == 1) {
            return d;
        }
        k++;
    }
}

int main() {
    // Пример значений p и q
    int p = 7;
    int q = 13;

    // Вычисление n и phi(n)
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    // Выбор e
    int e = 5;
    while (e < phi && gcd(e, phi) != 1) {
        e++;
    }

    // Вычисление d
    int d = modInverse(e, phi);

    // Сообщение для шифрования
    vector<int> msg = {12, 1, 22, 19, 10}; // Пример: коды символов слова 'КАФСИ'
    vector<int> encrypted;
    vector<int> decrypted;

    // Шифрование
    printf("encrypted:\n");
    printf("msg: ");
    for (int m : msg) {
        int c = modExp(m, e, n);
        encrypted.push_back(c);
        printf("%d  ", c);
    }

    // Расшифровка
    printf("\ndecrypted:\n");
    printf("msg: ");
    for (int c : encrypted) {
        int m = modExp(c, d, n);
        decrypted.push_back(m);
        printf("%d  ", m);
    }

    return 0;
}

