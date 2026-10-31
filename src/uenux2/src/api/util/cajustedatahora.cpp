// Reconstruction's note, not TSE's text. No record names this file. It is here by data order: the class's vtable
// (@1584156) and the interface's typeinfo (1584192) lie between cinisection.cpp's records and cdate.cpp's, where api/'s
// objects run in name order, and only fn 10876 stores the class's vptr. Registra's name and class are chosen: only a table
// slot (118) reaches it.
#include "api/pattern/cpolysingleton.h"
#include "api/util/cajustedatahora.h"
#include "api/util/isystemdatetime.h"

namespace api {

void CAjusteDataHora::Ajusta(const time_t& agora)
{
    ISystemDateTime::GetInst().SetTime(agora);
}

void CAjusteDataHora::Registra()
{
    if (!CPolySingletonList::has<IAjusteDataHora>()) {
        CPolySingleton<IAjusteDataHora>::set(std::unique_ptr<IAjusteDataHora>(new CAjusteDataHora));
    }
}

} // namespace api
