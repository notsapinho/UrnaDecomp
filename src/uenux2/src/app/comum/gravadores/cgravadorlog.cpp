// comum::CGravadorLog::GravaResultado (target fn 11584, slot 7 of the class's vtable, its key function), in
// app/comum/gravadores/cgravadorlog.cpp: the class's name in lower case beside igravador.h, a path chosen; no record
// names this file (11584's one record is api::CSystem::Rename's, csystem.cpp:692, which binaryen inlines into it).
// The reconstruction's notes are in src/units/136-uenux2-app-comum-gravadores-md.mk.

#include "app/comum/gravadores/cgravadorlog.h"

#include <filesystem>
#include <map>
#include <string>

#include "api/util/csystem.h"
#include "ecourna/api/compression/czip.hpp"

namespace comum {

void CGravadorLog::GravaResultado(api::CFile&) const
{
    const std::filesystem::path arquivoLog(m_arquivoLog);
    std::map<std::filesystem::path, std::filesystem::path> arquivos{{arquivoLog, arquivoLog.filename()}};
    for (const std::filesystem::directory_entry& entrada : std::filesystem::directory_iterator(m_diretorioArquivados)) {
        if (entrada.is_regular_file()) {
            arquivos.insert({entrada.path(), entrada.path().filename()});
        }
    }

    const std::string temporario = m_diretorioTrabalho + "temp.jez";
    ecourna::api::compression::CZip zip(temporario, arquivos, ecourna::api::compression::ENivelCompressao::PADRAO);
    zip.Close();
    api::CSystem::Rename(temporario, m_diretorioTrabalho + m_nomeArquivo);
}

} // namespace comum
