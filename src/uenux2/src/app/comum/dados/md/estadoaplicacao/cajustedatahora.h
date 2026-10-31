#pragma once

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// A pending change of the urna's date and time: its kind at +0 and its delta at +4 (target fns 3702, 11405).
class CAjusteDataHora {
public:
    // AdicionaDeltaT's message names eAlterarDataSistema, and 3702 tests it as 2; the other two names are chosen from
    // the generated enumerators of ModuloEstadoGeralUrna::TipoAjusteDataHora, whose values are these plus 1 (fn 11405).
    enum ETipoDeltaT {
        eSemAjusteDataHora,
        eAlterarDataEleicao,
        eAlterarDataSistema,
    };

    CAjusteDataHora(ETipoDeltaT tipo, ueint32 deltaT);

    ETipoDeltaT GetTipoDeltaT() const { return m_tipo; }
    ueint32 GetDeltaT() const { return m_deltaT; }

    void AdicionaDeltaT(const ueint32 deltaT);

private:
    ETipoDeltaT m_tipo;
    ueint32 m_deltaT;
};

} // namespace comum::md::estadoaplicacao

template <>
struct std::formatter<comum::md::estadoaplicacao::CAjusteDataHora::ETipoDeltaT> : comum::SFormatoEnum {};
