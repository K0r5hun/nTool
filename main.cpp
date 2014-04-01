#include <QCoreApplication>
#include <iostream>
#include <QTime>

#include "image.h"
#include "bmp.h"
#include "filter.h"
#include "effect.h"
#include "detection.h"
#include "analysis.h"
#include "shapes.h"
#include "triangle.h"

#define TIMER true
#define PREPROCESSING true
#define DETECTION true
#define ANALYSIS true


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTime tPreprocessing,tDetect,tAnalyse,tMain;
    if(TIMER) tMain.start();

    Image* image=new BMP("img/NT1.bmp");
    image->convertToBMP24b();


    //Preprocessing
    std::cout<<"PREPROCESSING //"<<std::endl;
    if(PREPROCESSING)
    {
        if(TIMER) tPreprocessing.start();


        Effect::contrastColor(image);
       // Detection::deleteRectangle(image,50);
       Effect::tresholdGray(image,150);


        if(TIMER) std::cout<<"-- TIMER : "<<(float)tPreprocessing.elapsed()/1000<<" seconds elapsed"<<std::endl;
    }

    //Detection
    std::cout<<"DETECTION //"<<std::endl;
    if(DETECTION)
    {
        if(TIMER) tDetect.start();

        Detection::giveId(image);
        Detection::detect(image);

        if(TIMER) std::cout<<"-- TIMER : "<<(float)tDetect.elapsed()/1000<<" seconds elapsed"<<std::endl;
    }



    //Analysis
    std::cout<<"ANALYSIS //"<<std::endl;
    if(ANALYSIS)
    {
        if(TIMER) tAnalyse.start();

        Shapes* shapes = new Shapes(image);
        shapes->update();
        shapes->deleteFromSurface(4000,70);
        Analysis::convolutionTriangle(shapes);
        Detection::colorByConvolution(shapes);
        std::cout<<"-- There is "<<shapes->shape.size()<<" shapes"<<std::endl;
        if(TIMER) std::cout<<"-- TIMER : "<<(float)tAnalyse.elapsed()/1000<<" seconds elapsed"<<std::endl;

    }

    image->writeImage();
    if(TIMER) std::cout<<std::endl<<"TIMER MAIN PROJECT: "<<(float)tMain.elapsed()/1000<<" seconds elapsed"<<std::endl;

  //  return a.exec();
}
