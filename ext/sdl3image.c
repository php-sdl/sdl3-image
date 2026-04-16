
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "sdl3image.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *sdl3image_sdlimage_img_ce;

ZEND_DECLARE_MODULE_GLOBALS(sdl3image)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(sdl3image)
{
	REGISTER_INI_ENTRIES();
	zephir_module_init();
	ZEPHIR_INIT(Sdl3image_SDLImage_IMG);
	
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(sdl3image)
{
	
	zephir_deinitialize_memory();
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_sdl3image_globals *sdl3image_globals)
{
	sdl3image_globals->initialized = 0;

	/* Cache Enabled */
	sdl3image_globals->cache_enabled = 1;

	/* Recursive Lock */
	sdl3image_globals->recursive_lock = 0;

	/* Static cache */
	memset(sdl3image_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);

	
	
}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_sdl3image_globals *sdl3image_globals)
{
	
}

static PHP_RINIT_FUNCTION(sdl3image)
{
	zend_sdl3image_globals *sdl3image_globals_ptr;
	sdl3image_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(sdl3image_globals_ptr);
	zephir_initialize_memory(sdl3image_globals_ptr);

	
	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(sdl3image)
{
	
	zephir_deinitialize_memory();
	return SUCCESS;
}



static PHP_MINFO_FUNCTION(sdl3image)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_SDL3IMAGE_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_SDL3IMAGE_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_SDL3IMAGE_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_SDL3IMAGE_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_SDL3IMAGE_ZEPVERSION);
	php_info_print_table_end();
	
	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(sdl3image)
{
#if defined(COMPILE_DL_SDL3IMAGE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	php_zephir_init_globals(sdl3image_globals);
	php_zephir_init_module_globals(sdl3image_globals);
}

static PHP_GSHUTDOWN_FUNCTION(sdl3image)
{
	
}


zend_function_entry php_sdl3image_functions[] = {
	ZEND_FE_END

};

static const zend_module_dep php_sdl3image_deps[] = {
	
	ZEND_MOD_END
};

zend_module_entry sdl3image_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	php_sdl3image_deps,
	PHP_SDL3IMAGE_EXTNAME,
	php_sdl3image_functions,
	PHP_MINIT(sdl3image),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(sdl3image),
#else
	NULL,
#endif
	PHP_RINIT(sdl3image),
	PHP_RSHUTDOWN(sdl3image),
	PHP_MINFO(sdl3image),
	PHP_SDL3IMAGE_VERSION,
	ZEND_MODULE_GLOBALS(sdl3image),
	PHP_GINIT(sdl3image),
	PHP_GSHUTDOWN(sdl3image),
#ifdef ZEPHIR_POST_REQUEST
	PHP_PRSHUTDOWN(sdl3image),
#else
	NULL,
#endif
	STANDARD_MODULE_PROPERTIES_EX
};

/* implement standard "stub" routine to introduce ourselves to Zend */
#ifdef COMPILE_DL_SDL3IMAGE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(sdl3image)
#endif
