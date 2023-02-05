
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
#include <memory>
#include <algorithm>
#include <chrono>
#include <fstream>
#include "windows.h"
#include "psapi.h"
#include "imageprocessing.h"
#include "functions.h"
using namespace cv;

int main()
{
	std::fstream config;
	std::string conftab[6];
	std::string conftab2[6];
	int i = 0;
	config.open("config.ini", std::ios::in);
	
	while (config.peek() != EOF) 
	{
		std::getline(config, conftab[i], '=');
		std::getline(config, conftab2[i]);
		i++;
	}
	
	int MAXSIZE = 1000000000 * stoi(conftab2[0]);
	std::string ifloop = conftab2[1];
	std::string path = std::filesystem::current_path().string();

	while (true) 
	{

		std::cout << '\n' << path << "  ";
		std::string userinput;
		std::getline(std::cin, userinput);
		std::stringstream linia(userinput);
		std::vector<std::string> filenames;
		std::vector<std::string> commandnames;
		std::string word;
		
		while (std::getline(linia, word, ' ')) 
		{

			if (std::regex_match(word, std::regex(formats))) {
				filenames.push_back(word);
			}

			else if (word == "all") 
			{
				getAllFiles(path, filenames);
			}

			else 
			{
				commandnames.push_back(word);
				std::cout << word << '\n';
			}
		}
		
		std::vector<std::unique_ptr<Command>> commandsready;
		
		for (auto& i : commandnames) {

			if (i == "blackwhite") 
			{
				std::unique_ptr<Command> comm(new BlackWhite);
				commandsready.push_back(std::move(comm));
			}

			else if (i == "boxfilterblur") 
			{
				std::unique_ptr<Command> comm(new BoxFilterBlur);
				commandsready.push_back(std::move(comm));
			}

			else if (i == "gaussianblur") 
			{
				std::unique_ptr<Command> comm(new GausianBlur);
				commandsready.push_back(std::move(comm));
			}

			else if (i == "negative") 
			{
				std::unique_ptr<Command> comm(new Negative);
				commandsready.push_back(std::move(comm));
			}

			else if (i == "dty") 
			{
				std::unique_ptr<Command> comm(new DarkToLight);
				commandsready.push_back(std::move(comm));
			}

			else if (std::regex_match(i, std::regex("(scale)(\\()(.*)(\\))"))) 
			{
				double argument = getFactorParameter(i);
				std::unique_ptr<Command> comm(new Scale(argument));
				commandsready.push_back(std::move(comm));
			}

			else if (std::regex_match(i, std::regex("(resize)(\\()(.*)(\\))"))) 
			{
				std::string argument = getParameter(i);
				std::unique_ptr<Command> comm(new Resize(argument));
				commandsready.push_back(std::move(comm));
			}

			else if (i == "cartoon") 
			{
				std::unique_ptr<Command> comm(new Cartoon);
				commandsready.push_back(std::move(comm));
			}

			else if (i == "autom")
			{
				std::unique_ptr<Command> comm(new Autom);
				commandsready.push_back(std::move(comm));
			}

			else 
			{
				std::cout << i << "is not recognized as Command or filename";


			}
		}
		
		if (filenames.empty()) 
		{

			std::cout << "Brak prawidłowo wybranych zdjęć";
		}

		else if (commandsready.empty())
		{
			std::cout << "Brak prawidłowo wybranych komend";
		}

		else 
		{
			std::string tempfilepath;
			std::replace(path.begin(), path.end(), '\\', '/');
			std::string currentfile;

			std::vector<std::string>::iterator nameit = filenames.begin();
			std::vector<std::string>::iterator nameit2 = filenames.begin();
			auto t1 = std::chrono::high_resolution_clock::now();
			
			while (currentfile != filenames.back())
			{
				std::vector<Mat> images;
				images.reserve(100);
				int size = 0;
				for (nameit; nameit != filenames.end(); nameit++)
				{
					if (size > MAXSIZE) 
					{
						break;
					}
					tempfilepath = path + '/' + *nameit;
					currentfile = *nameit;
					images.push_back(cv::imread(tempfilepath));
					size = images.front().size().area() + size;


				}

				for (std::vector<std::unique_ptr<Command>> ::iterator it = commandsready.begin(); it != commandsready.end(); ++it)
				{
					for (auto& i : images) 
					{
						(*it)->execute(i);

					}
				}

				for (auto& i : images) 
				{
					tempfilepath = path + '/' + "(1)" + *nameit2;
					imwrite(tempfilepath, i);
					nameit2++;
				}
			}

			auto t2 = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::ratio<60>> ms_double = t2 - t1;
			std::cout << "czas: " << ms_double.count();
			
			if (ifloop == "FALSE") 
			{
				exit(0);
			}
		}
	}
}
