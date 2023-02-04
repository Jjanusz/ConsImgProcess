

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/photo.hpp"
#include <iostream>
#include <array>
#include <string>
#include <sstream>


class Command {
public:
    virtual void execute(cv::Mat&) = 0;
    virtual ~Command();
private:
    std::string info;


};

class BlackWhite : public Command {

public:
    void execute(cv::Mat& img);

     ~BlackWhite();

private:
    std::string info;

};


class GausianBlur : public Command {

public:
    void execute(cv::Mat& img);

     ~GausianBlur();

private:
    std::string info;

};

class BoxFilterBlur : public Command {

public:
    void execute(cv::Mat& img);
    

     ~BoxFilterBlur();

private:
    std::string info;

};


class Scale : public Command {

public:
    Scale(double x);
        

    Scale();
       

    


    void execute(cv::Mat& img);

     ~Scale();

private:
    double parameter;
    std::string info;
};






class Resize : public Command {

public:
    Resize(std::string parameter);


        Resize();
        void execute(cv::Mat& img);
     ~Resize();

private:
    cv::Size size;
    std::string parameter;
    std::string info;
};

class Negative : public Command {

public:



    void execute(cv::Mat& img);
     ~Negative();

private:

    std::string info;
};

class DarkToLight : public Command {

public:



    void execute(cv::Mat& img);
     ~DarkToLight();

private:

    std::string info;
};



class Cartoon : public Command {

public:



    void execute(cv::Mat& img);


     ~Cartoon();

private:

    std::string info;
};



class Autom : public Command {

public:


    void execute(cv::Mat& img);

     ~Autom();

private:

    std::string info;
};


