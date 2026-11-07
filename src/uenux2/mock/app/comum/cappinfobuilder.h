#pragma once

#include <format>
#include <string>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralsa.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/eflashorigem.h"
#include "app/comum/eurnaturno.h"

namespace comum::teste {

// The media and the applications a test writes the urna's state files for. The records of CAppInfoBuilder's members
// name both types (std::vector<EMidia>, std::vector<EApp>, EApp), unqualified as they print EUrnaTurno. The values are
// evidence: the converter of a media (target fn 5344) refuses 2 and above and returns 0 and 1 as the EFlashOrigem it
// is, and SalvaApp (inlined into fn 10212) switches on 0, 1 and 2 to the gap's files, the apuracao's and the vota
// application's. That they are scoped enums is chosen, from the media's message: it formats the value as an int
// (fn 9935, its handle, calls __formatter_integer<char>::format<int>, fn 5924, where EUrnaTurno's handle 9868 calls the
// unsigned one, 5906). The enumerators' names, this namespace and this header's path are chosen.
enum class EMidia {
    INTERNA,
    EXTERNA,
};

enum class EApp {
    GAP,
    SA,
    VOTA,
};

} // namespace comum::teste

// The media's converter passes the value through table slot 468, the handle of target fn 9935, whose parse and format
// are __formatter_integer<char>'s, the format of an int. The base and the cast are chosen.
template <>
struct std::formatter<comum::teste::EMidia> : std::formatter<int> {
    template <typename FormatContext>
    auto format(comum::teste::EMidia midia, FormatContext& contexto) const
    {
        return std::formatter<int>::format(static_cast<int>(midia), contexto);
    }
};

namespace comum::teste {

// A test's builder of the urna's state: it saves the states it holds into each media's files, through the services of
// app/comum/appinfo/servicos/, and writes a stand-in signature file beside each when asked. RTTI does not name it (no
// vtable); the records name the class, its namespace and three members (cappinfobuilder.cpp lines 112, 277 and 287).
// The data members are evidence by their offsets and strides: SalvaGeral (fn 10243) copies the general state from +0,
// and SalvaApp (inlined into fn 10212) indexes by the turn the gap's state at +180 (44 bytes each), the apuracao's at
// +268 (16) and the vota application's at +300 (100), the sizes of the md::estadoaplicacao classes. Their names, that
// they are arrays and not std::array are chosen. The class is 500 bytes: votaInit (target fn 7840, in
// wasm/vota_web/vota_web_wasm.cpp) builds one in its frame from +16 to +516, and its destructor (fn 5644, implicit)
// destroys the gap states and the general one.
//
// What votaInit calls, each through a table slot it invokes but the two inline ones: the constructor (fn 10268), which
// default-constructs the states (their defaults, in md/estadoaplicacao/, are what it stores and calls: fns 10261 and
// 10278 for the correspondence and the gap states) and then stores the PE at +4; SetFase, SetTurno, SetTipoUrna and
// SetLocalidade (fns 10197, 10188, 10181 and 10176: one or more stores each, returning the object); SetUF and
// PreparaVotacao, whose code votaInit holds (std::string's operator= on +8, and four stores into the vota states:
// EAVINICIAL and the training flag, at +300, +372, +400 and +472); and SalvaTudo (fn 10256), which calls SalvaGeral
// (slot 414) and the two turns' SalvaAppsTurno1 and SalvaAppsTurno2 (fns 10242 and 10239, thunks of binaryen's 6004
// with 49 and 50, slots 416 and 417) on the result, each with a copy of the media (fn 2720) and TodosApps (fn 10286,
// slot 415). The members write the states' members directly, so the class is a friend of the classes they write, a
// choice. Every name but the records' is chosen, and so are the parameters' types where a store's width allows more.
class CAppInfoBuilder {
public:
    explicit CAppInfoBuilder(uedword idPE);

    CAppInfoBuilder& SetFase(EUrnaFase fase);
    CAppInfoBuilder& SetTurno(EUrnaTurno turno);
    CAppInfoBuilder& SetTipoUrna(EUrnaTipo tipo);
    CAppInfoBuilder& SetLocalidade(uedword municipio, ueword zona, ueword secao);
    void SetUF(const std::string& uf) { m_geral.m_dadoLocal.m_uf = uf; }
    void PreparaVotacao(bool treinamentoEleitor)
    {
        for (md::estadoaplicacao::CEstadoGeralVota& vota : m_vota) {
            vota.m_estadoVota = EAVINICIAL;
            vota.m_treinamentoEleitor = treinamentoEleitor;
        }
    }

    CAppInfoBuilder& SalvaTudo(bool assina, std::vector<EMidia> midias);
    CAppInfoBuilder& SalvaGeral(bool assina, std::vector<EMidia> midias);
    CAppInfoBuilder& SalvaAppsTurno1(bool assina, std::vector<EMidia> midias, std::vector<EApp> apps);
    CAppInfoBuilder& SalvaAppsTurno2(bool assina, std::vector<EMidia> midias, std::vector<EApp> apps);
    CAppInfoBuilder& SalvaApps(bool assina, std::vector<EMidia> midias, EUrnaTurno turno, std::vector<EApp> apps);
    CAppInfoBuilder& SalvaApp(bool assina, EFlashOrigem origem, EUrnaTurno turno, EApp app);

private:
    md::estadoaplicacao::CEstadoGeral m_geral;
    md::estadoaplicacao::CEstadoGeralGap m_gap[2];
    md::estadoaplicacao::CEstadoGeralSA m_sa[2];
    md::estadoaplicacao::CEstadoGeralVota m_vota[2];
};

// The applications, gap's, apuracao's and vota's, that SalvaTudo saves in each turn: target fn 10286, a function its
// two calls reach through table slot 415. Its name and its being a free function are chosen.
std::vector<EApp> TodosApps();

} // namespace comum::teste
