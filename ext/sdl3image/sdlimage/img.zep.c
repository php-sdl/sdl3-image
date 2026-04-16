
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/operators.h"
#include "kernel/object.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>



ZEPHIR_INIT_CLASS(Sdl3image_SDLImage_IMG)
{
	ZEPHIR_REGISTER_CLASS(Sdl3image\\SDLImage, IMG, sdl3image, sdlimage_img, sdl3image_sdlimage_img_method_entry, 0);

	return SUCCESS;
}

PHP_METHOD(Sdl3image_SDLImage_IMG, IMGLoad)
{
	zval pixels_data, _1;
	zend_long ptr = 0, flags = 0, format = 0, w = 0, h = 0, pitch = 0, pixels_ptr = 0, refcount = 0;
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval *file_param = NULL, _0;
	zval file;

	ZVAL_UNDEF(&file);
	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&pixels_data);
	ZVAL_UNDEF(&_1);
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 1, 0, &file_param);
	zephir_get_strval(&file, file_param);
	
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
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 8, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, flags);
	zephir_array_update_string(return_value, SL("flags"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pitch);
	zephir_array_update_string(return_value, SL("pitch"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_VAR(&_1);
	zephir_create_array(&_1, 2, 0);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, pixels_ptr);
	zephir_array_update_string(&_1, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(&_1, SL("data"), &pixels_data, PH_COPY | PH_SEPARATE);
	zephir_array_update_string(return_value, SL("pixels"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, refcount);
	zephir_array_update_string(return_value, SL("refcount"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();
}

PHP_METHOD(Sdl3image_SDLImage_IMG, IMGLoadTexture)
{
	zephir_method_globals *ZEPHIR_METHOD_GLOBALS_PTR = NULL;
	zval file;
	zval *renderer_param = NULL, *file_param = NULL, _0;
	zend_long renderer, ptr = 0, format = 0, w = 0, h = 0;

	ZVAL_UNDEF(&_0);
	ZVAL_UNDEF(&file);
	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_LONG(renderer)
		Z_PARAM_STR(file)
	ZEND_PARSE_PARAMETERS_END();
	ZEPHIR_METHOD_GLOBALS_PTR = pecalloc(1, sizeof(zephir_method_globals), 0);
	zephir_memory_grow_stack(ZEPHIR_METHOD_GLOBALS_PTR, __func__);
	zephir_fetch_params(1, 2, 0, &renderer_param, &file_param);
	zephir_get_strval(&file, file_param);
	
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
        
	if (ptr == 0) {
		array_init(return_value);
		RETURN_MM();
	}
	zephir_create_array(return_value, 5, 0);
	ZEPHIR_INIT_VAR(&_0);
	ZVAL_LONG(&_0, ptr);
	zephir_array_update_string(return_value, SL("ptr"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, format);
	zephir_array_update_string(return_value, SL("format"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, w);
	zephir_array_update_string(return_value, SL("w"), &_0, PH_COPY | PH_SEPARATE);
	ZEPHIR_INIT_NVAR(&_0);
	ZVAL_LONG(&_0, h);
	zephir_array_update_string(return_value, SL("h"), &_0, PH_COPY | PH_SEPARATE);
	add_assoc_long_ex(return_value, SL("refcount"), 1);
	RETURN_MM();
}

