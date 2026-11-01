// Pending members: comum::impl::CValidaMidia's slots 3 to 9, which no source holds yet. The class's vtable is emitted
// with EhValida, its key function (app/comum/validamidia/cvalidamidia.cpp), and needs every slot defined; these bodies
// are NOT the target's, they trap. Their names and types are chosen (app/comum/validamidia/ivalidamidia.h says from
// what).
// Target functions, by slot:
//   3  Valida   fn 11172 (2432 B): holds the record of CFabricaConteudoMidiaStart::ConteudoIncializacao
//      (app/comum/validamidia/cfabricaconteudomidiastart.cpp, line 62), builds "infomidia.dat"/"infomidia.vsc" and the
//      "#regex#..." names, and calls fn 5572; CFabricaConteudoMidiaStart has no header in this tree. Its stub was the
//      last of the stub-only file cfabricaconteudomidiastart.cpp, which went with it: writing 11172 writes that file
//      again, with line 62 for that record.
//   4  Slot4    fn 11171 (259 B), calls fns 949 and 2784.
//   5  Slot5    fn 11170 (887 B), formats "#regex#{}{:05}{}{:05}{:04}{:04}-[a-z]+\\.[a-z]+".
//   6  Slot6    fn 11169 (388 B), and 8  Slot8  fn 11167 (1260 B): both build
//      "#regex#[ost][0-9]{5}[a-z]{2}[0-9]{13}-...".
//   7  Slot7    fn 11168 (414 B).
//   9  Slot9    fn 11166 (138 B), calls fns 949 and 5571.
// None is read further than that here; fns 2784, 5571 and 5572 have no name (splat/symbol_addrs.txt), and 949 is
// comum::CPath::GetPathMR (unit 190). Move each into cvalidamidia.cpp when it is reconstructed; delete this file with
// the last.
#include "app/comum/validamidia/cvalidamidia.h"

namespace comum::impl {

SResultadoValidacao CValidaMidia::Valida(EAplicativosDeUrna, EUrnaTurno)
{
    __builtin_trap();
}

int CValidaMidia::Slot4()
{
    __builtin_trap();
}

int CValidaMidia::Slot5(int, int, int, int, int, int)
{
    __builtin_trap();
}

int CValidaMidia::Slot6()
{
    __builtin_trap();
}

int CValidaMidia::Slot7(int)
{
    __builtin_trap();
}

int CValidaMidia::Slot8()
{
    __builtin_trap();
}

void CValidaMidia::Slot9()
{
    __builtin_trap();
}

} // namespace comum::impl
