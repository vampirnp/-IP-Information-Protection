//
// Created by Dmitriy on 14.03.2025.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для чтения ключа из файла
vector<int> readKey(const string& keyFile) {
    ifstream file(keyFile);
    if (!file) {
        cerr << "Unable to open key file";
        exit(1);
    }

    vector<int> key(5);
    for (int i = 0; i < 5; ++i) {
        file >> key[i];
        key[i]--; // Преобразование ключа в нумерацию с нуля
    }

    return key;
}

// Функция для шифрования
void encrypt(const string& inputFile, const string& outputFile, const vector<int>& key) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Unable to open input file";
        exit(1);
    }

    vector<char> buffer((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    // Дополнение файла символами 'z', если длина не кратна 5
    while (buffer.size() % 5 != 0) {
        buffer.push_back('z');
    }

    vector<vector<char>> columns(5);
    for (size_t i = 0; i < buffer.size(); ++i) {
        columns[i % 5].push_back(buffer[i]);
    }

    ofstream outFile(outputFile, ios::binary);
    for (int col : key) {
        outFile.write(&columns[col][0], columns[col].size());
    }
    outFile.close();
}

// Функция для расшифрования
void decrypt(const string& inputFile, const string& outputFile, const vector<int>& key) {
    ifstream inFile(inputFile, ios::binary);
    if (!inFile) {
        cerr << "Unable to open input file";
        exit(1);
    }

    vector<char> buffer((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    int numRows = buffer.size() / 5;
    vector<vector<char>> columns(5, vector<char>(numRows));

    int index = 0;
    for (int col : key) {
        copy(buffer.begin() + index, buffer.begin() + index + numRows, columns[col].begin());
        index += numRows;
    }

    ofstream outFile(outputFile, ios::binary);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < 5; ++j) {
            outFile.put(columns[j][i]);
        }
    }
    outFile.close();
}

int main() {
    string mode;
    cout << "Enter mode (encrypt/decrypt): ";
    cin >> mode;

    string inputFile, outputFile;
    cout << "Enter input file name: ";
    cin >> inputFile;
    cout << "Enter output file name: ";
    cin >> outputFile;

    vector<int> key = readKey("key.txt");

    if (mode == "encrypt") {
        encrypt(inputFile, outputFile, key);
        cout << "File encrypted successfully." << endl;
    } else if (mode == "decrypt") {
        decrypt(inputFile, outputFile, key);
        cout << "File decrypted successfully." << endl;
    } else {
        cerr << "Invalid mode. Use 'encrypt' or 'decrypt'." << endl;
    }

    return 0;
}
