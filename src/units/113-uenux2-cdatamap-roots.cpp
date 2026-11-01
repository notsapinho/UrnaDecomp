// Roots: api::CDataMap<KeyType, RecordType> (api/io/cdatamap.h), a class template whose users are not reconstructed yet,
// instantiated as the target's records spell it and reached the way the target reaches it. The bodies are the template's
// instances (src/units/README.md, "A body a companion object supplies"). This object compiles at the tree's flags, so no
// match rests on a flag its tree lacks; fragment 113 says what that decides. src/api/'s own objects drop
// -fno-strict-aliasing (src/Makefile UENUX2_TBAA_DIRS); the four bodies this object supplies, 1283, 3697, 3741 and
// 5611, are the same without it (wasm-objdump -d of the object compiled both ways). Each function here has two call
// sites or more, as each has in the target, so binaryen keeps it out of line:
// - GetCurrent, four instantiations: 656 (19 callers), 1200 (7: 2268, 2838, 11972 and 11973 are in the link, 5604, 6999
//   and 11254 wait), 1283 (9), 3125 (4). All four in the link are what makes
//   binaryen form 2919: the second parameter of that body is the pair's second member's offset, 32 or 20.
// - Next, three: 3697 (5604, 11213, 11255), 5601 (12105; 11206 is in the link), 5611 (5604, 11254), which form 3892.
//   The fourth record's instance is inlined into 12105, not instantiated here; nor is CRespostaConsulta's (no record).
// - find<CNumeroInscricaoEleitoral>, 3741 (5725, 10587, 10590), through Find, and the copy of the pair's second member, 3743
//   (5725, 6734, 10590). Nothing here reaches Add over this key: 5725 waits for a real caller (the fragment says why).
// - CRegistradorMesario::Registra, 5378 (10337, twice). Add(KeyType, RecordType), 5377 (5378, 6734), and the insert of
//   the second map, 5379 (5378, 6734): cregistradormesario.cpp's object is ahead of this one on the link line, so its
//   copies are the link's; a stand-in here only adds their second call site.
// - find<CEleitorIdentidade> and __find_equal<CEleitorIdentidade>, 1703 (2225, 2264, 3614, 5378, 10842) and 860 (2805,
//   3728, 5379, 6734, 7787, 10842): no other tree of this key is in our link, and these bodies do not depend on the
//   mapped type, so a std::map<CEleitorIdentidade, int> gives each its second call site, and binaryen merges the copies.
// - comum::CJustificador's constructor, 3742 (1391, 11474, 11475): two call sites, so binaryen keeps it out of line;
//   it stores CJustificadorServico's vptr, the reference the target has to that vtable.
// - CRegistradorMesario::GetInst, 815 (ten callers; 10795, unit 119's slot 7, is in the link), its counts 3606 and 2727
//   (each called by 10795 and two more), and HasInst, 2221 (11616, 12105): ConsultaRegistrador calls GetInst and each
//   count once, beside 10795, and HasInst twice.
// A stand-in goes when the target callers it names are in splat/matched.txt.
#include <map>
#include <new>

#include "api/io/cdatamap.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/dados/celeitordetalhe.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "app/comum/dados/md/cpartido.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"
#include "app/comum/justificativa/cjustificador.h"
#include "app/comum/justificativa/cjustificadordetalhe.h"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

using TMapaEleitores = api::CDataMap<comum::md::CEleitorIdentidade, comum::CEleitorDetalhe>;
using TMapaCandidaturas = api::CDataMap<unsigned int, comum::md::CCandidatura>;
using TMapaPartidos = api::CDataMap<unsigned short, comum::md::CPartido>;
using TMapaRespostas = api::CDataMap<unsigned int, comum::md::CRespostaConsulta>;
using TMapaJustificados = api::CDataMap<ecourna::app::dados::CNumeroInscricaoEleitoral, comum::CJustificadorDetalhe>;
using TComparecimento = comum::md::CComparecimentoMesario;

