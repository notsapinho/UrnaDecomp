#pragma once

#include "api/gui/itext.h"

namespace api {
class CPaperFormBuilder;
}

// The free functions of app/vota/comum/votadefs.cpp that other files call. No record names this header, so its path is
// chosen, beside the .cpp, whose records name free functions of namespace vota. Only what a written function needs is
// declared.

namespace vota {

// Target fns 1488 and 1487: the marker file "dinamico/imprimindo" under the internal flash's root
// (comum::CPath::GetPathRootSemSA(FLASH_INTERNA), fn 634), which a printing state opens around each printed file: 1488
// creates it empty (an api::CFile opened "wb" and closed) and 1487 removes it when it exists, each then calling
// api::CSynchronizer::GetInst().Sync() (fns 600, 620). Seven printing functions call both (2890, 11852, 11855, 11991,
// 12068, 12071, 12074). 1487 holds the existence test after a stack prologue of its own: a function binaryen inlined
// into its one caller (docs/reference/facts/reading.md R10), ExisteArquivoImprimindo. No record, slot or string names
// the three: their names, their being free functions of namespace vota (they read no state) and their file are chosen.
void CriaArquivoImprimindo();
bool ExisteArquivoImprimindo();
void RemoveArquivoImprimindo();

// Target fn 1485: whether the load is the training phase. Its name is chosen (no record, slot or string names it), after
// the tree's spelling of the same test (comum::CAppInfo::EhTreinamentoEleitor, CRelatorioTesteImpressora::EhTreinamento).
bool EhTreinamento();

// Target fn 1387: a line of 38 '-' added to a report with IPaper's style 1, aligned as the caller says (11946 and 12110
// pass 0, 11908 and 12105 pass 2). Four vota states' slot 2 call it (11908, 11946, 12105, 12110). No record names
// it; its name, its being a free function and its file are chosen.
void AdicionaSeparador(api::CPaperFormBuilder& builder, api::ETextAlignment alinhamento);

} // namespace vota
