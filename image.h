#include <vector>
#include <string>

#ifndef LABWORK3_IMAGE_H
#define LABWORK3_IMAGE_H

#endif //LABWORK3_IMAGE_H

#pragma once
struct Color{
    float r,g,b;
    Color();
    Color(float r,float g, float b);
    ~Color();
};

class Image{
public:
    Image(int width,int height);
    ~Image();

    Color GetColor(int x,int y) const;
    void SetColor(const Color& color,int x,int y);

    void Export(const char*  path) const;
private:
    int m_width;
    int m_height;
    std::vector <Color> m_colors;

};

