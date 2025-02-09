#include "BMPImageConverter.h"

#include <iostream>
#include <fstream>
#include <cstring>

#define BMP_FORMAT 0x4D42
#define BYTES_PER_PIXEL 3
#define BPP 24

bool BMPImageConverter::load(const std::string& filePath) 
{
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error opening BMP file: " << filePath << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    if (fileHeader.fileType != BMP_FORMAT) {
        std::cout << "Not a BMP file!" << std::endl;
        return false;
    }

    file.read(reinterpret_cast<char*>(&dibHeader), sizeof(dibHeader));

    if (dibHeader.bitCount != BPP) {
        std::cout << "Only 24-bit BMP images are supported" << std::endl;
        return false;
    }

    file.seekg(fileHeader.offsetData, std::ios::beg);
    pixelData.resize(dibHeader.imageSize);
    file.read(reinterpret_cast<char*>(pixelData.data()), dibHeader.imageSize);

    return true;
}

bool BMPImageConverter::save(const std::string& filePath)
{
    std::ofstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error opening BMP file for saving: " << filePath << std::endl;
        return false;
    }

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));

    file.write(reinterpret_cast<const char*>(&dibHeader), sizeof(dibHeader));

    file.write(reinterpret_cast<const char*>(pixelData.data()), pixelData.size());

    return true;
}

bool BMPImageConverter::convertToGrayscale()
{
    for (int y = 0; y < dibHeader.height; y++) {
        for (int x = 0; x < dibHeader.width; x++) {
            int pixelIndex = (y * dibHeader.width + x) * BYTES_PER_PIXEL;
            uint8_t* pixel = &pixelData[pixelIndex];

            uint8_t grayValue = static_cast<uint8_t>(0.3 * pixel[2] + 
                                                     0.59 * pixel[1] +
                                                     0.11 * pixel[0]);

            pixel[0] = grayValue;  
            pixel[1] = grayValue;  
            pixel[2] = grayValue;
        }
    }

    return true;
}
