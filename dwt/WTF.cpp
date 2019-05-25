// WTF.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "WaveTransform.h"
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;
int main()
{	
	//const char* filename = "C:\\Users\\18882\\Desktop\\毕设\\论文\\引用图片\\rail_65.jpg";
	const char* filename = "C:\\Users\\18882\\Desktop\\毕设\\论文\\引用图片\\rail_5.jpg";
	//const char* filename = "G:\\picture\\opencv\\11.jpg";
	Mat src = imread(filename);
	
	int level = 2;//分解阶次
	double dishu = 2;
	int result = (int)pow(dishu, level);

	WaveTransform m_waveTransform;

	//double a=clock();

	//resize(src,src,Size((512/result)*result,(512/result)*result));

	Mat img;
	cvtColor(src, img, CV_RGB2GRAY);
	normalize(img, img, 0, 255, CV_MINMAX);
	imshow("img", img);
	Mat float_src;
	img.convertTo(float_src, CV_32F);

	Mat imgWave = m_waveTransform.WDT(float_src, "sym2", level);	//haar,sym2
	imgWave.convertTo(float_src, CV_32F);
	Mat imgIWave = m_waveTransform.IWDT(float_src, "sym2", level);
	imshow("imgWave", Mat_<uchar>(imgWave));
	normalize(imgIWave, imgIWave, 0, 255, CV_MINMAX);
	imshow("IWDT", Mat_<uchar>(imgIWave));

	waitKey(0);
	return 0;
}
