#include <FileHandler.hpp>

FileHandler::FileHandler()
{
    //ctor
}

SDL_Surface* FileHandler::load_img(string filename){
    string filePath = imagePath+filename;
    return load_image(filePath.c_str());
}

const string FileHandler::imagePath = "images/";
