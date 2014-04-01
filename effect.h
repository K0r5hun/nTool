#ifndef EFFECT_H
#define EFFECT_H

#include "image.h"

namespace Effect
{

    bool tresholdGray(Image* image,const int &treshold);
    bool tresholdColor(Image* image,const int &treshold);
    bool tresholdColor(Image* image,const int &tresholdRed,const int &tresholdGreen,const int &tresholdBlue);
    bool contrastGray(Image* image);
    bool contrastColor(Image* image);
    void grayscale(Image* image);
}

#endif // EFFECT_H
