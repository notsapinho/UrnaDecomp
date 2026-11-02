#pragma once

#include "api/gui/itext.h"

namespace api {
class CPaperFormBuilder;
}

// The free functions of app/vota/comum/votadefs.cpp that other files call. No record names this header, so its path is
// chosen, beside the .cpp, whose records name free functions of namespace vota. Only what a written function needs is
// declared.

namespace vota {

// Target fn 1485: whether the load is the training phase. Its name is chosen (no record, slot or string names it), after
// the tree's spelling of the same test (comum::CAppInfo::EhTreinamentoEleitor, CRelatorioTesteImpressora::EhTreinamento).
bool EhTreinamento();

// Target fn 1387: a line of 38 '-' added to a report with IPaper's style 1, aligned as the caller says (11946 and 12110
// pass 0, 11908 and 12105 pass 2). Four vota states' slot 2 call it (11908, 11946, 12105, 12110). No record names
// it; its name, its being a free function and its file are chosen.
void AdicionaSeparador(api::CPaperFormBuilder& builder, api::ETextAlignment alinhamento);

} // namespace vota
