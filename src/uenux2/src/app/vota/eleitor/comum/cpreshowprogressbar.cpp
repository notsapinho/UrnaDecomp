// vota::CPreShowProgressBar::PreShow (target fn 13550, slot 2 of the class's vtable @1536544; the class head is in
// app/vota/comum/cpreshowformvota.h). This comment is the reconstruction's. No record names this file: PreShow is the
// class's key function, and the vtable and typeinfo its object emits lie in the target's data between
// cpoliticaexecucaoeleitor.cpp's records (@1536400 to @1536543) and ctelascargo.cpp's (@1536576), where this
// directory's files run in name order, so the file is this directory's, named after the class (the name a choice).
// src/units/391-uenux2-cpreshowprogressbar.mk has the forms measured and the choices.
#include "app/vota/comum/cpreshowformvota.h"

#include <string>
#include <vector>

#include "api/gui/cstepsprogressbar.h"
#include "api/gui/iscreen.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"

namespace vota {

void CPreShowProgressBar::PreShow(api::IScreen& tela)
{
    tela.Clear(static_cast<api::TColor>(1));
    DesenhaDescricaoModo(tela, api::SPoint{320, 30});

    std::vector<std::string> passos;
    const bool fim = comum::CCargos::GetInst().IsFim();
    comum::CCargos::TCargoEleicao cargoEleicaoAtual;
    if (!fim) {
        cargoEleicaoAtual.first = comum::CCargos::GetInst().GetCurrentEleicaoID();
        cargoEleicaoAtual.second = comum::CCargos::GetInst().GetCurrentCargoID();
    }
    const comum::md::TQtdEscolha escolhaAtual = g_escolhaAtual;

    uedword passoAtual = 0;
    bool atingido = fim;
    for (const auto& item : comum::CCargos::GetInst().GetCargos()) {
        const comum::md::CCargo& cargo = comum::CConfiguracaoEleicao::GetInst().GetCargo(item.second);
        const bool atual = !fim && item.first == cargoEleicaoAtual.first && item.second == cargoEleicaoAtual.second;
        const bool variasEscolhas = cargo.GetQtdeEscolhas() > 1;
        for (unsigned escolha = 1; escolha <= cargo.GetQtdeEscolhas(); ++escolha) {
            const std::string nome = cargo.GetNomeNeutro();
            const std::string ordinal = variasEscolhas ? " - " + cargo.GetOrdinalEscolha(escolha) : "";
            const std::string passo = nome + ordinal;
            passos.push_back(passo);
            if (atual && escolha == escolhaAtual) {
                atingido = true;
            }
            if (!atingido) {
                ++passoAtual;
            }
        }
    }

    if (passos.size() < 2) {
        return;
    }

    const api::SRect areaTela(0, 0, tela.GetWidth() - 1, tela.GetHeight() - 1);
    api::CStepsProgressBar barra(passoAtual, passos, api::SRect(2, 2, areaTela.right - 2, 30), static_cast<api::TColor>(3),
                                 static_cast<api::TColor>(2), static_cast<api::TColor>(36), static_cast<api::TColor>(2),
                                 static_cast<api::TColor>(1), static_cast<api::TColor>(3), static_cast<api::TColor>(0));
    barra.Draw(tela);
}

} // namespace vota

// <stubs>
// f6681 · 476 B · unmatched · placement: link order · name unknown
// void f6681(i32, i32) { ... }

// f6639 · 622 B · unmatched · placement: link order · name unknown
// void f6639(i32, i32) { ... }

// f1591 · 658 B · unmatched · placement: link order · name unknown
// void f1591(i32, i32, i32, i32, i32) { ... }
// </stubs>
