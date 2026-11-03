// The reconstruction's note, not TSE's text. The records name two function templates of an anonymous namespace in this
// header, each over the converter it reads with: LeEntidadeEm(const std::string &, const comum::md::CIndexer &, const
// std::string &) at lines 92 and 98 (target fn 3755, comum::CFotos::GetImagem, holds its instance for
// comum::asn::CConversorFotoCandidato inside the frame of the reader that names itself "LeFotoCandidato("; not written,
// so those lines stay blank) and LeEntidadeBiometria(const std::string &, const comum::md::CParametro &, const
// comum::md::CIndexer &, const std::string &) at lines 119 and 125, written from comum::CEleitorDetalhe::GetBiometria
// (fn 1937), which holds its one instance, for comum::asn::CConversorBiometriaEleitorCifrada, inside the frame of
// comum::LeBiometriaEleitor (celeitordetalhe.cpp): it opens the file "rb", seeks to the indexer's offset, reads as many
// bytes as its length (the two throws, whose texts begin "CLeitorASN::", the target's literals), decodes the entity
// through api::CFileASN::DecodeObject and converts it with the parameter. Chosen: the lines of every statement but the
// throws, the names of the parameters and locals, and the place of the includes.
#pragma once

#include <cstdio>
#include <format>
#include <string>
#include <vector>

#include "api/io/asn/cfileasn.h"
#include "api/io/cfile.h"
#include "app/comum/asn/euecomumasnerror.h"
#include "app/comum/dados/md/cindexer.h"
#include "app/comum/dados/md/eleitor/cparametro.h"

namespace {

// (original lines 27-112: content not recovered)
#line 113
template <typename CONVERSOR>
typename CONVERSOR::TDado LeEntidadeBiometria(const std::string& arquivo, const comum::md::CParametro& parametro,
    const comum::md::CIndexer& indexer, const std::string& nome)
{
    api::CFile leitor(arquivo, "rb");
    if (!leitor.Seek(indexer.GetOffset(), SEEK_SET)) {
        throw comum::CUeComumAsnError(comum::EUE_COMUM_ASN_LEITOR_SEEK, std::format("CLeitorASN::{} - não foi possível fazer o seek em {}", nome, arquivo));
    }

    std::vector<char> buffer(indexer.GetTamanho());
    const uedword lidos = leitor.RawRead(buffer.data(), buffer.size());
    if (lidos != buffer.size()) {
        throw comum::CUeComumAsnError(comum::EUE_COMUM_ASN_LEITOR_LEITURA, std::format("CLeitorASN::{} - não foi possível ler a entidade de {}", nome, arquivo));
    }

    const CONVERSOR conversor;
    return conversor.Desconverte(api::CFileASN::DecodeObject<typename CONVERSOR::TEntidade>(buffer), parametro);
}

} // namespace
