#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>
#include <regex>
#include <algorithm>
#include <chrono>
#include <forward_list>
#include "windows.h"
#include "psapi.h"
#include "Classes.cpp"
using namespace cv;
std::string word;
std::string userinput;
std::stringstream line;
std::vector<std::string> filenames;
std::vector<std::string> commandnames;





void getallfiles(std::string path) {

    
       
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            
            std::string filename = entry.path().string();
            int length=path.length();
            filename.erase(0, length+1);
            if (std::regex_match(filename, std::regex("(.*)(.jpg)|(.png)|(.jpeg)|(.bmp)|(.dib)|(.jpe)|(.jp2)|(.webp)|(.pbm)|(.pgm)|(.ppm)|(.pxm)|(.pnm)|(.sr)|(.ras)|(.tif)|(.tiff)|(.exr)|(.hdr)|(.pic)"))) {
                filenames.push_back(filename);
            }
        }
}



double getparameter(std::string &par) {

    std::smatch argument;
    std::regex_search(par, argument, std::regex("\\(.*\\)"));
    std::string word = argument[0];
    word.erase(word.begin());
    word.erase(word.end() - 1);
    std::cout << word;
    
    return std::stod(word);
}





int main()

{

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    std::string path = std::filesystem::current_path().string();
    std::cout << path<< "  ";

 
   

    std::getline(std::cin, userinput);
    std::stringstream linia(userinput);
    auto t1 = std::chrono::high_resolution_clock::now();
    while (std::getline(linia, word, ' ')) {

        std::cout << word;
        if (std::regex_match(word, std::regex("(.*)(.jpg)|(.png)|(.jpeg)|(.bmp)|(.dib)|(.jpe)|(.jp2)|(.webp)|(.pbm)|(.pgm)|(.ppm)|(.pxm)|(.pnm)|(.sr)|(.ras)|(.tif)|(.tiff)|(.exr)|(.hdr)|(.pic)"))) {
            std::cout << "\nplik";
            filenames.push_back(word);
        }
        else if (word == "all") {
            getallfiles(path);

        }
        else {

        commandnames.push_back(word);
        }

    }
    std::vector<command*> commandsready;
    for (auto i : commandnames) {

        if (i == "blackwhite") {

            command* comm = new blackwhite();
            commandsready.push_back(comm);
          
        }


        else if(i == "boxfilterblur") {

            command* comm = new boxfilterblur();
            commandsready.push_back(comm);
         
        }

        else if (i == "gaussianblur") {

            command* comm = new gaussianblur();
            commandsready.push_back(comm);
           
        }

        
        else if (std::regex_match(i, std::regex("(scale)(\\()(.*)(\\))"))) {
            double argument = getparameter(i);
            command* comm = new scale(argument);
            commandsready.push_back(comm);
            
        }
        else {
            std::cout << i << "is not recognized as command or filename";


        }





    }

   
    std::string tempfilepath;
    std::replace(path.begin(), path.end(), '\\', '/');
    std::string currentfile;
    std::vector<std::string>::iterator nameit = filenames.begin();
    std::vector<std::string>::iterator nameit2 = filenames.begin();
    while (currentfile != filenames.back()) {
        std::vector<Mat> images;
        int size = 0;
        images.reserve(100);
        
        for (nameit;  nameit != filenames.end(); nameit++) {
            if (size > 100000000) {
                break;
            }
            tempfilepath = path + '/' + *nameit;
            currentfile=*nameit;
            images.push_back(cv::imread(tempfilepath));
            size = images.front().size().area() + size;
            
           
        }

        size_t physMemUsedByMe = pmc.WorkingSetSize;
     
        for (std::vector<command*>::iterator it = commandsready.begin(); it != commandsready.end(); ++it) {


            for (auto& i : images) {
                (*it)->execute(i);

            }
            

        }
       
        for (auto i : images) {
           
            tempfilepath = path + '/' + "(2)" + *nameit2;
            /*imwrite(tempfilepath, images(i));*/
            std::cout << *nameit2<< '\n';
            nameit2++;
            

        }
    }
   
    for (std::vector<command*>::iterator it = commandsready.begin(); it != commandsready.end(); ++it) {
        delete* it;
    }
     commandsready.clear();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::ratio<60>> ms_double = t2 - t1;
   std::cout<<"czas: "<< ms_double.count();
    cv::waitKey(0);

  

    



   
  
}
