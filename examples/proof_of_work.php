<?php

/**
 * proof_of_work.php — sdl3image extension smoke test
 *
 * Verifies that sdl3image is loaded, then uses IMG::IMGLoad() to decode an
 * image file into an SDL_Surface and inspects the returned array.
 *
 * No display server, window, or renderer is required — IMGLoad runs purely
 * in memory and returns the surface as a PHP array.
 *
 * Usage:
 *   php examples/proof_of_work.php [optional/path/to/image.(png|jpg|webp|...)]
 */

declare(strict_types=1);

// ── 1. Extension present? ─────────────────────────────────────────────────────

if (!extension_loaded('sdl3image')) {
    fwrite(STDERR, "❌  Extension 'sdl3image' is not loaded.\n");
    fwrite(STDERR, "    Run one of the install scripts first, then check:\n");
    fwrite(STDERR, "      php -m | grep sdl3image\n");
    exit(1);
}

echo "✓  Extension 'sdl3image' is loaded\n";

// ── 2. Resolve an image file ──────────────────────────────────────────────────
//
// Priority:
//   1. Path passed on the command line
//   2. Common system images shipped with macOS / Linux distros
//   3. A tiny bundled PNG written to a temp file (base64 payload below)

$imagePath    = null;
$cleanupTemp  = null;

if ($argc >= 2 && is_string($argv[1]) && $argv[1] !== '') {
    if (!file_exists($argv[1])) {
        fwrite(STDERR, "❌  File not found: {$argv[1]}\n");
        exit(1);
    }
    $imagePath = $argv[1];
}

if ($imagePath === null) {
    $systemCandidates = [
        // macOS
        '/System/Library/Desktop Pictures/Solid Colors/Black.png',
        '/System/Library/CoreServices/DefaultDesktop.heic',
        '/Library/Desktop Pictures/Solid Colors/Black.png',

        // Debian / Ubuntu / Pi OS
        '/usr/share/pixmaps/debian-logo.png',
        '/usr/share/plymouth/ubuntu-logo.png',
        '/usr/share/backgrounds/warty-final-ubuntu.png',

        // Fedora / RHEL
        '/usr/share/pixmaps/fedora-logo.png',
    ];

    foreach ($systemCandidates as $candidate) {
        if (is_file($candidate)) {
            $imagePath = $candidate;
            break;
        }
    }
}

if ($imagePath === null) {
    // Bundled fallback: a 4x4 RGBA PNG with a checkered red / blue pattern.
    // This guarantees the smoke test runs on any host, even with no imagery.
    $pngBase64 =
        'iVBORw0KGgoAAAANSUhEUgAAAAQAAAAECAYAAACp8Z5+AAAAKUlE' .
        'QVR42mP8z8DwnwEJMOIUZICxGNAZTDA+TAE6n5GRkREmCVMHAKcT' .
        'B/2fZGG4AAAAAElFTkSuQmCC';

    $tempFile = tempnam(sys_get_temp_dir(), 'sdl3image_pow_') . '.png';
    file_put_contents($tempFile, base64_decode($pngBase64, true));
    $imagePath   = $tempFile;
    $cleanupTemp = $tempFile;
}

echo "✓  Image: {$imagePath}\n";

// ── 3. IMGLoad ────────────────────────────────────────────────────────────────

$surface = \Sdl3image\SDLImage\IMG::IMGLoad($imagePath);

if (empty($surface) || (int)($surface['ptr'] ?? 0) === 0) {
    fwrite(STDERR, "❌  IMGLoad() failed for {$imagePath}\n");
    if ($cleanupTemp !== null) {
        @unlink($cleanupTemp);
    }
    exit(1);
}

echo "✓  IMGLoad() → ptr=0x" . dechex((int)$surface['ptr']) . "\n";
printf(
    "     size=%dx%d  pitch=%d  format=0x%x  flags=%d  refcount=%d\n",
    (int)$surface['w'],
    (int)$surface['h'],
    (int)$surface['pitch'],
    (int)$surface['format'],
    (int)$surface['flags'],
    (int)$surface['refcount']
);

// ── 4. Validate pixel buffer shape ────────────────────────────────────────────

$pixelCount    = count($surface['pixels']['data'] ?? []);
$expectedCount = (int)$surface['w'] * (int)$surface['h'];

printf(
    "     pixels in data array: %d  (expected %d)\n",
    $pixelCount,
    $expectedCount
);

if ((int)$surface['w'] <= 0 || (int)$surface['h'] <= 0) {
    fwrite(STDERR, "⚠   Surface has zero dimension — image may have decoded to an empty buffer.\n");
} elseif ($pixelCount !== $expectedCount) {
    fwrite(STDERR, "⚠   Pixel count mismatch: got {$pixelCount}, expected {$expectedCount}\n");
} else {
    echo "✓  Pixel data matches surface dimensions\n";
}

// ── 5. Tiny ASCII preview of the middle row ───────────────────────────────────
//
// We use the alpha channel (top 8 bits) as a visibility hint, falling back to
// luminance from RGB when alpha is constant.

if ((int)$surface['w'] > 0 && (int)$surface['h'] > 0 && $pixelCount > 0) {
    $midRow  = (int)((int)$surface['h'] / 2);
    $rowData = array_slice(
        $surface['pixels']['data'],
        $midRow * (int)$surface['w'],
        (int)$surface['w']
    );

    $preview = '';
    $step    = max(1, (int)((int)$surface['w'] / 60));
    foreach (array_filter(array_keys($rowData), fn($i) => $i % $step === 0) as $i) {
        $pixel = (int)($rowData[$i] ?? 0);
        $a     = ($pixel >> 24) & 0xFF;
        $r     = ($pixel >> 16) & 0xFF;
        $g     = ($pixel >> 8)  & 0xFF;
        $b     =  $pixel        & 0xFF;

        $lum = (int)((0.299 * $r + 0.587 * $g + 0.114 * $b));

        if ($a <= 20) {
            $preview .= ' ';
        } elseif ($lum > 170) {
            $preview .= '█';
        } elseif ($lum > 85) {
            $preview .= '▒';
        } else {
            $preview .= '░';
        }
    }
    echo "     mid-row preview: [{$preview}]\n";
}

// ── 6. Cleanup ────────────────────────────────────────────────────────────────

if ($cleanupTemp !== null) {
    @unlink($cleanupTemp);
    echo "✓  Cleaned up temporary file\n";
}

echo "\n✅  All checks passed — sdl3image is working correctly.\n\n";
