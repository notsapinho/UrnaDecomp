// api::CSynchronizer (/home/rubio/tse/uenux2/src/api/util/csynchronizer.cpp). CreateInst's throw is the file's one record
// (line 37, column 15); the other lines are a choice around it, GetOpenFlag's and Sync's too (csynchronizer.h says
// what they are).

#include "api/util/csynchronizer.h"

#include <fcntl.h>
#include <unistd.h>

#include "api/util/eueutilerror.h"

namespace api {

std::unique_ptr<CSynchronizer> CSynchronizer::s_instancia;

// (original lines 16-33: content not recovered)
#line 34
void CSynchronizer::CreateInst(bool habilitado)
{
    if (s_instancia) {
        throw CUeUtilError(EUE_UTIL_SINCRONIZADOR_JA_CRIADO, "Instância já criada");
    }
    s_instancia.reset(new CSynchronizer(habilitado));
}

CSynchronizer& CSynchronizer::GetInst()
{
    if (!s_instancia) {
        CreateInst(true);
    }
    return *s_instancia;
}

CSynchronizer::CSynchronizer(bool habilitado)
    : m_habilitado(habilitado)
{
}

int CSynchronizer::GetOpenFlag() const
{
    return m_habilitado ? O_SYNC : 0;
}

void CSynchronizer::Sync() const
{
    if (m_habilitado) {
        sync();
    }
}

} // namespace api
