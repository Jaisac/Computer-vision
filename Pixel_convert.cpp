/*
 * 
 *
 *  Created on: 23/07/2016
 *      Author: Jaime Sacramento
 *	Description: Convert the color of the pixels of an image according to a 
 *	imposed threshold with a cascade effect.
 *	
 */


#include <opencv.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <core.hpp>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <imgcodecs.hpp>
#include <fstream>
using namespace cv;
using namespace std;


int main()
{
	int pixel;
	Mat img ;
	Mat img2;
	threshold = 110;
	
	img2 = imread("C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\opencv\\megumin_face.jpg", CV_LOAD_IMAGE_COLOR);
	 namedWindow("Miventana", CV_WINDOW_NORMAL);
	 resizeWindow("Miventana",420,520);
//########## Color to gray routine
	cv::cvtColor(img2, img,COLOR_BGR2GRAY);
//########## Saves the image in hardrive
	//Note: The image's path must be expressed here i.e C//myimages//images
	cv::imwrite("path",img);

//########## Mapping to identify the coordinate and the pixel value of every pixel
	std::ofstream imagen;
	imagen.open("megumin.txt");
	
	 for(int i=0;i < img.cols;i++){
		 for (int j=0;j < img.rows;j++){

			 if (img.at<uchar>(j, i) > threshold){
				 img.at<uchar>(j, i) = 0;
				 pixel = (int)img.at<uchar>(j, i);
			 }

			 imagen << pixel<<" |"<<"("<<j<<","<<i<<")" <<  "| ";

		 }
		 imagen<<"\n";
		 imshow("Miventana",img);
		 waitKey(10);

	 }
	 imagen.close();

	 imshow("Miventana",img);

	waitKey(0);
	return 0;
}
