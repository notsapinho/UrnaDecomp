// Reconstruction's note: api::CIniFile, the INI object (src/uenux2/src/api/io/cinifile.h). No record names this file or
// any of its functions: the file, its path and the functions' lines and order are chosen
// (src/units/379-uenux2-cinifile.mk says why the loader is not cinistrings.cpp's).
#include "api/io/cinifile.h"

#include <utility>

#include "api/io/cinistrings.h"
#include "ecourna/api/io/cfile.hpp"

namespace api {

CIniFile::TMapChaves::iterator CIniFile::FindKey(const std::string& nome)
{
    return m_chaves.find(nome);
}

CIniFile::TMapChaves::iterator CIniFile::EndKey()
{
    return m_chaves.end();
}

CIniFile::TMapSecoes::iterator CIniFile::SetSection(const CIniSection& secao)
{
    auto it = m_secoes.find(secao.GetNome());
    if (it != m_secoes.end()) {
        CIniSection atual(it->second);
        for (const auto& chave : secao.GetChaves()) {
            atual.SetKey(chave.second);
        }
        it->second = atual;
        return it;
    }
    return m_secoes.insert(std::make_pair(secao.GetNome(), secao)).first;
}

void CIniFile::SetKey(const CIniKey& chave)
{
    const std::string nome = chave.GetNome();
    auto it = m_chaves.find(nome);
    if (it != m_chaves.end()) {
        it->second = chave;
    } else {
        m_chaves.insert(m_chaves.end(), std::make_pair(nome, chave));
    }
}

CIniFile CIniFile::Interpreta(const std::vector<std::string>& linhas)
{
    CIniFile ini;
    bool temSecao = false;
    TMapSecoes::iterator secao;
    for (auto it = linhas.begin(); it != linhas.end(); ++it) {
        std::string linha;
        bool continua;
        do {
            std::string parte;
            parte = *it;
            if (parte.back() == '\n') {
                parte.resize(parte.size() - 1);
            }
            linha += parte;
            continua = TerminaComBarraInvertida(linha);
            if (!continua) {
                break;
            }
            linha.resize(linha.size() - 1);
        } while (++it != linhas.end());
        linha = RemoveEspacos(RemoveComentario(linha));
        if (LinhaUtil(linha)) {
            if (!EhSecao(linha)) {
                std::string nome;
                std::string valor;
                CIniStrings::ParseKeyLine(nome, valor, linha);
                CIniKey chave(nome, valor);
                if (!temSecao) {
                    ini.SetKey(chave);
                } else {
                    secao->second.SetKey(chave);
                }
            } else {
                CIniSection nova(TrataEscapes(linha.substr(1, linha.size() - 2)));
                secao = ini.SetSection(nova);
                temSecao = true;
            }
        }
    }
    return ini;
}

CIniFile CIniFile::Carrega(const std::string& arquivo)
{
    ecourna::api::io::CFile file(arquivo, "rb");
    std::vector<std::string> linhas;
    bool fim = false;
    while (!fim) {
        std::string linha;
        bool continua;
        do {
            std::string parte;
            file.ReadLine(parte);
            if (parte.empty() && file.Eof()) {
                break;
            }
            if (parte.back() == '\n') {
                parte.resize(parte.size() - 1);
            }
            linha += parte;
            continua = TerminaComBarraInvertida(linha);
            if (continua) {
                linha.resize(linha.size() - 1);
            }
        } while (continua);
        linha = RemoveEspacos(RemoveComentario(linha));
        if (!LinhaUtil(linha)) {
            fim = file.Eof();
        } else {
            linhas.push_back(linha);
            fim = false;
        }
    }
    return Interpreta(linhas);
}

} // namespace api
