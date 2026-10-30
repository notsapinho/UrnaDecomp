#pragma once

#include <string>

#include "api/persistencia/iuenuxgenericdao.h"
#include "app/comum/dados/md/eleitor/celeitordinamico.h"

namespace comum::dao {

// The name and the base are RTTI's (typeinfo 1558968). The path, beside celeitordinamicodao.cpp, is chosen: no record
// names this file. It adds no slot and no data member, as comum::dao::IJustificadorDAO.
class IEleitorDinamicoDAO : public api::persistencia::IUenuxGenericDAO<md::CEleitorDinamico, std::string> {
};

} // namespace comum::dao
