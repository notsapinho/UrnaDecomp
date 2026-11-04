// Roots: the constructors of this unit's classes but CParteEleitores's have no reconstructed caller. In the target each
// comum class is built by one function, with std::make_shared: fn 11946 builds the four of cpartecandidatos.h, 5971
// comum::CParteRdv, 11908 comum::CParteEleitores (in the link: unit 176's StartState, through fragment 317's
// cgeradorrellistaeleitores.cpp). api::CFormPart is built by those three, 11943 and 12105, through its constructor, fn
// 601. These stand-ins do the same: one for each comum class whose builder is not written, so binaryen inlines its
// constructor into it as the target shows, and two for CFormPart, whose constructor the target keeps out of line (its
// callers 11908 and CParteEleitores's constructor are in the link; the two stand for 5971, 11943, 11946 and 12105).
// They are address-taken from a static constructor. Their bodies differ, the second CFormPart one taking a reference;
// binaryen merges the two of each shape that differ only in vptrs into a shared body, which no target function pairs
// with. As unit 29's roots do, this TU includes the class headers for make_shared: the control blocks it instantiates,
// __shared_ptr_emplace<T>'s D2, D0 and __on_zero_shared, are this object's own, except CFormPart's, which fragment
// 317's cgeradorrellistaeleitores.cpp's object, linked ahead of cparteeleitores.cpp's and this one, emits first, and
// they move to the real callers' objects when those land. The destructors are reached through the vtables the
// constructors store, and those of the final classes through __on_zero_shared. Compiled with APP_CXXFLAGS, like the
// other stand-ins.
#include <functional>
#include <memory>
#include <utility>

#include "api/gui/reports/cformpart.h"
#include "app/comum/relatorios/cpartecandidatos.h"
#include "app/comum/relatorios/cparterdv.h"

namespace {

using Parte = std::shared_ptr<api::IReportPart>;
using Formulario = std::shared_ptr<api::IForm<api::IPaper>>;

__attribute__((noinline)) Parte CriaParteCandidatos(Parte a, Parte b, Parte c, Parte d, Parte e)
{
    return std::make_shared<comum::CParteCandidatos>(std::move(a), std::move(b), std::move(c), std::move(d),
                                                     std::move(e));
}

__attribute__((noinline)) Parte CriaParteMajoritarios(Parte a, Parte b, Parte c)
{
    return std::make_shared<comum::CParteCandidatosMajoritarios>(std::move(a), std::move(b), std::move(c));
}

__attribute__((noinline)) Parte CriaParteProporcionais(Parte a, Parte b, Parte c, Parte d, Parte e, Parte f, Parte g,
                                                       std::function<bool()> filtro)
{
    return std::make_shared<comum::CParteCandidatosProporcionais>(std::move(a), std::move(b), std::move(c), std::move(d),
                                                                  std::move(e), std::move(f), std::move(g),
                                                                  std::move(filtro));
}

__attribute__((noinline)) Parte CriaParteConsultas(Parte a, Parte b, Parte c)
{
    return std::make_shared<comum::CParteCandidatosConsultas>(std::move(a), std::move(b), std::move(c));
}

__attribute__((noinline)) Parte CriaParteRdv(Parte a, Parte b, Parte c, Parte d, Parte e)
{
    return std::make_shared<comum::CParteRdv>(std::move(a), std::move(b), std::move(c), std::move(d), std::move(e));
}

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
        ireportpart_sink = reinterpret_cast<void*>(&CriaParteCandidatos);
        ireportpart_sink = reinterpret_cast<void*>(&CriaParteMajoritarios);
        ireportpart_sink = reinterpret_cast<void*>(&CriaParteProporcionais);
        ireportpart_sink = reinterpret_cast<void*>(&CriaParteConsultas);
        ireportpart_sink = reinterpret_cast<void*>(&CriaParteRdv);
        ireportpart_sink = reinterpret_cast<void*>(&CriaPartePorForm);
        ireportpart_sink = reinterpret_cast<void*>(&CriaPartePorFormCopia);
    }
} ireportpart_roots;

} // namespace
