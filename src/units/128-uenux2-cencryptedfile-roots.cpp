// Roots: api::CEncryptedFile's members (api/io/cencryptedfile.cpp) whose target callers are not all in the link. Save
// and Write (2767, 2766) need none: the target callers of each are 5736, 5737 and 7174, all in the link
// (comum::CRdv::SalvaExterno and SalvaInterno, fragment 381; vota::impl::CSincronismoVotoEleitor::Sincroniza, unit
// 241).
#include <memory>
#include <string>
#include <vector>

#include "api/io/cencryptedfile.h"

// The destructor and Read (target fns 1691, 3652) have the target callers 5736, 5737, 6734 and 7174 (3652: 6734 and
// 7174). 5736, 5737 (fragment 381) and 7174 (unit 241, which calls Read twice and the destructor four times) are in the
// link: the call of Read and the one of the destructor stand for 6734, not reconstructed yet. The results are dropped,
// as every target caller drops them. Each call goes when the callers it stands for are in the link.
__attribute__((noinline)) void w128_le_grava(api::CEncryptedFile& escrita, api::CEncryptedFile& leitura,
                                             std::vector<uebyte>& lidos)
{
    leitura.Read(lidos);
    std::destroy_at(&escrita);
}

// Load (target fn 3653) has the target callers 6734 and 7174: 7174 (unit 241) is in the link with two call sites, and
// this call stands for 6734, not reconstructed yet. It goes when 6734 is in the link.
__attribute__((noinline)) int w128_carrega(api::CEncryptedFile& arquivo, const std::string& nome)
{
    arquivo.Load(nome);
    return 9;
}

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
        w128_sink = reinterpret_cast<void*>(&w128_le_grava);
        w128_sink = reinterpret_cast<void*>(&w128_carrega);
        w128_sink = reinterpret_cast<void*>(&w128_insere);
    }
} w128_roots;

} // namespace
