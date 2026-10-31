// Roots: keep api::CTextBox's members (target fns 10958 Draw, 10957 Move, 10955 and 10954 the destructors, 10953
// GetTypeName, and Rect 10956) in the skeleton link the way the target keeps them. In the target the vtable
// (@1582232) is referenced by the constructor, which binaryen inlined with std::make_shared<CTextBox> into fn 11805, not
// reconstructed; its slots put every member in the table, and no target function calls one directly
// (ledger/callgraph.tsv has no caller of 10953 to 10958). This stand-in builds the box the same way, with the status,
// the alignment and the colours fn 11805 passes, and so has the constructor's one call site. It also instantiates
// __shared_ptr_emplace<api::CTextBox>, the control block of target fns 11115 and 11114 (src/units/README.md, "Companion
// files"). Compiled with APP_CXXFLAGS, like the other stand-ins.
#include <memory>
#include <string>

#include "api/gui/ctextbox.h"

namespace {

__attribute__((noinline)) std::shared_ptr<api::IFormField<api::IScreen>> CaixaTexto(const std::string& texto, api::SPoint posicao,
                                                                                     api::TFontSize tamanhoFonte, api::SPoint tamanho)
{
    return std::make_shared<api::CTextBox>(texto, api::TEXTSTATUS_CONTORNO, posicao, tamanhoFonte, api::ALINHAMENTO_CENTRO, tamanho,
                                           static_cast<api::TColor>(1), static_cast<api::TColor>(2));
}

void* volatile ctextbox_sink;

struct SCTextBoxRoots {
    SCTextBoxRoots() { ctextbox_sink = reinterpret_cast<void*>(&CaixaTexto); }
} ctextbox_roots;

} // namespace
