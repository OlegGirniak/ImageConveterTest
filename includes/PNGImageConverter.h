#pragma once
#include "ImageConverter.h"

#include <vector>
#include <cinttypes>

struct PNGHeader 
{
    uint32_t width;
    uint32_t height;
    uint8_t bitDepth;
    uint8_t colorType;
    uint8_t compressionMethod;
    uint8_t filterMethod;
    uint8_t interlaceMethod;
};

class PNGImageConverter : public ImageConverter 
{
    std::vector<uint8_t> pixelData;
    PNGHeader fileHeader;

public:
    bool load(const std::string& filePath) override;
    bool save(const std::string& filePath) override;
    bool convertToGrayscale() override;
};