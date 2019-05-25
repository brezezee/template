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
	Mat WDT(const Mat & _src, const string _wname, const int _level);//С���ֽ�
	static Mat IWDT(const Mat & _src, const string _wname, const int _level);//С���ع�
	static void wavelet_D(const string _wname, Mat &_lowFilter, Mat &_highFilter);//�ֽ��
	static void wavelet_R(const string _wname, Mat &_lowFilter, Mat &_highFilter);//�ع���
	static Mat waveletDecompose(const Mat & _src, const Mat &_lowFilter, const Mat &_highFilter);
	static Mat waveletReconstruct(const Mat & _src, const Mat &_lowFilter, const Mat &_highFilter);
};
