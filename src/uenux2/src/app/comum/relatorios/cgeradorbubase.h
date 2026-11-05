#pragma once

// comum::CGeradorBUBase<RDV, DSAptos> (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbubase.h, its records'
// file). Reconstruction notes, not TSE's text. RTTI gives the instance <comum::CRdvVota, comum::CEleitores>, an si_class
// of comum::CGeradorRelBase<comum::CRdvVota, comum::CEleitores>, and its vtable (@1575364) has six slots: the D2 (fn
// 5612), 325 for the D0 (an abstract class's), slot 2 pure, and the three members its records name, which override the
// base's pure slots: ImprimeProporcionalPartido (fn 11255, line 187), ImprimeMajoritario (fn 11254, line 246) and
// ImprimeConsulta (fn 11253, line 286).
//
// Recovered: the layout and the destructor. The constructor (records lines 66 to 111, held inlined by fn 12110) takes
// thirteen std::shared_ptr<api::IForm<api::IPaper>>, passes the first three to the base and stores the other ten at +36
// to +108, throwing codes 9055 to 9064 at lines 66, 71, ... 111 when one is empty. The members are named after those
// messages, in the order of the stores: "headerProporcional nulo" (+36) to "trailerMajoritario nulo" (+108). The D2 (fn
// 5612) releases them from +108 down and calls the base's D2. The destructor is implicit: its D0 is a trap and its one
// caller (fn 3698) calls it, so the bytes do not tell its form, and reading.md R5 says to leave it implicit in a class
// with a base. The access of the members and where the class declares its data members are chosen.
//
// Written here: ImprimeProporcionalPartido, ImprimeVotosCandidatos (record line 222, inlined by binaryen into fn
// 11255), ImprimeMajoritario and ImprimeConsulta. Each record is the default std::source_location of a
// CPolySingleton<CCalculaCV>::instance() call. src/units/139-uenux2-cgeradorbu.mk has what the bytes decide and what is
// chosen. Not reconstructed: the constructor; its lines stay blank.

#include <algorithm>
#include <format>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cpaperformbuilder.h"
#include "api/gui/iform.h"
#include "api/gui/ipaper.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/comum/relatorios/cgeradorrelbase.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

template <typename RDV, typename DSAptos>
class CGeradorBUBase : public CGeradorRelBase<RDV, DSAptos> {
public:
    CGeradorBUBase(std::shared_ptr<api::IForm<api::IPaper>> header, std::shared_ptr<api::IForm<api::IPaper>> trailer,
                   std::shared_ptr<api::IForm<api::IPaper>> rodape,
                   std::shared_ptr<api::IForm<api::IPaper>> headerProporcional,
                   std::shared_ptr<api::IForm<api::IPaper>> headerProporcionalPartido,
                   std::shared_ptr<api::IForm<api::IPaper>> partidoApenasVotoLegenda,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerProporcionalPartido,
                   std::shared_ptr<api::IForm<api::IPaper>> cargoSemCandidato,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerCargoSemCandidato,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerProporcional,
                   std::shared_ptr<api::IForm<api::IPaper>> headerMajoritario,
                   std::shared_ptr<api::IForm<api::IPaper>> detalheCandidato,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerMajoritario);

// (original lines 58-178: content not recovered)
#line 179
protected:
    virtual void ImprimeProporcionalPartido() const override
    {
        m_headerProporcional->Slot2();
        const TCargoID idCargo = CCargos::GetInst().GetCurrent().GetID();
        CPartidos& partidos = CPartidos::GetInst();
        const RDV& rdv = RDV::GetInst();
        CCandidaturas& candidaturas = CCandidaturas::GetInst();
        CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
        if (!candidaturas.ExisteCandidato(idCargo)) {
            const std::string votosCargo = std::format("{:02}{:04}", idCargo, rdv.Cargo(idCargo));
            calculadoraCV.IncluiString(votosCargo);
            this->m_linhaEmBranco->Slot2();
            m_cargoSemCandidato->Slot2();
            m_trailerCargoSemCandidato->Slot2();
            return;
        }
        for (partidos.Reset(); !partidos.IsFim(); partidos.Next()) {
            const TPartidoID partido = partidos.GetCurrent()->GetNumero();
            if (rdv.Partido(idCargo, partido) == 0) {
                continue;
            }
            const std::string votosPartido = std::format("{:02}{:02}", idCargo, partido);
            calculadoraCV.IncluiString(votosPartido);
            m_headerProporcionalPartido->Slot2();
            ImprimeVotosCandidatos(candidaturas.GetCandidatosPartido(idCargo, partido));
            m_trailerProporcionalPartido->Slot2();
        }
        m_trailerProporcional->Slot2();
    }

