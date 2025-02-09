# Image Converter

This project is an application that loads a BMP or PNG image, applies a grayscale filter, and saves the processed image. Additionally, this application uses Docker to perform a simple image processing task.

## BUILT WITH

* G++ compiler
* C/C++
* STL
* CMake
* libpng
* Docker


## GETTING START

To launch scanner you need to do some steps:
* clone repository
* install libpng
* build project / use docker
* launch application

### Install libpng
To install on Ubuntu/Debian run this command:
```
sudo apt install libpng-dev
```

Fedora:
```
sudo dnf install libpng-devel
```

Arch Linux/Manjaro
```
sudo pacman -S libpng
```

### Build and Usage
To build your project you need install СMake:

Ubuntu/Debian
```
sudo apt install cmake make
```

Fedora:
```
sudo dnf install cmake make
```

Arch Linux/Manjaro
```
sudo pacman -S cmake make
```

So after that you need to enter in project directory with CMakeLists.txt
and run this command:
```
mkdir build
cmake ..
make
```

Execute this command to launch converter
```
./ImageConverter -i input_image_path.png -o output_image_path.png
```

input_image_path.png - source image path, could be PNG or BMP
output_image_path.png - result image path

So after that you see the new converted image.

You can use default photos from repository: test.png and test.bmp
./ImageConverter -i ../photos/test.png -o ../photos/resutl.png
./ImageConverter -i ../photos/test.bmp -o ../photos/resutl.bmp

## CLEAN
To remove executable file and build directory from project directory run this command:
```
make clean
```


## DOCKER
For launch application you can use Docker as well.

You need to install Docker for your os, you can find tutorial in the official page.

After installing you need to execute these commands:

```
sudo docker build -t image_converter .
sudo docker run --rm -v /path/to/photos:/data image-converter ./build/ImageConverter -i /data/input_image_path.png -o /data/output_image_path.png
```