namespace {

// Stands for the callers of GetCurrent and Next listed above.
template <typename TMapa>
__attribute__((noinline)) bool AvancaUm(TMapa& mapa)
{
    auto* primeiro = mapa.GetCurrent();
    mapa.Next();
    return primeiro == mapa.GetCurrent();
}

template <typename TMapa>
__attribute__((noinline)) bool AvancaDois(TMapa& mapa)
{
    mapa.Next();
    mapa.Next();
    return mapa.GetCurrent() != nullptr;
}

// Stands for 3125's callers 6999 and 11478 (11479 and 12621 are linked).
__attribute__((noinline)) int ComparaRespostas(TMapaRespostas& primeiro, TMapaRespostas& segundo)
{
    return primeiro.GetCurrent() == segundo.GetCurrent() ? 3 : 5;
}

// Stands for 10337.
__attribute__((noinline)) int RegistraDois(comum::CRegistradorMesario& registrador, const TComparecimento& primeiro, const TComparecimento& segundo)
{
    registrador.Registra(primeiro);
    registrador.Registra(segundo);
    return 11;
}

// Stands for the load loop 6734 holds: every row goes in the map, and a row of the section in the second map as well.
__attribute__((noinline)) int CarregaUm(api::CDataMap<comum::md::CComparecimentoMesarioPK, TComparecimento>& mapa,
    std::map<comum::md::CEleitorIdentidade, TComparecimento>& mesariosSecao, const TComparecimento& dado)
{
    mapa.Add(dado, dado);
    if (dado.PertenceSecao()) {
        mesariosSecao.insert({dado.GetMesario(), dado});
    }
    return 13;
}

// Stands for 3614, 2225, 2264 and 10842, which search and insert in other trees of this key.
__attribute__((noinline)) int ContaEleitor(std::map<comum::md::CEleitorIdentidade, int>& mapa, const comum::md::CEleitorIdentidade& eleitor)
{
    if (mapa.find(eleitor) != mapa.end()) {
        return 17;
    }
    mapa[eleitor] = 19;
    return 23;
}

// Stands for 10590's search.
__attribute__((noinline)) bool Justifica(TMapaJustificados& mapa, const ecourna::app::dados::CNumeroInscricaoEleitoral& numero)
{
    return mapa.Find(numero) != nullptr;
}

// Stands for 10587's search.
__attribute__((noinline)) int JustificaDois(TMapaJustificados& mapa, const ecourna::app::dados::CNumeroInscricaoEleitoral& numero)
{
    return mapa.Find(numero) != nullptr ? 29 : 31;
}

// Stand for 6734 and 10590, which copy the detail into the pair they build.
__attribute__((noinline)) int CopiaDetalhe(void* destino, const comum::CJustificadorDetalhe& origem)
{
    new (destino) comum::CJustificadorDetalhe(origem);
    return 37;
}

__attribute__((noinline)) int CopiaDetalheDois(void* primeiro, void* segundo, const comum::CJustificadorDetalhe& origem)
{
    new (primeiro) comum::CJustificadorDetalhe(origem);
    new (segundo) comum::CJustificadorDetalhe(origem);
    return 41;
}

// Stands for 3742's callers, 1391, 11474 and 11475, which build comum::CJustificador's singleton and are not
// reconstructed: two call sites, since binaryen inlines a function called once.
__attribute__((noinline)) int CriaJustificadores(void* primeiro, void* segundo)
{
    new (primeiro) comum::CJustificador();
    new (segundo) comum::CJustificador();
    return 43;
}

// Stands for the callers of CRegistradorMesario::GetInst (fn 815) not in the link, 3614, 5387, 6734, 10313, 10337,
// 10368, 10451, 11616 and 12105 (10795 is); of QuantidadeMesariosInicio (fn 3606), 5387 and 12105, and of
// QuantidadeMesariosFim (fn 2727), 10368 and 12105 (10795 calls both); and of HasInst (fn 2221), 11616 and 12105.
__attribute__((noinline)) int ConsultaRegistrador(std::size_t* quantidades)
{
    const comum::CRegistradorMesario& registrador = comum::CRegistradorMesario::GetInst();
    quantidades[0] = registrador.QuantidadeMesariosInicio();
    quantidades[1] = registrador.QuantidadeMesariosFim();
    return comum::CRegistradorMesario::HasInst() ? 47 : (comum::CRegistradorMesario::HasInst() ? 53 : 59);
}

const void* volatile w113_sink;

struct SW113Roots {
    SW113Roots()
    {
        w113_sink = reinterpret_cast<const void*>(&AvancaUm<TMapaEleitores>);
        w113_sink = reinterpret_cast<const void*>(&AvancaDois<TMapaEleitores>);
        w113_sink = reinterpret_cast<const void*>(&AvancaUm<TMapaCandidaturas>);
        w113_sink = reinterpret_cast<const void*>(&AvancaDois<TMapaCandidaturas>);
        w113_sink = reinterpret_cast<const void*>(&AvancaUm<TMapaPartidos>);
        w113_sink = reinterpret_cast<const void*>(&AvancaDois<TMapaPartidos>);
        w113_sink = reinterpret_cast<const void*>(&ComparaRespostas);
        w113_sink = reinterpret_cast<const void*>(&RegistraDois);
        w113_sink = reinterpret_cast<const void*>(&CarregaUm);
        w113_sink = reinterpret_cast<const void*>(&ContaEleitor);
        w113_sink = reinterpret_cast<const void*>(&Justifica);
        w113_sink = reinterpret_cast<const void*>(&JustificaDois);
        w113_sink = reinterpret_cast<const void*>(&CopiaDetalhe);
        w113_sink = reinterpret_cast<const void*>(&CopiaDetalheDois);
        w113_sink = reinterpret_cast<const void*>(&CriaJustificadores);
        w113_sink = reinterpret_cast<const void*>(&ConsultaRegistrador);
    }
} w113_roots;

} // namespace
