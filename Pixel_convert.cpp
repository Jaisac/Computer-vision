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
	img2 = imread("C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\opencv\\megumin_face.jpg", CV_LOAD_IMAGE_COLOR);
	 namedWindow("Miventana", CV_WINDOW_NORMAL);
	 resizeWindow("Miventana",420,520);
	//Conversión de color
	cv::cvtColor(img2, img,COLOR_BGR2GRAY);
	//Guarda la imagen en una carpeta
	cv::imwrite("C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\opencv\\Megumin_face2.png",img);
//	img = imread("C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\opencv\\Megumin_face2.png");

	//Mapeo de la imagen para identificar coordenada y valor en escala de grizes del pixel
	std::ofstream imagen;
	imagen.open("megumin.txt");
	 for(int i=0;i < img.cols;i++){
		 for (int j=0;j < img.rows;j++){

			 if (img.at<uchar>(j, i) > 110){
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
