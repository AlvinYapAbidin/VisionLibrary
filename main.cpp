#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "vision.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    Vision::cornerDetector("images/building.jpg");

    //Vision::rotateImage("images/lena.png");

    // Vision::drawShapes("images/lena.png"); 

    // Vision::drawTemplate("images/lena.png", "images/template.png");

    // Vision::pyr("images/lena.png");

    // Vision::imgresize("lena.png");

    // Vision::snpmedian("pepper.tiff");

    // Vision::snpguassian("pepper.tiff");

    // Vision::sharpen("blurry.jpg");

    // Vision::templateMatchMethods("images/lena.png", "images/template.png");
    
}