#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <vector>


class Triangle
{
public:
    Triangle();
    Triangle(int surface);

   void createTriangle(void);

//get :
    int getWidth(void) const;
    int getHeight(void) const;

//set:
    void setWidth(int cote);
    void setHeight(int height);

    std::vector<std::vector<int> > _triangle;

private:
    int _width;
    int _height;

};

#endif // TRIANGLE_H
