PHP_ARG_ENABLE(sdl3image, whether to enable sdl3image, [ --enable-sdl3image   Enable Sdl3image])

if test "$PHP_SDL3IMAGE" = "yes"; then

	dnl GCC 14 promoted several long-standing warnings to hard errors by default.
	dnl Zephir-generated C code trips these in dead-code paths that are
	dnl runtime-safe and have built cleanly on gcc <= 13 and clang for years.
	dnl Each flag is silently ignored by compilers that don't know it.
	CFLAGS="$CFLAGS -Wno-error=incompatible-pointer-types -Wno-error=int-conversion -Wno-error=implicit-function-declaration -Wno-error=implicit-int"

	dnl ── SDL3 + SDL3_image via pkg-config ────────────────────────────────────
	AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
	if test "x$PKG_CONFIG" = "xno"; then
		AC_MSG_ERROR([pkg-config not found. Install pkg-config and try again.])
	fi

	dnl SDL3 core
	AC_MSG_CHECKING([for sdl3])
	if $PKG_CONFIG --exists sdl3 2>/dev/null; then
		SDL3_CFLAGS=$($PKG_CONFIG --cflags sdl3)
		SDL3_LIBS=$($PKG_CONFIG --libs sdl3)
		AC_MSG_RESULT([yes ($($PKG_CONFIG --modversion sdl3))])
	else
		dnl Fallback: assume SDL3 is in the standard search paths
		SDL3_CFLAGS="-I/opt/homebrew/include -I/usr/local/include"
		SDL3_LIBS="-lSDL3"
		AC_MSG_RESULT([not found via pkg-config, using fallback paths])
	fi

	dnl SDL3_image — may be registered under several pc names depending on how it was built
	AC_MSG_CHECKING([for sdl3_image])
	SDL3IMAGE_FOUND=no
	for pc_name in SDL3_image sdl3-image sdl3_image; do
		if $PKG_CONFIG --exists $pc_name 2>/dev/null; then
			SDL3IMAGE_CFLAGS=$($PKG_CONFIG --cflags $pc_name)
			SDL3IMAGE_LIBS=$($PKG_CONFIG --libs $pc_name)
			SDL3IMAGE_FOUND=yes
			AC_MSG_RESULT([yes ($($PKG_CONFIG --modversion $pc_name) via $pc_name)])
			break
		fi
	done
	if test "x$SDL3IMAGE_FOUND" = "xno"; then
		dnl Fallback: assume SDL3_image is in the standard search paths
		SDL3IMAGE_CFLAGS="-I/opt/homebrew/include -I/usr/local/include"
		SDL3IMAGE_LIBS="-lSDL3_image"
		AC_MSG_RESULT([not found via pkg-config, using fallback paths])
	fi

	dnl Merge include and link flags
	ALL_CFLAGS="$SDL3_CFLAGS $SDL3IMAGE_CFLAGS"
	ALL_LIBS="$SDL3_LIBS $SDL3IMAGE_LIBS"

	dnl Wire the libs into the build
	PHP_EVAL_LIBLINE($ALL_LIBS, SDL3IMAGE_SHARED_LIBADD)

	AC_DEFINE(HAVE_SDL3IMAGE, 1, [Whether you have Sdl3image])
	sdl3image_sources="sdl3image.c kernel/main.c kernel/memory.c kernel/exception.c kernel/debug.c kernel/backtrace.c kernel/object.c kernel/array.c kernel/string.c kernel/fcall.c kernel/require.c kernel/file.c kernel/operators.c kernel/math.c kernel/concat.c kernel/variables.c kernel/filter.c kernel/iterator.c kernel/time.c kernel/exit.c sdl3image/sdlimage/img.zep.c "
	PHP_NEW_EXTENSION(sdl3image, $sdl3image_sources, $ext_shared,, $ALL_CFLAGS)
	PHP_ADD_BUILD_DIR([$ext_builddir/kernel/])
	for dir in "sdl3image/sdlimage"; do
		PHP_ADD_BUILD_DIR([$ext_builddir/$dir])
	done
	PHP_SUBST(SDL3IMAGE_SHARED_LIBADD)

	old_CPPFLAGS=$CPPFLAGS
	CPPFLAGS="$CPPFLAGS $INCLUDES"

	AC_CHECK_DECL(
		[HAVE_BUNDLED_PCRE],
		[
			AC_CHECK_HEADERS(
				[ext/pcre/php_pcre.h],
				[
					PHP_ADD_EXTENSION_DEP([sdl3image], [pcre])
					AC_DEFINE([ZEPHIR_USE_PHP_PCRE], [1], [Whether PHP pcre extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	AC_CHECK_DECL(
		[HAVE_JSON],
		[
			AC_CHECK_HEADERS(
				[ext/json/php_json.h],
				[
					PHP_ADD_EXTENSION_DEP([sdl3image], [json])
					AC_DEFINE([ZEPHIR_USE_PHP_JSON], [1], [Whether PHP json extension is present at compile time])
				],
				,
				[[#include "main/php.h"]]
			)
		],
		,
		[[#include "php_config.h"]]
	)

	CPPFLAGS=$old_CPPFLAGS

	PHP_INSTALL_HEADERS([ext/sdl3image], [php_SDL3IMAGE.h])

fi
