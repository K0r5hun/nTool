#ifndef SHAPES_H
#define SHAPES_H
#include "shape.h"
#include "image.h"
#include <vector>


class Shapes
{
public:
    Shapes();
    Shapes(Image* image);
    bool update();
    bool isIdPresent(int id);
    int whereId(int id);
    int deleteFromSurface(int surface,short int tolerance);
    int getGlobalSurface();

    Image* image;
    std::vector<Shape*> shape;

};

#endif // SHAPES_H
