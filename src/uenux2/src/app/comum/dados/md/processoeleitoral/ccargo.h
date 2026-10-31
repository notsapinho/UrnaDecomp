#pragma once

#include <cstddef>
#include <optional>
#include <string>

#include "app/comum/asn/util.h"
#include "app/comum/dados/md/candidatura/cdadoscandidato.h"
#include "app/comum/dados/md/processoeleitoral/cdetalhecandidato.h"
#include "app/comum/dados/md/processoeleitoral/cdetalheconsulta.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum::md {

// TQtdEscolha: a record names it (GetOrdinalEscolha(TQtdEscolha)). A byte: fn 2258 compares it with the byte at +13.
using TQtdEscolha = uebyte;

// Recovered: the layout, 140 bytes (the stride of fn 11371's loop over a vector of them), and the fields' meanings. fn
// 11373, CConversorCargo::DoDesconverte, stores them in the order of ModuloEleicao::CargoPergunta's fields, and Valida's
// messages confirm four of them. The two details are std::optional: fn 11373 clears each engaged flag (+84, +136) and
// builds the other detail. The enumerators' and members' names are chosen; ETipo's name is a record's
// (CConversorCargo::DesconverteTipoCargo), and Valida's switch gives which values hold which detail. That +8 is an
// md::ETipoAbrangencia is evidence (fn 5827, DesconverteAbrangencia): fn 11373 stores the converter's own word there, Valida's message calls it the
// abrangencia, and a plain enum, a scoped enum and an int give the same bytes.
class CCargo {
public:
    enum ETipo {
        MAJORITARIO,
        PROPORCIONAL,
        CONSULTA,
    };

    // The name is chosen: no record names this accessor.
    TCargoID GetID() const { return m_id; }
    // The names are chosen. CParteRdv::Imprime (fn 11203) reads the flag before the type (src/units/110-uenux2-singletons.mk).
    bool IsMajoritario() const { return m_detalheCandidato.has_value() && m_tipo == MAJORITARIO; }
    bool IsProporcional() const { return m_detalheCandidato.has_value() && m_tipo == PROPORCIONAL; }
    bool IsConsulta() const { return m_detalheConsulta.has_value(); }

    const CDetalheCandidato& GetDetalheCandidato() const;
    const CDetalheConsulta& GetDetalheConsulta() const;

    std::string GetNomeNeutro() const;
    std::string GetNomeMasculino() const;
    std::string GetNomeFeminino() const;
    std::string GetNomeAbreviado() const;
    std::string GetNome(CSexo::ESexo sexo) const;
    std::string GetNomeSuplente(size_t suplente, CSexo::ESexo sexo) const;
    std::string GetOrdinalEscolha(TQtdEscolha escolha) const;

    void Valida() const;

private:
    TCargoID m_id;
    ETipo m_tipo;
    ETipoAbrangencia m_abrangencia;
    uebyte m_numeroDigitos;
    TQtdEscolha m_qtdeEscolhas;
    bool m_podeRepetir;
    uebyte m_ordemAquisicao;
    uebyte m_ordemImpressao;
    uebyte m_ordemApuracao;
    uebyte m_paginaImpressaoVoto;
    std::optional<CDetalheCandidato> m_detalheCandidato;
    std::optional<CDetalheConsulta> m_detalheConsulta;
};

} // namespace comum::md
