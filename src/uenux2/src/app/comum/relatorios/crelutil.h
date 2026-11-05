#pragma once

#include <memory>
#include <string>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnafase.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "ecourna/app/dados/parametrizacaourna/ctitulorelatorio.hpp"

namespace api {
class CDateTime;
class CPaperFormBuilder;
class IPaper;
template <typename MEDIA>
class IForm;
} // namespace api

namespace comum {

namespace md {
class CPleito;
namespace estadoaplicacao {
class CDadoCorrespondencia;
} // namespace estadoaplicacao
} // namespace md

// Reconstruction notes, not TSE's text. comum::CRelUtil: the records of crelutil.cpp name the class and five functions,
// four of them static members (GetIDCargaFormatado, line 69; IncluiCabecalhoEleicoesMZS, 307; DSCodigoVerificador, 412;
// GetSeparadorFase, 554). Reconstructed and declared: GetIDCargaFormatado (target fn 2786), GetSeparadorFase (fn 1919) and
// IncluiAvisoModoDemonstracao (fn 5583), a static member by choice whose name is chosen: no record names it; it adds the
// demonstration mode's warning to a report and is called by IncluiCabecalhoEleicoesMZS (fn 1543) and fn 5591.
// DSCodigoVerificador (fn 11182) formats CCalculaCV::CalculaCodigo's ten digits as the report's verification code; the
// target reaches it only by table slot 3048, which comum::CGeradorBU::ImprimePreTexto (fn 11256) hands to AddTextField.
// FormTituloPartido builds a report part of one text field over the file's internal TituloPartido (fn 11181, record
// line 58 in the anonymous namespace): the target holds it inlined by binaryen in fn 11946 (vota::CGeraZeresimaBase's
// slot 2), the one function that passes TituloPartido's table slot (3050), and only crelutil.cpp's TU can take that
// address. Its name, and its being a static member (the class's records name only static members), are chosen. This
// header's path is chosen, beside the .cpp.
// ImprimeTitulos (fn 3689) prints a report's title lines: it creates comum::CSubstituidorTitulo with the UF the first
// time, then prints each line of each title's translated text with the substitutions applied, empty lines as new
// lines. Its overload without the UF (fn 5584) passes comum::CLocal's. ImprimeAberturaFechamento (fn 3688) prints the
// opening and closing date and time lines through ImprimeDataHora (fn 1542). None of the four has a record: their
// names, their parameters' types, that they are static members of this class and that they live in crelutil.cpp are
// chosen (src/units/123-uenux2-crelatoriotesteimpressora.mk says what places them).
// ImprimeSeparadorVia (fn 5581), which vota::CGeraBU's slot 2 (fn 12110) calls twice with a counter plus one and a
// total: no record names it, so its name, its being a static member (the class's records name only static members)
// and its parameters' unsigned int (the format's argument code says unsigned, not the width) are chosen.
class CRelUtil {
public:
    // The header IncluiCabecalhoEleicoesMZS (fn 1543) prints under the municipality and the zone: its record spells the
    // type, unqualified (const ETipoCabecalho), and fn 1543's switch gives each value's work: 0 the place's and the
    // section's lines (and the aggregated sections'), 1 the section's number split into "Mesa Receptora" and "Urna", 2
    // "Urna de contingência" (comum::CGeradorRelVersaoPacoteDados's slot 3, fn 11223, passes 2 for an eUrnaContingencia
    // urna and 0 otherwise; with 2 the pleito 2 may be printed), and 3 throws "Tipo inválido: {}" with the value, through
    // a std::formatter of its own (the format's argument code 15, a handle whose table slot, 3047, holds fn 536, the body
    // comum::SFormatoEnum's handles share). A value past 3 prints nothing there (the target's br_table sends it past
    // the switch), so no default throws. The enumerators' names, the enum's being nested in CRelUtil and its
    // formatter's being SFormatoEnum are chosen.
    enum ETipoCabecalho {
        eCabecalhoSecao,
        eCabecalhoMesaReceptora,
        eCabecalhoContingencia,
        eCabecalhoInvalido,
    };

