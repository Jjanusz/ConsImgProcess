



#include "functions.h"


void getAllFiles(std::string path, std::vector<std::string>& filenames) {



    for (const auto& entry : std::filesystem::directory_iterator(path)) {

        std::string filename = entry.path().string();
        size_t length = path.length();
        filename.erase(0, length + 1);
        if (std::regex_match(filename, std::regex("(.*)(.jpg)|(.png)|(.jpeg)|(.bmp)|(.dib)|(.jpe)|(.jp2)|(.webp)|(.pbm)|(.pgm)|(.ppm)|(.pxm)|(.pnm)|(.sr)|(.ras)|(.tif)|(.tiff)|(.exr)|(.hdr)|(.pic)"))) {
            filenames.push_back(filename);
        }
    }



}

double getParameter(std::string& par) {

    std::smatch argument;
    std::regex_search(par, argument, std::regex("\\(.*\\)"));
    std::string word = argument[0];
    word.erase(word.begin());
    word.erase(word.end() - 1);


    return std::stod(word);
}


std::string getParameterString(std::string& par) {

    std::smatch argument;
    std::regex_search(par, argument, std::regex("\\(.*\\)"));
    std::string word = argument[0];
    word.erase(word.begin());
    word.erase(word.end() - 1);


    return word;
}













