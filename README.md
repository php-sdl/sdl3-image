# php-sdl3-image

[![CI](https://github.com/php-sdl/sdl3-image/actions/workflows/ci.yml/badge.svg)](https://github.com/php-sdl/sdl3-image/actions/workflows/ci.yml)
[![PHP](https://img.shields.io/badge/php-%E2%89%A5%208.2-777bb4?logo=php&logoColor=white)](https://www.php.net)
[![SDL3](https://img.shields.io/badge/SDL3-%E2%89%A5%203.4.0-1d4ed8)](https://www.libsdl.org/)
[![SDL3_image](https://img.shields.io/badge/SDL3__image-%E2%89%A5%203.2-1d4ed8)](https://github.com/libsdl-org/SDL_image)
[![Built with Zephir](https://img.shields.io/badge/built%20with-Zephir-ff6a00)](https://zephir-lang.com/)
[![Platform](https://img.shields.io/badge/platform-linux%20%7C%20macOS-lightgrey)](#requirements)
[![License: MIT](https://img.shields.io/badge/license-MIT-green)](#license)

> PHP extension for SDL3_image — image loading built with [Zephir](https://zephir-lang.com/).

`sdl3image` wraps [SDL3_image](https://github.com/libsdl-org/SDL_image) for
PHP 8.2+, providing image decoding from common formats (PNG, JPG, WebP, and
more) into `SDL_Surface` values, and texture loading into an existing
`SDL_Renderer`.

Pair it with [php-sdl/sdl3](https://github.com/php-sdl/sdl3) for windowing,
renderer creation, and event handling. Both extensions share the `Sdl3*`
namespace prefix and can be loaded side-by-side.

---

## Table of contents

- [Requirements](#requirements)
- [Installation](#installation)
  - [Via PHP PIE (recommended)](#via-php-pie-recommended)
  - [Platform installers](#platform-installers)
  - [Manual build with `phpize`](#manual-build-with-phpize)
- [Verifying the install](#verifying-the-install)
- [Quick start](#quick-start)
- [API reference](#api-reference)
- [Companion extension](#companion-extension)
- [License](#license)

---

## Requirements

| Component            | Minimum version | Notes                                                                                                 |
| -------------------- | --------------- | ----------------------------------------------------------------------------------------------------- |
| PHP                  | 8.2             | ZTS and NTS builds both supported.                                                                    |
| [php-sdl/sdl3]       | any             | **Required for renderer usage.** Provides `SDL_Renderer` and other SDL3 runtime primitives.          |
| SDL3                 | 3.4.0           | C library — must be discoverable via `pkg-config sdl3`.                                               |
| SDL3_image           | 3.2             | C library — must be discoverable via `pkg-config SDL3_image` (or `sdl3-image` / `sdl3_image`).      |
| OS                   | Linux / macOS   | Windows is not currently supported.                                                                   |
| Compiler             | C11 toolchain   | `gcc`, `clang`, or Apple Clang.                                                                       |
| `php-dev` / `phpize` | matches PHP     | Required for any build path.                                                                          |

[php-sdl/sdl3]: https://github.com/php-sdl/sdl3

Tested on macOS (Apple Silicon + Intel), Debian Trixie, Raspberry Pi OS
(arm64 / armhf), and NVIDIA JetPack 6 (Jetson Orin).

---

## Installation

### Via PHP PIE (recommended)

Install [php-sdl/sdl3](https://github.com/php-sdl/sdl3) first, then install this extension:

```bash
pie install php-sdl/sdl3
pie install php-sdl/sdl3-image
```

PIE handles the full build pipeline (`phpize` → `configure` → `make` → `install`).
Make sure SDL3 >= 3.4.0 and SDL3_image >= 3.2 are already installed on the
system before running.

### Platform installers

Three installer scripts live at the repository root. Each one installs SDL3
and SDL3_image if needed, builds the extension with Zephir, and enables it for
detected PHP SAPIs.

**macOS** (Homebrew):

```bash
bash install-macos.sh
```

**Debian Trixie / Raspberry Pi OS** (amd64, arm64, armhf):

```bash
bash install-debian-trixie.sh
```

**JetPack 6 / Ubuntu 22.04** (builds SDL3 + SDL3_image from source):

```bash
bash install-jetpack6.sh
```

Each script writes build output to `./build.log` and prints concise diagnostics
on failure.

### Manual build with `phpize`

If generated C source exists in `ext/`, build without Zephir:

```bash
cd ext
phpize
./configure --enable-sdl3image
make -j"$(nproc 2>/dev/null || sysctl -n hw.logicalcpu)"
sudo make install
```

Then enable the extension:

```ini
; /etc/php/8.4/cli/conf.d/30-sdl3image.ini
extension=sdl3image.so
```

If SDL3 or SDL3_image is installed in a non-standard prefix, export
`PKG_CONFIG_PATH` before `./configure`.

---

## Verifying the install

One-liner sanity check:

```bash
php -m | grep sdl3image
```

Expected output:

```text
sdl3image
```

---

## Quick start

```php
<?php

use Sdl3image\SDLImage\IMG;

$surface = IMG::IMGLoad(__DIR__ . '/assets/logo.png');
if (empty($surface)) {
    fwrite(STDERR, "IMGLoad failed\n");
    exit(1);
}

printf(
    "Loaded image: %dx%d, pitch=%d, pixels=%d\n",
    $surface['w'],
    $surface['h'],
    $surface['pitch'],
    count($surface['pixels']['data'])
);

// Pass $surface['ptr'] into SDL3 renderer APIs from php-sdl/sdl3 as needed.
```

If you already have an `SDL_Renderer` pointer from `php-sdl/sdl3`, you can load
directly into a texture via `IMG::IMGLoadTexture($rendererPtr, $file)`.

---

## API reference

All methods live on:

### `Sdl3image\SDLImage\IMG`

#### `IMGLoad(string $file): array`

Loads an image file and returns an associative array describing an
`SDL_Surface`.

Returns `[]` on failure.

```php
[
    'ptr'      => int,   // SDL_Surface pointer
    'flags'    => int,   // surface flags
    'format'   => int,   // SDL pixel format enum
    'w'        => int,   // width in pixels
    'h'        => int,   // height in pixels
    'pitch'    => int,   // bytes per row
    'pixels'   => [
        'ptr'  => int,   // raw pixel buffer pointer
        'data' => int[], // packed 32-bit pixels in row-major order
    ],
    'refcount' => int,
]
```

#### `IMGLoadTexture(int $renderer, string $file): array`

Loads an image into an `SDL_Texture` for the given renderer pointer.

- `$renderer` is an `SDL_Renderer*` cast to integer, obtained via
  `php-sdl/sdl3`.
- Returns `[]` on failure.

```php
[
    'ptr'      => int,   // SDL_Texture pointer
    'format'   => int,   // SDL pixel format enum
    'w'        => int,   // texture width
    'h'        => int,   // texture height
    'refcount' => int,   // currently fixed to 1
]
```

---

## Companion extension

This extension focuses on image decoding/loading. For window creation, input,
rendering, and the rest of SDL3, install [php-sdl/sdl3](https://github.com/php-sdl/sdl3)
alongside it.

Both extensions can be loaded simultaneously with separate module names
(`sdl3` and `sdl3image`) and no conflict.

---

## License

MIT &copy; Project Saturn Studios, LLC.
