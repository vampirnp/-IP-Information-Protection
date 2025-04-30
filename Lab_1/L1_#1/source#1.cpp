#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("example.txt", std::ios::binary | std::ios::ate);

    if (!file) {
        std::cerr << "Unable to open file";
        return 1;
    }

    std::ifstream::pos_type pos = file.tellg();
    std::cout << "File size: " << pos << " bytes" << std::endl;

    return 0;
}
