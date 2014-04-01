#include "analysis.h"
#include "triangle.h"

namespace Analysis
{

bool convolutionTriangle(Shapes *shapes)
{

for(int h=0;h<shapes->shape.size();h++)
        {
            shapes->shape[h]->convolution=0;
            Triangle* triangle = new Triangle(shapes->shape[h]->surface);

            for(int i=shapes->shape[h]->ymin;i<=shapes->shape[h]->ymax;i++)
            {
                for(int j=shapes->shape[h]->xmin;j<=shapes->shape[h]->xmax;j++)
                {

                    int k=i-shapes->shape[h]->ymin;
                    int l=j-shapes->shape[h]->xmin;

                    if(k<triangle->getHeight() && l<triangle->getWidth() )
                    {

                        if(triangle->_triangle[k][l]==255 && shapes->image->pixel[i][j]->getId() != 0)
                        { shapes->shape[h]->convolution++;
                            shapes->image->pixel[i][j]->setRed(255);
                            shapes->image->pixel[i][j]->setGreen(0);
                            shapes->image->pixel[i][j]->setBlue(0);



                        }


                    }
                }
           }
           // shapes->shape[h]->surface < (triangle->getHeight()*triangle->getWidth()) ? shapes->shape[h]->convolution/= shapes->shape[h]->surface : shapes->shape[h]->convolution/= (triangle->getHeight()*triangle->getWidth()) ;

            shapes->shape[h]->convolution/= (shapes->shape[h]->surface+(triangle->getHeight()*triangle->getWidth()))/2;
            shapes->shape[h]->convolution*=100;


         }
}

//end namespace Analysis
}

