# Vision Library: OpenCV Image Processing Functions

## Introduction

Vision Library is a comprehensive image processing toolkit leveraging the power of OpenCV for C++ applications. It encompasses a wide array of functionalities, from elementary image manipulations such as resizing and filtering, to advanced operations including template matching and noise reduction. Aimed at facilitating rapid implementation and experimentation with diverse image processing techniques, this library serves as an invaluable resource for developers and researchers alike.

## Installation

### Prerequisites

Before installing the Vision Library, ensure that OpenCV is installed on your system. This library has been tested with OpenCV version 3.5 or later. For detailed installation instructions of OpenCV, please refer to the [official OpenCV documentation](https://docs.opencv.org/master/).

### Building the Library

To compile the Vision Library, follow these steps:

1. Clone the repository to your local machine.
2. Use CMake to prepare the build environment.
3. Compile the source code.

    git clone https://github.com/AlvinYapAbidin/VisionLibrary.git
    cd VisionLibrary
    mkdir build && cd build
    cmake .
    make

# Usage

To utilize the Vision Library in your project, include Vision.hpp and ensure your project links against OpenCV libraries. Below are several examples illustrating the use of the library's functions.

## Drawing Shapes
Draw shapes around object coordinates in an image:
    #include "Vision.hpp"
    
    int main() {
        Vision::draw("path/to/image.jpg", "path/to/template.jpg");
        return 0;
    }

## Template Matching
Execute template matching on an image:
    #include "Vision.hpp"
    
    int main() {
        Vision::templateMatch("path/to/image.jpg", "path/to/template.jpg", TM_CCORR_NORMED);
        return 0;
    }

## Image Resizing
Resize an image:
    #include "Vision.hpp"
    
    int main() {
        Vision::imgresize("path/to/image.jpg");
        return 0;
    }

## Noise Reduction
Reduce salt and pepper noise using median blur:
    #include "Vision.hpp"
    
    int main() {
        Vision::snpmedian("path/to/image.jpg");
        return 0;
    }

## License
This project is licensed under the MIT License. See the LICENSE.md file for more details.

**Note: Ensure to replace `"path/to/image.jpg"` and `"path/to/template.jpg"` with the actual paths to your images. Additionally, customize the installation instructions, usage examples, and other sections as necessary to align with the specifics of your project and environment.
**
