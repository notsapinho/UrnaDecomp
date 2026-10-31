// Roots: api::CDataMap<KeyType, RecordType> (api/io/cdatamap.h), a class template whose users are not reconstructed yet,
// instantiated as the target's records spell it and reached the way the target reaches it. The bodies are the template's
// instances (src/units/README.md, "A body a companion object supplies"). This object compiles without the tree's
// -fno-strict-aliasing, which fragment 113 measures member by member. Each function here has two call sites or more, as
// each has in the target, so binaryen keeps it out of line:
// - GetCurrent, four instantiations: 656 (19 callers), 1200 (7), 1283 (9), 3125 (4). All four in the link are what makes
//   binaryen form 2919: the second parameter of that body is the pair's second member's offset, 32 or 20.
// - Next, three: 3697 (5604, 11213, 11255), 5601 (11206, 12105), 5611 (5604, 11254), which form 3892. The fourth record's
//   instance is inlined into 12105 and is not instantiated here, nor is a Next for CRespostaConsulta, which has no record.
// - Add(value_type) for CNumeroInscricaoEleitoral, 5725 (6734, 10590), through the inline Add(KeyType, RecordType), which
//   clang inlines as those two callers show. 5725 stays here on purpose: the fragment says why.
// - CRegistradorMesario::Registra, 5378 (10337, twice). Add(KeyType, RecordType), 5377 (5378, 6734), and the insert of
//   the second map, 5379 (5378, 6734): cregistradormesario.cpp's object is ahead of this one on the link line, so its
//   copies are the link's; a stand-in here only adds their second call site.
// - find<CEleitorIdentidade> and __find_equal<CEleitorIdentidade>, 1703 (2225, 2264, 3614, 5378, 10842) and 860 (2805,
//   3728, 5379, 6734, 7787, 10842): no other tree of this key is in our link, and these bodies do not depend on the
//   mapped type, so a std::map<CEleitorIdentidade, int> gives each its second call site, and binaryen merges the copies.
// A stand-in goes when the target callers it names are in splat/matched.txt.
#include <map>

#include "api/io/cdatamap.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/dados/celeitordetalhe.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "app/comum/dados/md/cpartido.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"
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

// Stands for 3125's callers (6999, 11478, 11479, 12621).
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

// Stands for 10590, which searches and then adds, or throws with the cursor on the key.
__attribute__((noinline)) bool Justifica(TMapaJustificados& mapa, const ecourna::app::dados::CNumeroInscricaoEleitoral& numero, ueword ano)
{
    if (mapa.Find(numero) != nullptr) {
        return false;
    }
    mapa.Add(numero, comum::CJustificadorDetalhe(ano));
    return true;
}

// Stands for 6734's other loop, which adds with no search.
__attribute__((noinline)) int JustificaDois(TMapaJustificados& mapa, const ecourna::app::dados::CNumeroInscricaoEleitoral& numero, ueword ano)
{
    mapa.Add(numero, comum::CJustificadorDetalhe(ano + 1));
    return ano + 9;
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
    }
} w113_roots;

} // namespace
