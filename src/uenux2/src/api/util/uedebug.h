#pragma once

// Reconstruction's note, not TSE's text: the debug log the vota threads write. No record, symbol or RTTI names any of it:
// the file, its path and every name are chosen.
//
// What the bytes give:
// - Four functions are thunks into one body, target fn 2921 ((format, va_list, priority, int*) -> ()), each passing a
//   constant priority and the address of a 32-bit word of its own whose initial bytes are -1:
//   fn 2072 (7, @1534908, among app/vota/eleitor/cthreadeleitor.cpp's data), fn 3593 (7, @1601364, among
//   app/vota/operador/cthreadoperador.cpp's), fn 5895 (6, @1552472) and fn 5574 (6, @1577092). 2921 stores the va_list
//   in its frame first, then: if the word is -1, it sets it to whether access("/dev/urna", 0) returns 0; if the word is
//   set, vsyslog (fn 2946) with the priority; else, if getenv("DEBUG_UENUX") is not null, vprintf (fn 3964).
// - 2921 lies among binaryen's merged bodies (fns 2906 to 2920 and 2922 to 2926 match byn$mgfn-shared$ bodies of our
//   link, splat/matched.txt), and our link does the same with these two wrappers: clang inlines DepuraV into each
//   (-Rpass=inline: cost 195, threshold 325), and binaryen merges the two into one body that takes the word's address.
//   So 2921 is read as binaryen's merge of the four wrappers, each holding DepuraV, with the priority and the word as
//   the parameters that differ. Ours merges only the two of priority 7 (the wrappers of priority 6 are not written), so
//   its body takes no priority, and 2072, 3593 and 2921 do not match.
// - Not written: before the vprintf, 2921 calls fn 3978, printf over the tail "%s: " of musl's syslog format, with the
//   address of a 140-byte local that nothing in the target fills (the same as api::CPolySingletonList::debug, fn 13156,
//   api/pattern/cpolysingletonlist.h). Without it the body differs from 2921 even once the merge is the target's.
// - Depura is each TU's wrapper of priority 7 (LOG_DEBUG): a variadic function, which clang does not inline (-Rpass:
//   "varargs"), with a word of its own. That the wrapper and its word are defined here, static inline, so that every TU
//   that calls it has its own, rather than in each .cpp, is chosen; so is the word's being a local static.

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

#include <syslog.h>
#include <unistd.h>

namespace api {

inline void DepuraV(const char* formato, va_list argumentos, int prioridade, int* habilitado)
{
    va_list copia;
    va_copy(copia, argumentos);
    if (*habilitado == -1) {
        *habilitado = access("/dev/urna", F_OK) == 0;
    }
    if (*habilitado) {
        vsyslog(prioridade, formato, copia);
    } else if (getenv("DEBUG_UENUX")) {
        vprintf(formato, copia);
    }
    va_end(copia);
}

} // namespace api

static inline void Depura(const char* formato, ...)
{
    static int s_habilitado = -1;
    va_list argumentos;
    va_start(argumentos, formato);
    api::DepuraV(formato, argumentos, LOG_DEBUG, &s_habilitado);
    va_end(argumentos);
}