    static std::string GetIDCargaFormatado(const std::string& idCarga);
    static void ImprimeTitulos(api::CPaperFormBuilder& builder,
                               const std::vector<ecourna::app::dados::CTituloRelatorio>& titulos, const std::string& uf);
    static void ImprimeTitulos(api::CPaperFormBuilder& builder,
                               const std::vector<ecourna::app::dados::CTituloRelatorio>& titulos);
    static void ImprimeAberturaFechamento(api::CPaperFormBuilder& builder, const api::CDateTime& abertura,
                                          const api::CDateTime& fechamento);
    static void ImprimeDataHora(api::CPaperFormBuilder& builder, const api::CDateTime& dataHora,
                                const std::string& rotuloData, const std::string& rotuloHora);
    static std::shared_ptr<api::IForm<api::IPaper>> FormTituloPartido();
    static void IncluiAvisoModoDemonstracao(api::CPaperFormBuilder& builder);
    static std::string DSCodigoVerificador();
    static std::string GetSeparadorFase(const EUrnaFase fase);
    static void ImprimeSeparadorVia(api::CPaperFormBuilder& builder, unsigned int via, unsigned int totalVias);
    static void IncluiCabecalhoEleicoesMZS(api::CPaperFormBuilder& builder, const std::string& titulo,
                                           const TMunicipioID municipio, const TZonaID zona, const TSecaoID secao,
                                           const std::string& nomeMunicipio, const ETipoCabecalho tipo,
                                           const bool usaPleito2);
    // Target fn 1541, no record: "RESUMO DA CORRESPONDÊNCIA" and FormataCodigoCargaResumido (fn 2792) of the
    // correspondence it is given, in style 2, then a new line. Its six callers are the reports that call
    // IncluiCabecalhoEleicoesMZS (5977, 11223, 11902, 11908, 12105, 12110); use band 8 puts it right after
    // ImprimeDataHora (fn 1542) and before csigverifier.cpp's 1540. Its name, its parameter's type and its being a
    // static member of this class are chosen.
    static void ImprimeResumoCorrespondencia(api::CPaperFormBuilder& builder,
                                             const md::estadoaplicacao::CDadoCorrespondencia& correspondencia);
    // Target fn 2785, no record: GetSeparadorFase (fn 1919) of the phase it is given, centred in style 1. It builds a
    // CInformacaoEleicao on CConfiguracaoEleicao's parameters (fn 603) that nothing reads, and the separator is
    // default-constructed and then assigned (the target moves 1919's result from +4 to +16 of its frame). Use band 4
    // puts it right after GetIDCargaFormatado (fn 2786). Its name, its parameter's type and its being a static member
    // of this class are chosen.
    static void ImprimeSeparadorFase(api::CPaperFormBuilder& builder, const EUrnaFase fase);
    // Target fn 5579, no record: the zeresima reports' footer (fns 11943 and 11946 call it with GetSeparadorFase's text,
    // CConfiguracaoEleicao's +200, the parameters' GetRodapeZEVOTA, and CEstadoGeral's correspondence): the separator in
    // style 1, "Código de identificação da carga" and GetIDCargaFormatado (fn 2786) of the load's code centred,
    // "Ver: " and the version's number, the footer's titles through ImprimeTitulos (fn 3689), 20 new lines and a cut.
    // In use band 2 it follows ImprimeSeparadorVia (5581) in this file's object, with 5580 (FormCabecalhoEleicao) between,
    // so it is defined below ImprimeSeparadorVia. Its name, its parameters' types, its being a static member of this
    // class and both functions' lines (crelutil.cpp holds FormCabecalhoEleicao between them) are chosen.
    static std::shared_ptr<api::IForm<api::IPaper>> FormRodapeZeresima(
        const std::string& separador, const std::vector<ecourna::app::dados::CTituloRelatorio>& rodape,
        const md::estadoaplicacao::CDadoCorrespondencia& correspondencia);
    // Target fn 5580, no record: the header CParteCargos prints when the election changes (fns 5971 and 11946 hand it
    // over as its first part), a line of 38 '=' in style 1, NomeEleicaoCorrente's text (table slot 3049, fn 11556)
    // centred, the '=' line again and a new line, each '=' line through an internal helper of crelutil.cpp that clang
    // inlines (the frame's order: src/units/325-uenux2-geradores-zeresima.mk). In use band 2 it lies between
    // ImprimeSeparadorVia (5581) and FormRodapeZeresima (5579), so it is defined between them. Its name, its being a
    // static member of this class (the class's records name only static members), the helper and its lines are
    // chosen.
    static std::shared_ptr<api::IForm<api::IPaper>> FormCabecalhoEleicao();

private:
    // The two parts of fn 1543 that it holds behind stack frames of their own (240 and 32 bytes), each binaryen's
    // inlining of a function with one caller: IncluiCabecalhoEleicoes copies CConfiguracaoEleicao's pleito, takes CPE's
    // pleito 2 instead when its bool says so and that pleito's date is today or earlier, prints it through
    // IncluiCabecalhoPleito, then prints the names of its elections sorted by their order of printing (the std::sort
    // whose introsort is fn 5582, with its comparator taking both elections by value) when there are two or more. 1543
    // passes the bool as its last argument and a contingency header together: the target tests the two joined by an
    // `and` and then the result (`i32.eqz(i32.and(p7, i32.eq(p6, 2)))`); the test written in IncluiCabecalhoEleicoes
    // gave `i32.or(i32.eqz(p7), i32.ne(p6, 2))` (1543 216 over 2730 rows, 1 inserted and 1 deleted, against 212 over
    // 2729, all operand-only, with `pnpm wasm score`). Their names, their parameters and their being
    // static members of this class (the class's records name only static members) are chosen.
    static void IncluiCabecalhoEleicoes(api::CPaperFormBuilder& builder, const std::string& titulo,
                                        const bool usaPleito2);
    static void IncluiCabecalhoPleito(api::CPaperFormBuilder& builder, const std::string& titulo,
                                      const md::CPleito& pleito);
};

} // namespace comum

template <>
struct std::formatter<comum::CRelUtil::ETipoCabecalho> : comum::SFormatoEnum {};
