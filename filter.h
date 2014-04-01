#ifndef FILTER_H
#define FILTER_H
#include <vector>

#include "image.h"


namespace Filter
{

    void entropy(Image* image,const short int &windowSize);
    void dilatation(Image* image,const short int &windowSize);
    void erosion(Image* image,const short int &windowSize);
    void average(Image* image,const short int &windowSize);
    void median(Image* image,const short int &windowSize);

    void applyFilter(Image* image, std::vector<unsigned char> filter,const short int &windowSize);
    std::vector<unsigned char> getWindow(const Image &image, const int &i, const int &j, const int &windowSize);
    unsigned char convolution(const std::vector<unsigned char> &filter,const std::vector<unsigned char> &window);

}

#endif // FILTER_H
