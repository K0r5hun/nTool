#include "detection.h"
#include <algorithm>
#include <iostream>

namespace Detection
{

bool colorById(Image *image)
{
    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            if(image->pixel[i][j]->getId()!=0)
            {
                unsigned char colorRed=((int)image->pixel[i][j]->getId()*5)%255;
                unsigned char colorGreen=((int)image->pixel[i][j]->getId()*2)%255;
                unsigned char colorBlue=((int)image->pixel[i][j]->getId()*3)%255;
                if((colorRed+colorGreen+colorBlue)<20)
                {
                colorRed+=colorGreen+colorBlue;
                colorBlue+=colorGreen+colorRed;
                colorGreen+=colorRed+colorBlue;
                }

                image->pixel[i][j]->setRed(colorRed);
                image->pixel[i][j]->setBlue(colorBlue);
                image->pixel[i][j]->setGreen(colorGreen);
            }
        }
    }
    return true;
}

bool colorByShape(Shapes *shapes)
{
    int id;
    for(int i=0;i<shapes->image->getHeightImage();i++)
    {
        for(int j=0;j<shapes->image->getWidthImage();j++)
        {
            if((id=shapes->image->pixel[i][j]->getId())!=0)
            {
                if(shapes->isIdPresent(id))
                {
                unsigned char colorRed=((int)shapes->image->pixel[i][j]->getId()*5)%255;
                unsigned char colorGreen=((int)shapes->image->pixel[i][j]->getId()*2)%255;
                unsigned char colorBlue=((int)shapes->image->pixel[i][j]->getId()*3)%255;
                if((colorRed+colorGreen+colorBlue)<30)
                {
                colorRed+=2*(colorGreen+colorBlue);
                colorBlue+=2*(colorGreen+colorRed);
                colorGreen+=2*(colorRed+colorBlue);
                }

                shapes->image->pixel[i][j]->setRed(colorRed);
                shapes->image->pixel[i][j]->setBlue(colorBlue);
                shapes->image->pixel[i][j]->setGreen(colorGreen);
                }
                else
                shapes->image->pixel[i][j]->setGray(0);
            }
        }
    }
    return true;
}

bool colorByConvolution(Shapes *shapes)
{
    int id,convolution;
    for(int i=0;i<shapes->image->getHeightImage();i++)
    {
        for(int j=0;j<shapes->image->getWidthImage();j++)
        {
            if((id=shapes->image->pixel[i][j]->getId())!=0)
            {
                if(shapes->isIdPresent(id) )
                {

                convolution=shapes->shape[shapes->whereId(id)]->convolution;
                unsigned char colorRed=0;
                unsigned char colorGreen=0;
                unsigned char colorBlue=0;

                if(convolution<20)
                colorRed=255-convolution;
                else if(convolution<40)
                colorBlue=55+2*convolution;
                else
                colorGreen=55+2*convolution;

                shapes->image->pixel[i][j]->setRed(colorRed);
                shapes->image->pixel[i][j]->setBlue(colorBlue);
                shapes->image->pixel[i][j]->setGreen(colorGreen);
                }
                else
                shapes->image->pixel[i][j]->setGray(0);
            }
        }
    }
    return true;
}

bool smartDetection(Image *image)
{
    int count=0;
    int min;
    for(int i=0;i<image->getHeightImage()-1;i++)
    {
        for(int j=0;j<image->getWidthImage()-1;j++)
        {
             min=getMin(image,i,j);
             if(image->pixel[i][j]->getGray()==255)
                 min==0 ?  image->pixel[i][j]->setId(++count) : image->pixel[i][j]->setId(min);
             min=getMin(image,i,j);
             if(image->pixel[i][j+1]->getGray()==255)
                 min==0 ?  image->pixel[i][j+1]->setId(++count) : image->pixel[i][j+1]->setId(min);
             min=getMin(image,i,j);
             if(image->pixel[i+1][j]->getGray()==255)
                 min==0 ?  image->pixel[i+1][j]->setId(++count) : image->pixel[i+1][j]->setId(min);
             min=getMin(image,i,j);
             if(image->pixel[i+1][j+1]->getGray()==255)
                 min==0 ?  image->pixel[i+1][j+1]->setId(++count) : image->pixel[i+1][j+1]->setId(min);

        }
     }
    return true;
}

