// comum::CCopiadorMR (this file's name and path are the reconstruction's choice: no record names the class;
// app/comum/gravadores/ccopiadormr.h says what places it here). It holds the constructor, target fn 1276, and the
// class's slots 2 and 3 (fns 5874 and 5873, the key function first), none with a record: their lines are a choice, and
// so is the slots' place after the constructor (another band); Slot2 before Slot3 is the order of their use band, whose
// indices run in reverse link order.

#include "app/comum/gravadores/ccopiadormr.h"

#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/gravadores/cgravadorutil.h"

namespace comum {

CCopiadorMR::CCopiadorMR(TMunicipioID municipio, TZonaID zona, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao)
    : m_nomeArquivo(CGravadorUtil::DeterminaNomeArquivo(municipio, zona, secao, fase, extensao))
{
}

void CCopiadorMR::Slot2()
{
    const std::filesystem::path origem = CPath::GetPathResult(FLASH_INTERNA) / m_nomeArquivo;
    const std::filesystem::path destino = CPath::GetPathMR() / m_nomeArquivo;

    api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
}

void CCopiadorMR::Slot3()
{
    const std::filesystem::path origem = CPath::GetPathResult(FLASH_EXTERNA) / m_nomeArquivo;
    const std::filesystem::path destino = CPath::GetPathMR() / m_nomeArquivo;

    api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
}

} // namespace comum
