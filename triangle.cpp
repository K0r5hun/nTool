#include "triangle.h"
#include <math.h>
#include <iostream>
#include <vector>
#include "image.h"

Triangle::Triangle()
{
}

Triangle::Triangle(int surface)
{
    _width=sqrt((4*surface)/sqrt(3));
    _height=(_width*sqrt(3))/2;
     createTriangle();
}


//Get
int Triangle::getWidth(void) const
{
    return _width;
}

int Triangle::getHeight(void) const
{
    return _height;
}

 void Triangle::createTriangle(void)
{
    float counter =1;
    int medium=0;
    medium=_width/2;

    _triangle.resize(_height);

    for(int i=0;i<_height;i++)
        _triangle[i].resize(_width);

    for(int i=0; i<_height; i++)
    {
        for(int j=0; j<_width; j++)
        {
            _triangle[i][j]=0;
        }
            _triangle[i][medium]=255;
    }


       for(int i=1; i<_height-1; i=i+2)
          {

              counter+=1.15;
              for(int k=0; k<counter; k+=1)
              {
                  if(medium-k>=0 && medium+k<_width)
                  {
                      _triangle[i][medium-k]=255;
                      _triangle[i][medium+k]=255;
                      _triangle[i+1][medium-k]=255;
                      _triangle[i+1][medium+k]=255;
                  }
              }
          }


      for(int j=0;j<_width;j++)
          {
            if(_height>0)
            {
                  _triangle[_height-1][j]=255;
            }
          }

          //_triangle[0][_width/2]=255;



}



//Set
void Triangle::setWidth(int width)
{
    _width=width;
}

void Triangle::setHeight(int height)
{
   _height=height;
}
