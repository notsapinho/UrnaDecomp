// comum::CMenuBase (app/comum/informacao/cmenubase.cpp, a chosen path: cmenubase.h says why). No record names a line
// of this file; the reconstruction's notes are in cmenubase.h and src/units/59-uenux2-cmenubase.mk. MontaMenu, the
// class's key function, is still pending there.

#include "app/comum/informacao/cmenubase.h"

#include <format>

#include "app/comum/informacao/citemmenu.h"

namespace comum {

void CMenuBase::AdicionaItem(std::shared_ptr<CItemMenu> item)
{
    m_itens.push_back(item);
    if (item->Slot2()) {
        AdicionaOpcao(item->GetChave());
    }
}

void CMenuBase::AdicionaOpcao(unsigned int chave)
{
    m_opcoes += std::format("{}", chave);
}

} // namespace comum
