#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/photo.hpp"
using namespace cv;


#include "imageprocessing.h"

Command::~Command() = default;

void BlackWhite::execute(Mat & img) 
{
	cvtColor(img, img, COLOR_BGR2GRAY);
}

BlackWhite::~BlackWhite() = default;

void GausianBlur::execute(Mat & img) 
{
	GaussianBlur(img, img, Size(5, 5), 0);
}

GausianBlur::~GausianBlur() = default;

void BoxFilterBlur::execute(Mat & img) 
{
	blur(img, img, Size(5, 5));
	std::cout << "\nboxfilterblur ran";
}

BoxFilterBlur::~BoxFilterBlur() = default;

Scale::Scale(double x) 
{
	parameter = x;
}

Scale::Scale() 
{
	parameter = 1;
}

void Scale::execute(Mat & img) 
{
	Size size = img.size();
	size.height = size.height * parameter;
	size.width = size.width * parameter;
	if (parameter < 1) 
	{
		cv::resize(img, img, size, INTER_AREA);
	}
	else 
	{
		cv::resize(img, img, size, INTER_LINEAR);
	}
}

Scale::~Scale() = default;

Resize::Resize(std::string parameter) 
{
	std::string sparameter = parameter;
	std::stringstream stream(sparameter);
	std::string columns;
	std::string rows;
	std::getline(stream, columns, '.');
	std::getline(stream, rows, '.');

	size.height = stoi(columns);
	size.width = stoi(rows);
}

Resize::Resize() 
{
	parameter = 1;
	std::string sparameter = parameter;
	std::stringstream stream(sparameter);
	std::string columns;
	std::string rows;
	std::getline(stream, columns, '.');
	std::getline(stream, rows);

	size.height = stoi(columns);
	size.width = stoi(rows);
}

void Resize::execute(Mat & img) 
{
	if (size.area() < img.size().area()) 
	{
		cv::resize(img, img, size, INTER_AREA);
	}
	else
	{
		cv::resize(img, img, size, INTER_LINEAR);
	}
}

Resize::~Resize() = default;

void Negative::execute(Mat & img) 
{
	cv::bitwise_not(img, img);
}

Negative::~Negative() = default;

void DarkToLight::execute(Mat & img) 
{
	cv::bitwise_not(img, img);
	cvtColor(img, img, COLOR_BGR2HSV);
	Mat new_img = Mat::zeros(img.size(), img.type());

	for (int y = 0; y < img.rows; y++) 
	{
		for (int x = 0; x < img.cols; x++) 
		{
			for (int c = 0; c < img.channels(); c++) 
			{
				new_img.at<Vec3b>(y, x)[c] = img.at<Vec3b>(y, x)[c];
				new_img.at<Vec3b>(y, x)[0] = ((img.at<Vec3b>(y, x)[0] + 90));

			}
		}
	}

	img = new_img;
	cvtColor(img, img, COLOR_HSV2BGR);
}

DarkToLight::~DarkToLight() = default;

void Cartoon::execute(Mat & img) 
{
	Mat edges;
	Mat newimg;
	double t1 = 100;
	double t2 = 200;
	Mat imggray;
	cvtColor(img, imggray, COLOR_BGR2GRAY);
	cv::Canny(imggray, edges, t1, t2);
	cv::bitwise_not(edges, edges);

	cv::edgePreservingFilter(img, img, 1, 60.0F, 0.3F);
	cv::InputArray mask = edges;
	cv::bitwise_and(img, img, newimg, mask);
	img = newimg;
}

Cartoon::~Cartoon() = default;

void Autom::execute(Mat & img) 
{
	std::vector<Mat> channels;
	cvtColor(img, img, COLOR_BGR2GRAY);
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();

	if (img.channels() == 1) 
	{
		clahe->apply(img, img);
	}
	else 
	{
		cv::split(img, channels);
		clahe->apply(channels[0], channels[0]);
		clahe->apply(channels[1], channels[1]);
		clahe->apply(channels[2], channels[2]);
		cv::merge(channels, img);
	}
}

Autom::~Autom() = default;


