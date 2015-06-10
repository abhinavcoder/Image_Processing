#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>
//#include "opencv/cv.h"
#define threshold 200
#define edge_thresh 50
//#define INF 3278
using namespace std;
using namespace cv;

 
//

int thresh , thresh1 = 88 ; 
Mat get_grayscale(Mat image) {
	Mat gray(image.rows,image.cols,CV_8UC1,Scalar(0)); //To store and return the result
	
	for(int i=0; i < image.rows; i++) {
		for(int j=0; j < image.cols; j++) {
			//Conversion formula for gray-scale is applied as had been discusse
		    gray.at<uchar>(i,j) = 0.33*image.at<Vec3b>(i,j)[0] + 0.56*image.at<Vec3b>(i,j)[2] + 0.11*image.at<Vec3b>(i,j)[1] ;
		}
	}
	return gray; //Result returned
}
int get_intensity(Mat image , int i , int j) {
	int k = 0 ;
	int intensity = 0 , counter = 0 ;
 while(k<=8)
 { switch(k)
   {
      case 0 : break ;
      case 1 : j++ ;break;
	  case 2 : i--;break;
	  case 3 : i = i +2 ; break;
	  case 4 : j--;break;
	  case 5 : j--;break;
	  case 6 : i--;break;
	  case 7 : i--;break;
	  case 8 : j++;break;

   }

 if((i>0)&&(i<image.rows)&&(j>0)&&(j<image.cols))
 {
    counter++ ; 
	intensity = intensity + image.at<uchar>(i,j);
 }
 k++;
 }
 return intensity/counter ;
}
Mat get_advanceGrayscale(Mat image) {
	Mat gray(image.rows,image.cols,CV_8UC1,Scalar(0)); //To store and return the result
	
	for(int i=0; i < image.rows; i++) {
		for(int j=0; j < image.cols; j++) {
			//Conversion formula for gray-scale is applied as had been discusse
		    gray.at<uchar>(i,j) = get_intensity(image,i,j);
		}
	}
	return gray; //Result returned
}
Mat rotate(Mat image) {
	Mat turnpic(image.rows,image.cols,CV_8UC1,Scalar(0));
	for(int i=0; i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
		  turnpic.at<uchar>(i,j )= image.at<uchar>(i,j) ;
		}
	}
	return turnpic ;
}
Mat get_histogram(Mat image) {
	long long int freq[256] = {0};
	int intensity , maxi = 0  ;
	for(int i=0; i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			intensity = image.at<uchar>(i,j) ; 
		  freq[intensity]++ ;
			if(freq[intensity]>maxi)
				maxi = freq[intensity];
		}
    }
    Mat histo(256,maxi+1,CV_8UC1,Scalar(0));
   for(int i=0;i<maxi + 1;i++)
	{
		for(int j=0;j<256;j++)
		{  
		  histo.at<uchar>(j,i) = 255 ;
		}
   }
   
    for(int i=0; i<256;i++)
	{
	   int j = 0 ;
	   while(j<=freq[i])
		{
			histo.at<uchar>(i,j)= 0;
			j++;
	    }
	 }
	int k=0 , sum = 0  ; 
	while(k<256)
	{
	 sum = sum + freq[k];
	 if(sum>= (int)(image.rows*image.cols*0.5))
	 { thresh = k ;
	    break;
	 }
	 k++;
	}
	
	 
	return histo ;   
}
Mat get_binary(Mat image) {
	Mat pseudo = get_histogram(image);
 Mat binary(image.rows,image.cols,CV_8UC1,Scalar(0)); //To store and return the result
	
	for(int i=0; i < image.rows; i++) {
		for(int j=0; j < image.cols; j++) {
			//Conversion formula for gray-scale is applied as had been discusse
			if((0.33*image.at<Vec3b>(i,j)[0]+0.56*image.at<Vec3b>(i,j)[2]+0.11*image.at<Vec3b>(i,j)[1]) > thresh1)
		     binary.at<uchar>(i,j) = 255 ;
			else
			 binary.at<uchar>(i,j) = 0 ;
		}
	}
	return binary; //Result returned
}
int  get_dif(Mat image , int i , int j ) {
 int max = 0 , min = 256 , k = 0 ;
 while(k<8)
 { switch(k)
   {
      case 0 : j++ ;break;
	  case 1 : i--;break;
	  case 2 : i = i +2 ; break;
	  case 3 : j--;break;
	  case 4 : j--;break;
	  case 5 : i--;break;
	  case 6 : i--;break;
	  case 7 : j++;break;

   }

 if((i>0)&&(i<image.rows)&&(j>0)&&(j<image.cols))
 {
    if(image.at<uchar>(i,j)>max)
		max  = image.at<uchar>(i,j) ;
	if(image.at<uchar>(i,j)<min)
		 min = image.at<uchar>(i,j) ;
 }
 k++;
 }
 return max-min ;
}

