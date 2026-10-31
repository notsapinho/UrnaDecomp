#pragma once

#include "app/comum/dados/md/eleitor/celeitordadoshabilitacaobiometrica.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"

namespace comum {

// How the operator enabled a voter, which CEleitores::MarcaEleitorFoiHabilitado passes on to the current record. The
// record of that member (celeitores.cpp:435) spells the type unqualified beside md::-qualified ones; that it lives in
// comum, and this header's path, are chosen (docs/reference/facts/reading.md R11). Recovered: the layout of the 64 bytes
// CEleitorDetalhe::MarcaHabilitado (inlined into target fn 2825) reads, nothing after them: the identity it copies at +0,
// the kind it switches on at +16 (0, 1 and 2 have cases), a 32-bit word at +20 it copies, the biometric part at +24 whose
// members it reads, and the photo's 8 bytes at +56. The kinds' names, the members' names and the getters are chosen.
class CEleitorDadosHabilitacao {
public:
    enum ETipoHabilitacao {
        HABILITACAO_SEM_BIOMETRIA = 0,
        HABILITACAO_BIOMETRICA = 1,
        HABILITACAO_MESARIO = 2,
    };

    const md::CEleitorIdentidade& GetIdentidade() const { return m_identidade; }
    ETipoHabilitacao GetTipo() const { return m_tipo; }
    int GetTipoAtivacaoAudio() const { return m_tipoAtivacaoAudio; }
    const md::CEleitorDadosHabilitacaoBiometrica& GetBiometria() const { return m_biometria; }
    const ecourna::app::dados::CApresentacaoFotoEleitor& GetApresentacaoFoto() const { return m_apresentacaoFoto; }

private:
    md::CEleitorIdentidade m_identidade;
    ETipoHabilitacao m_tipo;
    int m_tipoAtivacaoAudio;
    md::CEleitorDadosHabilitacaoBiometrica m_biometria;
    ecourna::app::dados::CApresentacaoFotoEleitor m_apresentacaoFoto;
};

} // namespace comum
