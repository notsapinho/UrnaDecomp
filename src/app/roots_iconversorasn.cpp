// ecourna's IConversorASN<ENTIDADE, DADO> members whose target copies are uenux2's: their records name the conan
// package's installed header (p/include/ecourna/api/asn/iconversorasn.hpp, lines 49 and 66), as uenux2's compiles of
// the header do, while ecourna's own converters, the members' other users, emit copies whose records name b/src. Each
// pair is one merge body in the target: Converte for IdentificadorGeradorMidia (3734) and DadosComparecimento (5365)
// call 6031, and Deconverte for IdentificadorGeradorMidia (3733) and Foto (5708) call 6032, each passing its own record
// and typeid name. Their uenux2 callers (10290 10291 11399 11400; 11422,
// comum::asn::CConversorBiometriaEleitor::DoDesconverte by its record, and 11440; 11616) are not written, and a
// fragment's roots link after ecourna's objects, which would keep their own copies, so this object, ahead of both
// trees, holds them, as src/app/roots_cbasetype.cpp does for CBaseType (src/units/README.md "Companion files", the tree
// roots). It compiles at UENUX2_CXXFLAGS, the tree's own flags: what the instances bring is then uenux2's code. Each
// line goes when a real uenux2 caller instantiates that member.
#include "ModuloResultadoUrnaCadastro.h"
#include "ModuloTiposEcoUrna.h"
#include "ModuloTiposEleitorais.h"
#include "ecourna/api/asn/iconversorasn.hpp"
#include "ecourna/app/dados/cfoto.hpp"
#include "ecourna/app/dados/cidentificadorgeradormidia.hpp"
#include "ecourna/app/dados/resultadournacadastro/cdadoscomparecimento.hpp"

using ecourna::api::asn::IConversorASN;
using ecourna::app::dados::CDadosComparecimento;
using ecourna::app::dados::CFoto;
using ecourna::app::dados::CIdentificadorGeradorMidia;

template ModuloTiposEcoUrna::IdentificadorGeradorMidia
IConversorASN<ModuloTiposEcoUrna::IdentificadorGeradorMidia, CIdentificadorGeradorMidia>::Converte(
    const CIdentificadorGeradorMidia&) const;
template ModuloResultadoUrnaCadastro::DadosComparecimento
IConversorASN<ModuloResultadoUrnaCadastro::DadosComparecimento, CDadosComparecimento>::Converte(
    const CDadosComparecimento&) const;
template CIdentificadorGeradorMidia
IConversorASN<ModuloTiposEcoUrna::IdentificadorGeradorMidia, CIdentificadorGeradorMidia>::Deconverte(
    const ModuloTiposEcoUrna::IdentificadorGeradorMidia&) const;
template CFoto IConversorASN<ModuloTiposEleitorais::Foto, CFoto>::Deconverte(const ModuloTiposEleitorais::Foto&) const;

// Stands in for 5708's target callers, comum::asn::CConversorBiometriaEleitor::DoDesconverte (11422) and 11440, neither
// in our link: two call sites, since binaryen inlines a function called once (docs/reference/facts/tool-traps.md X1),
// and without one wasm-ld drops the instance and 3733 has no partner to merge with.
extern "C" void urna_deconverte_foto(int, int, int) __asm__(
    "_ZNK7ecourna3api3asn13IConversorASNIN21ModuloTiposEleitorais4FotoENS_3app5dados5CFotoEE10DeconverteERKS4_");

int urna_roots_iconversorasn(int a)
{
    urna_deconverte_foto(a, a + 4, a + 8);
    urna_deconverte_foto(a + 16, a + 4, a + 24);
    return a;
}
