#include "shape.h"

Shape::Shape()
{
    surface=0;
}

Shape::Shape(int pId)
{
    surface=1;
    id=pId;
}

Shape::Shape(int pId, int pXmin, int pXmax, int pYmin, int pYmax)
{
    surface=1;
    id=pId;
    xmin=pXmin;
    xmax=pXmax;
    ymin=pYmin;
    ymax=pYmax;
}
