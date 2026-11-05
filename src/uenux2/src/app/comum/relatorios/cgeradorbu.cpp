// comum::CGeradorBU (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbu.cpp, its records' file). This comment
// is the reconstruction's. The file's records are CriaQRCode's (line 124) and DefineTipo's (line 161), both held by fn
// 12110, and ImprimePreTexto's (line 257, fn 11256). The first two are not reconstructed, and their lines stay blank.
// Written here: the destructor, fns 3698 (D2) and 11258 (D0), which has no record; ImprimePreTexto, its instance() call
// on its record's line; and the free functions ImprimeHistoricoCargas and ConcatenaHistoricoCargas, which fn 11256 holds
// inlined by binaryen, declared above ImprimePreTexto and defined after it (src/units/139-uenux2-cgeradorbu.mk has the
// measurement of that order and of their parameters). Every line but 257 is a choice. CriaTituloCargo (fn 3699), above
// the destructor, is the zeresima and BU reports' title over the position's name:
// src/units/325-uenux2-geradores-zeresima.mk has why it is here and what is chosen.
#include "app/comum/relatorios/cgeradorbu.h"

#include <format>
#include <numeric>

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/relatorios/ccalculacv.h"
#include "app/comum/relatorios/crelutil.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

std::shared_ptr<api::IForm<api::IPaper>> CriaTituloCargo(const std::string& titulo)
{
    api::CPaperFormBuilder builder;
    builder.AddTextField(titulo, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
    builder.AddTextField(CPadDS<CToUpperDS<CCargoDSNome>>(
        38, '-',
        CToUpperDS<CCargoDSNome>(CCargoDSNome(md::CSexo::SEXO_NAO_INFORMADO),
                                 ecourna::api::util::CStringUtils::ToUpper)));
    return builder.Build();
}

CGeradorBU::~CGeradorBU()
{
    CCalculaCV::DestroyInst();
}

// (original lines 40-246: content not recovered)
#line 247
void ImprimeHistoricoCargas(api::CPaperFormBuilder& builder, const std::vector<std::string>& historicoCargas);
std::string ConcatenaHistoricoCargas(const std::vector<std::string>& historicoCargas);

void CGeradorBU::ImprimePreTexto() const
{
    api::CPaperFormBuilder builder;
    ImprimeHistoricoCargas(builder, m_historicoCargas);
    const std::shared_ptr<api::IForm<api::IPaper>> form = builder.Build();
    const std::string historico = ConcatenaHistoricoCargas(m_historicoCargas);

    CCalculaCV& calculo = api::CPolySingleton<CCalculaCV>::instance();
    calculo.IncluiString(historico);
    form->Slot2();
}

void ImprimeHistoricoCargas(api::CPaperFormBuilder& builder, const std::vector<std::string>& historicoCargas)
{
    builder.AddTextField(std::string(38, '-'), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Histórico de código de carga", static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    builder.AddTextField(std::string(38, '-'), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    for (size_t i = 0; i < historicoCargas.size(); ++i) {
        const std::string linha = std::format("{}: {}", i + 1, CRelUtil::GetIDCargaFormatado(historicoCargas[i]));
        builder.AddTextField(linha, static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
    }
    builder.AddNewLine(1);
    builder.AddTextField(CRelUtil::DSCodigoVerificador, api::ALINHAMENTO_ESQUERDA);
    builder.AddNewLine(1);
}

std::string ConcatenaHistoricoCargas(const std::vector<std::string>& historicoCargas)
{
    return std::accumulate(historicoCargas.begin(), historicoCargas.end(), std::string(),
                           [](const std::string& historico, const std::string& carga) { return historico + carga + "@"; });
}

} // namespace comum
