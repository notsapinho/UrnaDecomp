// Roots: api::CEncryptedFile::Save (api/io/cencryptedfile.cpp), whose target callers 5736, 5737 and 7174 are not
// reconstructed yet. The target calls it directly from those three, so it needs two call sites here for binaryen to keep
// it out of line; w128_salva calls it twice. It goes when those callers are in splat/matched.txt.
#include <memory>
#include <string>
#include <vector>

#include "api/io/cencryptedfile.h"

__attribute__((noinline)) void w128_salva(const api::CEncryptedFile& arquivo, const std::string& nome, const std::string& copia)
{
    arquivo.Save(nome);
    arquivo.Save(copia);
}

// The destructor, Write and Read (target fns 1691, 2766, 3652) have the target callers 5736, 5737, 6734 and 7174
// (2766: 5736, 5737 and 7174; 3652: 6734 and 7174), none reconstructed yet: two call sites each here, since binaryen
// inlines a function called once. The results are dropped, as every target caller drops them. It goes when those
// callers are in splat/matched.txt.
__attribute__((noinline)) void w128_le_grava(api::CEncryptedFile& escrita, api::CEncryptedFile& leitura,
                                             const std::vector<uebyte>& dados, std::vector<uebyte>& lidos)
{
    escrita.Write(dados);
    escrita.Write(lidos);
    leitura.Read(lidos);
    leitura.Read(lidos);
    std::destroy_at(&escrita);
    std::destroy_at(&leitura);
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
        w128_sink = reinterpret_cast<void*>(&w128_salva);
        w128_sink = reinterpret_cast<void*>(&w128_le_grava);
        w128_sink = reinterpret_cast<void*>(&w128_insere);
    }
} w128_roots;

} // namespace
