#pragma once

// comum::CDataSourcesRelatorio<RDV, DSAptos> (/home/rubio/tse/uenux2/src/app/comum/relatorios/cdatasourcesrelatorio.h,
// its records' file). Reconstruction notes, not TSE's text. The records name six functions of the one instance the
// target has, <comum::CRdvVota, comum::CEleitores>: the static members DetalheCandidatoZE (fn 11973, line 152),
// TrailerProporcionalPartido (fn 11260, line 188), TrailerProporcional (fn 11981, line 241), TrailerMajoritario (fn
// 11980, line 305) and CodVerificador (fn 11974, line 348), and a lambda of GetLinhasEleitoresAptos (fn 11968, line
// 212). fn 3872 hands DetalheCandidato's or DetalheCandidatoZE's address (table slots 1636 and 1635) to
// api::CPaperFormBuilder::AddTextField (fn 604), which makes a report line's text field of it.
//
// Written: DetalheCandidatoZE (fn 11973) and DetalheCandidato (fn 11972, no record of its own). The other members are not
// reconstructed: their lines stay blank, past the end of this file. src/units/183-uenux2-relatorios.mk
// lists what the bytes decide and what is chosen.
//
// Chosen: DetalheCandidato's name and its lines (11972 is DetalheCandidatoZE's body with the vote count printed and no
// assert), where the class is closed, the members' access and that they are defined in the class.

#include <format>
#include <string>

#include "api/util/eueasserterror.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

template <typename RDV, typename DSAptos>
class CDataSourcesRelatorio {
public:

    // (original lines 32-105: content not recovered)
#line 106
    static std::string DetalheCandidato()
    {
        const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
        const md::TCargoID idCargo = cargo.GetID();
        const uebyte digitos = cargo.GetNumeroDigitos();
        const CCandidaturas& candidaturas = CCandidaturas::GetInst();
        const TCandidatoID numero = candidaturas.GetCurrent()->GetCandidatoID();
        std::string nome = candidaturas.GetCurrent()->GetTitular().GetNomeUrna();
        if (nome.size() > 36) {
            nome.resize(36);
        }
        if (nome.size() < 23) {
            ecourna::api::util::CStringUtils::PreencheADireita(nome, ' ', 23);
        }
        if (nome.size() > 23) {
            nome.append(36 - nome.size(), '-');
            nome.append("\n  ");
            nome.append(22, '-');
            nome.append(">");
        }
        const int qtd = RDV::GetInst().Candidato(idCargo, numero, digitos);
        return std::format("  {}  {}{:0{}}  {:04}", nome, std::string(5 - cargo.GetNumeroDigitos(), ' '), numero,
                           cargo.GetNumeroDigitos(), qtd);
    }

    static std::string DetalheCandidatoZE()
    {
        const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
        const md::TCargoID idCargo = cargo.GetID();
        const uebyte digitos = cargo.GetNumeroDigitos();
        const CCandidaturas& candidaturas = CCandidaturas::GetInst();
        const TCandidatoID numero = candidaturas.GetCurrent()->GetCandidatoID();
        std::string nome = candidaturas.GetCurrent()->GetTitular().GetNomeUrna();
        if (nome.size() > 36) {
            nome.resize(36);
        }
        if (nome.size() < 31) {
            ecourna::api::util::CStringUtils::PreencheADireita(nome, ' ', 31);
        }
        if (nome.size() > 31) {
            nome.append(36 - nome.size(), '-');
            nome.append("\n  ");
            nome.append(30, '-');
            nome.append(">");
        }
        const auto qtd = RDV::GetInst().Candidato(idCargo, numero, digitos);
        ASSERT(qtd == 0u, api::EUA_DATASOURCESRELATORIO_DETALHECANDIDATOZE_VOTO);
        return std::format("  {}{}{:0{}}", nome, std::string(5 - cargo.GetNumeroDigitos(), ' '), numero,
                           cargo.GetNumeroDigitos());
    }
};

} // namespace comum
