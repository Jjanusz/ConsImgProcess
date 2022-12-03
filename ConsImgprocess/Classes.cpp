#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <array>
using namespace cv;


class command {
public:
    virtual void execute(Mat&) = 0;
    virtual ~command() = default;
private:
    std::string info;


};

class blackwhite : public command {

public:
    void execute(Mat& img) {

        cvtColor(img, img, COLOR_BGR2GRAY);
        std::cout << "\nblackwhite ran";



    }

    virtual ~blackwhite() = default;

private:
    std::string info;

};


class gaussianblur : public command {

public:
    void execute(Mat& img) {

        GaussianBlur(img, img, Size(5, 5), 0);
        
    


    }

    virtual ~gaussianblur() = default;

private:
    std::string info;

};

class boxfilterblur : public command {

public:
    void execute(Mat& img) {

        blur(img, img, Size(5, 5));
        std::cout << "\nboxfilterblur ran";
        //wywala sie przy podwojnym odpaleniu moze wykrywa ze nie jest to BGR po pierwszym razie cvtColor(img,img,COLOR_BGR2GRAY);


    }

    virtual ~boxfilterblur() = default;

private:
    std::string info;

};


class scale : public command {

public:
    scale(double x) {
        parameter = x;

    }

    scale() {
        parameter = 0.5;

    }

    
    void execute(Mat& img) {

        Size size = img.size();
        size.height = size.height * parameter;
        size.width = size.width * parameter;
        if (parameter < 1) {
            cv::resize(img, img, size, INTER_AREA);
        }
        else {
            cv::resize(img, img, size, INTER_LINEAR);
        }

      

        std::cout << "\nscale("<< parameter <<")ran";
     


    }

    virtual ~scale() = default;

private:
    double parameter;
    std::string info;
};