// Pending members: the comum::CGravadorBU member no source of ours holds yet. Its body is NOT the target's, it traps.
// GravaResultado, fn 11629 (slot 7, 15903 B, records cgravadorbu.cpp:484 and :485, with those of LeChavePublica and
// MontaEntidadeBU, lines 542 to 636, inlined into it), is the class's first out-of-line virtual member, so its vtable
// (@1554132) is emitted here, and with it the implicit destructors of slots 0 and 1 (fns 5857, 11628), the compiler's
// code for the class definition in app/comum/gravadores/cgravadorbu.h. GravaResultado calls fns 3819
// (comum::MontaVotosCargos, which calls AcrescentaVotoVotavel, fn 3820, written in cgravadorbu.cpp at its record's line
// 221), 3818 (FiltraCargos, written there after them), 2853, 3817, 3824, 3735, 3815 and 2724 (written), and it waits
// for: 1555 (a std::string copy kept out of line, called by 2725, 11419, 11616 and 11629, none written, so nothing
// names it); md::CEntidadeBU's constructor and ValidaCriacao (records centidadebu.cpp:159 to :177, inlined into it;
// centidadebu.h has the layout, fragment 321's, and no constructor) and the
// writer of its entity through comum::asn::CConversorEntidadeBU (its Converte record iconversorasn.h:56 and
// CodeObjectFunction's cfileasn.h:161 and :171 for ModuloBoletimUrna::EntidadeBoletimUrna, inlined into it; the
// converter's DoConverte, fn 10273, matches, fragment 321's), LeChavePublica and MontaEntidadeBU (its records, inlined), the
// results of each election (a helper of its own over CConfiguracaoEleicao::GetCargos, fn 3775, FiltraCargos, 3819 and
// the RDV's slot 10), and the encryption of the entity (CSymmetricCipherFactory::Create, the HSM, CPlainText and
// CCepescCipher::Encrypt) into the envelope's md::CSeguranca. It goes in cgravadorbu.cpp when it is reconstructed, and
// the vtable and the destructors move there with it, under the same symbols. Delete this file with it. cgravadorbu.cpp
// ends after FiltraCargos: its record lines 484, 485, 542, 552, 560 and 636 are this member's, LeChavePublica and
// MontaEntidadeBU inlined into it.
#include "app/comum/gravadores/cgravadorbu.h"

namespace comum {

void CGravadorBU::GravaResultado(api::CFile&) const
{
    __builtin_trap();
}

} // namespace comum
