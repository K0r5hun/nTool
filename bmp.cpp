#include "bmp.h"
#include <fstream>
#include <iostream>


BMP::BMP()
{

}

BMP::BMP(BMP *image)
{

}

BMP::BMP(const std::string &pathname)
{
    _pathname=pathname;
    readImage();
}

bool BMP::readImage()
{
    return readImage(_pathname);
}

bool BMP::readImage(const std::string &pathname)
{
    std::ifstream imageFile(pathname.c_str(),std::ios::binary);

/*Read Header Info*/
    imageFile>>_signatureImage[0]>>_signatureImage[1];
    imageFile.read((char*)&_sizeImage,sizeof(_sizeImage));
    imageFile.read((char*)&_reservedImage[0],sizeof(_reservedImage[0]));
    imageFile.read((char*)&_reservedImage[1],sizeof(_reservedImage[0]));
    imageFile.read((char*)&_offsetImage,sizeof(_offsetImage));
    imageFile.read((char*)&_sizeHeaderImage,sizeof(_sizeHeaderImage));
    imageFile.read((char*)&_widthImage,sizeof(_widthImage));
    imageFile.read((char*)&_heightImage,sizeof(_heightImage));
    imageFile.read((char*)&_numberPlanesImage,sizeof(short int));
    imageFile.read((char*)&_bitsPerPixelImage,sizeof(_bitsPerPixelImage));
    imageFile.read((char*)&_compressionImage,sizeof(_compressionImage));
    imageFile.read((char*)&_sizepixelImage,sizeof(_sizepixelImage));
    imageFile.read((char*)&_horizontalResolutionImage,sizeof(_horizontalResolutionImage));
    imageFile.read((char*)&_verticalResolutionImage,sizeof(_verticalResolutionImage));
    imageFile.read((char*)&_numberColorsImage,sizeof(_numberColorsImage));
    imageFile.read((char*)&_numberImportantColorImage,sizeof(_numberImportantColorImage));

    imageFile.close();

    switch(_bitsPerPixelImage)
    {
    case 8:
        return read8bits();
        break;
    case 24:
        return read24bits();
        break;
    default:
        std::cout<<"Format not working with this application"<<std::endl;
        break;
    }
    return false;
}

bool BMP::read8bits()
{
    std::ifstream imageFile(_pathname.c_str(),std::ios::binary);

    //Palette recuperation
    imageFile.seekg(_offsetImage-1024,std::ios::beg);
    unsigned char red,green,blue,alpha,color;
    RGBA* rgba;
    for(int i=0;i<256;i++)
    {
        rgba = new RGBA();
        imageFile.read((char*)&red,sizeof(char));
        imageFile.read((char*)&green,sizeof(char));
        imageFile.read((char*)&blue,sizeof(char));
        imageFile.read((char*)&alpha,sizeof(char));
        rgba->setRed(red);
        rgba->setGreen(green);
        rgba->setBlue(blue);
        rgba->setAlpha(alpha);
        this->palette.push_back(rgba);
        _correspondancepixelPalette[red][green][blue][alpha]=i;

    }
    imageFile.seekg(_offsetImage,std::ios::beg);
    //pixel recuperation

    //Initialisation array first to reverse to order : 0,0 means top left
    this->pixel.resize(this->getHeightImage());
    for(int i=0;i<this->getHeightImage();i++)
    {
        this->pixel[i].resize(this->getWidthImage());
    }


    for(int i=this->getHeightImage()-1;i>=0;i--)
    {
        for(int j=0;j<this->getWidthImage();j++)
        {
        imageFile.read((char*)&color,sizeof(char));
        this->pixel[i][j]=new RGBA(this->palette[color]);
        }
    }

    imageFile.close();
    return false;
}

bool BMP::read24bits()
{
    std::ifstream imageFile(_pathname.c_str(),std::ios::binary);
    unsigned char red,green,blue;

    imageFile.seekg(_offsetImage,std::ios::beg);

    //pixel recuperation
    int rowSize=(this->getWidthImage()*3+3)&(int)0x0FFFFFFFC;

    unsigned char* scanline = new unsigned char[rowSize];


    //Initialisation array first to reverse to order : 0,0 means top left
    this->pixel.resize(this->getHeightImage());
    for(int i=0;i<this->getHeightImage();i++)
    {
        this->pixel[i].resize(this->getWidthImage());
    }




    for(int i=this->getHeightImage()-1;i>=0;i--)
    {
        int k=0;
        imageFile.read((char*)scanline,rowSize);
        for(int j=0;j<this->getWidthImage();j++)
        {
            blue=scanline[k++];
            green=scanline[k++];
            red=scanline[k++];

//        imageFile.read((char*)&blue,sizeof(char));
//        imageFile.read((char*)&green,sizeof(char));
//        imageFile.read((char*)&red,sizeof(char));

        this->pixel[i][j]=new RGBA(red,green,blue,0);
        }
    }



    imageFile.close();
    return false;
}

bool BMP::writeImage()
{
    std::string pathname = _pathname;
    std::string extension = pathname.substr(pathname.find_last_of('.'));
    pathname.insert(pathname.length()-extension.length(),"_saved");
    return  writeImage(pathname);

}

bool BMP::writeImage(const std::string &pathname)
{
    switch(_bitsPerPixelImage)
    {
    case 8:
        writeImage8bits(pathname);
        break;
    case 24:
        writeImage24bits(pathname);
        break;
    default:
        break;
    }
    return false;
}

