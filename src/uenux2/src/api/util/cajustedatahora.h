#pragma once

// api::CAjusteDataHora: RTTI names the class, over api::IAjusteDataHora, and fn 10876 allocates 4 bytes for it, so it has no
// data member. The path, Registra and the members' names are chosen: no record names a file of this class.

#include "api/util/iajustedatahora.h"

namespace api {

class CAjusteDataHora : public IAjusteDataHora {
public:
    void Ajusta(const CDateTime& dataHora) override;
    void Ajusta(const time_t& agora) override;
    static void Registra();
};

} // namespace api
