#pragma once

#include <string>

class ImageConverter
{
public:
    virtual bool load(const std::string& filePath) = 0;
    virtual bool save(const std::string& filePath) = 0;
    virtual bool convertToGrayscale() = 0;
    virtual ~ImageConverter() {}
};