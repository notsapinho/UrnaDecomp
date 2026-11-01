#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cnumviasimpressasrelatorios.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
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
// `value | 1 << 32` for the 8-byte one. The member names follow the ASN.1 fields; the records' getters (lines 90, 106, 131
// and 159 here) and the rest of the class are not reconstructed.
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
    // GetQtdBU: the Assert texts name it (`poInfo.GetVota().GetQtdBU() == 0`, ledger/strings.tsv 403041, and three
    // more), and fn 12035 reads the byte at +8 before it throws that text. Defined in the class: a choice.
    uebyte GetQtdBU() const { return m_qtdBU; }
    // The name is chosen: the menu items' slot 3 (fns 12267, 12266, 12259, 12255) read the four bytes at +73 to +76 of
    // GetVota()'s result, the member's CNumViasImpressasRelatorios in that class's order.
    const CNumViasImpressasRelatorios& GetNumViasImpressasRelatorios() const { return m_numViasImpressasRelatorios; }
    bool GetTreinamentoEleitor() const { return m_treinamentoEleitor; }
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
    // Adds one to the byte at +8, the BU count: target fn 3701, out of line (three callers, the vota states' slots
    // 12065, 12077 and 12081; 12065 calls it on comum::CAppInfo::GetVota()'s result). No record names it; the name is
    // chosen from what it does.
    void IncrementaQtdBU();

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
