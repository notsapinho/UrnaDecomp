#pragma once

#include <memory>
#include <string>
#include <vector>

#include "app/comum/eurnafase.h"
#include "ecourna/app/dados/parametrizacaourna/ctitulorelatorio.hpp"

namespace api {
class CDateTime;
class CPaperFormBuilder;
class IPaper;
template <typename MEDIA>
class IForm;
} // namespace api

namespace comum {

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
};

} // namespace comum
