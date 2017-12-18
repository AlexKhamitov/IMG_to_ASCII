#include <iostream>
#include <fstream>
#include <Magick++.h>
#include <cmath>
#include <experimental/filesystem>
#include "libaa.hpp"
#include <string>

using namespace Magick;
using namespace libaa;
using namespace std::experimental::filesystem;


const char* int_to_color(int int_color)
{
    switch (int_color) {
    case 0:
        return "<font color=\"#b2b2b2\">";
    case 1:
        return "<font color=\"#686868\">";
    case 2:
        return "<font color=\"#ffffff\">";
    case 3:
        return "<font color=\"#ff0000\">";
    case 4:
        return "<font color=\"#ff0000\">";
    case 5:
        return "<font color=\"#ff0000\">";
    default:
        return "<font color=\"#ff0000\">";
    }
}

void print_text_to_file(const unsigned char* text,
                        const unsigned char* int_colors,
                        Context& context,
                        std::string image_name)
{
    try
    {
        int current_int_color = int_colors[0];
        std::ofstream text_stream(image_name + std::string("-ascii.html"));
        text_stream.exceptions(std::ios_base::failbit|std::ios_base::badbit);
        text_stream << "<html><br />"
                       "<body bgcolor=\"#000000\" text=\"#b2b2b2\"<br />"
                       "<font color =#b2b2b2 size=2><pre>"
                    << int_to_color(current_int_color);
        for(std::size_t y = 0; y < context.get_img_height(); ++y)
        {
            for(std::size_t x = 0; x < context.get_img_width(); ++x)
            {
                std::size_t index = y*context.get_img_width() + x;
                text_stream << text[index];
                int int_color = int_colors[index];
                if(int_color != current_int_color)
                {
                    current_int_color = int_color;
                    text_stream << "</font>" << int_to_color(current_int_color);
                }
            }
            text_stream << "<br />";
        }

        text_stream << "</font></pre></font></body><br />"
                       "</html>";
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        exit(1);
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
    if(args != 3 || argv[2][0] != '.')
    {
        std::cout << "Usage: program_name image_name image_extension" << '\n';
        return 1;
    }
    try
    {
        std::string image_name(argv[1]);
        std::string image_extension(argv[2]);
        Image image;
        image.read(image_name + image_extension);
        Context context(image.columns(), image.rows());
        context.resize();

        for(std::size_t y = 0; y < context.get_img_height(); ++y)
        {
            for(std::size_t x = 0; x < context.get_img_width(); ++x)
            {
                Color color = image.pixelColor(x,y);
                context.put_pixel(x, y,pixel_to_aacolor(color));
            }
        }

        context.render();
        const unsigned char *text = context.get_text();
        const unsigned char *int_colors = context.get_attributes();

        print_text_to_file(text ,int_colors, context, image_name);
        std::cout << "Result: " << image_name << "-ascii.html" << '\n';
    }
    catch(std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
