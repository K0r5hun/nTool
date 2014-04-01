#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:

    Shape();
    Shape(int id);
    Shape(int id,int xmin, int xmax, int ymin,int ymax);
    int surface,id,xmin,xmax,ymin,ymax;
    float convolution;
};


#endif // SHAPE_H
