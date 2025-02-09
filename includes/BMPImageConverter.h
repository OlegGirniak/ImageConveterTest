#pragma once

#include "ImageConverter.h"

#include <vector>
#include <cinttypes>

#pragma pack(push, 1)
struct BMPHeader 
{
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetData;
};

struct DIBHeader 
{
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xResolution;
    int32_t yResolution;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

class BMPImageConverter : public ImageConverter 
{
    std::vector<uint8_t> pixelData;
    BMPHeader fileHeader;
    DIBHeader dibHeader;

public:
    bool load(const std::string& filePath) override;
    bool save(const std::string& filePath) override;
    bool convertToGrayscale() override;
    
    ~BMPImageConverter() = default;
};