bool giveId(Image *image)
{
    int count=0;
    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            if(image->pixel[i][j]->getGray()==255)
                image->pixel[i][j]->setId(++count);
            else
                image->pixel[i][j]->setId(0);
        }
    }
    return true;
}

bool detect(Image *image)
{
    int min;
    bool change1,change2;

    do{
        change2=false;
        for(int j=image->getWidthImage()-1;j>=1;j--)
        {
            for(int i=image->getHeightImage()-1;i>=1;i--)
            {
                min=getMin2(image,i,j);
                if(image->pixel[i][j]->getGray()==255 && image->pixel[i][j]->getId()>min )
                {
                    image->pixel[i][j]->setId(min);
                    change2=true;
                }
                if(image->pixel[i][j-1]->getGray()==255 && image->pixel[i][j-1]->getId()>min)
                {
                    image->pixel[i][j-1]->setId(min);
                    change2=true;
                }

                if(image->pixel[i-1][j]->getGray()==255 && image->pixel[i-1][j]->getId()>min)
                {
                    image->pixel[i-1][j]->setId(min);
                    change2=true;
                }

                if(image->pixel[i-1][j-1]->getGray()==255 && image->pixel[i-1][j-1]->getId()>min)
                {
                    image->pixel[i-1][j-1]->setId(min);
                    change2=true;
                }

            }
        }

        change1=false;
        for(int i=0;i<image->getHeightImage()-1;i++)
        {
            for(int j=0;j<image->getWidthImage()-1;j++)
            {

                min=getMin(image,i,j);
                if(image->pixel[i][j]->getGray()==255 && image->pixel[i][j]->getId()>min )
                {
                    image->pixel[i][j]->setId(min);
                    change1=true;
                }
                if(image->pixel[i][j+1]->getGray()==255 && image->pixel[i][j+1]->getId()>min)
                {
                    image->pixel[i][j+1]->setId(min);
                    change1=true;
                }

                if(image->pixel[i+1][j]->getGray()==255 && image->pixel[i+1][j]->getId()>min)
                {
                    image->pixel[i+1][j]->setId(min);
                    change1=true;
                }

                if(image->pixel[i+1][j+1]->getGray()==255 && image->pixel[i+1][j+1]->getId()>min)
                {
                    image->pixel[i+1][j+1]->setId(min);
                    change1=true;
                }

            }
        }



   }while(change1 && change2);


   return true;

}




int getMin(Image *image, int k, int l)
{
    std::vector<int> window;
    for(int i=k;i<=k+1;i++)
    {
        for(int j=l;j<=l+1;j++)
        {
            window.push_back(image->pixel[i][j]->getId());
        }
    }
    std::sort(window.begin(),window.end());

    for(int i=0;i<(int)window.size();i++)
    {
        if(window[i]!=0)
        return window[i];
    }
    return 0;
}
int getMin2(Image *image, int k, int l)
{
    std::vector<int> window;
    for(int i=k;i>=k-1;i--)
    {
        for(int j=l;j>=l-1;j--)
        {
            window.push_back(image->pixel[i][j]->getId());
        }
    }
    std::sort(window.begin(),window.end());

    for(int i=0;i<(int)window.size();i++)
    {
        if(window[i]!=0)
        return window[i];
    }
    return 0;
}






void deleteRectangle(Image *image,int size)
{
    for(int i=image->getHeightImage()-1; i>=image->getHeightImage()-size; i--)
    {
        for(int j=0; j<image->getWidthImage(); j++)
        {
            image->pixel[i][j]->setGray(0);
        }
    }

}

}


