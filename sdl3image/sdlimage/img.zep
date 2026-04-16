namespace Sdl3image\SDLImage;

%{
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
}%
class IMG
{
    public static function IMGLoad(string file) -> array
    {
        int ptr;
        int flags;
        int format;
        int w;
        int h;
        int pitch;
        int pixels_ptr;
        array pixels_data;
        int refcount;

        %{
            SDL_Surface *surface = IMG_Load(Z_STRVAL(file));

            if (!surface) {
                ptr = 0; flags = 0; format = 0; w = 0; h = 0; pitch = 0; refcount = 0;
            } else {
                ptr      = (zend_long)(uintptr_t) surface;
                flags    = (zend_long) surface->flags;
                format   = (zend_long) surface->format;
                w        = (zend_long) surface->w;
                h        = (zend_long) surface->h;
                pitch    = (zend_long) surface->pitch;
                pixels_ptr = surface->pixels ? (zend_long)(uintptr_t) surface->pixels : 0;
                refcount = (zend_long) surface->refcount;
                array_init(&pixels_data);
                if (surface->pixels) {
                    for (int py = 0; py < surface->h; py++) {
                        Uint32 *row = (Uint32 *)(((Uint8 *)surface->pixels) + py * surface->pitch);
                        for (int px = 0; px < surface->w; px++) {
                            add_next_index_long(&pixels_data, (zend_long)(zend_ulong)row[px]);
                        }
                    }
                }
            }
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "flags": flags, "format": format, "w": w, "h": h, "pitch": pitch, "pixels": ["ptr": pixels_ptr, "data": pixels_data], "refcount": refcount];
    }

    public static function IMGLoadTexture(int renderer, string file) -> array
    {
        int ptr;
        int format;
        int w;
        int h;

        %{
            SDL_Renderer *ren     = (SDL_Renderer *)(uintptr_t) renderer;
            SDL_Texture  *texture = IMG_LoadTexture(ren, Z_STRVAL(file));

            if (!texture) {
                ptr = 0; format = 0; w = 0; h = 0;
            } else {
                ptr = (zend_long)(uintptr_t) texture;

                float fw = 0.0f, fh = 0.0f;
                SDL_GetTextureSize(texture, &fw, &fh);
                w = (zend_long) fw;
                h = (zend_long) fh;

                SDL_PropertiesID props = SDL_GetTextureProperties(texture);
                format = (zend_long) SDL_GetNumberProperty(props, SDL_PROP_TEXTURE_FORMAT_NUMBER, SDL_PIXELFORMAT_UNKNOWN);
            }
        }%

        if ptr == 0 {
            return [];
        }

        return ["ptr": ptr, "format": format, "w": w, "h": h, "refcount": 1];
    }
}
