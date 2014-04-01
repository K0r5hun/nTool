#include "image.h"
#include "fstream"
#include "iostream"

Image::Image()
{
}


//Get
std::string Image::getPathname() const
{
    return _pathname;
}
int Image::getSizeImage() const
{
    return _sizeImage;
}

int Image::getWidthImage() const
{
    return _widthImage;
}

int Image::getHeightImage() const
{
    return _heightImage;
}


//Set
void Image::setPathname( std::string const & pathname)
{
    _pathname=pathname;
}
void Image::setSizeFile(int sizeImage)
{
    _sizeImage=sizeImage;
}

bool Image::isBMP(std::string pathname)
{
    std::ifstream imageFile;
    imageFile.open(pathname.c_str());
    char signature[2];
    imageFile>>signature[0]>>signature[1];
    imageFile.close();
    return signature[0]=='B' && signature[1]=='M' ? true : false;
}

std::vector<std::vector<RGBA*> > Image::copypixel(std::vector<std::vector<RGBA *> > pixel)
{
    std::vector<std::vector<RGBA*> > copy(pixel);

    for(int i=0;i<(int)pixel.size();i++)
    {
        copy[i].resize(pixel[i].size());
        for(int j=0;j<(int)copy[i].size();j++)
            copy[i][j] = new RGBA(pixel[i][j]->getRed(),pixel[i][j]->getGreen(),pixel[i][j]->getBlue(),pixel[i][j]->getAlpha(),pixel[i][j]->getId());
    }
    return copy;
}

bool Image::shareSameId(std::vector<std::vector<RGBA *> > pixel1, std::vector<std::vector<RGBA *> > pixel2)
{
    bool value=true;

    for(int i = 0 ; i<(int)pixel1.size();i++)
    {
        for(int j= 0; j<(int)pixel1[i].size();j++)
            if(pixel1[i][j]->getId() != pixel2[i][j]->getId())
                value=false;
    }
    return value;
}
