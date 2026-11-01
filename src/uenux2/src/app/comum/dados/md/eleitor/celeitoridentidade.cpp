// Reconstruction notes: comum::md::CEleitorIdentidade's constructor (target fn 566) and FormataIdentidade (fn 2798). No
// record names this file or these functions: src/units/178-*.mk says why they are here and what is chosen.
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"

#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

using ecourna::api::util::CStringUtils;

namespace {

void Normaliza(std::string& identificador, ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    const size_t tamanho = tipo == ecourna::app::dados::TipoIDCPF ? 11 : 12;
    if (identificador.size() > tamanho) {
        CStringUtils::RemoveZerosAEsquerda(identificador);
    }
    CStringUtils::PreencheAEsquerda(identificador, '0', tamanho);
}

} // namespace

std::string FormataIdentidade(std::string identificador, ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    Normaliza(identificador, tipo);
    return identificador;
}

CEleitorIdentidade::CEleitorIdentidade(std::string identificador, ecourna::app::dados::ETipoIdentificadorEleitor tipo)
    : m_identificador(FormataIdentidade(std::move(identificador), tipo)), m_tipo(tipo)
{
    CValidadorIdentidade::GetInst().Valida(m_tipo, m_identificador);
    Normaliza(m_identificador, m_tipo);
}

} // namespace comum::md
