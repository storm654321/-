#include<iostream>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;
//golbal variable
#define WINDOW_NAME "Thresh"
int thresholdValue = 100;
int thresholdType = 3;
Mat srcImg, grayImg, dstImg, dstImg_adaptive;
//golbal function
void on_threshold(int, void*);
void type1(Mat input);
Mat gold;
char* hi;
int main(int argc,char**argv)
{
	hi = argv[1];
	srcImg = imread(argv[1]);//only thing you have to do is to change the picture name
	gold = imread("gold.jpg");
	resize(gold, gold, Size(srcImg.cols, srcImg.rows));
	//imshow("sourceImg", srcImg);
	cvtColor(srcImg, grayImg, COLOR_RGB2GRAY);
	//imshow("grayImg", grayImg);
	//namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//crate trackbar at here
	//createTrackbar("Mode", WINDOW_NAME, &thresholdType, 5, on_threshold);//select mode
	//createTrackbar("Variable Value", WINDOW_NAME, &thresholdValue, 255, on_threshold);
	on_threshold(0, 0);

	//adaptive
	adaptiveThreshold(grayImg, dstImg_adaptive, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 111, 2);
	//imshow("adaptive", dstImg_adaptive);

	//while (true)
	//{
	//	int key;
	//	key = waitKey(20);
	//	if (char(key) == 27)
	//		break;
	//}
	return 0;
}
void on_threshold(int, void*)
{

	threshold(grayImg, dstImg, thresholdValue, 255, thresholdType);
	
	//imshow(WINDOW_NAME, dstImg);
	type1(dstImg);
}
void type1(Mat input)
{
	int histgram[256];
	int cumulative_distribution_function[256];
	for (int i = 0; i < 256; i++)
	{
		histgram[i] = 0;
		cumulative_distribution_function[i] = 0;
	}
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			histgram[input.at<uchar>(i,j)]++;
	cumulative_distribution_function[0] = histgram[0];
	int midian = (input.rows*input.cols )/ 2;
	int threshold_value=0;
	
	for (int i = 1; i < 256; i++)
	{

		cumulative_distribution_function[i] += cumulative_distribution_function[i - 1];
		//cout << cumulative_distribution_function[i]<<endl;
		if (cumulative_distribution_function[i] > midian)
		{
			threshold_value = i;
			break;
		}
	}
	//cout << threshold_value;
	Mat output(Size(input.cols	,input.rows), CV_8UC3);
	for (int i = 0; i < input.rows; i++)
		for (int j = 0; j < input.cols; j++)
			if(input.at<uchar>(i, j)>20)
			{
				output.at<Vec3b>(i, j)[0] = gold.at<Vec3b>(i,j)[0];  //B
				output.at<Vec3b>(i, j)[1] = gold.at<Vec3b>(i, j)[1];
				output.at<Vec3b>(i, j)[2] = gold.at<Vec3b>(i, j)[2];
			}
			else
			{
				output.at<Vec3b>(i, j)[0] = 0;  //B
				output.at<Vec3b>(i, j)[1] = 0;
				output.at<Vec3b>(i, j)[2] = 0;
			}
	//imshow("output", output);

	string output_name="output/";

	char fuck[300];
	string temp(hi);
	temp.copy(fuck,temp.size()-10,6);

	string tee(fuck);

	output_name = output_name + fuck+".jpg";
	cout << output_name;

	cout <<endl<< output_name;
	imwrite(output_name, output);
}



