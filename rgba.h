#ifndef RGBA_H
#define RGBA_H

class RGBA
{
public:
    RGBA();
    RGBA(RGBA* palette);
    RGBA(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha);
    RGBA(unsigned char red,unsigned char green,unsigned char blue,unsigned char alpha, int id);

    unsigned char getRed(void) const;
    unsigned char getGreen(void) const;
    unsigned char getBlue(void) const;
    unsigned char getAlpha(void) const;
    unsigned char getGray(void) const;
    int getId(void) const;


    void setRed(const unsigned char & color);
    void setGreen(const unsigned char & color);
    void setBlue(const unsigned char & color);
    void setAlpha(const unsigned char &color);
    void setGray(const unsigned char &color);
    void setId(const int &id);

private:
    unsigned char _red,_green,_blue,_alpha;
    int _id;
};

#endif // RGBA_H
