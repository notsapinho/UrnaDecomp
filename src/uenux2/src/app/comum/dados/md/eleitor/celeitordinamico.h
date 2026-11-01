#pragma once

#include <optional>

#include "app/comum/dados/md/eleitor/cdedo.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"

namespace comum::md {

// What the machine records of a voter who showed up, a row of the table eleitor_dinamico. No vtable of its own; the target
// holds its type name, which fn 11540 passes. Recovered: the layout, 84 bytes. fns 5775 and 5776 bind each column to one offset, and the columns' names name
// the members: titulo and tipo_identificador at +0, identidade_habilitacao and tipo_identidade_habilitacao at +16,
// estado_comparecimento +32, tipo_habilitacao +36, dedo_habilitacao +40, score_habilitacao +44 (16 bits),
// numero_tentativa +46 (8 bits), tipo_ativacao_audio +48, erro_decifrar_biometria +52, an optional titulo_mesario with
// tipo_identificador_mesario at +56 (its flag at +72), and the two columns of the photo at +76, one member: both
// constructors copy them as one i64 from the address of what fn 1081, CApresentacaoFotoEleitor's constructor, returns.
// The member names and the getters' are chosen from those columns, but for GetTituloMesarioHabilitacao, the record's.
// The 32-bit members are plain ints: their enums are not recovered and the two functions only bind them.
//
// Constructors: fns 5664 and 5663, the second with the optional, whose one difference is that argument. The parameters'
// order is the wasm's and their types what the bodies do; their callers (3766, 11542, CEleitorDinamicoDAO's SELECTs) pass
// the columns in that order. The photo's reference could be a by-value parameter, since the caller passes an address
// either way.
class CEleitorDinamico {
public:
    CEleitorDinamico(const CEleitorIdentidade& eleitor, const CEleitorIdentidade& identidadeHabilitacao,
                     int estadoComparecimento, int tipoHabilitacao, CDedo::TipoDedo dedoHabilitacao,
                     ueword scoreHabilitacao, uebyte numeroTentativa, int tipoAtivacaoAudio, int erroDecifrarBiometria,
                     const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto);
    CEleitorDinamico(const CEleitorIdentidade& eleitor, const CEleitorIdentidade& identidadeHabilitacao,
                     int estadoComparecimento, int tipoHabilitacao, CDedo::TipoDedo dedoHabilitacao,
                     ueword scoreHabilitacao, uebyte numeroTentativa, int tipoAtivacaoAudio, int erroDecifrarBiometria,
                     const CEleitorIdentidade& tituloMesarioHabilitacao,
                     const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto);

    const CEleitorIdentidade& GetEleitor() const { return m_eleitor; }
    const CEleitorIdentidade& GetIdentidadeHabilitacao() const { return m_identidadeHabilitacao; }
    int GetEstadoComparecimento() const { return m_estadoComparecimento; }
    int GetTipoHabilitacao() const { return m_tipoHabilitacao; }
    CDedo::TipoDedo GetDedoHabilitacao() const { return m_dedoHabilitacao; }
    ueword GetScoreHabilitacao() const { return m_scoreHabilitacao; }
    uebyte GetNumeroTentativa() const { return m_numeroTentativa; }
    int GetTipoAtivacaoAudio() const { return m_tipoAtivacaoAudio; }
    int GetErroDecifrarBiometria() const { return m_erroDecifrarBiometria; }
    bool TemTituloMesarioHabilitacao() const { return m_tituloMesarioHabilitacao.has_value(); }
    const CEleitorIdentidade& GetTituloMesarioHabilitacao() const;
    const ecourna::app::dados::CApresentacaoFotoEleitor& GetApresentacaoFoto() const { return m_apresentacaoFoto; }

    // How CEleitorDetalhe::MarcaHabilitado (inlined into target fn 2825) changes a voter who showed up. Each kind of
    // enabling stores the state 2, its kind and its own set of the members after them, in reverse member order, from
    // values read before the first store: the shape of a call clang inlined (docs/reference/facts/codegen.md C1). The
    // mesario's kind with a title reads as a call binaryen inlined (2825 keeps this object's address in a local across
    // GetTituloMesario); the inline member here gives that shape at the tree's -O3 (src/units/110-uenux2-singletons.mk has the
    // measurement). The members, their names, their parameters and the four-way split are chosen, and so are the setters.
    void HabilitaSemBiometria()
    {
        m_estadoComparecimento = 2;
        m_tipoHabilitacao = 0;
        m_dedoHabilitacao = CDedo::TipoDedo();
        m_numeroTentativa = 0;
        m_erroDecifrarBiometria = 0;
    }
    void HabilitaPorBiometria(CDedo::TipoDedo dedo, ueword score, uebyte numeroTentativa)
    {
        m_estadoComparecimento = 2;
        m_tipoHabilitacao = 1;
        m_dedoHabilitacao = dedo;
        m_scoreHabilitacao = score;
        m_numeroTentativa = numeroTentativa;
        m_erroDecifrarBiometria = 0;
    }
    void HabilitaPorMesario(uebyte numeroTentativa, int erroDecifrarBiometria, const CEleitorIdentidade& tituloMesario)
    {
        m_estadoComparecimento = 2;
        m_tipoHabilitacao = 2;
        m_dedoHabilitacao = CDedo::TipoDedo();
        m_numeroTentativa = numeroTentativa;
        m_erroDecifrarBiometria = erroDecifrarBiometria;
        m_tituloMesarioHabilitacao = tituloMesario;
    }
    void HabilitaPorMesario(uebyte numeroTentativa, int erroDecifrarBiometria)
    {
        m_estadoComparecimento = 2;
        m_tipoHabilitacao = 2;
        m_dedoHabilitacao = CDedo::TipoDedo();
        m_numeroTentativa = numeroTentativa;
        m_erroDecifrarBiometria = erroDecifrarBiometria;
        m_tituloMesarioHabilitacao.reset();
    }
    void SetTipoAtivacaoAudio(int tipoAtivacaoAudio) { m_tipoAtivacaoAudio = tipoAtivacaoAudio; }
    void SetIdentidadeHabilitacao(const CEleitorIdentidade& identidade) { m_identidadeHabilitacao = identidade; }
    void SetApresentacaoFoto(const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto)
    {
        m_apresentacaoFoto = apresentacaoFoto;
    }

private:
    CEleitorIdentidade m_eleitor;
    CEleitorIdentidade m_identidadeHabilitacao;
    int m_estadoComparecimento;
    int m_tipoHabilitacao;
    CDedo::TipoDedo m_dedoHabilitacao;
    ueword m_scoreHabilitacao;
    uebyte m_numeroTentativa;
    int m_tipoAtivacaoAudio;
    int m_erroDecifrarBiometria;
    std::optional<CEleitorIdentidade> m_tituloMesarioHabilitacao;
    ecourna::app::dados::CApresentacaoFotoEleitor m_apresentacaoFoto;
};

} // namespace comum::md
