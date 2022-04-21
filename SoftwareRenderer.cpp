#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Vec2.h"
#include "Vec3.h"

unsigned char* image;
const int width = 512;
const int height = 512;

void setPixel(int x, int y, const Vec3 &color)
{
    image[(x + width * y) * 3 + 0] = (int)(color.r * 255);
    image[(x + width * y) * 3 + 1] = (int)(color.g * 255);
    image[(x + width * y) * 3 + 2] = (int)(color.b * 255);
}

void triangle(Vec2 corners[3])
{

}


int main()
{
    image = new unsigned char[width * height * 3];
    memset(image, 0, width * height * 3);


    Vec2 corners[3] = {
        Vec2(100,100),
        Vec2(200,200),
        Vec2(500,250)
    };

    triangle(corners);



    stbi_write_png("out.png", width, height, 3, image, width * 3);
#ifdef _WIN32
    ShellExecute(0, 0, L"out.png", 0, 0, SW_SHOW);
#endif
}
