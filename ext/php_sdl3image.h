
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_SDL3IMAGE_H
#define PHP_SDL3IMAGE_H 1

#ifdef PHP_WIN32
#define ZEPHIR_RELEASE 1
#endif

#include "kernel/globals.h"

#define PHP_SDL3IMAGE_NAME        "sdl3image"
#define PHP_SDL3IMAGE_VERSION     "0.2.0"
#define PHP_SDL3IMAGE_EXTNAME     "sdl3image"
#define PHP_SDL3IMAGE_AUTHOR      "Project Saturn Studios, LLC"
#define PHP_SDL3IMAGE_ZEPVERSION  "0.19.0-$Id$"
#define PHP_SDL3IMAGE_DESCRIPTION "PHP extension for SDL3_image ? image loading (PNG, JPG, WebP, and more) via SDL3"



ZEND_BEGIN_MODULE_GLOBALS(sdl3image)

	int initialized;

	/** Function cache */
	HashTable *fcache;

	zephir_fcall_cache_entry *scache[ZEPHIR_MAX_CACHE_SLOTS];

	/* Cache enabled */
	unsigned int cache_enabled;

	/* Max recursion control */
	unsigned int recursive_lock;

	
ZEND_END_MODULE_GLOBALS(sdl3image)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(sdl3image)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) ZEND_MODULE_GLOBALS_ACCESSOR(sdl3image, v)
#else
	#define ZEPHIR_GLOBAL(v) (sdl3image_globals.v)
#endif

#ifdef ZTS
	ZEND_TSRMLS_CACHE_EXTERN()
	#define ZEPHIR_VGLOBAL ((zend_sdl3image_globals *) (*((void ***) tsrm_get_ls_cache()))[TSRM_UNSHUFFLE_RSRC_ID(sdl3image_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(sdl3image_globals)
#endif

#define ZEPHIR_API ZEND_API

#define zephir_globals_def sdl3image_globals
#define zend_zephir_globals_def zend_sdl3image_globals

extern zend_module_entry sdl3image_module_entry;
#define phpext_sdl3image_ptr &sdl3image_module_entry

#endif
