#pragma once

#include <optional>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/eleitor/cdedo.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

namespace comum::md {

// The key of the table comparecimento_mesario. Declared only: the DAOs take it by reference, and the three slots that
// read it are not written. The name is the record's (iuenuxgenericdao.h:41).
class CComparecimentoMesarioPK;

// A row of the table comparecimento_mesario. The name is RTTI's (typeid in fn 10398's constant) and no vtable holds it.
// Recovered: the layout, 52 bytes. fn 10403 binds each column to one offset, and the columns name the members:
// numero_titulo and tipo_identificador at +0, periodo_presente +16, pertence_secao +20 (8 bits), estado_biometria +24,
// dedo_habilitacao +28, data_hora_registro +32, an optional id_arquivo at +44 (its flag at +48). The members' names,
// the types of periodo_presente and id_arquivo, and this header's path are chosen.
class CComparecimentoMesario {
public:
    enum EstadoReconhecimentoBiometrico {};

private:
    CEleitorIdentidade m_mesario;
    int m_periodoPresente;
    bool m_pertenceSecao;
    EstadoReconhecimentoBiometrico m_estadoBiometria;
    CDedo::TipoDedo m_dedoHabilitacao;
    api::CDateTime m_dataHoraRegistro;
    std::optional<int> m_idArquivo;
};

} // namespace comum::md
