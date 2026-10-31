// Roots: keep comum::CMenuBase's destructors (target fns 12235, 6188) in the skeleton link the way the target reaches
// them: only through slots 0 and 1 of the class's vtable (@1550924; the base-object destructor's one table entry,
// elem[1357], is also slot 0 of vota::CMenuMaisInformacoesVota's), with no direct caller (ledger/callgraph.tsv has no
// edge into either). Their users, the constructor that binaryen inlined into fn 6599 (the builder of the
// "Mais informa\xE7\xF5es" menu) and that builder, are not reconstructed yet. Taking the vtable's address from a static
// constructor keeps the same set: it puts both destructors and slot 2 in the table, as the target has them. Compiled as
// app code.
// AdicionaItem (fn 2285) has one caller in the target, fn 6599, which calls it five times; the stand-in calls it twice,
// with the copies a by-value std::shared_ptr takes, and returns a value no target function computes. AdicionaOpcao is
// left with its one caller, AdicionaItem, so that binaryen inlines it as the target's did.
#include <memory>

#include "app/comum/informacao/cmenubase.h"

extern "C" {
extern const char cmenubase_vt[] __asm__("_ZTVN5comum9CMenuBaseE");
}

namespace {

const void* volatile cmenubase_sink;

// stands for fn 6599
__attribute__((noinline)) int w59_itens(comum::CMenuBase& menu, const std::shared_ptr<comum::CItemMenu>& item,
    const std::shared_ptr<comum::CItemMenu>& outro)
{
    menu.AdicionaItem(item);
    menu.AdicionaItem(outro);
    return 9;
}

int (*volatile w59_sink_itens)(comum::CMenuBase&, const std::shared_ptr<comum::CItemMenu>&, const std::shared_ptr<comum::CItemMenu>&);

struct SCMenuBaseRoots {
    SCMenuBaseRoots()
    {
        cmenubase_sink = cmenubase_vt;
        w59_sink_itens = w59_itens;
    }
} cmenubase_roots;

} // namespace
