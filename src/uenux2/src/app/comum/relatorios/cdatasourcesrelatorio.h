#pragma once

// comum::CDataSourcesRelatorio<RDV, DSAptos> (/home/rubio/tse/uenux2/src/app/comum/relatorios/cdatasourcesrelatorio.h,
// its records' file). Reconstruction notes, not TSE's text. The records name six functions of the one instance the
// target has, <comum::CRdvVota, comum::CEleitores>: the static members DetalheCandidatoZE (fn 11973, line 152),
// TrailerProporcionalPartido (fn 11260, line 188), TrailerProporcional (fn 11981, line 241), TrailerMajoritario (fn
// 11980, line 305) and CodVerificador (fn 11974, line 348), and a lambda of GetLinhasEleitoresAptos (fn 11968, line
// 212). fn 3872 hands DetalheCandidato's or DetalheCandidatoZE's address (table slots 1636 and 1635) to
// api::CPaperFormBuilder::AddTextField (fn 604), which makes a report line's text field of it.
//
// Written: DetalheCandidatoZE (fn 11973), DetalheCandidato (fn 11972, no record of its own) and LinhaPartido (fn 11261,
// no record: src/units/296-uenux2-relatorios-impressao.mk has it), and since, at their records' lines,
// TrailerProporcional (fn 11981), TrailerMajoritario (fn 11980) and GetLinhasEleitoresAptos's lambda (fn 11968), with
// GetLinhasEleitoresAptos (fn 3871, no record; the trailers call it): src/units/325-uenux2-geradores-zeresima.mk.
// The other members, TrailerProporcionalPartido and CodVerificador, are not reconstructed: their lines stay blank.
// src/units/183-uenux2-relatorios.mk lists what the bytes decide and what is chosen for the first three.
//
// Chosen: DetalheCandidato's name and its lines (11972 is DetalheCandidatoZE's body with the vote count printed and no
// assert), where the class is closed, the members' access and that they are defined in the class.

#include <format>
#include <map>
#include <string>

#include "api/pattern/cpolysingleton.h"
#include "api/util/eueasserterror.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/md/parametrizacaourna/ctradutorfrase.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/comum/relatorios/celeitoresaptos.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

template <typename RDV, typename DSAptos>
class CDataSourcesRelatorio {
public:

    // (original lines 44-105: content not recovered)
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

    static std::string LinhaPartido()
    {
        const md::TCargoID idCargo = CCargos::GetInst().GetCurrent().GetID();
        const md::CPartido* partido = CPartidos::GetInst().GetCurrent();
        const int numero = partido->GetNumero();
        std::string texto =
            std::format("{}: {} - {}\n", md::CTradutorFrase::Traduz("<PLSN>"), numero, partido->GetSigla());
        const RDV& rdv = RDV::GetInst();
        if (rdv.Legenda(idCargo, numero) != rdv.Partido(idCargo, numero)) {
            texto += CCargoDSLabelRelatorio::HeaderDetalhe();
            texto += "\n";
        }
        return texto;
    }

    // (original lines 172-205: content not recovered)
#line 206
    static std::string GetLinhasEleitoresAptos()
    {
        const auto qtdeAptos = []() {
            const auto aptos = DSAptos::GetInst().QuantidadeAptosPorAbrangencia();
            const md::ETipoAbrangencia abrangencia = CCargos::GetInst().GetCurrent().GetAbrangencia();
            if (!aptos.contains(abrangencia)) {
                throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9089,
                                              std::format("Abrangência inválida: {}", static_cast<int>(abrangencia)));
            }
            return aptos.at(abrangencia);
        };
        return CEleitoresAptos(qtdeAptos).Formata() + "\n";
    }

    // (original lines 220-230: content not recovered)
#line 231
    static std::string TrailerProporcional()
    {
        const md::TCargoID idCargo = CCargos::GetInst().GetCurrent().GetID();
        const RDV& rdv = RDV::GetInst();
        const int nominais = rdv.Nominais(idCargo);
        const int legendas = rdv.Legendas(idCargo);
        const int brancos = rdv.Brancos(idCargo);
        const int nulos = rdv.Nulos(idCargo);
        const int total = rdv.Cargo(idCargo);
        if (api::CPolySingletonList::has<CCalculaCV>()) {
            CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
            const std::string votos =
                std::format("{:04}{:04}{:04}{:04}{:04}", nominais, legendas, brancos, nulos, total);
            calculadoraCV.IncluiString(votos);
        }
        std::string texto;
        texto += GetLinhasEleitoresAptos();
        texto += std::vformat(CCargoDSLabelRelatorio::TotalVotoNominal(), std::make_format_args(nominais));
        texto += std::format("Total de votos de Legenda         {:04}\n", legendas);
        texto += std::format("Brancos                           {:04}\n", brancos);
        texto += std::format("Nulos                             {:04}\n", nulos);
        texto += std::format("Total Apurado                     {:04}", total);
        return texto;
    }

    // (original lines 256-295: content not recovered)
#line 296
    static std::string TrailerMajoritario()
    {
        const md::TCargoID idCargo = CCargos::GetInst().GetCurrent().GetID();
        const RDV& rdv = RDV::GetInst();
        const int nominais = rdv.Nominais(idCargo);
        const int brancos = rdv.Brancos(idCargo);
        const int nulos = rdv.Nulos(idCargo);
        const int total = rdv.Cargo(idCargo);
        if (api::CPolySingletonList::has<CCalculaCV>()) {
            CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
            const std::string votos = std::format("{:04}{:04}{:04}{:04}", nominais, brancos, nulos, total);
            calculadoraCV.IncluiString(votos);
        }
        std::string texto;
        texto += GetLinhasEleitoresAptos();
        texto += std::vformat(CCargoDSLabelRelatorio::TotalVotoNominal(), std::make_format_args(nominais));
        texto += std::format("Brancos                           {:04}\n", brancos);
        texto += std::format("Nulos                             {:04}\n", nulos);
        texto += std::format("Total Apurado                     {:04}", total);
        return texto;
    }
};

} // namespace comum
