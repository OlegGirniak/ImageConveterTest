#include <iostream>
#include <getopt.h>

#include "BMPImageConverter.h"
#include "PNGImageConverter.h"

bool GetOptions(int argc, char *argv[], std::string& inputFile,
                std::string& outputFile)
{
    int option = 0;

    while ((option = getopt(argc, argv, "i:o:")) != -1) {
        switch (option) {
            case 'i':
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case '?':
                std::cout << "Invalid option or missing argument." << std::endl;
                return false;
        }
    }

    if (inputFile.empty() || outputFile.empty()) {
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    int result = 0;
    std::string inputFile;
    std::string outputFile;
    ImageConverter* converter = nullptr;

    if (GetOptions(argc, argv, inputFile, outputFile)) {
        if (inputFile.find(".png") != std::string::npos) {
            converter = new PNGImageConverter();
        } else if (inputFile.find(".bmp") != std::string::npos) {
            converter = new BMPImageConverter();
        } else {
            std::cout << "Incorrect file" << std::endl;
            return 1;
        }
    } else {
        std::cout << "Both input and output file paths"
                "must be provided." << std::endl;
        return 1;
    }
    
    if (!converter->load(inputFile)) {
        result = 1;
        goto exit;
    }

    if (!converter->convertToGrayscale()) {
        result = 1;
        goto exit;
    }

    if (!converter->save(outputFile)) {
        result = 1;
    }

exit:
    delete converter;
    converter = nullptr;

    return result;
}