﻿#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
#include <experimental/filesystem>
#include "libaa.hpp"
#include <string>

using namespace Magick;
using namespace aalib;
using std::size_t;
using namespace std::experimental::filesystem;

void print_text_to_file(unsigned char* text, Context& context, std::string directory)
{
    try
    {
        std::ofstream text_stream(directory + std::string("ascii.html"));
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
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

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
    //Image image("../IMG_to_ASCII/sources/a.png");
    if(args < 3)
    {
        std::cout << "Write directory and image name" << '\n';
        return 0;
    }
    try
    {
        std::string directory(argv[1]);
        std::string image_name(argv[2]);
        Image image(directory + image_name);
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
        print_text_to_file(text, context, directory);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
