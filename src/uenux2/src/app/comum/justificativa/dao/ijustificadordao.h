#pragma once
#include <string>

#include "api/persistencia/iuenuxgenericdao.h"
#include "ecourna/app/dados/resultadournacadastro/cidentificacaojustificativa.hpp"

namespace comum::dao {

// The name and the base are RTTI's (typeinfo 1560848). The path, beside cjustificadordao.cpp, is chosen: no record
// names this file. It adds no slot and no data member: CJustificadorDAO's vtable has the nine slots of the other two
// DAOs' and its destructor stores no vptr of this class.
class IJustificadorDAO
    : public api::persistencia::IUenuxGenericDAO<ecourna::app::dados::CIdentificacaoJustificativa, std::string> {
};

} // namespace comum::dao
