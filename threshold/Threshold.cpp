// Threshold.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <highgui.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace cv;
using namespace std;

Mat RegionGrow(Mat src, Point2i pt, int th);

int main()
{
	Mat It, ato, gray;
	Mat grow;
	Mat src = imread("C:\\Users\\18882\\Desktop\\毕设\\论文\\引用图片\\rail_5.jpg");
	cvtColor(src, gray, CV_RGB2GRAY);
	threshold(gray, It, 50, 255, CV_THRESH_BINARY);
	//cvAdaptiveThreshold(Igray, Iat, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 7, 5);
	//cvAdaptiveThreshold(Igray, Ibt, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 7, 5);
	adaptiveThreshold(gray, ato, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 7, 5);

	imshow("g", It);
	imshow("h", ato);
	Point2i start = { 50,50 };
	grow = RegionGrow(gray, start, 90);
	imshow("grow", grow);
	imwrite("C:\\Users\\18882\\Desktop\\毕设\\论文\\引用图片\\vali\\grow.png", grow);
	imwrite("C:\\Users\\18882\\Desktop\\毕设\\论文\\引用图片\\vali\\yuzhi.png",It);
	imwrite("C:\\Users\\18882\\Desktop\\毕设\\论文\\引用图片\\vali\\adapt.png", ato);
	cvWaitKey(0);

	return 0;
}



Mat RegionGrow(Mat src, Point2i pt, int th)
{
	Point2i ptGrowing;						//待生长点位置
	int nGrowLable = 0;								//标记是否生长过
	int nSrcValue = 0;								//生长起点灰度值
	int nCurValue = 0;								//当前生长点灰度值
	Mat matDst = Mat::zeros(src.size(), CV_8UC1);	//创建一个空白区域，填充为黑色
	//生长方向顺序数据
	int DIR[8][2] = { {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0} };
	vector<Point2i> vcGrowPt;						//生长点栈
	vcGrowPt.push_back(pt);							//将生长点压入栈中
	matDst.at<uchar>(pt.y, pt.x) = 255;				//标记生长点
	nSrcValue = src.at<uchar>(pt.y, pt.x);			//记录生长点的灰度值

	while (!vcGrowPt.empty())						//生长栈不为空则生长
	{
		pt = vcGrowPt.back();						//取出一个生长点
		vcGrowPt.pop_back();

		//分别对八个方向上的点进行生长
		for (int i = 0; i < 9; ++i)
		{
			ptGrowing.x = pt.x + DIR[i][0];
			ptGrowing.y = pt.y + DIR[i][1];
			//检查是否是边缘点
			if (ptGrowing.x < 0 || ptGrowing.y < 0 || ptGrowing.x >(src.cols - 1) || (ptGrowing.y > src.rows - 1))
				continue;

			nGrowLable = matDst.at<uchar>(ptGrowing.y, ptGrowing.x);		//当前待生长点的灰度值

			if (nGrowLable == 0)					//如果标记点还没有被生长
			{
				nCurValue = src.at<uchar>(ptGrowing.y, ptGrowing.x);
				if (abs(nSrcValue - nCurValue) < th)					//在阈值范围内则生长
				{
					matDst.at<uchar>(ptGrowing.y, ptGrowing.x) = 255;		//标记为白色
					vcGrowPt.push_back(ptGrowing);					//将下一个生长点压入栈中
				}
			}
		}
	}
	return matDst.clone();
}
