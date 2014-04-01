#include "shapes.h"
#include <iostream>

Shapes::Shapes()
{
    image=NULL;
}

Shapes::Shapes(Image *img)
{
    image=img;
}

bool Shapes::update()
{
    //Must contains an image to work
    if(image==NULL)
        return false;
    bool exist;
    int id;

    shape.resize(0);

    for(int i=0;i<image->getHeightImage();i++)
    {
        for(int j=0;j<image->getWidthImage();j++)
        {
            if((id=image->pixel[i][j]->getId())!=0)
            {
                if(shape.size()==0)
                    shape.push_back(new Shape(id,image->getWidthImage(),0,image->getHeightImage(),0));
                else
                {
                    exist=false;
                    for(int k=0;k<(int)shape.size();k++)
                    {
                        if(shape[k]->id==id)
                        {
                            if(j<shape[k]->xmin)
                                shape[k]->xmin=j;
                            if(j>shape[k]->xmax)
                                shape[k]->xmax=j;
                            if(i<shape[k]->ymin)
                                shape[k]->ymin=i;
                            if(i>shape[k]->ymax)
                                shape[k]->ymax=i;
                            shape[k]->surface++;
                            exist=true;
                            break;
                        }
                    }
                    if(!exist)
                        shape.push_back(new Shape(id,image->getWidthImage(),0,image->getHeightImage(),0));
                }
            }
        }
    }




    return true;
}

bool Shapes::isIdPresent(int id)
{
    for(int i=0;i<(int)shape.size();i++)
    {
        if(shape[i]->id == id)
            return true;
    }
    return false;
}

int Shapes::whereId(int id)
{
    for(int i=0;i<(int)shape.size();i++)
    {
        if(shape[i]->id == id)
            return i;
    }
    return  -1;
}
int Shapes::deleteFromSurface(int surface, short tolerance)
{

    int radius=(surface*tolerance)/100;

    int numDeleted=0;
    for(int i=(int)shape.size()-1;i>=0;i--)
    {
        if(shape[i]->surface <= surface-radius || shape[i]->surface >= surface+radius)
        {
            ++numDeleted;
            delete shape[i];
            shape.erase(shape.begin()+i);

        }
    }
    return numDeleted;

}

int Shapes::getGlobalSurface()
{
    int globalSurface=0;
    for(int i=0;i<shape.size();i++)
    {
        globalSurface+=shape[i]->surface;
    }
    return globalSurface;
}
