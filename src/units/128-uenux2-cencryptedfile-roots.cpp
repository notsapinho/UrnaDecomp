// Roots: api::CEncryptedFile's members (api/io/cencryptedfile.cpp) need no stand-in: the target callers of Save and
// Write (2767, 2766) are 5736, 5737 and 7174; of the destructor (1691) 5736, 5737, 6734 and 7174; of Read and Load
// (3652, 3653) 6734 and 7174; all are in the link (comum::CRdv::SalvaExterno and SalvaInterno, fragment 381;
// vota::CEstadoAudio::CarregaEleitores, fragment 386; vota::impl::CSincronismoVotoEleitor::Sincroniza, unit 241),
// and the stand-ins that called the last three for 6734 went with it. What is left is a table address.
#include <memory>
#include <string>
#include <vector>

#include "api/io/cencryptedfile.h"

// std::vector<uebyte>'s range insert, which Save calls (target fn 1927), is in the target's table (slot 6666) besides its
// five direct callers (2767, 5360, 10967, 11397, 11399): its address is taken here, so binaryen keeps it out of line and
// keeps its result, as the target's table entry does. cencryptedfile.cpp's object instantiates it, and binaryen merges
// that copy with std::vector<char>'s, which unit 124's cconversorestadogeral.cpp.o links first (fragment 128): the label
// only refers to it.
extern "C" int w128_insere(int, int, int, int, int) __asm__(
    "_ZNSt3__26vectorIhNS_9allocatorIhEEE18__insert_with_sizeB8ne210108INS_11__wrap_iterIPKhEES8_EENS5_IPhEES8_T_T0_l");

namespace {

void* volatile w128_sink;

struct SW128Roots {
    SW128Roots()
    {
        w128_sink = reinterpret_cast<void*>(&w128_insere);
    }
} w128_roots;

} // namespace
