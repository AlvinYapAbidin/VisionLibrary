#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <iostream>
using namespace cv;
using namespace std;

namespace Vision
{
    int featureDetection(std::string image1, std::string image2)
    {
        Mat img1 = imread(image1, IMREAD_GRAYSCALE);
        Mat img1Resize;
        Mat img2 = imread(image2, IMREAD_GRAYSCALE);
        Mat img2Resize;

        resize(img1, img1Resize, Size(), 0.2, 0.2);
        resize(img2, img2Resize, Size(), 0.2, 0.2);


        // Step 1: Detect the keypoints using SIFT Detector
        Ptr<SIFT> detector = SIFT::create();
        std::vector<KeyPoint> keypoints1, keypoints2;
        Mat descriptors1, descriptors2;
        detector->detectAndCompute(img1Resize, noArray(), keypoints1, descriptors1);
        detector->detectAndCompute(img2Resize, noArray(), keypoints2, descriptors2);

        // Step 2: Matching descriptor vectors
        BFMatcher matcher(NORM_L2);
        std::vector<cv::DMatch> matches;
        matcher.match(descriptors1, descriptors2, matches);

        // Sort matches by score
        std::sort(matches.begin(), matches.end());

        // Keep only the top N matches
        int N = 10;
        std::vector<cv::DMatch> bestMatches(matches.begin(), matches.begin() + std::min(N, (int)matches.size()));

        // Draw matches
        Mat img_matches;
        drawMatches(img1Resize, keypoints1, img2Resize, keypoints2, bestMatches, img_matches);

        // Show detected matches
        imshow("Matches", img_matches);

        waitKey();
        return 0;

    }

    // Harris Corner Detector
    int cornerDetector(std::string image)
    {
        Mat img = imread(image);
        Mat imgGray;
        Mat output = Mat::zeros(img.size(), CV_32FC1);

        cvtColor(img,imgGray, COLOR_BGR2GRAY);
        
        int blockSize = 2;
        int apertureSize = 3;
        double k = 0.04;
        cornerHarris(imgGray, output, blockSize, apertureSize, k);

        Mat outputNorm;
        Mat outputNormScaled;
        normalize(output, outputNorm, 0, 255 ,NORM_MINMAX, CV_32FC1, Mat()); // Ensure cornerHarris values between 0-255
        convertScaleAbs(outputNorm, outputNormScaled); // outputNorm is CV_32FC1, imshow expects CV_8UC1
        

        for (int i = 0; i < outputNorm.rows; i++)
        {
            for (int j = 0; j < outputNorm.cols; j++)
            {
                if ( (int) outputNorm.at<float>(i,j) >  160 )
                {
                    circle( outputNormScaled, Point(j,i), 5, Scalar(0), 2, 8, 0);
                }
            }
        }

        imshow("Input image", img);
        imshow("Corner detection", outputNormScaled);

        waitKey();
        return 0;
    }

    // Rotate images
    int rotateImage(std::string image)
    {
        Mat imgOriginal = imread(image);

        double angle = 45;  //Adjust to the angle you would like to rotate

        cv::Point2f center((imgOriginal.cols-1)/2.0, (imgOriginal.rows-1)/2.0);
        cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);

        // Find the rotated bounding rectangle size to find the edges where the rotated image falls outside the original image's bounds
        Rect2f box = RotatedRect(Point2f(), imgOriginal.size(), angle).boundingRect2f();
        // Ensure rotated image centered inside output image frame
        rot.at<double>(0,2) += box.width/2.0 - imgOriginal.cols/2.0;
        rot.at<double>(1,2) += box.height/2.0 - imgOriginal.rows/2.0;

        Mat output;
        warpAffine(imgOriginal, output, rot, box.size());

        imshow("Original image", imgOriginal);
        imshow("Rotated image", output);

        waitKey(0);

