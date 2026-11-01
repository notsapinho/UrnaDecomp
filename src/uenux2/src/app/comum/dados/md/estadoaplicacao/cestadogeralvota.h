#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cnumviasimpressasrelatorios.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// What the records of comum::asn::CConversorEstadoGeralVota say: the types' names, and 4 bytes wide in CEstadoGeralVota's
// first two members. That they are declared here is a choice, and so is `: int`. The values are evidence: the converter's
// ConverteEstadoVota and DesconverteEstadoVota (inlined into target fns 11390 and 11391) map 49 to 64 onto
// ModuloEstadoGeralVota::EstadoVota's values 0 to 15 (inicial to encerrada), refuse 65 as their end marker, and refuse
// EstadoVota's exibealertadesligamento (16), which has no EEstadoVota ("Estado não deve ser usado"); their
// EstadoEncerramento twins map 49 to 52 onto EstadoEncerramento's 0 to 3 and refuse 53. The target's Assert texts spell
// nine EEstadoVota names and three EEstadoEncerramento names (ledger/strings.tsv: EAVINICIAL, EAVGERADADOSDINAMICOS,
// EAVAGUARDAHORAZERESIMA, EAVGERARBU, EAVGERARRELATORIOS, EAVIMPRIMIRBU, EAVGRAVARRESULTADOS, EAVCOPIARESULTADOSMR,
// EAVENCERRADA; EAEIMPRIMIROBRIGATORIABU, EAERETIRAMR, EAEFIMDOSTRABALHOS). EAVIMPRIMIRBU is 61, which
// vota::CQuerImprimirBU::StartState (target fn 12035) compares GetEstadoVota() with before it throws "Assert
// (poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU)" (ledger/strings.tsv 398641). The other eight Assert names are
// placed at the value whose EstadoVota enumerator they spell, a reading; the names no text spells are chosen, after the
// EstadoVota or EstadoEncerramento enumerator of the same value (EAEINICIAL, EAEULTIMOID and EAVULTIMOID too).
enum EEstadoVota : int {
    EAVINICIAL = 49,
    EAVGERADADOSDINAMICOS,
    EAVAGUARDAHORAZERESIMA,
    EAVGERARZE,
    EAVZERESIMAGERADA,
    EAVZERESIMAIMPRESSA,
    EAVREGISTROMESARIOINICIAL,
    EAVVOTAR,
    EAVFIMAQUISICAOVOTOS,
    EAVREGISTROMESARIOFINAL,
    EAVGERARBU,
    EAVGERARRELATORIOS,
    EAVIMPRIMIRBU,
    EAVGRAVARRESULTADOS,
    EAVCOPIARESULTADOSMR,
    EAVENCERRADA,
    EAVULTIMOID,
};
enum EEstadoEncerramento : int {
    EAEINICIAL = 49,
    EAEIMPRIMIROBRIGATORIABU,
    EAERETIRAMR,
    EAEFIMDOSTRABALHOS,
    EAEULTIMOID,
};

} // namespace comum

// The converter's throws pass each enum as a handle on fn 536 (table slots 967 and 966), formatter<unsigned int>'s body,
// as eurna.h's SFormatoEnum gives it.
template <>
struct std::formatter<comum::EEstadoVota> : comum::SFormatoEnum {};
template <>
struct std::formatter<comum::EEstadoEncerramento> : comum::SFormatoEnum {};

namespace comum::md::estadoaplicacao {

// The vota application's state: the fields of ModuloEstadoGeralVota::EstadoGeralVota, as
// comum::asn::CConversorEstadoGeralVota::DoDesconverte (target fn 11391) hands them to the constructor (fn 5628), which
// gives the offsets. A std::optional is what fn 11391 builds for each OPTIONAL field: the value and a flag, as
// `value | 1 << 32` for the 8-byte one. The member names follow the ASN.1 fields; the rest of the class is not
// reconstructed. The four getters that throw when their optional is empty: their records (lines 90, 106, 131 and 159,
// column 19) give the names, the result types and the lines, and the throws inlined in their callers (fns 12105,
// 11242, 12110, 1956, 10566) the codes and the messages; fn 11242 tests the flags at +32 and +48 before 8090 and 8091.
// The test written as `!member` is a choice.
class CEstadoGeralVota {
public:
    CEstadoGeralVota(EEstadoVota estadoVota, EEstadoEncerramento estadoEncerramento, uebyte qtdBU,
                     std::optional<uedword> urnaIdGerouZeresima, std::optional<api::CDateTime> dhIniAquisicao,
                     std::optional<api::CDateTime> dhFimAquisicao, ueword comparecimento, ueword qtdJustificativa,
                     std::optional<api::CDateTime> dhUltimoVoto, bool treinamentoEleitor,
                     CNumViasImpressasRelatorios numViasImpressasRelatorios, std::optional<api::CDateTime> dhEmissao,
                     bool tecladoTestadoPosConversao);
    // GetEstadoVota: twelve Assert texts of the target call it (`vota.GetEstadoVota() == EAVENCERRADA`, ledger/strings.tsv
    // 398594 to 401161), so the name is evidence, and their holders show what it returns: fn 12078 compares the first
    // word of GetVota()'s result with 61 and throws `Assert (vota.GetEstadoVota() == EAVIMPRIMIRBU)` when it differs.
    // Defined in the class: a choice.
    EEstadoVota GetEstadoVota() const { return m_estadoVota; }


