// Roots of unit 187: reach libqrencode the way the target does while its one caller there is not written.
// - w187_codifica stands for fn 5502 (13,815 B, stub in api/gui/cqrcodeguard.cpp), the only target function that calls
//   into the library: it calls QRcode_encodeString once, on a std::string's characters. binaryen inlines
//   QRcode_encodeString and every library function with one call site into that caller, in the target as here, and
//   keeps out of line the ones with two or more (the fragment lists them).
// - It passes the constants 5502 does, read from its body: version 0 and QR_ECLEVEL_L (the QRinput it allocates is
//   stored with 0 in both fields), QR_MODE_8 (no Kanji test is left in 5502 or in Split_eat8, fn 5348, which has no
//   hint parameter) and case-sensitive (no copy of the string is upper-cased). The dead-argument pass folds them into the
//   library's functions here as in the target.
#include "qrencode.h"

namespace {

__attribute__((noinline)) QRcode* w187_codifica(const char* texto)
{
    return QRcode_encodeString(texto, 0, QR_ECLEVEL_L, QR_MODE_8, 1);
}

const void* volatile w187_sink;

struct SW187Roots {
    SW187Roots()
    {
        w187_sink = reinterpret_cast<const void*>(&w187_codifica);
    }
} w187_roots;

} // namespace
