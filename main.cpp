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
void drawLine(const Point&  pointOne,  const Point& pointTwo, TGAImage& frameBuffer, const TGAColor& colorOfLine)
{
    float t{ 0.f };
    while (t < 1.f)
    {
        int currentX = std::round(pointOne.x + t * (pointTwo.x - pointOne.x));
        int currentY = std::round(pointOne.y + t * (pointTwo.y - pointOne.y));

        frameBuffer.set(currentX, currentY, colorOfLine);
        t += .01;
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

    framebuffer.write_tga_file("lineTest_01Percent.tga");
    return 0;
}