#include <vector>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void plain_ole_video()
{
    char key;
    Mat img;
    VideoCapture cap(0);
    while (true) {
        cap >> img;
        imshow("window label", img);
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27) {
            break;      //If you hit ESC key loop will break.
        }
    }
}

void colorize()
{
    char key;
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;
    Mat edges;
    namedWindow("edges",1);
    for(;;) {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27) {
            break;      //If you hit ESC key loop will break.
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
}


void wire_frame()
{
    char key;
    Mat img;
    VideoCapture cap(0);
    while (true) {
        cap >> img;
        Mat edges;
        cvtColor(img, edges, CV_BGR2GRAY);
        Canny(edges, edges, 30, 60);
        imshow("window label", edges);
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27) {
            break;      //If you hit ESC key loop will break.
        }
    }
}


// Slider for the low threshold value of our edge detection
int maxLowThreshold = 1024;
int lowSliderPosition = 150;
// Slider for the high threshold value of our edge detection
int maxHighThreshold = 1024;
int highSliderPosition = 250;

IplImage* tempFrame;

// Function to find the edges of a given IplImage object
IplImage* findEdges(IplImage* sourceFrame, double thelowThreshold, double theHighThreshold, double theAperture)
{
    // Convert source frame to greyscale version (tempFrame has already been initialised to use greyscale colour settings)
    cvCvtColor(sourceFrame, tempFrame, CV_RGB2GRAY);
    // Perform canny edge finding on tempframe, and push the result back into itself!
    cvCanny(tempFrame, tempFrame, thelowThreshold, theHighThreshold, theAperture);
    // Pass back our now processed frame!
    return tempFrame;
}

void properties()
{
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system
    double prop;

    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_POS_MSEC); //Current position of the video file in milliseconds or video capture timestamp.
    cout << "position/timestamp (msec)          : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_POS_FRAMES); //0-based index of the frame to be decoded/captured next.
    cout << "frame capture index                : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_POS_AVI_RATIO); //Relative position of the video file: 0 - start of the film, 1 - end of the film.
    cout << "relative position                  : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH); //Width of the frames in the video stream.
    cout << "frame width                        : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT); //Height of the frames in the video stream.
    cout << "frame height                       : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS); //Frame rate.
    cout << "frame rate                         : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_FOURCC); //4-character code of codec.
    cout << "codec                              : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT); //Number of frames in the video file.
    cout << "num frames                         : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_FORMAT); //Format of the Mat objects returned by retrieve() .
    cout << "mat format                         : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_MODE); //Backend-specific value indicating the current capture mode.
    cout << "backend capture mode               : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_BRIGHTNESS); //Brightness of the image (only for cameras).
    cout << "camera brightness                  : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_CONTRAST); //Contrast of the image (only for cameras).
    cout << "camera contrast                    : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_SATURATION); //Saturation of the image (only for cameras).
    cout << "camera saturation                  : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_HUE); //Hue of the image (only for cameras).
    cout << "camera hue                         : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_GAIN); //Gain of the image (only for cameras).
    cout << "camera image gain                  : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_EXPOSURE); //Exposure (only for cameras).
    cout << "camera exposure                    : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_CONVERT_RGB); //Boolean flags indicating whether images should be converted to RGB.
    cout << "RGB convert?                       : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_WHITE_BALANCE_U); //The U value of the whitebalance setting (note: only supported by DC1394 v 2.x backend currently)
    cout << "u balance of whitebalance setting  : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_WHITE_BALANCE_V); //The V value of the whitebalance setting (note: only supported by DC1394 v 2.x backend currently)
    cout << "v balance of whitebalance setting  : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_RECTIFICATION); //Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)
    cout << "stereo camera rectification flag   : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_ISO_SPEED); //The ISO speed of the camera (note: only supported by DC1394 v 2.x backend currently)
    cout << "ISO camera speed                   : " << prop << endl;
    prop = cvGetCaptureProperty(capture, CV_CAP_PROP_BUFFERSIZE); //Amount of frames stored in internal buffer memory (note: only supported by DC1394 v 2.x backend currently)
    cout << "internally buffered frames         : " << prop << endl;


}

void camera()
{
    char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system
    IplImage* pProcessedFrame;
    IplImage* pRawFrame; //Create image frames from capture
    IplImage* imgThreshed;

    pRawFrame = cvQueryFrame(capture); //Create image frames from capture
	tempFrame = cvCreateImage(cvSize(pRawFrame->width, pRawFrame->height), IPL_DEPTH_8U, 1);    

    IplImage* imgHSV = cvCreateImage(cvGetSize(pRawFrame), IPL_DEPTH_8U, 3); 
    cvCvtColor(pRawFrame, imgHSV, CV_BGR2HSV);

    while (1) { //Create infinte loop for live streaming
        pRawFrame = cvQueryFrame(capture); //Create image frames from capture
        Mat img(pRawFrame); // cv::Mat replaces the CvMat and IplImage, but it's easy to convert
        Mat img_yuv;
        cvtColor(img, img_yuv, CV_BGR2YCrCb); // convert image to YUV color space. The output image will be created automatically

        imgThreshed = cvCreateImage(cvGetSize(pRawFrame), IPL_DEPTH_8U, 1);  //- See more at: http://aishack.in/tutorials/tracking-colored-objects-opencv/#sthash.iurwzPDm.dpuf

        cvInRangeS(imgHSV, cvScalar(20, 100, 100), cvScalar(30, 255, 255), imgThreshed);

        cvShowImage("Camera_Output", pRawFrame);   //Show image frames on created window
    	//pProcessedFrame = cvCreateImage(cvSize(pRawFrame->width, pRawFrame->height), IPL_DEPTH_8U, 1);
        pProcessedFrame = findEdges(pRawFrame, lowSliderPosition, highSliderPosition, 3);
 		// Showed the processed output in our other window
        cvShowImage("Processed WebCam", pProcessedFrame);
        cvShowImage("Thresholded", imgThreshed);
         
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27) {
            break;      //If you hit ESC key loop will break.
        }
    }
    cvReleaseCapture(&capture); //Release capture.
    cvDestroyWindow("Camera_Output"); //Destroy Window
}

