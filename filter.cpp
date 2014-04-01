#include "filter.h"
#include <iostream>
#include <algorithm>
#include "bmp.h"

namespace Filter
{

void applyFilter(Image *image, std::vector<unsigned char> filter, const short &windowSize)
{

    // A Faire : il faut travailler sur une nouvelle image, clone de l'image(constructeur par copie)
    Image* img=new BMP(image->getPathname());
    int height=image->getHeightImage();
    int width=image->getWidthImage();
    for(int i=windowSize;i<height-windowSize;i++)
    {
        for(int j=windowSize;j<width-windowSize;j++)
        {
        std::vector<unsigned char>window=getWindow(*img,i,j,windowSize);
        image->pixel[i][j]->setGray(convolution(filter,window));
        }
    }
}

std::vector<unsigned char> getWindow(const Image &image, const int &i, const int &j, const int &windowSize)
{
    std::vector<unsigned char> window;
    for(int k=i-windowSize;k<=i+windowSize;k++)
    {
        for(int l=j-windowSize;l<=j+windowSize;l++)
            window.push_back(image.pixel[k][l]->getGray());
    }
    //Sort the window
    std::sort(window.begin(),window.end());
    return window;
}

unsigned char convolution(const std::vector<unsigned char> &filter,const std::vector<unsigned char> &window)
{
    int sum=0;
    int sumCoef=0;
    if(filter.size()==window.size())
    {
        for(int i=0;i<(int)filter.size();i++)
        {
            sumCoef+=filter[i];
            sum+=filter[i]*window[i];
        }
        return sum/sumCoef;
    }
    return 0;
}

void entropy(Image *image, const short &windowSize)
{
    std::vector<unsigned char> filter;
    int length=(2*windowSize+1)*(2*windowSize+1);
    filter.push_back(1);
    for(int i=0;i<length-1;i++)
        filter.push_back(0);

    applyFilter(image,filter,windowSize);
}

void dilatation(Image *image, const short &windowSize)
{
    std::vector<unsigned char> filter;
    int length=(2*windowSize+1)*(2*windowSize+1);
    for(int i=0;i<length-1;i++)
        filter.push_back(0);
    filter.push_back(1);

    applyFilter(image,filter,windowSize);
}


void erosion(Image *image, const short &windowSize)
{
    std::vector<unsigned char> filter;
    int length=(2*windowSize+1)*(2*windowSize+1);
    filter.push_back(1);
    for(int i=0;i<length-1;i++)
        filter.push_back(0);


    applyFilter(image,filter,windowSize);
}

void median(Image *image, const short &windowSize)
{
    std::vector<unsigned char> filter;
    int length=(2*windowSize+1)*(2*windowSize+1);
    for(int i=0;i<length;i++)
    {
        if(i!=length/2)
        filter.push_back(0);
        else
        filter.push_back(1);

    }


    applyFilter(image,filter,windowSize);
}

void average(Image *image, const short &windowSize)
{
    std::vector<unsigned char> filter;
    int length=(2*windowSize+1)*(2*windowSize+1);
    for(int i=0;i<length;i++)
    {
        filter.push_back(1);
    }


    applyFilter(image,filter,windowSize);
}

}
