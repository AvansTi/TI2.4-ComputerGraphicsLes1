#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "Vec2.h"
#include "Vec3.h"
#include "Matrix.h"
#include "ObjModel.h"
#include <cmath>

unsigned char* image;
float* zBuffer;
const int width = 512;
const int height = 512;

Vec3 lightDirection = Vec3(1, 1, 1).normalized();

void setPixel(int x, int y, const Vec3 &color)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;
    image[(x + width * y) * 3 + 0] = (int)(color.r * 255);
    image[(x + width * y) * 3 + 1] = (int)(color.g * 255);
    image[(x + width * y) * 3 + 2] = (int)(color.b * 255);
}

//z value of corners is ignored here, just used for easy calling
Vec3 barycentric(Vec3 corners[3], const Vec2 &p)
{
    Vec3 x(corners[2].x - corners[0].x, corners[1].x - corners[0].x, corners[0].x - p.x);
    Vec3 y(corners[2].y - corners[0].y, corners[1].y - corners[0].y, corners[0].y - p.y);
    Vec3 u = x.cross(y);
    return Vec3(1 - (u.x+u.y)/u.z, u.y / u.z, u.x / u.z);
}


void drawTriangle(Vec3 corners[3], Vec3 normals[3])
{
    Vec2 bbmin(std::min(std::min(corners[0].x, corners[1].x), corners[2].x),
               std::min(std::min(corners[0].y, corners[1].y), corners[2].y));
    Vec2 bbmax(std::max(std::max(corners[0].x, corners[1].x), corners[2].x),
               std::max(std::max(corners[0].y, corners[1].y), corners[2].y));

    if (bbmin.x < 0)
        bbmin.x = 0;
    if (bbmax.x >= width)
        bbmax.x = width;
    if (bbmin.y < 0)
        bbmin.y = 0;
    if (bbmax.y >= height)
        bbmax.y = height;

//    Vec3 color(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX);
    Vec3 color(1, 1, 1);
    for (int x = (int)bbmin.x; x < bbmax.x; x++)
    {
        for (int y = (int)bbmin.y; y < bbmax.y; y++)
        {
            auto bary = barycentric(corners, Vec2((float)x, (float)y));
            if (bary.x < 0 || bary.y < 0 || bary.z < 0)
                continue;

            float z = bary.x * corners[0].z + bary.y * corners[1].z + bary.z * corners[2].z;
            if (z < zBuffer[x + width * y])
                continue;
            zBuffer[x + width * y] = z;

            Vec3 normal = normals[0] * bary.x + normals[1] * bary.y + normals[2] * bary.z;
            normal = normal.normalized();

            float lighting = 0.5f + 0.5f * normal.dot(lightDirection);

            setPixel(x, y, color * lighting);
        }
    }
}


int main()
{
    ObjModel model("suzanne.obj");
    for (int frame = 0; frame < 36; frame++)
    {
        srand(0);
        image = new unsigned char[width * height * 3];
        memset(image, 0, width * height * 3);
        zBuffer = new float[width * height];
        for (int i = 0; i < width * height; i++)
            zBuffer[i] = -99999;


        Mat4 mat = Mat4::rotation((10 * frame) * 3.1415/180, Vec3(0, 1, 0));
        mat = mat * Mat4::scale(Vec3(0.5f, 0.5f, 0.5f));


        Vec3 corners[3] = {
            Vec3(100,500,0),
            Vec3(200,200,0),
            Vec3(500,500,0)
        };
        Vec3 normals[3] = {
            Vec3(100,500,0),
            Vec3(200,200,0),
            Vec3(500,500,0)
        };
        for (const auto& face : model.faces)
        {
            for (int i = 0; i < 3; i++)
            {
                Vec3 pos = model.positions[face.pos[i]];
                pos = mat * pos;
                
                corners[i].x = pos.x * width / 2 + width / 2;
                corners[i].y = pos.y * height / 2 + height / 2;
                corners[i].z = pos.z;
                normals[i] = mat * model.normals[face.normal[i]];
            }
            drawTriangle(corners, normals);

        }



        stbi_flip_vertically_on_write(true);
        stbi_write_png(("out"+std::to_string(frame) + ".png").c_str(), width, height, 3, image, width * 3);
    }
#ifdef _WIN32
    ShellExecute(0, 0, L"out.png", 0, 0, SW_SHOW);
#endif
}
