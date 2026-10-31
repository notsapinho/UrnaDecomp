#pragma once

#include <cstddef>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralsa.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/eurnaturno.h"

namespace comum {

// The application's states, one per turn where there are two. Recovered: the layout, 532 bytes, from the constructor and
// destructor (target fns 5813, 3792), and that the accessor allocates it (fn 185). The literals the accessors pass to their
// throws, "GetGeral", "GetVota" and "GetGap", are the evidence for those three names, and IndiceTurno is a record's. GetInst
// is evidence too: the target holds the text of `Assert (comum::CAppInfo::GetInst().GetVota().GetEstadoVota() == EAVENCERRADA)`
// (ledger/strings.tsv, 401161). That text and nine like it call GetVota() with no argument, and all 86 direct calls of fn 261
// pass 51, TURNO_ATUAL, so GetVota's parameter defaults to it; that the const overload does too is read from its callers'
// folded 51 (fn 903). The data members' names are not in the target. The word at +528 is -1 until something not reconstructed
// sets it, so its name and type are chosen; the rest of the class is not reconstructed.
class CAppInfo {
public:
    static CAppInfo& GetInst();

    CAppInfo();
    ~CAppInfo();

    md::estadoaplicacao::CEstadoGeral& GetGeral();
    const md::estadoaplicacao::CEstadoGeral& GetGeral() const;
    md::estadoaplicacao::CEstadoGeralVota& GetVota(EUrnaTurno turno = TURNO_ATUAL);
    const md::estadoaplicacao::CEstadoGeralVota& GetVota(EUrnaTurno turno = TURNO_ATUAL) const;
    const md::estadoaplicacao::CEstadoGeralGap& GetGap(EUrnaTurno turno) const;
    std::vector<std::string> GetCodigosCarga(EUrnaTurno turno) const;

    static bool EhTreinamentoEleitor();

private:
    static std::unique_ptr<CAppInfo> s_inst;
    static std::mutex s_mutex;

    static size_t IndiceTurno(const std::string& nome, EUrnaTurno turno);

    std::optional<md::estadoaplicacao::CEstadoGeral> m_geral;
    std::optional<md::estadoaplicacao::CEstadoGeralGap> m_gap[2];
    std::optional<md::estadoaplicacao::CEstadoGeralVota> m_vota[2];
    std::optional<md::estadoaplicacao::CEstadoGeralSA> m_sa[2];
    int m_turnoCarregado = -1;
};

std::string GetIdentificacaoUrna();

} // namespace comum
