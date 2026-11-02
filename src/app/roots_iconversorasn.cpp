// ecourna's IConversorASN<ENTIDADE, DADO> members whose target copies are uenux2's: their records name the conan
// package's installed header (p/include/ecourna/api/asn/iconversorasn.hpp, lines 49 and 66), as uenux2's compiles of
// the header do, while ecourna's own converters, the members' other users, emit copies whose records name b/src. Each
// pair is one merge body in the target: Converte for IdentificadorGeradorMidia (3734) and DadosComparecimento (5365)
// call 6031, and Deconverte for IdentificadorGeradorMidia (3733) and Foto (5708) call 6032, each passing its own record
// and typeid name. Their uenux2 callers were not written, and a fragment's roots link after ecourna's objects, which
// would keep their own copies, so this object, ahead of both trees, held them, as src/app/roots_cbasetype.cpp does for
// CBaseType (src/units/README.md "Companion files", the tree roots). It compiles at UENUX2_CXXFLAGS, the tree's own
// flags: what the instances bring is then uenux2's code. Each line goes when a real uenux2 caller instantiates that
// member: IdentificadorGeradorMidia's Converte and Deconverte went with 10290, 10291, 11399 and 11400, and Foto's
// Deconverte with 11440 (fragment 172's objects, which link ahead of ecourna's). DadosComparecimento's Converte stays
// for 11616, not written.
#include "ModuloResultadoUrnaCadastro.h"
#include "ModuloTiposEleitorais.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/resultadournacadastro/cdadoscomparecimento.hpp"

using ecourna::api::asn::IConversorASN;
using ecourna::app::dados::CDadosComparecimento;

template ModuloResultadoUrnaCadastro::DadosComparecimento
IConversorASN<ModuloResultadoUrnaCadastro::DadosComparecimento, CDadosComparecimento>::Converte(
    const CDadosComparecimento&) const;

// Two more copies whose target bodies are uenux2's, for the same 11616: they have no landing pad, and 11616 calls each
// directly, while ecourna's converters reach them only through invoke slots (9094 passes 5842's, 6936; 9052 and 9056
// pass 5846's, 7026), whose own copies have landing pads (pnpm wasm score against ours: 185 over 295 rows and 312 over
// 449). Each goes when a real uenux2 caller instantiates it:
// - vector<CIdentificacaoJustificativa>::__emplace_back_slow_path<CIdentificacaoJustificativa> (5842), which calls
//   __uninitialized_allocator_relocate (5831) directly, as comum::dao::CJustificadorDAO::RecuperarTodos (11469, unit
//   66) does: with ecourna's copy reaching 5831 through a slot, the relocate kept its allocator parameter;
// - CDadosComparecimento's implicit copy constructor (5846), with std::optional<TVectorComparecimentoMesario>'s copy
//   (5832), which it calls twice, and its callee __uninitialized_allocator_copy_impl<CEstadoComparecimento> (2278),
//   which the link now takes from this object instead of ecourna's ccomparecimentosecao.cpp.o, the same code;
//   urna_copia_dados_comparecimento only instantiates it (clang keeps the copy out of line, a call) and leaves the
//   link.
template ecourna::app::dados::CIdentificacaoJustificativa*
std::vector<ecourna::app::dados::CIdentificacaoJustificativa>::__emplace_back_slow_path<
    ecourna::app::dados::CIdentificacaoJustificativa>(ecourna::app::dados::CIdentificacaoJustificativa&&);

void urna_copia_dados_comparecimento(void* destino, const CDadosComparecimento& dados)
{
    ::new (destino) CDadosComparecimento(dados);
}

// Stands in for 5708's target caller comum::asn::CConversorBiometriaEleitor::DoDesconverte (11422), not in our link
// (its other caller, 11440, is): two call sites, since binaryen inlines a function called once
// (docs/reference/facts/tool-traps.md X1), and without one wasm-ld drops the instance and 3733 has no partner to merge
// with.
extern "C" void urna_deconverte_foto(int, int, int) __asm__(
    "_ZNK7ecourna3api3asn13IConversorASNIN21ModuloTiposEleitorais4FotoENS_3app5dados5CFotoEE10DeconverteERKS4_");

int urna_roots_iconversorasn(int a)
{
    urna_deconverte_foto(a, a + 4, a + 8);
    urna_deconverte_foto(a + 16, a + 4, a + 24);
    return a;
}
