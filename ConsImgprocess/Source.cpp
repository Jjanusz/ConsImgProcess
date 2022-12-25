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
#include <fstream>
#include "windows.h"
#include "psapi.h"
#include "Classes.cpp"
using namespace cv;
std::string word;

std::stringstream line;






void getallfiles(std::string path,std::vector<std::string> &filenames ) {

    
       
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            
            std::string filename = entry.path().string();
            size_t length=path.length();
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


std::string getparameterstring(std::string& par) {

    std::smatch argument;
    std::regex_search(par, argument, std::regex("\\(.*\\)"));
    std::string word = argument[0];
    word.erase(word.begin());
    word.erase(word.end() - 1);
    std::cout << word;

    return word;
}



int main()

{
    
    std::fstream config;
    std::string conftab[6];
    std::string conftab2[6];
    int i = 0;
    config.open("config.ini", std::ios::in);
    while (config.peek() != EOF) {

        std::getline(config, conftab[i], '=');

        std::getline(config, conftab2[i]);

        i++;

    }
    
    int MAXSIZE = 1000000000 * stoi(conftab2[0]);
    std::string ifloop = conftab2[1];

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    std::string path = std::filesystem::current_path().string();
   
    
    
    while (true) {

        std::cout <<'\n'<< path << "  ";



        std::string userinput;
        std::getline(std::cin, userinput);
        std::stringstream linia(userinput);



        std::vector<std::string> filenames;
        std::vector<std::string> commandnames;


        while (std::getline(linia, word, ' ')) {

            std::cout << word;
            if (std::regex_match(word, std::regex("(.*\\.jpg)|(.*\\.png)|(.*\\.jpeg)|(.*\\.bmp)|(.*\\.dib)|(.*\\.jpe)|(.*\\.jp2)|(.*\\.webp)|(.*\\.pbm)|(.*\\.pgm)|(.*\\.ppm)|(.*\\.pxm)|(.*\\.pnm)|(.*\\.sr)|(.*\\.ras)|(.*\\.tif)|(.*\\.tiff)|(.*\\.exr)|(.*\\.hdr)|(.*\\.pic)"))) {
                
                filenames.push_back(word);
            }
            else if (word == "all") {
                getallfiles(path, filenames);

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


            else if (i == "boxfilterblur") {

                command* comm = new boxfilterblur();
                commandsready.push_back(comm);

            }

            else if (i == "gaussianblur") {

                command* comm = new gaussianblur();
                commandsready.push_back(comm);

            }
            else if (i == "negative") {

                command* comm = new negative();
                commandsready.push_back(comm);

            }
            else if (i == "dty") {

                command* comm = new darktolight();
                commandsready.push_back(comm);

            }


            else if (std::regex_match(i, std::regex("(scale)(\\()(.*)(\\))"))) {
                double argument = getparameter(i);
                command* comm = new scale(argument);
                commandsready.push_back(comm);

            }
            else if (std::regex_match(i, std::regex("(resize)(\\()(.*)(\\))"))) {
                std::string argument = getparameterstring(i);
                command* comm = new res(argument);
                commandsready.push_back(comm);

            }
            else if (i == "cartoon") {

                command* comm = new cartoon();
                commandsready.push_back(comm);

            }
            else if (i == "autom") {

                command* comm = new autom();
                commandsready.push_back(comm);

            }
            else {
                std::cout << i << "is not recognized as command or filename";


            }





        }
        if (filenames.empty()) {
            
            std::cout <<"Brak prawidłowo wybranych zdjęć";
        }
        else if (commandsready.empty()) {
            std::cout << "Brak prawidłowo wybranych komend";


        }
        else {

            std::string tempfilepath;
            std::replace(path.begin(), path.end(), '\\', '/');
            std::string currentfile;
            std::vector<std::string>::iterator nameit = filenames.begin();
            std::vector<std::string>::iterator nameit2 = filenames.begin();
            while (currentfile != filenames.back()) {
                std::vector<Mat> images;
                int size = 0;
                images.reserve(100);
                auto t1 = std::chrono::high_resolution_clock::now();
                for (nameit; nameit != filenames.end(); nameit++) {
                    if (size > MAXSIZE) {
                        break;
                    }
                    tempfilepath = path + '/' + *nameit;
                    currentfile = *nameit;
                    images.push_back(cv::imread(tempfilepath));
                    size = images.front().size().area() + size;


                }
                auto t2 = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::ratio<60>> ms_double = t2 - t1;
                std::cout << '\n' << "czas: " << '\n' << ms_double.count();
                size_t physMemUsedByMe = pmc.WorkingSetSize;

                for (std::vector<command*>::iterator it = commandsready.begin(); it != commandsready.end(); ++it) {

                   
                    for (auto& i : images) {
                        (*it)->execute(i);

                    }
                  
                }

                for (auto i : images) {

                    tempfilepath = path + '/' + "(3)" + *nameit2;
                    imwrite(tempfilepath, i);
                    std::cout << *nameit2 << '\n';
                    nameit2++;


                }
            }

            for (std::vector<command*>::iterator it = commandsready.begin(); it != commandsready.end(); ++it) {
                delete* it;
            }
            commandsready.clear();
            if (ifloop == "FALSE") {

                exit(0);


            }
        }

        


       

    }


   
  
}