Mat noise_erosion(Mat image) {
  Mat noise(image.rows,image.cols,CV_8UC1,Scalar(0));
  for(int i = 0 ; i < image.rows ;i++)
	  for(int j = 0 ; j < image.cols ;j++)
		  noise.at<uchar>(i,j) = 255 ;

  for(int i = 1 ; i < image.rows -1 ;i++)
  {
    for(int j = 1 ; j < image.cols - 1 ; j++)
	{
	  int m = i-1 ;
	  int flag = 0 ;
	  while(m<=i+1)
	  {
	    int n = j-1 ;
		while(n<=j+1)
		{
		    if(image.at<uchar>(i,j)==0)
				flag=1 ;
			n++;
		}
		m++;
	  }
	  if(flag==1)
		  noise.at<uchar>(i,j) =  0 ;
	}
  }
return noise ;
}

Mat get_edge(Mat image) {
 Mat edge(image.rows,image.cols,CV_8UC1,Scalar(0)) ;
 for(int i=0; i < image.rows; i++) {
	for(int j=0; j < image.cols; j++) {
		  edge.at<uchar>(i,j)  = 255 ;
           int diff = get_dif(image,i,j) ;
		   if(diff > edge_thresh)   //255 for binary image
			    edge.at<uchar>(i,j) = 0 ;
	}

 }
 return edge ;
}

Mat RedDetectBGR(Mat img, int min_thresh, int max_thresh){
 
    Mat result(img.rows,img.cols,CV_8UC1);          //the result image matrix is initialized
    int i,j,r = img.rows, c = img.cols;
 
    for(i=0;i<r;i++){                               //loop through all rows
        for(j=0;j<c;j++){                           //loop through all columns
 
            Vec3b colours = img.at<Vec3b>(i,j);     //extract 3 channel pixel information in a vector
            if(colours[2]>=min_thresh && colours[1]<max_thresh && colours[0]<max_thresh)
                                                    //enforce condition on uchar value of each channel 
                result.at<uchar>(i,j) = 255;        //particular pixel is made white
            else
                result.at<uchar>(i,j) = 0;          //particular pixel is made black
        }
    }
 
    return result;
}

Mat HSV_detector(Mat img , int tolh , int tols , int tolv) {
	Mat i1(1,1,CV_8UC3) ;
	i1.at<Vec3b>(0,0)[0] = 0 ; 
	i1.at<Vec3b>(0,0)[1] = 0 ;
	i1.at<Vec3b>(0,0)[2] = 255 ;

	Mat i2(1,1,CV_8UC3);
	cvtColor(i1,i2,CV_RGB2HSV);
	int hue = i2.at<Vec3b>(0,0)[0] ;
	int sat = i2.at<Vec3b>(0,0)[1] ;
	int val = i2.at<Vec3b>(0,0)[2] ;

	Mat HSV(img.rows,img.cols,CV_8UC3);
	Mat result(img.rows,img.cols,CV_8UC1);
	cvtColor(img,HSV,CV_RGB2HSV);
	//return HSV ;
	for(int i = 0 ; i <img.rows ; i++)
	{
	 for(int j = 0 ; j<img.cols ;j++)
	 {
	  if((HSV.at<Vec3b>(i,j)[0]< hue+tolh)&&(HSV.at<Vec3b>(i,j)[0]> hue-tolh)&&(HSV.at<Vec3b>(i,j)[1]< sat+tols)&&(HSV.at<Vec3b>(i,j)[1] > sat-tols)&&(HSV.at<Vec3b>(i,j)[2]< val+tolv)&&(HSV.at<Vec3b>(i,j)[2]> val-tolv))
	    result.at<uchar>(i,j) = 255;
	  else
		result.at<uchar>(i,j) = 0;
	 }
	}
return result ;
}

int mini(int a, int b ,int c) {
 if((a<=b)&&(a<=c))
	 return a ;
 if((b<=a)&&(b<=c))
	 return b ; 
 if((c<=a)&&(c<=b))
	 return c ;
 return a;
}

int mini4(int a ,int b, int c , int d) {
return (d<mini(a,b,c))?(d):(mini(a,b,c));
}