void color_filter()
{
    char key;
    cvNamedWindow("Camera_Output", 1);    //Create window
    IplImage* pRawFrame; //Create image frames from capture
    IplImage* upper_red_hue_range;
    IplImage* lower_red_hue_range;
    IplImage* imgHSV; 
    CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY);  //Capture using any camera connected to your system
    unsigned long long frame_no = 0;

    //pRawFrame = cvQueryFrame(capture); //Create image frames from capture

    while (1) { //Create infinte loop for live streaming
        pRawFrame = cvQueryFrame(capture); //Create image frames from capture
        Mat raw_img_mat(pRawFrame);
        imgHSV = cvCreateImage(cvGetSize(pRawFrame), IPL_DEPTH_8U, 3); 
        cvCvtColor(pRawFrame, imgHSV, CV_BGR2HSV);

        upper_red_hue_range = cvCreateImage(cvGetSize(pRawFrame), IPL_DEPTH_8U, 1);  //- See more at: http://aishack.in/tutorials/tracking-colored-objects-opencv/#sthash.iurwzPDm.dpuf
        lower_red_hue_range = cvCreateImage(cvGetSize(pRawFrame), IPL_DEPTH_8U, 1);  //- See more at: http://aishack.in/tutorials/tracking-colored-objects-opencv/#sthash.iurwzPDm.dpuf

        // Scalar values are: BGR color such as: Blue = a, Green = b and Red = c
        // Scalar(0, 0, 0)       => black, 
        // Scalar(255, 255, 255) => white
        // Scalar(0, 0, 255)     => red
        // Scalar(0, 255, 0)     => green
        // Scalar(0, 255, 255)   => yellow
        // Scalar( 255, 0, 0)    => blue
        cvInRangeS(imgHSV, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lower_red_hue_range);
        cvInRangeS(imgHSV, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), upper_red_hue_range);

        Mat red_hue_image;
        Mat red_hue_up(upper_red_hue_range);
        Mat red_hue_lo(lower_red_hue_range);
        addWeighted(red_hue_lo, 1.0, red_hue_up, 1.0, 0.0, red_hue_image);
        GaussianBlur(red_hue_image, red_hue_image, cv::Size(9, 9), 2, 2);

        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(red_hue_image, circles, CV_HOUGH_GRADIENT, 1, red_hue_image.rows/8, 100, 20, 0, 0);

        // Loop over all detected circles and outline them on the original image
        if(circles.size() != 0) {
            for(size_t current_circle = 0; current_circle < circles.size(); ++current_circle) {
                cv::Point center(std::round(circles[current_circle][0]), std::round(circles[current_circle][1]));
                int radius = std::round(circles[current_circle][2]);
                cv::circle(raw_img_mat, center, radius, cv::Scalar(0, 255, 0), 5);
            }
        
            if (!circles.empty()) {
                int roi_x = circles[0][0];
                int roi_y = circles[0][1];
                if ((frame_no % 30) == 0) {
                    cout << "frame: " << frame_no << ", x: " << roi_x << ", y: " << roi_y << endl;
                }
    		}
        }
        ++frame_no;

        cvShowImage("Camera_Output", pRawFrame);   //Show image frames on created window
 		// Showed the processed output in our other window
        cvShowImage("Lower", lower_red_hue_range);
        cvShowImage("Upper", upper_red_hue_range);
         
        cvReleaseImage(&imgHSV);
        cvReleaseImage(&upper_red_hue_range);
        cvReleaseImage(&lower_red_hue_range);

        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27) {
            break;      //If you hit ESC key loop will break.
        }
    }
    cvReleaseCapture(&capture); //Release capture.
    cvDestroyWindow("Camera_Output"); //Destroy Window
}

int jpg_image(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << " Usage: display_image ImageToLoadAndDisplay" << std::endl;
        return -1;
    }
    cv::Mat image;
    image = cv::imread(argv[1], cv::IMREAD_COLOR); // Read the file
    if (!image.data) { // Check for invalid input
        cout << "Could not open or find the image" << std::endl;
        return -1;
    }
    cv::namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
    cv::imshow("Display window", image); // Show our image inside it.
    cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}

int main(int argc, char** argv)
{
    properties();
    //jpg_image(argc, argv);
    //camera();
    //wire_frame();
    //colorize();
    color_filter();
    return 0;
}
