#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
#include <experimental/filesystem>
#include "libaa.hpp"

using namespace Magick;
using namespace aalib;
using std::size_t;
using namespace std::experimental::filesystem;

int pixel_to_aacolor(Color& color)
{
    double r = sqrt(color.quantumRed());
    double g = sqrt(color.quantumGreen());
    double b = sqrt(color.quantumBlue());
    double a = sqrt(color.quantumAlpha());
    int gray = 0.2126*r + 0.7152*g + 0.0722*b;
    return gray;
}

int main(int args, char * argv[]) {
    Image image(argv[1]);
    Context context(image.columns(), image.rows());
    context.resize();

    for(size_t x = 0; x < context.get_img_width(); ++x)
    {
        for(size_t y = 0; y < context.get_img_height(); ++y)
        {
            Color color = image.pixelColor(x,y);
            context.put_pixel(x, y,pixel_to_aacolor(color));
        }
    }

    context.render();
    unsigned char *text = context.get_text();

    std::ofstream text_stream(argv[2]);
    text_stream.exceptions(std::ios_base::failbit|std::ios_base::badbit);
    text_stream << "<html><br />"
                   "<body bgcolor=\"#000000\" text=\"#b2b2b2\"<br />"
                   "<font color =#b2b2b2 size=2><pre>";
    for(size_t y = 0; y < context.get_scr_height(); ++y)
    {
        for(size_t x = 0; x < context.get_scr_width(); ++x)
        {
            text_stream << text[y*context.get_scr_width() + x];
        }
        text_stream << "<br />";
    }

    text_stream << "</pre></font></body><br />"
                   "</html>";
}
