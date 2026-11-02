// comum::IResultado's and comum::IGravador's constructors and IGravador's slots 2, 6 and 3
// (/home/rubio/tse/uenux2/src/app/comum/gravadores/iresultado.cpp, the file IResultado's record names). The two
// constructors are one target function, fn 1396: binaryen inlined IResultado's into IGravador's, its one caller.
// IResultado's throw is a record of the target (line 40, column 15). Nothing else here has a record, so every other
// line is a choice: IGravador's constructor after the constructor it calls, then the slots. Their order is their
// use band's: there the indices run in reverse link order, and fns 11632, 11631 and 11630 are Slot2, Slot6 and Slot3.
// That IGravador's members are in this file is a choice the data allow (app/comum/gravadores/igravador.h). Slots 4
// and 5 (fns 11634, 11633) are not written: src/units/60-uenux2-cgravadorwsq-pending.cpp says what they wait for.

#include "app/comum/gravadores/iresultado.h"

#include <format>

#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/gravadores/igravador.h"

namespace comum {

// (original lines 22-32: content not recovered)
#line 33
IResultado::IResultado(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd)
    : m_municipio(municipio), m_zona(zona), m_local(local), m_secao(secao), m_fase(fase),
      m_nomeArquivo(CGravadorUtil::DeterminaNomeArquivo(municipio, zona, secao, fase, extensao)), m_extensao(extensao),
      m_arquivoSavd(arquivoSavd)
{
    if (fase != 'o' && fase != 's' && fase != 't') {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8657, std::format("Fase inválida: {}", fase));
    }
}

IGravador::IGravador(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
    EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd)
    : IResultado(municipio, zona, local, secao, fase, extensao, arquivoSavd)
{
}

void IGravador::Slot2()
{
    const std::filesystem::path origem = CPath::GetPathTrab(FLASH_INTERNA) / m_nomeArquivo;
    const std::filesystem::path destino = CPath::GetPathResult(FLASH_INTERNA) / m_nomeArquivo;

    api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
}

void IGravador::Slot6()
{
    const std::filesystem::path origem = CPath::GetPathTrab(FLASH_EXTERNA) / m_nomeArquivo;
    const std::filesystem::path destino = CPath::GetPathResult(FLASH_EXTERNA) / m_nomeArquivo;

    api::CSystem::CopyFile(origem.string(), destino.string(), false, true);
}

void IGravador::Slot3()
{
    const std::filesystem::path trabalhoInterno = CPath::GetPathTrab(FLASH_INTERNA) / m_nomeArquivo;
    const std::filesystem::path trabalhoExterno = CPath::GetPathTrab(FLASH_EXTERNA) / m_nomeArquivo;

    api::CSystem::CopyFile(trabalhoInterno.string(), trabalhoExterno.string(), false, true);

    const std::filesystem::path resultadoInterno = CPath::GetPathResult(FLASH_INTERNA) / m_nomeArquivo;
    const std::filesystem::path resultadoExterno = CPath::GetPathResult(FLASH_EXTERNA) / m_nomeArquivo;

    api::CSystem::CopyFile(resultadoInterno.string(), resultadoExterno.string(), false, true);
}

} // namespace comum
