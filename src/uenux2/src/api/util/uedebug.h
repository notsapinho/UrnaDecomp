#pragma once

// Reconstruction's note, not TSE's text: the debug log the vota threads write. No record, symbol or RTTI names any of it:
// the file, its path and every name are chosen.
//
// What the bytes give:
// - Four functions are thunks into one body, target fn 2921 ((format, va_list, priority, int*) -> ()), each passing a
//   constant priority and the address of a 32-bit word of its own whose initial bytes are -1:
//   fn 2072 (7, @1534908, among app/vota/eleitor/cthreadeleitor.cpp's data), fn 3593 (7, @1601364, among
//   app/vota/operador/cthreadoperador.cpp's), fn 5895 (6, @1552472, right after comum::IInterfaceInit's typeinfo
//   @1552464, read as app/comum/iinterfaceinit.cpp's) and fn 5574 (6, @1577092, right after
//   comum::impl::IValidaMidia's typeinfo @1577084, read as app/comum/validamidia/cvalidamidia.cpp's). Each word is
//   touched by its own thunk alone (/usr/bin/grep -rlE 'i32\.const <word>($|[^0-9])' build/out/splat/pieces/asm prints
//   only the thunk's piece). 2921 stores the va_list in its frame
//   first (+156), then: if the word is -1, it sets it to whether access("/dev/urna", 0) returns 0; it reads the word
//   again, and if it is set calls vsyslog (fn 2946) with the priority; else, if getenv("DEBUG_UENUX") is not null,
//   it calls fn 3978 with the address of a local at +16 and then vprintf (fn 3964), each va_list read from +156.
// - 2921 lies among binaryen's merged bodies (fns 2906 to 2920 and 2922 to 2926 match byn$mgfn-shared$ bodies of our
//   link, splat/matched.txt), and our link merges these wrappers the same way, into one body that takes the priority
//   and the word's address: 2921 matches as that merge (byn$mgfn-shared$ over Depura) with all four wrappers in the
//   link. So 2921 is read as binaryen's merge of the four wrappers, each the whole body below.
// - fn 3978 is musl's iprintf (clang's printf of a format with no floating-point conversion; fn 3965, which it calls
//   with stdout, is vfiprintf) with its format folded in: it loads the address 444300 itself, the tail "%s: " of musl's
//   syslog format, and its three callers (2921, 12134 and 13156, api::CPolySingletonList::debug) pass the string
//   argument alone, which binaryen's dead-argument elimination gives when every call passes that format (a reading).
//   So the wrapper prints "%s: " over the local before the message. Nothing in the target fills that local.
//
// The form, measured on scratch copies of one wrapper compiled at the vota flags (-O3 -fPIC):
// - The word's second read: a plain int is read once and kept in a local at -O2, -O3, -Os and -Oz (reloaded at -O1
//   only), while std::atomic<int> is read again after the store, as 2921 is. So the word is written as a
//   std::atomic<int>, the form measured to give the reload (volatile, which the rules exclude, was not tried).
// - The frame: va_start before the word's test stores the va_list first, at +156, the top of a 160-byte frame, and the
//   local at +16 is a char array of 125 to 140 bytes (124 bytes makes the frame 144, 141 bytes 176). With the body in
//   a helper the wrapper calls with the va_list, which clang inlines, the wrapper stores the va_list at +12, under the
//   helper's array: measured with the va_list passed by value and va_copy'd in the helper (a 160-byte frame) and by
//   reference (144). So each wrapper holds the whole body.
// Chosen: the array's size, 128, in that range; its name; that the two wrappers repeat the body rather than share a
// macro; the wrapper and its word being defined here, static inline, so that every TU that calls one has its own copy,
// rather than in each .cpp; the word's being a local static. Depura is the wrapper of priority 7 (LOG_DEBUG),
// DepuraInfo of priority 6 (LOG_INFO): variadic functions, which clang does not inline (-Rpass: "varargs").

#include <atomic>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <syslog.h>
#include <unistd.h>

static inline void Depura(const char* formato, ...)
{
    static std::atomic<int> s_habilitado = -1;
    va_list argumentos;
    va_start(argumentos, formato);
    if (s_habilitado == -1) {
        s_habilitado = access("/dev/urna", F_OK) == 0;
    }
    if (s_habilitado) {
        vsyslog(LOG_DEBUG, formato, argumentos);
    } else if (getenv("DEBUG_UENUX")) {
        char prefixo[128];
        printf("%s: ", prefixo);
        vprintf(formato, argumentos);
    }
    va_end(argumentos);
}

static inline void DepuraInfo(const char* formato, ...)
{
    static std::atomic<int> s_habilitado = -1;
    va_list argumentos;
    va_start(argumentos, formato);
    if (s_habilitado == -1) {
        s_habilitado = access("/dev/urna", F_OK) == 0;
    }
    if (s_habilitado) {
        vsyslog(LOG_INFO, formato, argumentos);
    } else if (getenv("DEBUG_UENUX")) {
        char prefixo[128];
        printf("%s: ", prefixo);
        vprintf(formato, argumentos);
    }
    va_end(argumentos);
}
