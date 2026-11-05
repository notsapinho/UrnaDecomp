#pragma once

// comum::CDataSourcesRelatorio<RDV, DSAptos> (/home/rubio/tse/uenux2/src/app/comum/relatorios/cdatasourcesrelatorio.h,
// its records' file). Reconstruction notes, not TSE's text. The records name six functions of the one instance the
// target has, <comum::CRdvVota, comum::CEleitores>: the static members DetalheCandidatoZE (fn 11973, line 152),
// TrailerProporcionalPartido (fn 11260, line 188), TrailerProporcional (fn 11981, line 241), TrailerMajoritario (fn
// 11980, line 305) and CodVerificador (fn 11974, line 348), and a lambda of GetLinhasEleitoresAptos (fn 11968, line
// 212). fn 3872 hands DetalheCandidato's or DetalheCandidatoZE's address (table slots 1636 and 1635) to
// api::CPaperFormBuilder::AddTextField (fn 604), which makes a report line's text field of it.
//
// Written: all six, DetalheCandidato (fn 11972, no record of its own), LinhaPartido (fn 11261, no record:
// src/units/296-uenux2-relatorios-impressao.mk has it), GetLinhasEleitoresAptos (fn 3871, no record; the trailers call
// it), IncluiDadosFinaisCV (fn 5967) and HeaderNominais (fn 11259), neither with a record of its own.
// src/units/183-uenux2-relatorios.mk says what the bytes decide and what is chosen for DetalheCandidatoZE,
// DetalheCandidato and LinhaPartido, src/units/325-uenux2-geradores-zeresima.mk for the other two trailers and the
// lambda, src/units/220-uenux2-fimvotacao-estados.mk for the rest.
//
// Chosen: the names and lines of DetalheCandidato (11972 is DetalheCandidatoZE's body with the vote count printed and
// no assert), IncluiDadosFinaisCV and HeaderNominais, where the class closes, the members' access and in-class bodies.

#include <format>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "api/pattern/cpolysingleton.h"
#include "api/util/eueasserterror.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
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

    // (original lines 47-105: content not recovered)
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

    // (original lines 172-173: content not recovered)
#line 174
    static std::string TrailerProporcionalPartido()
    {
        using namespace std::string_view_literals;
        CCargos& cargos = CCargos::GetInst();
        const md::TCargoID idCargo = cargos.GetCurrent().GetID();
        const int numero = CPartidos::GetInst().GetCurrent()->GetNumero();
        const RDV& rdv = RDV::GetInst();
        const md::TQtdVoto legenda = rdv.Legenda(idCargo, numero);
        const md::TQtdVoto partido = rdv.Partido(idCargo, numero);
        std::string texto;
        texto += std::format("{:<33s} {:04}\n", "    Votos de legenda"sv, legenda);
        const std::string total = md::CTradutorFrase::Traduz("    Total <P|de|do|da> <PLSB>");
        texto += std::format("{:<33s} {:04}", total.substr(0, 33), partido);
        if (api::CPolySingletonList::has<CCalculaCV>()) {
            CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
            const std::string votos = std::format("{:04}{:04}", legenda, partido);
            calculadoraCV.IncluiString(votos);
            if (cargos.IsUltimo()) {
                IncluiDadosFinaisCV(cargos, calculadoraCV);
            }
            const std::string codigo = calculadoraCV.CalculaCodigo();
            const std::string linhaCodigo = "\n\n    Código Verificador: " + codigo.substr(0, 1) + "." +
                                            codigo.substr(1, 3) + "." + codigo.substr(4, 3) + "." + codigo.substr(7, 3);
            texto += linhaCodigo;
        }
        return texto;
    }

    // (original lines 202-205: content not recovered)
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

    static void IncluiDadosFinaisCV(const CCargos& cargos, CCalculaCV& calculadoraCV)
    {
        calculadoraCV.IncluiResultado();
        const md::CPleito pleito = CConfiguracaoEleicao::GetInst().GetPleito();
        calculadoraCV.IncluiString(pleito.GetData().Format("YYYYMMDD"));
        const std::vector<CCargos::TCargoEleicao> cargosEleicoes = cargos.GetCargos();
        for (const CCargos::TCargoEleicao& cargo : cargosEleicoes) {
            calculadoraCV.IncluiString(std::to_string(cargo.second));
        }
    }

    // (original lines 329-344: content not recovered)
#line 345
    static std::string CodVerificador()
    {
        CCargos& cargos = CCargos::GetInst();
        CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
        if (cargos.IsUltimo()) {
            IncluiDadosFinaisCV(cargos, calculadoraCV);
        }
        const std::string codigo = calculadoraCV.CalculaCodigo();
        return "Código Verificador: " + codigo.substr(0, 1) + "." + codigo.substr(1, 3) + "." + codigo.substr(4, 3) +
               "." + codigo.substr(7, 3);
    }

    static std::string HeaderNominais()
    {
        const md::TCargoID idCargo = CCargos::GetInst().GetCurrent().GetID();
        if (RDV::GetInst().Nominais(idCargo) != 0) {
            return CCargoDSLabelRelatorio::HeaderDetalhe() + "\n";
        }
        return "";
    }
};

} // namespace comum

// The reconstruction's note on fn 11975 (table slot 1632, no record), which fns 11946 (through
// vota::FormSemCandidatos, inlined there) and 12110 pass to api::CPaperFormBuilder::AddTextField: the trailer of a
// post with no candidate, CDataSourcesRelatorio<RDV, DSAptos>::GetLinhasEleitoresAptos's text and the comparecimento
// for the current post, RDV's count (comum::CRdvVota::Cargo, fn 1930, slot 10). Its name, its being a free function
// template of comum over the class's two parameters (no record, vtable or RTTI names a class) and its place, a block of
// its own at this file's end, are chosen.
namespace comum {

template <typename RDV, typename DSAptos>
std::string TrailerSemCandidatos()
{
    const md::TCargoID idCargo = CCargos::GetInst().GetCurrent().GetID();
    const int comparecimento = RDV::GetInst().Cargo(idCargo);
    std::string texto;
    texto += CDataSourcesRelatorio<RDV, DSAptos>::GetLinhasEleitoresAptos();
    texto += std::format("Comparecimento                    {:04}\n", comparecimento);
    return texto;
}

} // namespace comum
