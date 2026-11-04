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
#include <vector>

#include "asn1.h"
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

// ASN1::CoderEnv::decode over a range of std::vector<char> (target fn 679), the copy of asn1.h's template its callers
// keep, read as uenux2's: no landing pad, and istringstream's constructor inlined where the runtime's -Os decode(const
// char*, ...) calls it. binaryen inlined that decode(const char*, ...) and BERDecoder's constructor into it, each with
// one caller, which src/units/115-asn1-leftovers.mk takes out of the generated roots. Its target callers are
// api::CFileASN's readers inlined into 1937, 2280, 3735, 3755, 3771, 3791, 5706, 5740, 5778, 5825, 7787, 11419, 11517
// and 11905. 3791, comum::IServicoEstado's reader (unit 206), and 11905 (unit 176's) are in our link, and 3791's object
// (app/uenux2/src/app/comum/appinfo/servicos/cservicoestadogeralvota.cpp.o) gives the copy, so the explicit instance
// this file held went: without it 679 matches from that object (steps 7 to 9). 3735, 3771, 5706, 5778 (unit 280),
// 11517, 1937 (unit 110), 5825 (unit 305), 2280 (unit 293, ecourna's DeserializeFromBuffer inlined) and 5740 (unit 89,
// CarregaArquivo<CConversorLocal>'s reader inlined) are in our link too, the others not:
// urna_roots_iconversorasn stands in for them with two calls, each passing defered as false, the constant binaryen
// folded. The iterator type is DecodeObjectFunction's (api/io/asn/cfileasn.h), the begin() and end() of its const
// std::vector<char>&, a chosen spelling: an instance over const char* gave the same function when this file held it.
extern "C" bool urna_decodifica(int, int, int, int, bool) __asm__(
    "_ZN4ASN18CoderEnv6decodeINSt3__211__wrap_iterIPKcEEEEbT_S7_RNS_12AbstractDataEb");

int urna_roots_iconversorasn(int a)
{
    urna_deconverte_foto(a, a + 4, a + 8);
    urna_deconverte_foto(a + 16, a + 4, a + 24);
    bool lido;
    [[clang::noinline]] lido = urna_decodifica(a, a + 4, a + 8, a + 12, false);
    [[clang::noinline]] lido &= urna_decodifica(a + 16, a + 4, a + 8, a + 20, false);
    return a + lido;
}

// comum's IConversorASN<ModuloTiposEleitorais::CodigoCargoConsulta, unsigned char>::Converte, which binaryen inlines into
// its one target caller, comum::asn::CConversorEntidadeBU::DoConverte (fn 10273, unit 321), where its frame opens. The
// target's copy is not the converter's object's: its record (1556668, iconversorasn.h:56) lies with Desconverte's
// (1556684) after app/comum/asn/util.cpp's records and the vtables that object emits, a deferred instance of that
// object (a reading of the data order; no function of util.cpp that uses the cargo code's converter is recovered).
// app/comum/asn/util.cpp's object (unit 96) links after cconversorentidadebu.cpp's in our link, and no earlier object
// instantiates the member.
// Measured in the whole link (pnpm wasm score against the target): with the copy from cconversorentidadebu.cpp's own
// object, 10273 folds the converter's address into the vtable load where the target keeps it in a local, and the
// locals after it are numbered otherwise (831 over 5399 rows, 21 inserted and 22 deleted); with the copy from this
// object, ahead of the trees, 10273 differs in operands only and matches. Why the copy's place decides is a reading
// (binaryen inlines the copy into 10273 and optimizes them in module order). It goes when an object ahead of
// cconversorentidadebu.cpp's on the link line instantiates the member. The instance also brings a weak copy of libc++'s
// basic_ostringstream<char>::str() const & (match 230), and the link takes 230 from this object, ahead of
// app/uenux2/src/app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.cpp.o, whose copy it took without
// the instance (splat/scan.tsv's object column).
#include "app/comum/asn/cconversorcodigocargoconsulta.h"

template ModuloTiposEleitorais::CodigoCargoConsulta
comum::asn::IConversorASN<ModuloTiposEleitorais::CodigoCargoConsulta, unsigned char>::Converte(const unsigned char&) const;
