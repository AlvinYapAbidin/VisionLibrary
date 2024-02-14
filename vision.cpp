#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

namespace Vision
{

    // Drawing shapes around object coordinates with cv::point
    int draw(std::string dir)
    {
        Mat img = imread(dir, IMREAD_COLOR);

        waitKey(0);

        return 0;
    }

    // Matching templates to appropriate image
    int templateMatch(std::string dir, std::string dir2)
    {
        Mat img = imread(dir, IMREAD_COLOR);
        Mat templ = imread(dir2, IMREAD_COLOR);

        matchTemplate; // function

        waitKey(0);

        return 0;
    }

    // Using pyramids to change the scale
    int pyr(std::string dir)
    {
        Mat img = imread(dir);

        const char* window_n = "Pyramids demo";

        for(;;)
        {
            imshow(window_n, img);
            char c = (char)waitKey(0);

            if(c==27)
            {
                break;
            }
            else if(c == 'i')
            {
                pyrUp(img, img, Size(img.cols*2, img.rows*2));
                printf("** Zoom In: Image x2 \n");
            }
            else if(c == 'o')
            {
                pyrDown(img,img,Size(img.cols/2, img.rows/2));
                printf("** Zoom Out: Imge / 2 \n");
            }
        }

        waitKey(0);

        return 0;
    }

    // Function to resize images
    int imgresize(std::string dir)
    {
        Mat img = imread(dir);

        // Apply resize to smaller image
        Mat imgSmaller;
        resize(img, imgSmaller, Size(round(0.75*img.cols), round(0.75*img.rows)));

        // Apply resize back to original size
        Mat imgToOriginal;
        resize(imgSmaller, imgToOriginal, img.size(), 0, 0);


        printf("Original image size: %d  %d\n" , img.rows, img.cols);
        printf("Resized to smaller image size: %d  %d\n" , imgSmaller.rows, imgSmaller.cols);
        printf("Resized back to original image size: %d  %d\n" , imgToOriginal.rows, imgToOriginal.cols);


        imshow("Original image", img);
        imshow("Resized to smaller image", imgSmaller);
        imshow("Resized back to original image", imgToOriginal);

        waitKey(0);

        return 0;
    }

    // Function to get rid of salt and peper noise using median blur
    int snpmedian(std::string dir)
    {
        Mat img = imread(dir, IMREAD_GRAYSCALE);

        // Apply gaussian blurring technique
        // Try different filter sizes to see effects
        Mat imgBlurred3x3;
        medianBlur(img, imgBlurred3x3, 3);

        Mat imgBlurred5x5;
        medianBlur(img, imgBlurred5x5, 5);

        Mat imgBlurred7x7;
        medianBlur(img, imgBlurred7x7, 7);

        // Apply laplacian sharpening technique
        Mat imgSharpened3x3;
        Laplacian(imgBlurred3x3, imgSharpened3x3, img.depth(), 3, 1, 0, 4);

        Mat imgSharpened5x5;
        Laplacian(imgBlurred5x5, imgSharpened5x5, img.depth(), 3, 1, 0, 4);

        Mat imgSharpened7x7;
        Laplacian(imgBlurred7x7, imgSharpened7x7, img.depth(), 3, 1, 0, 4);

        imshow("Original image", img);
        imshow("Blurred image 3x3 filter", imgBlurred3x3);
        imshow("Blurred image 5x5 filter", imgBlurred5x5);
        imshow("Blurred image 7x7 filter", imgBlurred7x7);
        imshow("Sharpened image 3x3", imgSharpened3x3);
        imshow("Sharpened image 5x5", imgSharpened5x5);
        imshow("Sharpened image 7x7", imgSharpened7x7);

        waitKey(0);

        return 0;
    }

