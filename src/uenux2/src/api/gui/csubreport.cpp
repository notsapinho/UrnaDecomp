// api::CSubReport (api/gui/csubreport.h). This file holds the class's constructors, its only members defined out of
// line: the one of target fn 3660 and the one it delegates to, which 3660 inlines (no target function of its own). No
// record names the file or a line, so its path and layout are chosen.

#include "api/gui/csubreport.h"

#include <utility>

namespace api {

CSubReport::CSubReport(std::string titulo, std::string subtitulo, bool habilitado)
    : CSubReport(std::move(titulo), std::move(subtitulo), nullptr, habilitado)
{
}

CSubReport::CSubReport(std::string titulo, std::string subtitulo, std::shared_ptr<IReportPart> parte,
                       bool habilitado)
    : m_titulo(std::move(titulo)),
      m_subtitulo(std::move(subtitulo)),
      m_parte(std::move(parte)),
      m_habilitado(habilitado)
{
}

} // namespace api
