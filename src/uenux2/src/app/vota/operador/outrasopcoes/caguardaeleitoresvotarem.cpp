// vota::CAguardaEleitoresVotarem (/home/rubio/tse/uenux2/src/app/vota/operador/outrasopcoes/caguardaeleitoresvotarem.cpp).
// This comment is the reconstruction's. The file's one record is StartState's, line 47, column 5 (the
// CPolySingleton<api::IInputMT>::instance() call); the functions above it are on chosen lines.
#include "app/vota/operador/outrasopcoes/caguardaeleitoresvotarem.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CAguardaEleitoresVotarem::~CAguardaEleitoresVotarem() = default;

CAguardaEleitoresVotarem::CAguardaEleitoresVotarem()
    : comum::CAppState(EVENTO_NENHUM)
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Aguarde até todos os", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("eleitores presentes votarem", api::SPoint{1, 3}, api::ALINHAMENTO_CENTRO);
    m_form = builder.GetInteractiveForm("", true);
}

CAguardaEleitoresVotarem& CAguardaEleitoresVotarem::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAguardaEleitoresVotarem());
    }
    return *s_inst;
}

std::unique_ptr<CAguardaEleitoresVotarem> CAguardaEleitoresVotarem::s_inst;
std::mutex CAguardaEleitoresVotarem::s_mutex;

// (original lines 38-42: content not recovered)
#line 43
void CAguardaEleitoresVotarem::StartState()
{
    m_form->Slot2();
    api::CSystem::Dorme(3000);
    api::CPolySingleton<api::IInputMT>::instance().Clear();
    m_pNextState = &CPedeIdentidade::GetInst();
}

} // namespace vota
