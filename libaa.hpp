#ifndef UUID_C47BF788_0DD4_449A_AF1E_05842174073B
#define UUID_C47BF788_0DD4_449A_AF1E_05842174073B

#include <aalib.h>
#include <cstddef>

namespace libaa {

    using std::size_t;

    class Context
    {
        aa_context *context;
    public:
        Context(size_t width, size_t height)
        {
            aa_hardware_params params = aa_defparams;
            params.width = width;
            params.height = height;
            context = aa_init(&mem_d, &params, NULL);
        }

        ~Context()
        {
            aa_close(context);
        }

        Context(Context&& other)
            :context(other.context)
        {
            other.context = nullptr;
        }

        Context& operator = (Context&& other)
        {   if(this != &other)
            {
                aa_close(context);
                context = other.context;
                other.context = nullptr;
            }
            return *this;
        }

        void resize()
        {
            aa_resize(context);
        }

        void render()
        {
            aa_render(context, &aa_defrenderparams, 0, 0, aa_scrwidth(context), aa_scrheight(context));
        }

        void put_pixel(size_t x, size_t y, int color)
        {
            aa_putpixel(context, x, y, color);
        }

        unsigned char* get_text() const
        {
            return aa_text(context);
        }

        size_t get_img_width() const
        {
            return context->imgwidth;
        }

        size_t get_img_height() const
        {
            return context->imgheight;
        }

        size_t get_scr_width() const
        {
            return aa_scrwidth(context);
        }

        size_t get_scr_height() const
        {
            return aa_scrheight(context);
        }
    };

}

#endif
