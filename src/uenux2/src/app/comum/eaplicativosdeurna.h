#pragma once

#include "app/comum/dados/md/estadoaplicacao/eurna.h"

namespace comum {

// The urna's applications. A record names the type, unqualified, in comum::CFabricaConteudoMidiaStart::
// ConteudoIncializacao(const EAplicativosDeUrna, const EUrnaTurno) (ledger/strings.tsv 389206), whose record target fn
// 11172 holds. 11172 tests its first argument against 1 to 20 and against a bit mask (1341440); that this argument is
// the application is a reading. The name and the size are recovered, and the values 1 to 20 are the range
// comum::impl::CValidaMidia::Valida (fn 11172) allows. No code shows what an application is: what each value gets from
// ConteudoIncializacao is below its enumerator. Every enumerator's name is chosen, from its value; the comum:: scope and
// this path, beside app/comum/eurnaturno.h, are chosen.
enum EAplicativosDeUrna {
    eAplicativo01 = 1,
    eAplicativo02,
    eAplicativo03,
    eAplicativo04,
    eAplicativo05,
    eAplicativo06,
    // 7 to 10: a turn is required, and no content
    eAplicativo07,
    eAplicativo08,
    eAplicativo09,
    eAplicativo10,
    // 11 to 14 and 18: "infomidia.dat" and "infomidia.vsc", any turn
    eAplicativo11,
    eAplicativo12,
    eAplicativo13,
    eAplicativo14,
    // 15, 16 and 17: a turn is required, and those two with the 't', 'o' and 's' packages ("-pkgsa\.jez", "-pkgsa\.vsc")
    eAplicativo15,
    eAplicativo16,
    eAplicativo17,
    eAplicativo18,
    eAplicativo19,
    // 20: "##.pub", "##.id", "##ue" and "###ue##.vpe", any turn
    eAplicativo20,
};

} // namespace comum

// ConteudoIncializacao's message passes the application through table slot 3057, fn 536, the handle binaryen shares
// among the enums formatted as unsigned (comum::SFormatoEnum, app/comum/dados/md/estadoaplicacao/eurna.h). The base is
// chosen as theirs is.
template <>
struct std::formatter<comum::EAplicativosDeUrna> : comum::SFormatoEnum {};
