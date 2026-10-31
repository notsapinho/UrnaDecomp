#include "ecourna/api/util/csynchronizer.hpp"

#include <unistd.h>

#include "ecourna/api/util/eutilerror.hpp"

namespace ecourna::api::util {

CSynchronizer* CSynchronizer::s_instancia = nullptr;

// (original lines 11-55: content not recovered)
#line 56
void CSynchronizer::CreateInst(bool habilitado)
{
    if (s_instancia != nullptr) {
        throw CUtilError(EUE_SYNCHRONIZER_INSTANCIA_JA_CRIADA, "Instância já criada");
    }
    s_instancia = new CSynchronizer(habilitado);
}

int CSynchronizer::Sync(int descritor) const
{
    return m_habilitado ? fsync(descritor) : 0;
}

} // namespace ecourna::api::util
