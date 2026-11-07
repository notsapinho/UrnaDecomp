#pragma once

#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/gravadores/igravador.h"
#include "ecourna/app/dados/cfaseid.hpp"
#include "ecourna/app/dados/iidentificadoreleitor.hpp"
#include "ecourna/app/dados/resultadournacadastro/cresultadournacadastro.hpp"

namespace comum {

namespace md {
class CComparecimentoMesario;
class CEleitorDinamico;
class CEleitorIdentidade;
}

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorRCSecao), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 60 bytes (12098 allocates it with f137(60)), the
// virtual members, and the members the records name. The constructor, which 12098 holds inlined with no frame of its own
// (no target index; written in cgravadorrcsecao.cpp, unrooted), calls IGravador's constructor (fn 1396) with the
// extension 8 and the SAVD file 39, copies the api::CDateTime 12098 builds to +40, and stores at +52 and +56 what
// CGravadorUtil::ConverteFaseEcourna and ConverteSituacaoArquivoEcourna return, each behind a 480-byte frame of its own
// in 12098 (out of line in cgravadorutil.cpp, inlined by binaryen); the second's code is the constant 0 alone there, its
// argument a constant every caller passed (docs/reference/facts/reading.md R1). GravaResultado (fn 11616) passes +52 to
// CResultadoUrnaCadastro's constructor as its ecourna::app::dados::CFaseID and +56 as its ESituacaoArquivo; the records
// cgravadorutil.cpp:113 (CGravadorUtil::ConverteFaseEcourna, which 12098 loads) and :129
// (ConverteSituacaoArquivoEcourna, which no target function loads) return those two types: the members' types are a
// reading of them. No member's destruction emits code: slot 0 holds IResultado's base-object destructor (fn 12090), and
// the deleting one (fn 11615, slot 1) holds that body and frees `this`, so the destructor is not declared (implicit).
// GravaResultado (slot 7, record cgravadorrcsecao.cpp:110) is out of line, so it is the key function and
// cgravadorrcsecao.cpp emits the vtable.
// LeChavePublica and CriaIdentidadeEleitor (fn 5845) are declared as their records (cgravadorrcsecao.cpp:65, :230)
// print them; ObtemComparecimentoEleitores calls CriaIdentidadeEleitor, so it reaches the object and is a member too.
// The functions after the class read no state of it: free functions of comum. Their external linkage is a reading:
// 11616 holds each but ConverteComparecimentoMesario (fn 5841, two calls) behind a stack frame of its own, the shape
// of an out-of-line function binaryen inlined into its one caller (src/units/122-uenux2-app-comum-gravadores.mk lists
// the frames).
// Chosen: every name but the records', that the three members are private, that the others are free functions
// declared here, every parameter's name and type beyond what the records spell, and the constructor's parameters
// (their order, the char it passes ConverteSituacaoArquivoEcourna, and the extension and SAVD file as constants of the
// constructor rather than 12098's arguments: one call in 12098 cannot tell them apart).
class CGravadorRCSecao : public IGravador {
public:
    CGravadorRCSecao(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
        TSecaoID secao, char fase, char situacao);

    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    std::vector<uebyte> LeChavePublica() const;
    ecourna::app::dados::TVectorEstadoComparecimento ObtemComparecimentoEleitores() const;
    ecourna::app::dados::TSharedIdentificadorEleitor CriaIdentidadeEleitor(
        const comum::md::CEleitorIdentidade& identidade) const;

    api::CDateTime m_dataHora;
    ecourna::app::dados::TFaseID m_faseUrna;
    ecourna::app::dados::CResultadoUrnaCadastro::ESituacaoArquivo m_situacao;
};

std::string FormataDataHora(const api::CDateTime& dataHora);
ecourna::app::dados::CHabilitacaoBiometrica CriaHabilitacaoPorMesario(const md::CEleitorDinamico& dinamico);
ecourna::app::dados::CEstadoHabilitacaoPorCodigo::ESituacaoReconhecimentoMesario ObtemSituacaoReconhecimentoMesario(
    const md::CEleitorDinamico& dinamico);
ecourna::app::dados::TVectorIdentificacaoJustificativa ObtemJustificativas();
std::vector<md::CComparecimentoMesario> ObtemRegistrosMesariosAbertura();
ecourna::app::dados::TVectorComparecimentoMesario ObtemMesariosAbertura();
std::vector<md::CComparecimentoMesario> ObtemRegistrosMesariosEncerramento();
ecourna::app::dados::TVectorComparecimentoMesario ObtemMesariosEncerramento();
ecourna::app::dados::CComparecimentoMesario ConverteComparecimentoMesario(const md::CComparecimentoMesario& mesario);

} // namespace comum
