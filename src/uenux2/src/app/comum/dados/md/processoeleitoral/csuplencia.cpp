// comum::md::CSuplencia's constructor (the reconstruction's note, not TSE's text). No record names this file: the path
// is csuplencia.h's, chosen; the class is in that header.
#include "app/comum/dados/md/processoeleitoral/csuplencia.h"

namespace comum::md {

CSuplencia::CSuplencia(uebyte ordem, bool temFoto, const CNomesCargo& nomes)
    : m_ordem(ordem), m_temFoto(temFoto), m_nomes(nomes)
{
}

} // namespace comum::md
