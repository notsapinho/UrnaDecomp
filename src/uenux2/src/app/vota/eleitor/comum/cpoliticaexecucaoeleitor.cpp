// Reconstruction's note, not TSE's text: the records fix lines 33, 34 and 37 (LimpaBufferInput) and 45
// (IPoliticaExecucaoEleitor::GetInst, column 100, the closing parenthesis of
// POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO's invocation). Every other line, the interface's destructor's too, is
// chosen (src/units/165-uenux2-app-vota-execucao.mk).
#include "app/vota/eleitor/comum/ipoliticaexecucaoeleitor.h"

#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pattern/polysingletongetinst.h"
#include "api/util/csystem.h"
#include "ecourna/api/security/irng.hpp"
#include "ecourna/api/uetypes.hpp"

namespace vota::impl {

// (original lines 16-24: content not recovered)
#line 25
IPoliticaExecucaoEleitor::~IPoliticaExecucaoEleitor() = default;

// (original lines 27-28: content not recovered)
#line 29
class CPoliticaExecucaoEleitor : public IPoliticaExecucaoEleitor {
public:
    virtual void LimpaBufferInput() const override
    {
        auto n = api::CPolySingleton<ecourna::api::security::IRng>::instance().GetInt() % 4 + 3;
        const uebyte tempoPausa = api::CPolySingleton<ecourna::api::security::IRng>::instance().GetInt() % 100 + 50;

        for (size_t i = 0; i < n; i++) {
            api::IInputKbd& teclas = api::CPolySingleton<api::IInputKbd>::instance();
            teclas.Clear();
            api::CSystem::Dorme(tempoPausa);
        }
    }
};


POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IPoliticaExecucaoEleitor, CPoliticaExecucaoEleitor)

} // namespace vota::impl
