#ifndef BMP_H
#define BMP_H
#include "image.h"

#include <map>

class BMP : public Image
{
public:
    BMP();
    BMP(BMP* image);
    BMP(const std::string &pathname);
    bool readImage();
    bool readImage(const std::string &pathname);
    bool read8bits();
    bool read24bits();
    bool writeImage();
    bool writeImage(const std::string &pathname);
    bool writeImage8bits(const std::string &pathname);
    bool writeImage24bits(const std::string &pathname);
    bool convertToBMP24b();
    bool convert8bTo24b();

protected:
    //BMP Informations
    char _signatureImage[2];
    int _offsetImage;
    short int _reservedImage[2];
    short int _bitsPerPixelImage;
    int _sizeHeaderImage;
    short int _numberPlanesImage;
    int _compressionImage;
    int _sizepixelImage;
    int _verticalResolutionImage;
    int _horizontalResolutionImage;
    int _numberColorsImage;
    int _numberImportantColorImage;

    std::map<unsigned char, std::map<unsigned char, std::map<unsigned char,std::map<unsigned char, unsigned char> > > >_correspondancepixelPalette;

};

#endif // BMP_H
