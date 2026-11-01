// Pending members: the comum::CRdvVota slots no source of ours defines yet, which the class's vtable (emitted by
// crdvvota.cpp with slot 0) needs. Their bodies are NOT the target's; they trap.
// - Converte (slot 11, fn 11488): the entity of m_conversor encoded to bytes through the ASN.1 encoder (its messages
//   at 443022 and 443333). Not written: it calls fn 1532 (an ASN1::BEREncoder user with exception landing pads, eight
//   target callers) and fn 518 (no name), and the scan finds no body of ours for either (no-candidate).
// - Desconverte (slot 12, fn 11487, record crdvvota.cpp:237, which stays a blank line there): it decodes the bytes
//   through fn 5680 (no name) into an md::CVotosEleicoesVota, tests it against m_votos with fn 5638 (throwing code 4660
//   with the message at 126733 when they differ) and moves it into m_votos. Not written: 5680 has no body of ours.
// - Confere (slot 13, fn 11486): decodes the bytes the same way (fn 5680) and compares the result with m_votos (fn
//   5638, then the maps and their votes). Not written, for 5680.
#include "app/comum/dados/crdvvota.h"

namespace comum {

std::vector<uebyte> CRdvVota::Converte() const
{
    __builtin_trap();
}

void CRdvVota::Desconverte(const std::vector<uebyte>&)
{
    __builtin_trap();
}

bool CRdvVota::Confere(const std::vector<uebyte>&) const
{
    __builtin_trap();
}

} // namespace comum