bool BMP::writeImage8bits(const std::string &pathname)
{

    unsigned char red,green,blue,alpha,color;
    std::ofstream imageFile;
    imageFile.open(pathname.c_str(),std::ofstream::binary);
    //Header Writing
    imageFile<<_signatureImage[0]<<_signatureImage[1];
    imageFile.write((char*)&_sizeImage,sizeof(_sizeImage));
    imageFile.write((char*)&_reservedImage[0],sizeof(_reservedImage[0]));
    imageFile.write((char*)&_reservedImage[1],sizeof(_reservedImage[1]));
    imageFile.write((char*)&_offsetImage,sizeof(_offsetImage));
    //Header Info Writing;
    imageFile.write((char*)&_sizeHeaderImage,sizeof(_sizeHeaderImage));
    imageFile.write((char*)&_widthImage,sizeof(_widthImage));
    imageFile.write((char*)&_heightImage,sizeof(_heightImage));
    imageFile.write((char*)&_numberPlanesImage,sizeof(_numberPlanesImage));
    imageFile.write((char*)&_bitsPerPixelImage,sizeof(_bitsPerPixelImage));
    imageFile.write((char*)&_compressionImage,sizeof(_compressionImage));
    imageFile.write((char*)&_sizepixelImage,sizeof(_sizepixelImage));
    imageFile.write((char*)&_horizontalResolutionImage,sizeof(_horizontalResolutionImage));
    imageFile.write((char*)&_verticalResolutionImage,sizeof(_verticalResolutionImage));
    imageFile.write((char*)&_numberColorsImage,sizeof(_numberColorsImage));
    imageFile.write((char*)&_numberImportantColorImage,sizeof(_numberImportantColorImage));


    //Palette Writing

    for(int i=0;i<256;i++)
    {
        red=palette[i]->getRed();
        green=palette[i]->getGreen();
        blue=palette[i]->getBlue();
        alpha=palette[i]->getAlpha();

        imageFile.write((char*)&blue,sizeof(char));
        imageFile.write((char*)&green,sizeof(char));
        imageFile.write((char*)&red,sizeof(char));

        imageFile.write((char*)&alpha,sizeof(char));
    }


    //pixel Writing
    for(int i=this->getHeightImage()-1;i>=0;i--)
    {

        for(int j=0;j<this->getWidthImage();j++)
        {
            red=pixel[i][j]->getRed();
            green=pixel[i][j]->getGreen();
            blue=pixel[i][j]->getBlue();
            alpha=pixel[i][j]->getAlpha();
            color=_correspondancepixelPalette[red][green][blue][alpha];
            imageFile.write((char*)&color,sizeof(unsigned char));
        }
    }
    imageFile.close();
    return false;
}

bool BMP::writeImage24bits(const std::string &pathname)
{
    unsigned char red,green,blue;
    std::ofstream imageFile;
    imageFile.open(pathname.c_str(),std::ofstream::binary);
     _offsetImage=0;
    //Header Writing
    imageFile<<_signatureImage[0]<<_signatureImage[1];
    imageFile.write((char*)&_sizeImage,sizeof(_sizeImage));
    imageFile.write((char*)&_reservedImage[0],sizeof(_reservedImage[0]));
    imageFile.write((char*)&_reservedImage[1],sizeof(_reservedImage[1]));
    imageFile.write((char*)&_offsetImage,sizeof(_offsetImage));
    //Header Info Writing;
    imageFile.write((char*)&_sizeHeaderImage,sizeof(_sizeHeaderImage));
    imageFile.write((char*)&_widthImage,sizeof(_widthImage));
    imageFile.write((char*)&_heightImage,sizeof(_heightImage));
    imageFile.write((char*)&_numberPlanesImage,sizeof(_numberPlanesImage));
    imageFile.write((char*)&_bitsPerPixelImage,sizeof(_bitsPerPixelImage));
    imageFile.write((char*)&_compressionImage,sizeof(_compressionImage));
    imageFile.write((char*)&_sizepixelImage,sizeof(_sizepixelImage));
    imageFile.write((char*)&_horizontalResolutionImage,sizeof(_horizontalResolutionImage));
    imageFile.write((char*)&_verticalResolutionImage,sizeof(_verticalResolutionImage));
    imageFile.write((char*)&_numberColorsImage,sizeof(_numberColorsImage));
    imageFile.write((char*)&_numberImportantColorImage,sizeof(_numberImportantColorImage));

    //Offset
    unsigned char blank=0;

//    for(int i=0;i<_offsetImage-_sizeHeaderImage;i++)
//        imageFile.write((char*)&blank,sizeof(unsigned char));


    int rowSize=(this->getWidthImage()*3+3)&(int)0x0FFFFFFFC;

    unsigned char* scanline = new unsigned char[rowSize];
    for(int i=0;i<rowSize;i++)
        scanline[i]=0;

    //pixel Writing

    for(int i=this->getHeightImage()-1;i>=0;i--)
    {
        int k=0;
        for(int j=0;j<this->getWidthImage();j++)
        {
            blue=pixel[i][j]->getBlue();
            green=pixel[i][j]->getGreen();
            red=pixel[i][j]->getRed();
            scanline[k++]=blue;
            scanline[k++]=green;
            scanline[k++]=red;
//            imageFile.write((char*)&blue,sizeof(unsigned char));
//            imageFile.write((char*)&green,sizeof(unsigned char));
//            imageFile.write((char*)&red,sizeof(unsigned char));

        }
       imageFile.write((char*)scanline,sizeof(unsigned char)*rowSize);
    }
    imageFile.close();
    return false;
}

bool BMP::convertToBMP24b()
{
    if(_bitsPerPixelImage==8)
        return convert8bTo24b();
    return false;
}

bool BMP::convert8bTo24b()
{
    _bitsPerPixelImage=24;
    _offsetImage=0;
    palette.clear();
    _correspondancepixelPalette.clear();
    return true;
}
