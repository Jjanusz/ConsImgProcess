#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/photo.hpp"
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
        parameter = 1;

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

      

     
     


    }

    virtual ~scale() = default;

private:
    double parameter;
    std::string info;
};






class res : public command {

public:
    res(std::string x) {
        parameter = x;

        std::string sparameter = parameter;
        std::stringstream stream(sparameter);
        std::string columns;
        std::string rows;
        std::getline(stream, columns, '.');
        std::getline(stream, rows, '.');
   
        size.height = stoi(columns);
        size.width = stoi(rows);

    }

    res() {
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


    void execute(Mat& img) {
     

        
      
        if (size.area() < img.size().area()) {
            cv::resize(img, img, size, INTER_AREA);
        }
        else {
            cv::resize(img, img, size, INTER_LINEAR);
        }



       



    }

    virtual ~res() = default;

private:
    Size size;
    std::string parameter;
    std::string info;
};

class negative: public command {

public:



    void execute(Mat& img) {

        cv::bitwise_not(img,img);







    }

    virtual ~negative() = default;

private:
  
    std::string info;
};

class darktolight : public command {

public:



    void execute(Mat& img) {

        
        cv::bitwise_not(img, img);
        cvtColor(img, img, COLOR_BGR2HSV);
        Mat new_img = Mat::zeros(img.size(), img.type());
        
        for (int y = 0; y < img.rows; y++) {
            for (int x = 0; x < img.cols; x++) {
                for (int c = 0; c < img.channels(); c++) {
    

                    new_img.at<Vec3b>(y, x)[c] = img.at<Vec3b>(y, x)[c];
                    new_img.at<Vec3b>(y, x)[0] = ((img.at<Vec3b>(y, x)[0]+90));

                }
            }
        }



        
        img = new_img;
        cvtColor(img, img, COLOR_HSV2BGR);

    }

    virtual ~darktolight() = default;

private:

    std::string info;
};



class cartoon : public command {

public:



    void execute(Mat& img) {

        Mat edges;
        Mat newimg;
        double t1=100;
        double t2=200;

        Mat imggray;
        cvtColor(img, imggray, COLOR_BGR2GRAY);
      


        cv::Canny(imggray, edges, t1, t2);
        cv::bitwise_not(edges, edges);
   
       
        cv::edgePreservingFilter(img,img,1,60.0F,0.3F);
        cv::InputArray mask = edges;
        cv::bitwise_and(img,img,newimg,mask);
        img = newimg;

    }

    virtual ~cartoon() = default;

private:

    std::string info;
};



class autom : public command {

public:


    void execute(Mat& img) {
        std::vector<Mat> channels;
        cvtColor(img, img, COLOR_BGR2GRAY);
        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
        if (img.channels() == 1) {


            clahe->apply(img, img);
        }
        else {
            cv::split(img, channels);
            clahe->apply(channels[0], channels[0]);
            clahe->apply(channels[1], channels[1]);
            clahe->apply(channels[2], channels[2]);
            cv::merge(channels, img);
        }
    }

    virtual ~autom() = default;

private:

    std::string info;
};


