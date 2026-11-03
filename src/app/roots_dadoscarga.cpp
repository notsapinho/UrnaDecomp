// libc++'s destroy of the two vectors comum::md::CDadosDisponiveisCarga holds: vector<md::CCabecalhoPacote>'s
// __destroy_vector::operator() (target fn 3863) and vector<md::CMunicipioDisponivel>'s (5956). Their target callers are
// 11423 (comum::asn::CConversorDadosDisponiveisCarga::DoDesconverte, unit 245's, matched), 11905
// (vota::CImpressaoVersaoPacotes::StartState, unit 176's pending member) and, for 3863, 3691
// (comum::CGeradorRelVersaoPacoteDados's slot 0, not written).
// - Whose copy: the target's are compiled with strict aliasing (src/units/245-uenux2-cdadosdisponiveiscarga.mk has the
//   measurement), which 11423's directory, app/comum/dados/asn, does not have, and 11905's, app/vota, does. A reading
//   of the data: CImpressaoVersaoPacotes's vtable (@1545168, ledger/vtables.json) lies before
//   CConversorDadosDisponiveisCarga's (@1565788, read from the data), so 11905's object links first and gives the
//   copies. This root stands for that object, src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.cpp,
//   whose StartState is not written (it calls fn 491, which has no name yet, and holds CFileASN::ReadFromFile inlined),
//   and goes once 11905 is written there: unit 176 lists that file ahead of unit 96's list, which holds 11423's object.
// - It compiles at the flags of that file (src/Makefile's rule). Its place in APP_OBJS, after roots_vector.o, is chosen:
//   it brings no callee of its own, and first or last there moves no row (measured). Instantiated so, the two score
//   4 over 104 and 4 over 118 rows against the target, their four calls of free (fn 136) only (pnpm wasm score on the
//   whole link), where the converter object's copies score 20 over 108 and 45 over 127; they match; 11423 is unchanged.
// - The instances need no caller here: 11423 calls both, and unit 245's roots stand for 11905's calls.
#include "app/comum/dados/md/correspondencia/cdadosdisponiveiscarga.h"

template void std::vector<comum::md::CCabecalhoPacote>::__destroy_vector::operator()();
template void std::vector<comum::md::CMunicipioDisponivel>::__destroy_vector::operator()();