    // Function to get rid of salt and peper noise using gaussian blur
    int snpguassian(std::string dir)
    {
        // Function to get rid of salt and peper noise using gaussian blur
        Mat img = imread(dir, IMREAD_GRAYSCALE);

        // Apply gaussian blurring technique
        // Try different filter sizes to see effects
        Mat imgBlurred3x3;
        GaussianBlur(img, imgBlurred3x3, Size(3, 3), 0);

        Mat imgBlurred5x5;
        GaussianBlur(img, imgBlurred5x5, Size(5, 5), 0);

        Mat imgBlurred7x7;
        GaussianBlur(img, imgBlurred7x7, Size(7, 7), 0);

        // Apply laplacian sharpening technique
        Mat imgSharpened3x3;
        Laplacian(imgBlurred3x3, imgSharpened3x3, img.depth(), 3, 1, 0, 4);

        Mat imgSharpened5x5;
        Laplacian(imgBlurred5x5, imgSharpened5x5, img.depth(), 3, 1, 0, 4);

        Mat imgSharpened7x7;
        Laplacian(imgBlurred7x7, imgSharpened7x7, img.depth(), 3, 1, 0, 4);

        imshow("Original image", img);
        imshow("Blurred image 3x3 filter", imgBlurred3x3);
        imshow("Blurred image 5x5 filter", imgBlurred5x5);
        imshow("Blurred image 7x7 filter", imgBlurred7x7);
        imshow("Sharpened image 3x3", imgSharpened3x3);
        imshow("Sharpened image 5x5", imgSharpened5x5);
        imshow("Sharpened image 7x7", imgSharpened7x7);

        waitKey(0);

        return 0;

    }
    
    // Function to sharpen an image
    int sharpen(std::string dir)
    {
        Mat img = imread(dir, IMREAD_COLOR);   

        Mat result;

        Mat kernel = (Mat_<float>(3,3) <<
            -1, -1, -1,
            -1,  9, -1,
            -1, -1, -1);
        filter2D(img, result, img.depth(), kernel, Point(-1,-1), 0, 4);

        imshow("Original image", img);
        imshow("Sharpened image", result);

        waitKey(0);

        return 0;
    }

    // Apply kernel filters to images and see their effects
    int filter(std::string dir, std::string dir2)
    {
         // Read Image
        Mat image = imread(dir, 0);
        Mat image2 = imread(dir2, 0);
    
        // Print Error message if image is null
       if (image.empty()) 
       {
            cout << "Could not read image" << endl;
            return -1; // Indicate failure
        }

        
        // Apply identity filter using kernel
        Mat kernel1 = (Mat_<double>(3,3) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
        Mat identity;
        filter2D(image, identity, -1 , kernel1, Point(-1, -1), 0, 4);

        printf("Original image size: %d  %d\n" , image.rows, image.cols);
        printf("Identity image size: %d  %d\n" , image.rows, image.cols);

        imshow("Original", image);
        imshow("Identity", identity);
    
        // Blurred using kernel
        // Initialize matrix with all ones
        Mat kernel2 = Mat::ones(5,5, CV_64F);
        // Normalize the elements
        kernel2 = kernel2 / 25;
        Mat imgBlur;
        filter2D(image, imgBlur, -1 , kernel2, Point(-1, -1), 0, 4);
        imshow("Kernel blur", imgBlur);

        // Blurred using kernel
        // Initialize matrix with all ones
        Mat kernel3 = Mat::ones(9,9, CV_64F);
        // Normalize the elements
        kernel3 = kernel3 / 81;
        Mat imgBlur2;
        filter2D(image, imgBlur2, -1 , kernel3, Point(-1, -1), 0, 4);
        imshow("Kernel blur 9x9", imgBlur2);

        waitKey(0); 

        return 0; 
    }
    
    //
    int tmplt(std::string dir, std::string dir2)
    {
        Mat img = imread(dir, IMREAD_COLOR);
        Mat tmplate = imread(dir2, IMREAD_COLOR);

        Mat result(img.rows - tmplate.rows + 1, img.cols - tmplate.cols + 1, CV_32FC1);

        matchTemplate(img, tmplate, result, TM_CCORR_NORMED);

        normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat()); // visualise point of interest

        double min;
        double max;

        Point minLoc;
        Point maxLoc;
        Point matchLoc;

        minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());

        //print min and max values

        rectangle(result, Point(maxLoc.x-tmplate.cols/2, maxLoc.y-tmplate.rows/2), Point(maxLoc.x+tmplate.cols/2, maxLoc.y+tmplate.rows/2), Scalar::all(0), 2, 8, 0);

        rectangle(img, Point(maxLoc.x, maxLoc.y), Point(maxLoc.x+tmplate.cols, maxLoc.y+tmplate.rows), Scalar::all(0), 2, 8, 0);


        imshow("Input", img);
        imshow("Template", tmplate);

        imshow("Result", result);

        waitKey(0);

        return 0; 
    }
    



    
}
