#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
using namespace cv;


class command {
public:
    virtual void execute(Mat&) = 0;
    virtual ~command() = default;
private:
    std::string info;


};

class blackwhite: public command {

public:
    void execute(Mat& img) {



        cvtColor(img,img,COLOR_BGR2GRAY);


    }

    virtual ~blackwhite() = default;

private:
    std::string info;

};

    std::vector<Mat> images;
    







std::string userinput;

int main()
{
    std::string path = std::filesystem::current_path().string();
    

    cv::Mat img = cv::imread("C:/Users/jedre/OneDrive - Politechnika Wroclawska/Pulpit/temps.png");
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    
    cv::destroyAllWindows();
    imwrite("test.jpg", img);











    command* comm = new blackwhite();
    comm->execute(img);
    cv::imshow("First OpenCV Application", img);
    delete comm;

    cv::waitKey(0);
    while (1) {


        std::cin >> userinput;

        

    }

    



   
  
}
