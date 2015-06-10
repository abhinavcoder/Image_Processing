#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>
#include "headers.h"
// #include "opencv/cv.h"
#define threshold 200
#define edge_thresh 50
//#define INF 3278
using namespace std;
using namespace cv;

int main()
{
	Mat image;
	string fname;
	//cin >> fname;
	image = imread("ms.png",CV_LOAD_IMAGE_COLOR);
	char win[] = "Striped Image"; //String with the name of the window
	int location;
	/*
	   if(!image.data){
		cout << "jvd";
		waitKey(0);
		return -1;
	*/
	
	namedWindow(win,CV_WINDOW_AUTOSIZE);
 
  //  imshow(win,image);
	waitKey(1000);
	
	//imshow(win,get_grayscale(image));
	Mat secondary = get_binary(image);
//	imshow(win,secondary);
	//Shape(secondary);
	waitKey(1000);
//	imshow(win,Blob_detection(secondary));
	waitKey(0);
 
 
	/*
	//imshow(win,get_histogram(secondary));
	imshow(win,image);
	waitKey(1000);
	imshow(win,get_binary(image));
	waitKey(1000);
	imshow(win,noise_erosion(get_binary(image)));
	//imshow(win,get_advanceGrayscale(get_grayscale(image)));
	waitKey(1000);
	imshow(win,get_edge(secondary));
	waitKey(0);
	 */
	/*
    createTrackbar("trackbar",win,&thresh1,255);
	VideoCapture vid(0);
    while(1)
	{
	 Mat temp ;
	 vid.read(temp);
	 imshow(win,(get_grayscale(temp)));
	 if(waitKey(30)==27)
			  break;
	}
	*/
	/*
	createTrackbar("trackbar",win,&thresh1,255);
	 while(1)
	 {
		  imshow(win,get_binary(image));

		  if(waitKey(30)==27)
		   break ;
	 }
	*/ 
	/*int minthresh = 144 , maxthresh = 133 ;
	imshow(win,(image));
	waitKey(1000);
	Mat result = RedDetectBGR(image,minthresh,maxthresh);
	imshow(win,result);
	waitKey(1000);
    imshow(win,get_edge(result));
	waitKey(0);
	*/
	/*
	int tolh = 0 , tols = 0 , tolv = 0 ;
	createTrackbar("tolH",win,&tolh,255);
    createTrackbar("tolS",win,&tols,255);
	createTrackbar("tolV",win,&tolv,255);
	while(1){
        Mat result = HSV_detector(image ,tolh ,tols , tolv);
        imshow(win,result);
        char ch = waitKey(33);
        if(ch==27)
            break;
    }
	*/ 
//	createTrackbar("Low Threshold",win,&minthresh,255);
  //  createTrackbar("High Threshold",win,&maxthresh,255);
   /*
    while(1){
        Mat result = RedDetectBGR(image,minthresh,maxthresh);
        imshow(win,result);
        char ch = waitKey(33);
        if(ch==27)
            break;
    }*/
	return 0;
}
