#ifndef VISION_H
#define VISION_H

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

namespace Vision
{
    int pyr(std::string dir);

    int imgresize(std::string dir);

    int snpmedian(std::string dir);

    int snpguassian(std::string dir);

    int sharpen(std::string dir);

    int filter(std::string dir, std::string dir2);
    
    int tmplt(std::string dir, std::string dir2);

}

#endif