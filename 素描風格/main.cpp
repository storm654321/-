#include<iostream>
#include<opencv2\opencv.hpp>
using namespace std;
using namespace cv;
//golbal variable
int thresholdValue = 100;
int thresholdType = 3;
Mat srcImg,grayImg;
int main(int argc, char**argv)
{
	argv[1] = "input/10665252_912467052101402_9073466386744481729_n.jpg";
	srcImg = imread(argv[1]);//only thing you have to do is to change the picture name
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
	imshow("asdf", grayImg);
	Mat pencial_black = imread("black.jpg",1);
	Mat pencial_gray = imread("gray.jpg", 1);
	Mat pencial_light_gray = imread("light_gray.jpg", 1);
	int value;
	for (int i = 0; i < srcImg.rows; i++)
	{
		for (int j = 0; j < srcImg.cols; j++)
		{
			if (grayImg.at<uchar>(i, j) < 80)
			{
				value = pencial_black.at<uchar>(i, j);
				if(value>255)
					grayImg.at<uchar>(i, j) = 255;
				else
					grayImg.at<uchar>(i, j) = value;
			}
			else if (grayImg.at<uchar>(i, j) < 170)
			{
				value = pencial_gray.at<uchar>(i, j);
				if (value>255)
					grayImg.at<uchar>(i, j) = 255;
				else
					grayImg.at<uchar>(i, j) = value;
			}
			else if (grayImg.at<uchar>(i, j) < 240)
			{
				value = pencial_light_gray.at<uchar>(i, j);
				if (value>255)
					grayImg.at<uchar>(i, j) = 255;
				else
					grayImg.at<uchar>(i, j) = value;
			}
			else
			{
				grayImg.at<uchar>(i, j) = 255;
			}
		}
	}


	imshow("­ì¹Ï",srcImg);
	imshow("¯À´y",grayImg);
	waitKey(0);
	return 0;
}