void Shape(Mat img) {
    vector<vector<Point> > contours;
    findContours(img,contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE) ;
	int num_contour  = contours.size() ;
	cout<<"num_contours "<<num_contour<<endl;
	vector<Point> approxCurve ; 
	for(int i = 0 ; i < num_contour ; i++)
	{
		approxPolyDP(contours[i],approxCurve, 0.02*arcLength(contours[i],true), true);
		cout<<approxCurve.size()<<endl ;
	}
	
}

Mat Blob_detection(Mat img) {
	int INF= 32767;
 Mat blob(img.rows,img.cols,CV_8UC1,Scalar(0));
 int rows = img.rows ;
 int cols = img.cols ;
 int counter = 1 ; 
 vector<vector<int> > pixel_ID(rows,vector<int>(cols,INF));
  for(int i = 0 ; i < img.rows ; i++)
  {
    for(int j =0 ; j < img.cols ; j++)
	{
	  if(img.at<uchar>(i,j) == 255)
	  { 
        if((i-1>=0)&&(j-1>=0))
		{ 
		 if((pixel_ID[i-1][j]==INF)&&(pixel_ID[i][j-1]==INF)&&(pixel_ID[i-1][j-1]==INF))
		 { pixel_ID[i][j]= counter ; counter++ ; }
		 else
		 {pixel_ID[i][j] = mini(pixel_ID[i-1][j],pixel_ID[i][j-1],pixel_ID[i-1][j-1]); }
		}
		else
		{ 
	     if((i-1<0)&&(j-1<0))
		 { pixel_ID[i][j] = counter ; counter++ ;}
		 else
		  { if(i-1<0)
			  { pixel_ID[i][j] = pixel_ID[i][j-1] ;}
			 if(j-1<0)
			  { pixel_ID[i][j] = pixel_ID[i-1][j] ;}
	      }
	     }
	   }
      }
	
   }

  //mat 2 
  int a[1000] = {0};
  int idt ;
  int c1 = 1 ;
  int x = 2 ;
 
  for(int i = 1 ; i <img.rows-1 ;i++)
  {
  for(int j = 1 ; j < img.cols-1 ; j++) 
  {    
	  
	  if((!((pixel_ID[i+1][j]==INF)&&(pixel_ID[i-1][j]==INF)&&(pixel_ID[i][j-1]==INF)&&(pixel_ID[i][j+1]==INF)))&&(img.at<uchar>(i,j) == 255))
	   {
	   // if(img.at<uchar>(i,j+1) == 255)
		   idt = mini4(pixel_ID[i-1][j],pixel_ID[i+1][j],pixel_ID[i][j-1],pixel_ID[i][j+1]); //change here
	        if(a[idt]==0)
			{a[idt] = c1 ; c1++;}
			else
			{	a[pixel_ID[i][j]] = a[idt] ; }
	  
	  }

  }
  }

  for(int i = 0 ; i < img.rows ;i++)
  {
   for(int j = 0 ; j< img.cols ; j++)
   {
     if(img.at<uchar>(i,j) == 255)
	 {
		 pixel_ID[i][j] = a[pixel_ID[i][j]] ;
	 }
   }
  }

  int inf1 = 0 ;
  int k=0;
  int b[1000] = {0} ;
  int flagger  ;
  for(int i = 0 ; i <img.rows ;i++)
  {
  for(int j = 0 ; j < img.cols ; j++)
  {  flagger = 0 ; 
	  if(pixel_ID[i][j]==INF)
	  {  cout<<0;
	  }
	  else	  
	  { cout<<pixel_ID[i][j]; 
	    for(int z = 0 ; z<k;z++)
		{
		
		  if(b[z]==pixel_ID[i][j])
		   {  flagger = 1 ;break;}
		         
		}
		if(flagger==0)
		{b[k] = pixel_ID[i][j] ;k++;}
	  }
	  
  }
  cout<<endl;
  }
 
  int id , flag = 0 ;
  char win1[] = "blob Image";
  k++;
  while(k--)
  { 
	 // cout<<"K :: "<<k ;
    for(int i = 0 ; i < img.rows ; i++)
     {
      for(int j = 0 ; j < img.cols ; j++)
       { 
	      blob.at<uchar>(i,j) = 255 ;
		  if(pixel_ID[i][j] == b[k])
			   blob.at<uchar>(i,j) = 0 ;
	   }
	 }
	imshow(win1,blob);
	//Shape(blob);
	waitKey(1000);
  }
 return blob ; 
}
/*
Mat Blob_BFS(Mat img) {
	queue<>
  Mat blob(img.rows,img.cols,CV_8UC1,Scalar(0));
  for(int i = 0 ;i<img.rows;i++) {
  	for(int j =0 ;j<img.cols;j++) {
  	  if(img.at<uchar>(i,j) == 255)	
  	}
  }

}
*/

