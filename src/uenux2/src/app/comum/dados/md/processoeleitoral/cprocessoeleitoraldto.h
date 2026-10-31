#pragma once

#include <optional>
#include <string>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/cpleitodto.h"
#include "app/comum/dados/md/processoeleitoral/eorigemconfiguracao.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum::md {

// Recovered: the layout, 92 bytes, from comum::asn::CConversorProcessoEleitoral::DoDesconverte (target fn 11363), which
// holds both constructors: a word at +0, the name at +4, a byte at +16, the configuration's origin at +20, a CPleitoDTO
// at +24, a std::optional<CPleitoDTO> at +48 with its flag at +72, the principal identifier's type at +76 and a vector
// of the identifiers' types at +80. 11363 builds the two branches with two constructors: one copies a second pleito
// into the optional and sets the flag, the other leaves the optional empty; both copy the pleitos and the name, and
// move the vector they take by value. Out of line in cprocessoeleitoraldto.cpp, where the record of GetPleito2 is
// (line 57, held by fn 3771), a reading of 11363's rows: it copies the name with a 4-byte alignment (i64.load
// align=2), a reference's, after its own 8-byte-aligned copy into a local. The member names and the id's type are
// chosen; GetPleito2 is declared for its record and not written.
class CProcessoEleitoralDTO {
public:
    CProcessoEleitoralDTO(uedword id, const std::string& nome, bool utilizaBiometria, EOrigemConfiguracao origem,
        const CPleitoDTO& pleito1, ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
        std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores);
    CProcessoEleitoralDTO(uedword id, const std::string& nome, bool utilizaBiometria, EOrigemConfiguracao origem,
        const CPleitoDTO& pleito1, const CPleitoDTO& pleito2,
        ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
        std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores);

    const CPleitoDTO& GetPleito2() const;

private:
    uedword m_id;
    std::string m_nome;
    bool m_utilizaBiometria;
    EOrigemConfiguracao m_origem;
    CPleitoDTO m_pleito1;
    std::optional<CPleitoDTO> m_pleito2;
    ecourna::app::dados::ETipoIdentificadorEleitor m_identificadorPrincipal;
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> m_identificadores;
};

} // namespace comum::md
