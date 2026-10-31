#pragma once

#include <optional>
#include <string>

#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/gravadores/md/ctipoapuracaosa.h"

namespace comum {

// The type of a result file (const ETipoArquivo in the records of cconversorurna.cpp:117 and :139, unqualified, so its
// scope is chosen). CUrna::ValidaCriacao (target fn 5862) refuses 48, and CConversorUrna::DoConverte (fn 10287) accepts 49
// to 54 and stores the value less 48, ModuloTiposResultadosEcoUrna::TipoArquivo's votacaoUE (1) to saEletronica (6). The
// values are evidence; the character spelling and every enumerator's name are chosen, from the ASN.1 enumerators.
enum ETipoArquivo {
    TIPO_ARQUIVO_SEM_TIPO = '0',
    TIPO_ARQUIVO_VOTACAO_UE = '1',
    TIPO_ARQUIVO_VOTACAO_RED = '2',
    TIPO_ARQUIVO_SA_MISTA_MR_PARCIAL_CEDULA = '3',
    TIPO_ARQUIVO_SA_MISTA_BU_IMPRESSO_CEDULA = '4',
    TIPO_ARQUIVO_SA_MANUAL = '5',
    TIPO_ARQUIVO_SA_ELETRONICA = '6',
};

namespace md {

// Recovered: the layout, 136 bytes, from the constructors (target fns 2854 and 2855) and its implicit destructor (fn
// 1394): the urna's type at +0, a string at +4, the CCorrespondenciaResultado at +16 (8 bytes copied, CCarga's copy
// constructor fn 1557, then the word at +84), the file type at +104, a byte both constructors set to 1 at +108, a string
// at +112 that ValidaCriacao (records curna.cpp:58 to :69) wants as 8 hexadecimal digits ("Serial da MV inválido"), and
// a std::optional<CTipoApuracaoSA> at +124 (engaged at +132), which fn 2855 fills and fn 2854 leaves empty. The members
// follow ModuloTiposResultadosEcoUrna::Urna's fields (tipoUrna, versaoVotacao, correspondenciaResultado, tipoArquivo,
// numeroSerieFV, motivoUtilizacaoSA). That the type is comum::EUrnaTipo, the parameters' forms beyond what the bodies
// copy (const references: each is copied, none moved), the byte as a bool and every name are chosen; the converters
// fns 10287, 10284, 10270 and 10271 load no word at +108 (fn 5860 copies it), so its role is not recovered.
class CUrna {
public:
    CUrna(EUrnaTipo tipoUrna, const std::string& versaoVotacao, const CCorrespondenciaResultado& correspondencia,
        ETipoArquivo tipoArquivo, const std::string& numeroSerieFV);
    CUrna(EUrnaTipo tipoUrna, const std::string& versaoVotacao, const CCorrespondenciaResultado& correspondencia,
        ETipoArquivo tipoArquivo, const std::string& numeroSerieFV, const CTipoApuracaoSA& tipoApuracao);

    // CEnvelopeGenerico's constructor (fn 5860) reads the type through it; the name is chosen.
    EUrnaTipo GetTipoUrna() const { return m_tipoUrna; }

private:
    void ValidaCriacao() const;

    EUrnaTipo m_tipoUrna;
    std::string m_versaoVotacao;
    CCorrespondenciaResultado m_correspondencia;
    ETipoArquivo m_tipoArquivo;
    bool m_flag;
    std::string m_numeroSerieFV;
    std::optional<CTipoApuracaoSA> m_tipoApuracao;
};

} // namespace md
} // namespace comum
