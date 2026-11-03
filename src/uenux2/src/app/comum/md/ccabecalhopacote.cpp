// Reconstruction: comum::md::CCabecalhoPacote's constructor (records ccabecalhopacote.cpp:33, 36 and 39), which target
// fn 11437 holds behind a stack-pointer prologue of its own (binaryen inlined it into
// comum::asn::CConversorCabecalhoPacote::DoDesconverte). It copies its arguments into the members, then tests the
// members (the loads are the object's). The rest is blank where the original is not recovered.
#include "app/comum/md/ccabecalhopacote.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 11-27: content not recovered)
#line 28
CCabecalhoPacote::CCabecalhoPacote(const ETipoPacote tipo, const CIDPacote& id, const std::string& nome,
    const std::string& versao, const ESistemaJE sistema)
    : m_tipo(tipo), m_id(id), m_nome(nome), m_versao(versao), m_sistema(sistema)
{
    if (m_nome.empty()) {
        throw CUeComumMdError(EUE_COMUM_MD_8908, "Nome do pacote vazio.");
    }
    if (m_versao.size() != 12) {
        throw CUeComumMdError(EUE_COMUM_MD_8909, "Versão deve ter tamanho 12.");
    }
    if (m_sistema < SISTEMA_CONFIGURADOR || m_sistema > SISTEMA_PADA_UE) {
        throw CUeComumMdError(EUE_COMUM_MD_8910, "Valor de origem inválido.");
    }
}

} // namespace comum::md
