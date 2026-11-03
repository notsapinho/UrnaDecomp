#pragma once

#include <string>

#include "app/comum/md/cidpacote.h"

namespace comum {

// The system a package comes from, 4 bytes wide (fn 11437 stores it at +68 of the header). The values are evidence:
// comum::asn::Utils::ConverteIdSistema and DesconverteIdSistema (held inlined by fns 11438 and 11437) compile to tables
// (@498196, @498244) that map 1 to 12 to ModuloTiposEleitorais::Sistema's 1, 2, 3, 13, 12, 6, 7, 8, 9, 10, 11 and 14,
// and CCabecalhoPacote's constructor accepts 1 to 12. ConverteIdSistema's throw formats it through fn 536,
// formatter<unsigned int> (table slot 2287), which a plain enum of non-negative values gives. The enumerators' names
// (from the Sistema enumerators each maps to), the plain form and the comum:: scope are chosen; the records spell it
// ESistemaJE unqualified from comum::md and comum::asn.
enum ESistemaJE {
    SISTEMA_CONFIGURADOR = 1,
    SISTEMA_INTERCAD,
    SISTEMA_CANDIDATURAS,
    SISTEMA_SIMON,
    SISTEMA_SEWEB,
    SISTEMA_GEDAI,
    SISTEMA_URNA_ELETRONICA,
    SISTEMA_SIMULADOR,
    SISTEMA_PARAMETRIZADOR,
    SISTEMA_GERADOR_DE_BASES,
    SISTEMA_SISTOT,
    SISTEMA_PADA_UE,
};

namespace md {

// The package's type, 4 bytes wide (+0 of the header). The values are evidence: comum::asn::Utils::ConverteTipoPacote
// and DesconverteTipoPacote compile to tables (@497872, @498004) that map 0 to 32, in order, to the enumerators of
// ModuloTiposPacotes::TipoPacote from pacoteEleitores (1) to pacoteSituacoesEleicoes (40), 32 of them, and to
// pacoteTransferenciaTemporariaEleitores (48), and ConverteTipoPacote's throw formats it through fn 536 (table slot
// 2286), as for ESistemaJE. The enumerators' names (from the TipoPacote enumerators) and the plain form are chosen.
enum ETipoPacote {
    PACOTE_ELEITORES,
    PACOTE_MUNICIPIOS_ZONAS,
    PACOTE_IMPEDIDOS,
    PACOTE_CANDIDATOS_TRE,
    PACOTE_FOTOS_CANDIDATOS_TRE,
    PACOTE_CORRESPONDENCIA,
    PACOTE_SECOES,
    PACOTE_NOTIFICACAO_PACOTE,
    PACOTE_CONFIGURACAO_PROCESSO_ELEITORAL,
    PACOTE_VALIDACAO_CANDIDATOS,
    PACOTE_ALTERACAO_CANDIDATURA_TRE,
    PACOTE_RESULTADO_TOTALIZACAO,
    PACOTE_RESPOSTA_VERSAO_PACOTE,
    PACOTE_JUNTAS,
    PACOTE_ELEICOES_SEGUNDO_TURNO,
    PACOTE_PARAMETROS_URNA,
    PACOTE_NOTIFICACAO_IMPORTACAO,
    PACOTE_PRESTACAO_CONTAS,
    PACOTE_SOLICITACAO_ESTADO_SISTEMA,
    PACOTE_RESPOSTA_ESTADO_SISTEMA,
    PACOTE_SOLICITACAO_VERSAO_PACOTE,
    PACOTE_PROCESSAMENTO_RESULTADO_URNA_CADASTRO,
    PACOTE_NOTIFICACAO_DISPONIBILIDADE_SISTEMA,
    PACOTE_CANDIDATOS_TSE,
    PACOTE_FOTOS_CANDIDATOS_TSE,
    PACOTE_ALTERACAO_CANDIDATURA_TSE,
    PACOTE_SOLICITACAO_DADOS_CADASTRO,
    PACOTE_DADOS_ELEITOR,
    PACOTE_DADOS_DOCUMENTACAO_CANDIDATURA,
    PACOTE_COMPLEMENTOS_MUNICIPIOS,
    PACOTE_ELEICAO,
    PACOTE_SITUACOES_ELEICOES,
    PACOTE_TRANSFERENCIA_TEMPORARIA_ELEITORES,
};

// The layout, 72 bytes, from the constructor as fn 11437 holds it (records ccabecalhopacote.cpp:33, :36, :39): the type
// at +0, the identifier at +4, the two strings at +44 and +56, the system at +68; the constructor copies its arguments
// into the members, then tests the members. fn 11438 reads the five back (the type and the system by value, the
// others in place). The getters' names, their being inline and the member names are chosen.
class CCabecalhoPacote {
public:
    CCabecalhoPacote(const ETipoPacote tipo, const CIDPacote& id, const std::string& nome, const std::string& versao,
        const ESistemaJE sistema);

    ETipoPacote GetTipo() const { return m_tipo; }
    const CIDPacote& GetIdPacote() const { return m_id; }
    const std::string& GetNome() const { return m_nome; }
    const std::string& GetVersao() const { return m_versao; }
    ESistemaJE GetSistema() const { return m_sistema; }

private:
    ETipoPacote m_tipo;
    CIDPacote m_id;
    std::string m_nome;
    std::string m_versao;
    ESistemaJE m_sistema;
};

} // namespace md

} // namespace comum
