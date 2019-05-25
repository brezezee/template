#pragma once
#include "opencv2/opencv.hpp"
#include <imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;
class WaveTransform
{
public:
	WaveTransform(void);
	~WaveTransform(void);
	Mat WDT(const Mat & _src, const string _wname, const int _level);//小波分解
	static Mat IWDT(const Mat & _src, const string _wname, const int _level);//小波重构
	static void wavelet_D(const string _wname, Mat &_lowFilter, Mat &_highFilter);//分解包
	static void wavelet_R(const string _wname, Mat &_lowFilter, Mat &_highFilter);//重构包
	static Mat waveletDecompose(const Mat & _src, const Mat &_lowFilter, const Mat &_highFilter);
	static Mat waveletReconstruct(const Mat & _src, const Mat &_lowFilter, const Mat &_highFilter);
};
