// comum::md::CHorarioVerao. The reconstruction's own note: the blank lines stand for text not recovered. Lines 29 and
// 32 are the records of the constructor, which fn 11384 holds inlined and which is not written: they stay blank.
// src/units/147-uenux2-chorarioverao.mk says what the member below rests on.
#include "app/comum/dados/md/chorarioverao.h"

namespace comum::md {



























bool CHorarioVerao::Contem(const api::CDate& data) const
{
    return m_inicio <= data && data < m_fim;
}

} // namespace comum::md
