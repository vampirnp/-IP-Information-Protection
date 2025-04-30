//
// Created by Dmitriy on 14.03.2025.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

int main() {
    std::ifstream file("example.txt", std::ios::binary);

    if (!file) {
        std::cerr << "Unable to open file";
        return 1;
    }

    std::vector<unsigned int> byteFrequency(256, 0); // Массив для подсчета частоты каждого байта
    char byte;

    while (file.get(byte)) {
        byteFrequency[static_cast<unsigned char>(byte)]++;
    }

    file.close();

    // Вывод частоты появления каждого байта
    for (int i = 0; i < 256; ++i) {
        if (byteFrequency[i] > 0) {
            std::cout << "Byte: " << std::hex << std::setw(2) << std::setfill('0') << i
                      << " Frequency: " << std::dec << byteFrequency[i] << std::endl;
        }
    }

    return 0;
}
