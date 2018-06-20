/*
 * 
 *
 *  Created on: 23/05/2017
 *      Author: Jaime Sacramento
 *	Description: Execute a folder of images to enhance them into a particular 
 *	resolution using the nearest neighbor, bilinear and bicubic interpolation
 *	and measure its new image quality using the quantitative metrics PSNR and 
 * 	SSIM.
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
#include <sstream>
#include <time.h>
#include <conio.h>

using namespace cv;
using namespace std;
double getPSNR ( const Mat& I1, const Mat& I2);
Scalar getMSSIM(const Mat& I1, const Mat& I2);

float residuo=0;
int dividir,ctr, xy[1];
double psnr;

Scalar mssim;
Mat imgin, img1, img2;
string index,convert,imagen="_standard",tipo[3]={"_NN_","_BL_","_BC_"};




int main(){
	ofstream registro("recopilacion.txt");
	ofstream registroA("psnr.txt");
	ofstream registroB("ssim.txt");
	ofstream registroC("tiempo.txt");



//########  Uploading images module
cv::String path("C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\standard_test_images/*.bmp");
vector<cv::String> fn;
vector <cv::Mat> datos;
cv::glob(path,fn,true);

//##########   Ciclo principal hasta que lea toda la carpeta
for(size_t k=0;k < fn.size();++k){


	imgin= cv::imread(fn[k],IMREAD_UNCHANGED);

	if(! imgin.data){
		cout << "Error, no se cargó la imagen.";
		return -1;
	}
//###########    Color to gray
	if(imgin.channels()> 0){
		cv::cvtColor(imgin,imgin,COLOR_BGR2GRAY);
	}


//############## Resolution control 
	xy[0]= imgin.rows * 2;
	xy[1]= imgin.cols * 2;

	Size size(xy[0],xy[1]);

//#############Proceso de interpolacion
	cv::resize(imgin,img1,size, 0.75, 0.75,INTER_AREA);
	stringstream num;
		num <<k;
		num >> convert;
	index= "C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\standard_test_images\\Proc\\"+convert+ "_ref_"+imagen+".bmp";
	if(residuo==0){
	imwrite(index, img1);
	}
	registro<<k<<imagen<<";";

//###############Ciclo secundario para usar los 3 algoritmos######
	for(int i=0;i < 3;i++){

//#############Proceso de adquisición de datos
		clock_t  meta, salida;
		salida = clock();
		cv::resize(imgin,img2,size, 0.75, 0.75,i);
		meta = clock() - salida;
		psnr=getPSNR(img1,img2);
		mssim=getMSSIM(img1,img2);

//############## Modulo de escritura txt1       
		registro<<" PSNR :"<<psnr<<" ; SSIM :"<< mssim.val[0] << " ; Tiempo : ";
		registro<< (float)meta/CLOCKS_PER_SEC << " ; algoritmo ; "<< tipo[i]<<" ||" ;


//############# Módulo de escritura txt2    
		registroA <<psnr<<",";

//############ Módulo de escritura txt3         
		registroB<<mssim.val[0]<<",";
//############ Módulo de escritura txt4        

		registroC<<(float)meta/CLOCKS_PER_SEC<<",";

//########### Módulo de escritura imágenes      
		if(residuo==0){
			index="C:\\Users\\jamessacramento\\Pictures\\lab_imagenes\\standard_test_images\\Proc\\"+convert+tipo[i]+imagen+".bmp";
			imwrite(index, img2);
		}
	}   
/*
		ctr=ctr + 1;
		residuo=ctr;
		dividir= residuo/10;
		residuo=residuo/10;
		residuo=residuo-dividir;
*/


//########### Salto de línea en los .txt
	registro<<"\n";
	registroA<<"\n";
	registroB<<"\n";
	registroC<<"\n";
	datos.push_back(imgin);

}//##################Fin del ciclo principal
registro.close();
registroA.close();
registroB.close();
registroC.close();
}
//##################Función para calcular el psnr
double getPSNR(const Mat& I1, const Mat& I2){
Mat s1;
absdiff(I1, I2, s1);

s1.convertTo(s1, CV_32F);
s1 = s1.mul(s1);

Scalar s = sum(s1);

double sse = s.val[0] + s.val[1] + s.val[2];

if (sse <= 1e-10)
		return 0;
	else
	{
		 double  mse =sse /(double)(I1.channels() * I1.total());
	     double psnr = 10.0*log10((255*255)/mse);
	     return psnr;

	}

}
//##################Función para calcular SSIM
Scalar getMSSIM(const Mat& i1, const Mat& i2){

const double C1 = 6.5025, C2 = 58.5225;

int d     = CV_32F;

Mat I1, I2;
i1.convertTo(I1, d);
i2.convertTo(I2, d);

Mat I2_2   = I2.mul(I2);
Mat I1_2   = I1.mul(I1);
Mat I1_I2  = I1.mul(I2);

Mat mu1, mu2;
GaussianBlur(I1, mu1, Size(11, 11), 1.5);
GaussianBlur(I2, mu2, Size(11, 11), 1.5);

Mat mu1_2   =   mu1.mul(mu1);
Mat mu2_2   =   mu2.mul(mu2);
Mat mu1_mu2 =   mu1.mul(mu2);

Mat sigma1_2, sigma2_2, sigma12;

GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
sigma1_2 -= mu1_2;

GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
sigma2_2 -= mu2_2;

GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
sigma12 -= mu1_mu2;

Mat t1, t2, t3;

t1 = 2 * mu1_mu2 + C1;
t2 = 2 * sigma12 + C2;
t3 = t1.mul(t2);

t1 = mu1_2 + mu2_2 + C1;
t2 = sigma1_2 + sigma2_2 + C2;
t1 = t1.mul(t2);

Mat ssim_map;
divide(t3, t1, ssim_map);
Scalar mssim = mean( ssim_map );

return mssim;
}
