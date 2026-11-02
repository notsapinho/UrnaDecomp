// Pending members of src/units/217-uenux2-ctesteteclado.mk: the slots vota::testeteclado::CTesteTeclado's vtable needs
// and src/uenux2/src/app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp does not hold yet. Their bodies are
// NOT the target's, they trap. Both are reached only through the vtable. What each waits for (a callee "with no name"
// has no line in splat/matched.txt or splat/symbol_addrs.txt):
// - StartState 11805 (slot 2, 10638 B, records ctesteteclado.cpp:38 and :42, and :121, the record of
//   vota::testeteclado::impl::IGeradorTeclas::GetInst, which it holds inlined): fns 940, 3054, 3853, 3854, 4148 and
//   6579, with no name. Fn 4148 destroys a tree whose nodes hold a std::string at +16, called on a local; fn 3854
//   bounds-checks an index into a vector of 12-byte elements (fn 234 when it is out of range), called on +48 with +60.
// - ProcessInput 11804 (slot 7, 1437 B, records :50, :60 and :81): fns 653, 901, 940, 3054 and 3854, with no name.
// Their record lines in ctesteteclado.cpp stay blank, past that file's end. Move each into ctesteteclado.cpp when it is
// reconstructed, and delete this file with the last.
#include "app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.h"

namespace vota::testeteclado {

void CTesteTeclado::StartState()
{
    __builtin_trap();
}

void CTesteTeclado::ProcessInput()
{
    __builtin_trap();
}

} // namespace vota::testeteclado
