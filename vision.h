#ifndef VISION_H
#define VISION_H

#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;

namespace Vision
{
    int cornerDetector(std::string image);

    int rotateImage(std::string image);

    int drawShapes(std::string image);

    int drawTemplate(std::string image, std::string tem);

    int templateMatchMethods(std::string image, std::string tem);
    
    int templateMatch(std::string image, std::string tem, int matchMethod);

    int pyr(std::string dir);

    int imgresize(std::string dir);

    int snpmedian(std::string dir);

    int snpguassian(std::string dir);

    int sharpen(std::string dir);

    int filter(std::string dir);
    

}

#endif