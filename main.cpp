#include <cmath>
#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

struct Point
{
    int x{ 0 }, y{ 0 };
    Point(int xIn, int yIn) : x{ xIn }, y{ yIn } {}
};
void drawLine(Point  pointOne, Point pointTwo, TGAImage& frameBuffer, const TGAColor& colorOfLine)
{
    bool steep = std::abs(pointOne.x - pointTwo.x) < std::abs(pointOne.y - pointTwo.y);
    if (steep)
    {
        // Transpose x & y so that steep lines still get filled in
        std::swap(pointOne.x, pointOne.y);
        std::swap(pointTwo.x, pointTwo.y);
    }
    if (pointOne.x > pointTwo.x) // Distance is negative
    {
        std::swap(pointOne, pointTwo); // Swap Points to get have negative dist filled in
    }
    for (int x = pointOne.x; x <= pointTwo.x; x++)
    {
        float t = (x - pointOne.x) / static_cast<float>(pointTwo.x - pointOne.x);
        int y = std::round(pointOne.y + (pointTwo.y - pointOne.y)*t);

        if (!steep)
        {
            frameBuffer.set(x, y, colorOfLine);
        }
        else
        {
            frameBuffer.set(y, x, colorOfLine);
        }

    }
}
int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    int ax =  7, ay =  3;
    int bx = 12, by = 37;
    int cx = 62, cy = 53;

    Point pointOne(ax, ay);
    Point pointTwo(bx, by);
    Point pointThree(cx, cy);

    // Creates lines between points to form triangle
    drawLine(pointOne, pointTwo, framebuffer, red);
    drawLine(pointTwo, pointThree, framebuffer, green);
    drawLine(pointThree, pointOne, framebuffer, blue);

    // Sets intial points to white
    framebuffer.set(ax, ay, white);
    framebuffer.set(bx, by, white);
    framebuffer.set(cx, cy, white);

    framebuffer.write_tga_file("lineTest_FixedDynamicTri_T1.tga");
    return 0;
}