    const api::CDateTime& GetDtHrInicioAquisicao() const
    {
        if (!m_dhIniAquisicao) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8090, "Início da aquisição não marcado");
        }
        return *m_dhIniAquisicao;
    }
    // GetQtdBU: the Assert texts name it (`poInfo.GetVota().GetQtdBU() == 0`, ledger/strings.tsv 403041, and three
    // more), and fn 12035 reads the byte at +8 before it throws that text. Defined in the class: a choice.
    uebyte GetQtdBU() const { return m_qtdBU; }
    // The name is chosen: the menu items' slot 3 (fns 12267, 12266, 12259, 12255) read the four bytes at +73 to +76 of
    // GetVota()'s result, the member's CNumViasImpressasRelatorios in that class's order.
    const CNumViasImpressasRelatorios& GetNumViasImpressasRelatorios() const { return m_numViasImpressasRelatorios; }
    bool GetTreinamentoEleitor() const { return m_treinamentoEleitor; }


    const api::CDateTime& GetDtHrFimAquisicao() const
    {
        if (!m_dhFimAquisicao) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8091, "Fim da aquisição não marcado");
        }
        return *m_dhFimAquisicao;
    }
    // GetEstadoEncerramento: four Assert texts name it (`vota.GetEstadoEncerramento() == EAEFIMDOSTRABALHOS`). The
    // getters below are what comum::asn::CConversorEstadoGeralVota::DoConverte (fn 11390) reads, the optionals and the
    // copies' classes by reference; their names are chosen, after the ASN.1 fields.
    EEstadoEncerramento GetEstadoEncerramento() const { return m_estadoEncerramento; }
    const std::optional<uedword>& GetUrnaIdGerouZeresima() const { return m_urnaIdGerouZeresima; }
    const std::optional<api::CDateTime>& GetDhIniAquisicao() const { return m_dhIniAquisicao; }
    const std::optional<api::CDateTime>& GetDhFimAquisicao() const { return m_dhFimAquisicao; }
    ueword GetComparecimento() const { return m_comparecimento; }
    ueword GetQtdJustificativa() const { return m_qtdJustificativa; }
    const std::optional<api::CDateTime>& GetDhUltimoVoto() const { return m_dhUltimoVoto; }
    const std::optional<api::CDateTime>& GetDhEmissao() const { return m_dhEmissao; }
    bool GetTecladoTestadoPosConversao() const { return m_tecladoTestadoPosConversao; }

    // (original lines 123-127: content not recovered)
#line 128
    const api::CDateTime& GetDtHrUltimoVoto() const
    {
        if (!m_dhUltimoVoto) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8092, "Nenhum eleitor votou");
        }
        return *m_dhUltimoVoto;
    }

    // Adds one to the byte at +8, the BU count: target fn 3701, out of line (three callers, the vota states' slots
    // 12065, 12077 and 12081; 12065 calls it on comum::CAppInfo::GetVota()'s result). No record names it; the name is
    // chosen from what it does.
    void IncrementaQtdBU();
    // Sets m_dhIniAquisicao to api::CDateTime::Now() (fn 479) when it is empty: target fn 5627, out of line (a direct
    // caller, fn 5972, which calls it on GetVota()'s result, and table slot 52). No record names it; the name is chosen,
    // after MarcaFimAquisicao and MarcaUltimoVoto, whose records are cestadogeralvota.cpp's (lines 108 to 136).
    void MarcaInicioAquisicao();

    // (original lines 145-155: content not recovered)
#line 156
    const api::CDateTime& GetDtHrEmissaoBU() const
    {
        if (!m_dhEmissao) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8093, "A data/hora da emissão do BU não foi registrada");
        }
        return *m_dhEmissao;
    }

private:
    EEstadoVota m_estadoVota;
    EEstadoEncerramento m_estadoEncerramento;
    uebyte m_qtdBU;
    std::optional<uedword> m_urnaIdGerouZeresima;
    std::optional<api::CDateTime> m_dhIniAquisicao;
    std::optional<api::CDateTime> m_dhFimAquisicao;
    ueword m_comparecimento;
    ueword m_qtdJustificativa;
    std::optional<api::CDateTime> m_dhUltimoVoto;
    bool m_treinamentoEleitor;
    CNumViasImpressasRelatorios m_numViasImpressasRelatorios;
    std::optional<api::CDateTime> m_dhEmissao;
    bool m_tecladoTestadoPosConversao;
};

} // namespace comum::md::estadoaplicacao
