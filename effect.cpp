#include "effect.h"
#include <iostream>

namespace Effect
{

bool tresholdGray(Image *image, const int &treshold)
{
    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
            image->pixel[i][j]->getGray()>treshold ? image->pixel[i][j]->setGray(255) : image->pixel[i][j]->setGray(0);
    }
    return true;
}
bool tresholdColor(Image *image, const int &treshold)
{
    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            image->pixel[i][j]->getRed()>treshold ? image->pixel[i][j]->setRed(255) : image->pixel[i][j]->setRed(0);
            image->pixel[i][j]->getBlue()>treshold ? image->pixel[i][j]->setBlue(255) : image->pixel[i][j]->setBlue(0);
            image->pixel[i][j]->getGreen()>treshold ? image->pixel[i][j]->setGreen(255) : image->pixel[i][j]->setGreen(0);
        }
    }
    return true;
}

bool tresholdColor(Image *image, const int &tresholdRed, const int &tresholdGreen, const int &tresholdBlue)
{
    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            image->pixel[i][j]->getRed()>tresholdRed ? image->pixel[i][j]->setRed(255) : image->pixel[i][j]->setRed(0);
            image->pixel[i][j]->getBlue()>tresholdGreen ? image->pixel[i][j]->setBlue(255) : image->pixel[i][j]->setBlue(0);
            image->pixel[i][j]->getGreen()>tresholdBlue ? image->pixel[i][j]->setGreen(255) : image->pixel[i][j]->setGreen(0);
        }
    }
    return true;
}


void grayscale(Image *image)
{
    unsigned char gray;
    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            gray=image->pixel[i][j]->getGray();
            image->pixel[i][j]->setRed(gray);
            image->pixel[i][j]->setGreen(gray);
            image->pixel[i][j]->setBlue(gray);
        }
    }
}

bool contrastGray(Image *image)
{
    int min=255;
    int max=0;

    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            if(max<image->pixel[i][j]->getGray())
                max = image->pixel[i][j]->getGray();
            if(min>image->pixel[i][j]->getGray())
                min = image->pixel[i][j]->getGray();
        }
    }
    std::cout<<min<<std::endl<<max<<std::endl;

    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            int color = image->pixel[i][j]->getGray();
            image->pixel[i][j]->setGray(255*(color-min)/(max-min));
        }
    }
    return true;
}

bool contrastColor(Image *image)
{
    int minRed=255;
    int minGreen=255;
    int minBlue=255;

    int maxRed=0;
    int maxGreen=0;
    int maxBlue=0;


    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {


            if(maxRed<image->pixel[i][j]->getRed())
                maxRed = image->pixel[i][j]->getRed();
            if(minRed>image->pixel[i][j]->getRed())
                minRed = image->pixel[i][j]->getRed();

            if(maxGreen<image->pixel[i][j]->getGreen())
                maxGreen = image->pixel[i][j]->getGreen();
            if(minGreen>image->pixel[i][j]->getGreen())
                minGreen = image->pixel[i][j]->getGreen();

            if(maxBlue<image->pixel[i][j]->getBlue())
                maxBlue = image->pixel[i][j]->getBlue();
            if(minBlue>image->pixel[i][j]->getBlue())
                minBlue = image->pixel[i][j]->getBlue();
        }
    }

    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            int colorRed = 255*(image->pixel[i][j]->getRed()-minRed)/(maxRed-minRed);
            int colorGreen = 255*(image->pixel[i][j]->getGreen()-minGreen)/(maxGreen-minGreen);
            int colorBlue = 255*(image->pixel[i][j]->getBlue()-minBlue)/(maxBlue-minBlue);

            image->pixel[i][j]->setRed(colorRed);
            image->pixel[i][j]->setGreen(colorGreen);
            image->pixel[i][j]->setBlue(colorBlue);
        }
    }
    return true;


}

}
