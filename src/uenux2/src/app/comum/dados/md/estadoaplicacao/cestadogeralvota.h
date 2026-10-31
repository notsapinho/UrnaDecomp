#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/cnumviasimpressasrelatorios.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// What the records of comum::asn::CConversorEstadoGeralVota say: the types' names, and 4 bytes wide in CEstadoGeralVota's
// first two members. That they are declared here is a choice, and so is `: int`, now that they are defined here:
// which formatter body the target uses for them is not read. The enumerators are recovered only where a body compares
// with one and an Assert text names it: EAVIMPRIMIRBU is 61, which vota::CQuerImprimirBU::StartState (target fn 12035)
// compares GetEstadoVota() with before it throws "Assert (poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU)"
// (ledger/strings.tsv 398641). The Assert texts spell them unqualified.
enum EEstadoVota : int {
    EAVIMPRIMIRBU = 61,
};
enum EEstadoEncerramento : int;

} // namespace comum

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

// <stubs>
// f11242 · 10017 B · unmatched · name unknown
// void f11242(i32, i32) { ... }
// </stubs>
