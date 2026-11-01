#pragma once

namespace comum {

// The urna's applications. A record names the type, unqualified, in comum::CFabricaConteudoMidiaStart::
// ConteudoIncializacao(const EAplicativosDeUrna, const EUrnaTurno) (ledger/strings.tsv 389206), whose record target fn
// 11172 holds. 11172 tests its first argument against 1 to 20 and against a bit mask (1341440); that this argument is
// the application is a reading, and no code shows what each value is, so the enumerators are not recovered. The name
// and the size are all that is recovered: the comum:: scope and this path, beside app/comum/eurnaturno.h, are chosen.
enum EAplicativosDeUrna {};

} // namespace comum
