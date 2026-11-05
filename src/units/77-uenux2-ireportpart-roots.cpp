// Roots: api::CFormPart's constructor, fn 601, which the target keeps out of line. In the target each comum class of
// this unit is built by one function, with std::make_shared: fn 11946 builds the four of cpartecandidatos.h (in the
// link: fragment 325's cgeradorzeresima.cpp, inlined into vota::CGeraZeresimaBase::StartState), 5971 comum::CParteRdv
// (in the link: fragment 325's vota::CriaPartesExtratoRDV), 11908 comum::CParteEleitores (in the link: unit 176's
// StartState, through fragment 317's cgeradorrellistaeleitores.cpp). api::CFormPart is built by those three, 11943 and
// 12105, through its constructor. These two stand-ins do the same for 12105, the one caller not written (5971, 11908,
// 11943, 11946 and CParteEleitores's constructor are in the link); the stand-ins for 11946's builds of the four comum
// classes went with it. They are address-taken from a static constructor. Their bodies differ, the second one taking a
// reference. The control blocks the stand-ins instantiate, __shared_ptr_emplace<api::CFormPart>'s D2, D0 and
// __on_zero_shared, come from fragment 317's cgeradorrellistaeleitores.cpp's object, linked ahead of this one. Compiled
// with APP_CXXFLAGS, like the other stand-ins.
#include <memory>
#include <utility>

#include "api/gui/reports/cformpart.h"

namespace {

using Parte = std::shared_ptr<api::IReportPart>;
using Formulario = std::shared_ptr<api::IForm<api::IPaper>>;

__attribute__((noinline)) Parte CriaPartePorForm(Formulario form)
{
    return std::make_shared<api::CFormPart>(std::move(form));
}

// the form is shared here, so the two callers of the constructor differ
__attribute__((noinline)) Parte CriaPartePorFormCopia(const Formulario& form)
{
    return std::make_shared<api::CFormPart>(form);
}

void* volatile ireportpart_sink;

struct SIReportPartRoots {
    SIReportPartRoots()
    {
        ireportpart_sink = reinterpret_cast<void*>(&CriaPartePorForm);
        ireportpart_sink = reinterpret_cast<void*>(&CriaPartePorFormCopia);
    }
} ireportpart_roots;

} // namespace
