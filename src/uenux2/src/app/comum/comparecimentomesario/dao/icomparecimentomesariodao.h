#pragma once

#include "api/persistencia/iuenuxgenericdao.h"
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

namespace comum::dao {

// The name and the base are RTTI's (typeinfo 1593452). The path, beside ccomparecimentomesariodao.cpp, is chosen: no
// record names this file. It adds no slot and no data member, as comum::dao::IJustificadorDAO.
class IComparecimentoMesarioDAO
    : public api::persistencia::IUenuxGenericDAO<md::CComparecimentoMesario, md::CComparecimentoMesarioPK> {
};

} // namespace comum::dao
