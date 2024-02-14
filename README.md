# Vision Library: OpenCV Image Processing Functions

## Introduction

Vision Library is a collection of image processing functions built with OpenCV in C++. It offers a range of functionalities, from basic image manipulation like resizing and filtering to more complex operations such as template matching and noise reduction. This library is designed to help developers and researchers quickly implement and experiment with various image processing techniques.

## Installation
### Prerequisites

Ensure you have OpenCV installed on your system. VisionLib is tested with OpenCV version 4.x. For installation instructions of OpenCV, refer to the official OpenCV documentation.
Building the Library

Clone the repository and compile the source code using CMake. Ensure your CMakeLists.txt is set up correctly to include OpenCV libraries.

git clone https://github.com/yourusername/VisionLib.git
cd VisionLib
mkdir build && cd build
cmake ..
make

## Usage

Include Vision.hpp in your project and compile it with OpenCV. Here are some examples of how to use the functions provided in the library.

### Drawing Shapes
To draw shapes around object coordinates:

#include "Vision.hpp"

int main() {
    Vision::draw("path/to/image.jpg");
    return 0;
}

### Template Matching
To perform template matching:

#include "Vision.hpp"

int main() {
    Vision::templateMatch("path/to/image.jpg", "path/to/template.jpg");
    return 0;
}

### Image Resizing
To resize an image:

#include "Vision.hpp"

int main() {
    Vision::imgresize("path/to/image.jpg");
    return 0;
}

### Noise Reduction
To reduce salt and pepper noise using median blur:

#include "Vision.hpp"

int main() {
    Vision::snpmedian("path/to/image.jpg");
    return 0;
}

### License

This project is licensed under the MIT License - see the LICENSE.md file for details.
Make sure to replace "path/to/image.jpg" and "path/to/template.jpg" with the actual paths to your images. Also, customize the installation, usage examples, and other sections as necessary to match the specifics of your project and environment.
