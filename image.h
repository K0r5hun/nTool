#ifndef IMAGE_H
#define IMAGE_H

#include "vector"
#include "string"

#include "rgba.h"

class Image
{
public:

    //Methods
    Image();
    Image(const std::string &pathname);
    Image(Image* src);
    virtual bool readImage()=0;
    virtual bool readImage(const std::string &pathname)=0;
    virtual bool writeImage()=0;
    virtual bool writeImage(const std::string &pathname)=0;
    virtual bool convertToBMP24b()=0;

    //Get
    std::string getPathname(void) const;
    int getSizeImage(void) const;
    int getWidthImage(void) const;
    int getHeightImage(void) const;

    //Set
    void setPathname(std::string const & pathname);
    void setSizeFile(int sizeImage);

    //Static
    static bool isBMP(std::string pathname);
    static std::vector<std::vector<RGBA*> > copypixel(std::vector<std::vector<RGBA*> > pixel);
    static bool shareSameId(std::vector<std::vector<RGBA*> > pixel1,std::vector<std::vector<RGBA*> > pixel2);

    //Variables
    std::vector<std::vector<RGBA*> > pixel;
    std::vector<RGBA*> palette;

protected:
    std::string _pathname;
    int _sizeImage;
    int _widthImage;
    int _heightImage;
};

#endif // IMAGE_H
