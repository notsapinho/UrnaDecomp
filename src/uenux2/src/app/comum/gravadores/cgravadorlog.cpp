// comum::CGravadorLog's constructor, which fn 12098 holds inlined (no index; unrooted), and GravaResultado (target fn
// 11584, slot 7 of the class's vtable, its key function), in app/comum/gravadores/cgravadorlog.cpp: the class's name in
// lower case beside igravador.h, a path chosen; no record names this file (11584's one record is
// api::CSystem::Rename's, csystem.cpp:692, which binaryen inlines into it). The reconstruction's notes are in
// src/units/136-uenux2-app-comum-gravadores-md.mk.

#include "app/comum/gravadores/cgravadorlog.h"

#include <filesystem>
#include <map>
#include <string>

#include "api/util/csystem.h"
#include "app/comum/carquivosresultado.h"
#include "app/comum/cpath.h"
#include "ecourna/api/compression/czip.hpp"

namespace comum {

CGravadorLog::CGravadorLog(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
    const std::string& diretorioArquivados, const std::string& arquivoLog, const std::string& diretorioTrabalho)
    : IGravador(municipio, zona, local, secao, fase, EXTENSAO_LOG_JEZ, static_cast<ESavdArquivoUE>(60)),
      m_diretorioArquivados(diretorioArquivados), m_arquivoLog(arquivoLog), m_diretorioTrabalho(diretorioTrabalho)
{
}

std::filesystem::path GetPathLogArquivados()
{
    return CPath::GetPathLog() / "arquivados/";
}

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
