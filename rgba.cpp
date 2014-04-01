#include "rgba.h"

RGBA::RGBA()
{
}

RGBA::RGBA(RGBA *palette)
{
    _red=palette->getRed();
    _green=palette->getGreen();
    _blue=palette->getBlue();
    _alpha=palette->getAlpha();
}

RGBA::RGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    _red=red;
    _green=green;
    _blue=blue;
    _alpha=alpha;
    _id=0;
}
RGBA::RGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha,int id)
{
    _red=red;
    _green=green;
    _blue=blue;
    _alpha=alpha;
    _id=id;
}

unsigned char RGBA::getRed() const
{
    return _red;
}

unsigned char RGBA::getGreen() const
{
    return _green;
}

unsigned char RGBA::getBlue() const
{
    return _blue;
}

unsigned char RGBA::getAlpha() const
{
    return _alpha;
}

unsigned char RGBA::getGray() const
{
    return (_red == _green && _red== _blue) ? _red : 0.2125*_red+0.7154*_green+0.0721*_blue ;
}

int RGBA::getId() const
{
    return _id;
}
void RGBA::setRed(const unsigned char &color)
{
    _red=color;
}

void RGBA::setGreen(const unsigned char &color)
{
    _green=color;
}
void RGBA::setBlue(const unsigned char &color)
{
    _blue=color;
}
void RGBA::setAlpha(const unsigned char &color)
{
    _alpha=color;
}

void RGBA::setGray(const unsigned char &color)
{
    _red=color;
    _green=color;
    _blue=color;
}

void RGBA::setId(const int &id)
{
    _id=id;
}
