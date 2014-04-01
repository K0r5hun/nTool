#ifndef DETECTION_H
#define DETECTION_H
#include "image.h"
#include "shapes.h"
#include "triangle.h"
#include <vector>

namespace Detection
{
    bool colorById(Image* image);
    bool colorByShape(Shapes* shapes);
    bool colorByConvolution(Shapes* shapes);
    bool giveId(Image* image);
    bool detect(Image* image);

    bool smartDetection(Image* image);

    int getMin(Image* image, int k, int l);
    int getMin2(Image* image, int k, int l);

    void deleteRectangle(Image *image,int size);


}


#endif // DETECTION_H
