#include "api/gui/cbuzzfieldmt.h"

#include "api/gui/iscreenmt.h"

namespace api {

void CBuzzFieldMT::Draw(IScreenMT& screen) const
{
    screen.Buzz(m_frequencia, m_duracao);
}

} // namespace api
