#pragma once

#include <format>
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
// they are arrays and not std::array, and the class's members past +500 are not recovered; nothing here constructs
// the class.
class CAppInfoBuilder {
public:
    CAppInfoBuilder& SalvaGeral(bool assina, std::vector<EMidia> midias);
    CAppInfoBuilder& SalvaApps(bool assina, std::vector<EMidia> midias, EUrnaTurno turno, std::vector<EApp> apps);
    CAppInfoBuilder& SalvaApp(bool assina, EFlashOrigem origem, EUrnaTurno turno, EApp app);

private:
    md::estadoaplicacao::CEstadoGeral m_geral;
    md::estadoaplicacao::CEstadoGeralGap m_gap[2];
    md::estadoaplicacao::CEstadoGeralSA m_sa[2];
    md::estadoaplicacao::CEstadoGeralVota m_vota[2];
};

} // namespace comum::teste