    // (original lines 210-215: content not recovered)
#line 216
    void ImprimeVotosCandidatos(const std::vector<TCandidatoID>& candidatos) const
    {
        const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
        const TCargoID idCargo = cargo.GetID();
        const uebyte digitos = cargo.GetNumeroDigitos();
        CCandidaturas& candidaturas = CCandidaturas::GetInst();
        CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
        bool apenasLegenda = true;
        for (auto candidato = candidatos.begin(); candidato != candidatos.end(); ++candidato) {
            const md::CCandidatura* candidatura = candidaturas.Busca(idCargo, *candidato);
            const md::TQtdVoto votos = RDV::GetInst().Candidato(idCargo, candidatura->GetCandidatoID(), digitos);
            if (votos != 0) {
                const std::string votosCandidato = std::format("{:05}{:04}", candidatura->GetCandidatoID(), votos);
                calculadoraCV.IncluiString(votosCandidato);
                m_detalheCandidato->Slot2();
                apenasLegenda = false;
            }
        }
        if (apenasLegenda) {
            m_partidoApenasVotoLegenda->Slot2();
        }
    }


    virtual void ImprimeMajoritario() const override
    {
        m_headerMajoritario->Slot2();
        const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
        const uebyte digitos = cargo.GetNumeroDigitos();
        const TCargoID idCargo = cargo.GetID();
        CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
        const std::string cargoCV = std::format("{:02}", idCargo);
        calculadoraCV.IncluiString(cargoCV);
        CCandidaturas& candidaturas = CCandidaturas::GetInst();
        const RDV& rdv = RDV::GetInst();
        if (!candidaturas.ExisteCandidato(idCargo)) {
            const std::string votosCargo = std::format("{:02}{:04}", idCargo, rdv.Cargo(idCargo));
            calculadoraCV.IncluiString(votosCargo);
            m_cargoSemCandidato->Slot2();
            m_trailerCargoSemCandidato->Slot2();
            return;
        }
        for (candidaturas.Reset(); !candidaturas.IsFim(); candidaturas.Next()) {
            const md::CCandidatura* candidatura = candidaturas.GetCurrent();
            if (candidatura->GetCargoID() != idCargo) {
                continue;
            }
            const TCandidatoID candidato = candidatura->GetCandidatoID();
            const int votos = rdv.Candidato(idCargo, candidato, digitos);
            if (votos != 0) {
                const std::string votosCandidato = std::format("{:05}{:04}", candidato, votos);
                calculadoraCV.IncluiString(votosCandidato);
                m_detalheCandidato->Slot2();
            }
        }
        m_trailerMajoritario->Slot2();
    }

    // (original lines 274-279: content not recovered)
#line 280
    virtual void ImprimeConsulta() const override
    {
        m_headerMajoritario->Slot2();
        const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
        const uebyte digitos = cargo.GetNumeroDigitos();
        const TCargoID idCargo = cargo.GetID();
        CCalculaCV& calculadoraCV = api::CPolySingleton<CCalculaCV>::instance();
        const std::string cargoCV = std::format("{:02}", idCargo);
        calculadoraCV.IncluiString(cargoCV);
        md::TVectorRespostaConsulta respostas = cargo.GetDetalheConsulta().GetRespostas();
        std::sort(respostas.begin(), respostas.end(),
                  [](const md::CRespostaConsulta& a, const md::CRespostaConsulta& b) {
                      return a.GetNumero() < b.GetNumero();
                  });
        for (std::size_t i = 0; i < respostas.size(); ++i) {
            const md::CRespostaConsulta& resposta = respostas[i];
            const TCandidatoID numero = resposta.GetNumero();
            const md::TQtdVoto votos = RDV::GetInst().Candidato(idCargo, numero, digitos);
            if (votos == 0) {
                continue;
            }
            const std::string votosResposta = std::format("{:05}{:04}", numero, votos);
            calculadoraCV.IncluiString(votosResposta);
            api::CPaperFormBuilder builder;
            const std::string numeroResposta = std::format("{:0{}}", numero, digitos);
            builder.AddTextField(
                "  " + ecourna::api::util::CStringUtils::PreencheADireita(resposta.GetResposta(), ' ', 26) +
                    ecourna::api::util::CStringUtils::PreencheAEsquerda(numeroResposta, ' ', 4) + "  " +
                    std::format("{:04}", votos),
                static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
            builder.Build()->Slot2();
        }
        m_trailerMajoritario->Slot2();
    }

    std::shared_ptr<api::IForm<api::IPaper>> m_headerProporcional;
    std::shared_ptr<api::IForm<api::IPaper>> m_headerProporcionalPartido;
    std::shared_ptr<api::IForm<api::IPaper>> m_partidoApenasVotoLegenda;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerProporcionalPartido;
    std::shared_ptr<api::IForm<api::IPaper>> m_cargoSemCandidato;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerCargoSemCandidato;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerProporcional;
    std::shared_ptr<api::IForm<api::IPaper>> m_headerMajoritario;
    std::shared_ptr<api::IForm<api::IPaper>> m_detalheCandidato;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerMajoritario;
};

} // namespace comum
