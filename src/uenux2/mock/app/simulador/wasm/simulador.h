#pragma once

// Reconstruction's note, not TSE's text: the wasm simulator's start, which the executable TU's main calls (fn 8302,
// through its table slot), and the settings main builds for it (fn 8311, the constructor). No record names this header
// or anything it declares: every name, the path and the types beyond the widths the bodies use are chosen
// (src/units/188-uenux2-simulador.mk says what each rests on).
#include <functional>
#include <string>

#include "api/gui/primitives.h"

namespace simulador {

struct SConfiguracao {
    SConfiguracao(int parametro, std::string nome, api::TPosition largura, api::TPosition altura);

    int m_parametro;
    std::string m_nome;
    api::TPosition m_largura;
    api::TPosition m_altura;
};

void InicializaAmbiente();
void InicializaDispositivos(const SConfiguracao& configuracao);
void InicializaLog();
void Inicializa(const SConfiguracao& configuracao, std::function<void()> aoIniciar);

} // namespace simulador