        return 0;
    }

    // Draw shapes in images
    int drawShapes(std::string image)
    {
        Mat img = imread(image, IMREAD_COLOR);
        
        // Points for rectangle
        Point vt = Point(50, 100);// Specify the rectangle vertex
        Point vtOp = Point(250, 300);// Specify the rectangle opposite vertex

        // Center point for circle
        Point center = Point(600, 500);

        rectangle(img, vt, vtOp, Scalar::all(0), 2, 8, 0);

        circle(img, center, 120, Scalar(0, 255, 0), FILLED, 8, 0);

        imshow("Shapes" , img);

        waitKey(0);

        return 0;
    }

    // Matching templates to appropriate image
    int templateMatch(std::string image, std::string tem, int matchMethod)
    {
        Mat img = imread(image, IMREAD_COLOR);
        Mat templ = imread(tem, IMREAD_COLOR);
        Mat result(img.rows - templ.rows + 1, img.cols - templ.cols + 1, CV_32FC1);
        
        matchTemplate(img, templ, result, matchMethod);

        normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat()); 

        double min; double max; Point minLoc; Point maxLoc; Point matchLoc;
        
        minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
        printf("Min value: %d Max value: %d\n" , min, max);

        rectangle(img, Point(maxLoc.x, maxLoc.y), Point(maxLoc.x+templ.cols, maxLoc.y+templ.rows), Scalar::all(0), 2, 8, 0);
        rectangle(result, Point(maxLoc.x-templ.cols/2, maxLoc.y-templ.rows/2), Point(maxLoc.x+templ.cols/2, maxLoc.y+templ.rows/2), Scalar::all(0), 2, 8, 0);

        //printf("Original image size: %d x %d\n" , img.rows, img.cols);
        //printf("Result image size: %d x %d\n" , result.rows, result.cols); // Result image size smaller because template can't go pass the edge of input image, when template matching

        std::string methodName{};

        switch (matchMethod) 
        {
            case cv::TM_SQDIFF: methodName = "TM_SQDIFF"; break;
            case cv::TM_SQDIFF_NORMED: methodName = "TM_SQDIFF_NORMED"; break;
            case cv::TM_CCORR: methodName = "TM_CCORR"; break;
            case cv::TM_CCORR_NORMED: methodName = "TM_CCORR_NORMED"; break;
            case cv::TM_CCOEFF: methodName = "TM_CCOEFF"; break;
            case cv::TM_CCOEFF_NORMED: methodName = "TM_CCOEFF_NORMED"; break;
            default: methodName = "Unknown Method"; 
        }

        cv::putText(result, methodName, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);


        imshow("Input", img);
        imshow("Template", templ);
        imshow("Result" , result);

        waitKey(0);

        return 0; 
    }

    // Apply different template matching methods
    int templateMatchMethods(std::string image, std::string tem)
    {
        printf("Press [esc] to go through the different filter types");

        templateMatch(image, tem, TM_SQDIFF);
        templateMatch(image, tem, TM_CCORR );
        templateMatch(image, tem, TM_CCORR_NORMED);
        templateMatch(image, tem, TM_CCOEFF);
        templateMatch(image, tem, TM_CCOEFF_NORMED);

        waitKey(0);

        return 0; 
    }

    // Using pyramids to change the scale
    int pyr(std::string dir)
    {
        cout << "press [i] to zoom in";
        cout << "press [o] to zoom out";
        cout << "press [esc] to exit";

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
    int filter(std::string dir)
    {
         // Read Image
        Mat image = imread(dir, 0);

        // Apply identity filter using kernel
        Mat kernel1 = (Mat_<double>(3,3) << 0, 0, 0, 0, 1, 0, 0, 0, 0); // Edit identity filter here by adjusting filter values
        Mat identity;
        filter2D(image, identity, -1 , kernel1, Point(-1, -1), 0, 4);

        printf("Original image size: %d  %d\n" , image.rows, image.cols);
        printf("Identity image size: %d  %d\n" , image.rows, image.cols);

        imshow("Original", image);
        imshow("Identity", identity);
    
        // Blurred using kernel
        // Initialize matrix with all ones
        Mat kernel2 = Mat::ones(5,5, CV_64F); // 5x5 matrix
        // Normalize the elements
        kernel2 = kernel2 / 25;
        Mat imgBlur;
        filter2D(image, imgBlur, -1 , kernel2, Point(-1, -1), 0, 4);
        imshow("Kernel blur", imgBlur);

        // Blurred using kernel
        // Initialize matrix with all ones
        Mat kernel3 = Mat::ones(9,9, CV_64F); // 9x9 matrix
        // Normalize the elements
        kernel3 = kernel3 / 81;
        Mat imgBlur2;
        filter2D(image, imgBlur2, -1 , kernel3, Point(-1, -1), 0, 4);
        imshow("Kernel blur 9x9", imgBlur2);

        waitKey(0); 

        return 0; 
    }

    // Drawing shapes around object template with cv::point
    // int drawTemplate(std::string image, std::string tem)
    // {
    //     Mat img = imread(image, IMREAD_COLOR);
    //     Mat templ = imread(tem, IMREAD_COLOR);
    //     Mat result(img.rows - templ.rows + 1, img.cols - templ.cols + 1, CV_32FC1);
    //     matchTemplate(img, templ, result, TM_CCORR_NORMED);
    //     normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat()); 
    //     double min; double max; Point minLoc; Point maxLoc; Point matchLoc;
    //     minMaxLoc(result, &min, &max, &minLoc, &maxLoc, Mat());
    //     Mat img2 = img.clone();
    //     rectangle(img, Point(maxLoc.x, maxLoc.y), Point(maxLoc.x+templ.cols, maxLoc.y+templ.rows), Scalar::all(0), 2, 8, 0);
    //     circle(img2, Point(maxLoc.x+templ.cols/2, maxLoc.y+templ.rows/2), 120, Scalar(0, 255, 0), 2, 8, 0);
    //     imshow("Rectangle" , img);
    //     imshow("Circle" , img2);
    //     waitKey(0);
    //     return 0;
    // }
}
