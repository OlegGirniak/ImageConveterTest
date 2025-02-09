#include "PNGImageConverter.h"

#include <iostream>
#include <fstream>
#include <png.h>

bool PNGImageConverter::load(const std::string& filePath) 
{
    FILE *fp = nullptr;
    png_structp png = nullptr;
    png_infop info = nullptr;
    int rowBytes = 0;
    std::vector<png_bytep> rowPointers;
    
    fp = fopen(filePath.c_str(), "rb");
    if (!fp) {
        std::cout << "Error opening PNG file: " << filePath << std::endl;
        return false;
    }

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::cout << "png_create_read_struct failed" << std::endl;
        fclose(fp);
        return false;
    }

    info = png_create_info_struct(png);
    if (!info) {
        std::cout << "png_create_info_struct failed" << std::endl;
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        std::cout << "Error during PNG reading" << std::endl;
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return false;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    fileHeader.width = png_get_image_width(png, info);
    fileHeader.height = png_get_image_height(png, info);
    fileHeader.bitDepth = png_get_bit_depth(png, info);
    fileHeader.colorType = png_get_color_type(png, info);
    fileHeader.compressionMethod = png_get_compression_type(png, info);
    fileHeader.filterMethod = png_get_filter_type(png, info);
    fileHeader.interlaceMethod = png_get_interlace_type(png, info);

    png_read_update_info(png, info);

    rowBytes = png_get_rowbytes(png, info);
    pixelData.resize(rowBytes * fileHeader.height);

    rowPointers.resize(fileHeader.height);
    for (size_t i = 0; i < fileHeader.height; i++) {
        rowPointers[i] = &pixelData[i * rowBytes];
    }

    png_read_image(png, rowPointers.data());

    png_destroy_read_struct(&png, &info, nullptr);
    fclose(fp);
    return true;
}

bool PNGImageConverter::save(const std::string& filePath) 
{
    FILE* fp = nullptr;
    png_structp png = nullptr;
    png_infop info = nullptr;
    std::vector<png_bytep> rowPointers;

    fp = fopen(filePath.c_str(), "wb");
    if (!fp) {
        std::cout << "Error opening PNG file for saving: " << filePath << std::endl;
        return false;
    }

    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        std::cout << "png_create_write_struct failed" << std::endl;
        fclose(fp);
        return false;
    }

    info = png_create_info_struct(png);
    if (!info) {
        std::cout << "png_create_info_struct failed" << std::endl;
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) {
        std::cout << "Error during PNG saving" << std::endl;
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return false;
    }

    png_init_io(png, fp);
    png_set_IHDR(png, info, fileHeader.width, fileHeader.height,
                 fileHeader.bitDepth, fileHeader.colorType, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_BASE);
    png_write_info(png, info);

    rowPointers.resize(fileHeader.height);
    for (size_t i = 0; i < fileHeader.height; i++) {
        rowPointers[i] = &pixelData[i * png_get_rowbytes(png, info)];
    }

    png_write_image(png, rowPointers.data());
    png_write_end(png, nullptr);

    png_destroy_write_struct(&png, &info);
    fclose(fp);

    return true;
}

bool PNGImageConverter::convertToGrayscale() 
{
    int numChannels = 0;

    if (fileHeader.colorType != PNG_COLOR_TYPE_RGB &&
        fileHeader.colorType != PNG_COLOR_TYPE_RGBA) {
        std::cout << "Grayscale conversion is only supported" 
                     " for RGB or RGBA images" << std::endl;
        return false;
    }

    numChannels = (fileHeader.colorType == PNG_COLOR_TYPE_RGBA) ? 4 : 3;

    for (uint32_t y = 0; y < fileHeader.height; y++) {
        for (uint32_t x = 0; x < fileHeader.width; x++) {
            uint8_t* pixel = &pixelData[(y * fileHeader.width + x) * numChannels];
            uint8_t grayValue = static_cast<uint8_t>(0.3 * pixel[0] + 0.59 *
                                                     pixel[1] + 0.11 * pixel[2]);
            pixel[0] = pixel[1] = pixel[2] = grayValue;
            if (numChannels == 4) {
                pixel[3] = 255;
            }
        }
    }

    return true;
}
