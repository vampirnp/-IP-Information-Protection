#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cstdint>
#include <string>  // Добавлен заголовочный файл для работы с std::string и getline

using namespace std;

void hideByteIntoPixel(RGBQUAD& pixel, uint8_t hideByte) {
    pixel.rgbBlue = (pixel.rgbBlue & 0xFC) | ((hideByte >> 6) & 0x3);
    pixel.rgbGreen = (pixel.rgbGreen & 0xFC) | ((hideByte >> 4) & 0x3);
    pixel.rgbRed = (pixel.rgbRed & 0xFC) | ((hideByte >> 2) & 0x3);
    pixel.rgbReserved = (pixel.rgbReserved & 0xFC) | (hideByte & 0x3);
}

uint8_t extractByteFromPixel(const RGBQUAD& pixel) {
    return ((pixel.rgbBlue & 0x3) << 6) | ((pixel.rgbGreen & 0x3) << 4) | ((pixel.rgbRed & 0x3) << 2) | (pixel.rgbReserved & 0x3);
}

vector<uint8_t> readBMP(const string& filePath, BITMAPFILEHEADER& fileHeader, BITMAPINFOHEADER& infoHeader) {
    ifstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Unable to open file: " + filePath);
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    if (infoHeader.biBitCount != 24) {
        throw runtime_error("Unsupported BMP format. Only 24-bit images are supported.");
    }

    int rowSize = (infoHeader.biWidth * 3 + 3) & ~3; // Выравнивание строк
    vector<uint8_t> pixelData(rowSize * abs(infoHeader.biHeight));

    file.seekg(fileHeader.bfOffBits);
    file.read(reinterpret_cast<char*>(pixelData.data()), pixelData.size());

    return pixelData;
}

void writeBMP(const string& filePath, const BITMAPFILEHEADER& fileHeader, const BITMAPINFOHEADER& infoHeader, const vector<uint8_t>& pixelData) {
    ofstream file(filePath, ios::binary);
    if (!file) {
        throw runtime_error("Unable to open file: " + filePath);
    }

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
    file.write(reinterpret_cast<const char*>(pixelData.data()), pixelData.size());
}

void hideTextInImage(vector<uint8_t>& pixelData, const string& text) {
    int textIndex = 0;
    int pixelIndex = 0;

    while (textIndex < text.size()) {
        RGBQUAD* pixel = reinterpret_cast<RGBQUAD*>(&pixelData[pixelIndex]);
        hideByteIntoPixel(*pixel, text[textIndex]);
        textIndex++;
        pixelIndex += sizeof(RGBQUAD);
    }

    // Добавляем маркер конца файла
    RGBQUAD* endPixel = reinterpret_cast<RGBQUAD*>(&pixelData[pixelIndex]);
    hideByteIntoPixel(*endPixel, 0xFF);
}

string extractTextFromImage(const vector<uint8_t>& pixelData) {
    string text;
    int pixelIndex = 0;

    while (true) {
        const RGBQUAD* pixel = reinterpret_cast<const RGBQUAD*>(&pixelData[pixelIndex]);
        uint8_t byte = extractByteFromPixel(*pixel);

        if (byte == 0xFF) {
            break; // Конец файла
        }

        text += byte;
        pixelIndex += sizeof(RGBQUAD);
    }

    return text;
}

void writetxt(const string& filePath, const string& text) {
    ofstream file(filePath);
    if (!file) {
        throw runtime_error("Unable to open file: " + filePath);
    }

    file << text;
    if (file.fail()) {
        throw runtime_error("Failed to write to file: " + filePath);
    }

    cout << "Success " << filePath << endl;
}


int main() {
    try {
        string inputFilePath;
        cout << "Enter the path to the input BMP file: ";
        cin >> inputFilePath;

        //C:/Users/Dmitriy/CLionProjects/5.bmp - исток
        //C:/Users/Dmitriy/CLionProjects/output.bmp - сток

        // Пример полного пути для выходного файла
        string outputFilePath = "C:/Users/Dmitriy/CLionProjects/output.txt";
        string outputFilePath2 = "C:/Users/Dmitriy/CLionProjects/output.bmp";

        BITMAPFILEHEADER fileHeader;
        BITMAPINFOHEADER infoHeader;
        auto pixelData = readBMP(inputFilePath, fileHeader, infoHeader);

        int choice;
        cout << "Choose an action:\n";
        cout << "1. Extract hidden text from the image\n";
        cout << "2. Hide text in the image\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        if (choice == 1) {
            // Извлечение текста из изображения
            string extractedText = extractTextFromImage(pixelData);
            cout << "Extracted text: " << extractedText << endl;

            writetxt(outputFilePath, extractedText);
            cout << "Text has been written to " << outputFilePath << endl;
        }
        else if (choice == 2) {
            // Сокрытие текста в изображении
            string textToHide;
            cout << "Enter the text to hide: ";
            cin.ignore();
            getline(cin, textToHide);

            hideTextInImage(pixelData, textToHide);

            writeBMP(outputFilePath2, fileHeader, infoHeader, pixelData);

            cout << "Image with hidden text saved to: " << outputFilePath2 << endl;
        }
        else {
            cout << "Invalid choice. Exiting...\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}