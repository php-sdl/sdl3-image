
extern zend_class_entry *sdl3image_sdlimage_img_ce;

ZEPHIR_INIT_CLASS(Sdl3image_SDLImage_IMG);

PHP_METHOD(Sdl3image_SDLImage_IMG, IMGLoad);
PHP_METHOD(Sdl3image_SDLImage_IMG, IMGLoadTexture);

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3image_sdlimage_img_imgload, 0, 1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_sdl3image_sdlimage_img_imgloadtexture, 0, 2, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, renderer, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, file, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(sdl3image_sdlimage_img_method_entry) {
	PHP_ME(Sdl3image_SDLImage_IMG, IMGLoad, arginfo_sdl3image_sdlimage_img_imgload, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Sdl3image_SDLImage_IMG, IMGLoadTexture, arginfo_sdl3image_sdlimage_img_imgloadtexture, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
