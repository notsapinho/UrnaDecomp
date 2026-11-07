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
// throws, "GetGeral", "GetVota" and "GetGap", are the evidence for those three names, and IndiceTurno is a record's;
// TemVota (fn 2841) passes "TemVota" to IndiceTurno, and its name is read from that literal, a reading. GetInst
// is evidence too: the target holds the text of `Assert (comum::CAppInfo::GetInst().GetVota().GetEstadoVota() == EAVENCERRADA)`
// (ledger/strings.tsv, 401161). That text and nine like it call GetVota() with no argument, and all 86 direct calls of fn 261
// pass 51, TURNO_ATUAL, so GetVota's parameter defaults to it; that the const overload does too is read from its callers'
// folded 51 (fn 903). The data members' names are not in the target. The word at +528 is -1 until CarregaGeral (fn 11572)
// sets it to 0, so its name and type are chosen; the rest of the class is not reconstructed.
class CAppInfo {
public:
    static CAppInfo& GetInst();

    CAppInfo();
    ~CAppInfo();

    md::estadoaplicacao::CEstadoGeral& GetGeral();
    const md::estadoaplicacao::CEstadoGeral& GetGeral() const;
    md::estadoaplicacao::CEstadoGeralVota& GetVota(EUrnaTurno turno = TURNO_ATUAL);
    const md::estadoaplicacao::CEstadoGeralVota& GetVota(EUrnaTurno turno = TURNO_ATUAL) const;
    // The non-const overload: vota::IQRCodeBUDS::GeraPartes (inlined into target fn 1956) holds GetEstado's non-const
    // instance for CEstadoGeralGap (record cappinfo.cpp:42) inlined, through this one. Out of line here, a choice.
    md::estadoaplicacao::CEstadoGeralGap& GetGap(EUrnaTurno turno);
    const md::estadoaplicacao::CEstadoGeralGap& GetGap(EUrnaTurno turno) const;
    std::vector<std::string> GetCodigosCarga(EUrnaTurno turno) const;
    bool TemVota(EUrnaTurno turno) const;
    // Target fns 3790 and 3789, thunks of 6039, binaryen's merge of the two (they differ in the origin and the name they
    // pass to IndiceTurno). Those literals are the evidence for the names; that they are const members is chosen.
    void SalvaVotaInterno() const;
    void SalvaVotaExterno() const;
    // The general state's save to each flash: vota::CSincronizaVota::SincronizaEstadoGeral (fn 3333), their one caller,
    // holds each inlined by binaryen behind a 16-byte stack frame of its own: when m_geral holds a value, a
    // comum::CServicoEstadoGeral of that origin (fn 1941, 0 then 1) saves it (fn 3592). They read the private m_geral
    // and its flag (+180) with no call, so they are members; their names, after SalvaVotaInterno's, and their being
    // const are chosen.
    void SalvaGeralInterno() const;
    void SalvaGeralExterno() const;
    // Target fn 2273: the general state read anew from the internal flash, a comum::CServicoEstadoGeral of origin 0 (fn
    // 1941) and its Carrega (fn 3791). It reads nothing of the object, and binaryen drops the unused this; that it is a
    // member is read from a caller: comum::CRelUtil::IncluiCabecalhoEleicoesMZS (fn 1543) calls CAppInfo::GetInst (fn
    // 185) and discards its result right before the call. Its name, after SalvaGeralInterno's, its const and its place
    // in cappinfo.cpp are chosen.
    md::estadoaplicacao::CEstadoGeral LeGeralInterno() const;
    // Target fn 11572, which votaInit (fn 7840) invokes through table slot 34 on GetInst's result: the word at +528 set
    // to 0, then m_geral assigned the general state read from the internal flash (fns 1941 and 3791, LeGeralInterno's
    // code, held inlined), the optional's assignment inlined. Its name, after LeGeralInterno's, and its place in
    // cappinfo.cpp are chosen.
    void CarregaGeral();
    // The general state of the internal flash: the one held when m_geral is set and the word at +528 is 0, a copy of
    // GetGeral()'s, else LeGeralInterno's. Fn 5740 holds it with no frame of its own (the copy goes to the caller's
    // frame): CAppInfo::GetInst once for the two tests, GetInst again for GetGeral (fn 291), and LeGeralInterno (fn
    // 2273) called on the first one's result. It reads private members, so it is a member. Out of line in cappinfo.cpp,
    // clang inlines LeGeralInterno into it, the CServicoEstadoGeral in a 16-byte frame of its own where 5740 calls 2273
    // (measured in the whole link: 5740's inserted rows); inline here, 2273 stays a call. Its name, its being static, the
    // local reference and the test's spelling are chosen; what the word at +528 holds is not known.
    static md::estadoaplicacao::CEstadoGeral GetGeralInterno()
    {
        const CAppInfo& appInfo = GetInst();
        if (appInfo.m_geral && appInfo.m_turnoCarregado == 0) {
            return GetInst().GetGeral();
        }
        return appInfo.LeGeralInterno();
    }

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
