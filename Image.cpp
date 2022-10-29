#include "image.h"
#include <iostream>
#include <fstream>
Color::Color()
    :r(0),g(0),b(0)
{

}

Color::Color(float r,float g,float b)
    :r(r),g(g),b(b)
{

}

Color::~Color(){

}

Image::Image(int width,int height)
    :m_width(width),m_height(height),m_colors(std::vector <Color> (width*height))
{

}

Image::~Image(){

}

Color Image::GetColor(int x,int y) const{
    return m_colors[y*m_width+x];
}

void Image::SetColor(const Color &color, int x, int y) {
    m_colors[y*m_width+x].r=color.r;
    m_colors[y*m_width+x].g=color.g;
    m_colors[y*m_width+x].b=color.b;
}

void Image::Export(const char *path) const {
    std::ofstream f;
    f.open(path,std::ios::out | std::ios::binary);
    unsigned char bmpPad[3]={0,0,0};
    const int PaddingCount=((4-(m_width*3)%4)%4);
    const int FileHeaderSize=14;
    const int InformationHeaderSize=40;
    const int FileSize=FileHeaderSize+InformationHeaderSize+m_width*m_height*3+PaddingCount*m_height;

    unsigned char fileHeader[FileHeaderSize];

    fileHeader[0]='B';
    fileHeader[1]='M';

    fileHeader[2]=FileSize;
    fileHeader[3]=FileSize>>8;
    fileHeader[4]=FileSize>>16;
    fileHeader[5]=FileSize>>24;

    fileHeader[6]=0;
    fileHeader[7]=0;
    fileHeader[8]=0;
    fileHeader[9]=0;

    fileHeader[10]=FileHeaderSize+InformationHeaderSize;
    fileHeader[11]=0;
    fileHeader[12]=0;
    fileHeader[13]=0;

    unsigned char InformationHeader[InformationHeaderSize];

    InformationHeader[0]=InformationHeaderSize;
    InformationHeader[1]=0;
    InformationHeader[2]=0;
    InformationHeader[3]=0;

    InformationHeader[4]=m_width;
    InformationHeader[5]=m_width>>8;
    InformationHeader[6]=m_width>>16;
    InformationHeader[7]=m_width>>24;

    InformationHeader[8]=m_height;
    InformationHeader[9]=m_height>>8;
    InformationHeader[10]=m_height>>16;
    InformationHeader[11]=m_height>>24;

    InformationHeader[12]=1;
    InformationHeader[13]=0;
    InformationHeader[14]=24;
    InformationHeader[15]=0;
    InformationHeader[16]=0;
    InformationHeader[17]=0;
    InformationHeader[18]=0;
    InformationHeader[19]=0;
    InformationHeader[20]=0;
    InformationHeader[21]=0;
    InformationHeader[22]=0;
    InformationHeader[23]=0;
    InformationHeader[24]=0;
    InformationHeader[25]=0;
    InformationHeader[26]=0;
    InformationHeader[27]=0;
    InformationHeader[28]=0;
    InformationHeader[29]=0;
    InformationHeader[30]=0;
    InformationHeader[31]=0;
    InformationHeader[32]=0;
    InformationHeader[33]=0;
    InformationHeader[34]=0;
    InformationHeader[35]=0;
    InformationHeader[36]=0;
    InformationHeader[37]=0;
    InformationHeader[38]=0;
    InformationHeader[39]=0;

    f.write(reinterpret_cast<char*>(fileHeader),FileHeaderSize);
    f.write(reinterpret_cast<char*>(InformationHeader),InformationHeaderSize);

    for(int y=0;y<m_height;++y){
        for(int x=0;x<m_width;++x){
            unsigned char r= static_cast<unsigned char> (GetColor(x,y).r*255.0f);
            unsigned char g= static_cast<unsigned char> (GetColor(x,y).g*255.0f);
            unsigned char b= static_cast<unsigned char> (GetColor(x,y).b*255.0f);

            unsigned char color []={b,g,r};

            f.write(reinterpret_cast<char*>(color),3);
        }
        f.write(reinterpret_cast<char*>(bmpPad),PaddingCount);
    }
    //free(fileHeader);
    //free(InformationHeader);
    f.close();

}


