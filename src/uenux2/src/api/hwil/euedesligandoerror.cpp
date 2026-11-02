// api::CUeDesligandoError's constructor (target fn 1685). The reconstruction's file: no record names it;
// euedesligandoerror.h says why it is out of line and in a TU of api/.

#include "api/hwil/euedesligandoerror.h"

namespace api {

CUeDesligandoError::CUeDesligandoError(std::source_location local)
    : CBaseError(EUE_DESLIGANDO_URNA_DESLIGANDO, "Urna desligando", local)
{
}

} // namespace api
