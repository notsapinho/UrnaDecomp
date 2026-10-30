#pragma once

#include <optional>

#include "app/comum/dados/md/eleitor/cdedo.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"

namespace comum::md {

// What the machine records of a voter who showed up, a row of the table eleitor_dinamico. No vtable and no RTTI of its
// own. Recovered: the layout, 84 bytes. fns 5775 and 5776 bind each column to one offset, and the columns' names name
// the members: titulo and tipo_identificador at +0, identidade_habilitacao and tipo_identidade_habilitacao at +16,
// estado_comparecimento +32, tipo_habilitacao +36, dedo_habilitacao +40, score_habilitacao +44 (16 bits),
// numero_tentativa +46 (8 bits), tipo_ativacao_audio +48, erro_decifrar_biometria +52, an optional titulo_mesario with
// tipo_identificador_mesario at +56 (its flag at +72), and the two columns of the photo at +76, one member: both
// constructors copy them as one i64 from the address of what fn 1081, CApresentacaoFotoEleitor's constructor, returns.
// The member names and the getters' are chosen from those columns, but for GetTituloMesarioHabilitacao, the record's.
// The 32-bit members are plain ints: their enums are not recovered and the two functions only bind them.
//
// Constructors: fns 5664 and 5663, the second with the optional, whose one difference is that argument. Their callers
// (3766, 11542) are not written, so the parameters' order is the wasm's and their types what the bodies do: the
// photo's reference could be a by-value parameter, since the caller passes an address either way.
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
