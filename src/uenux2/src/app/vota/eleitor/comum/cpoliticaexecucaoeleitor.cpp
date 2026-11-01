#include "app/vota/eleitor/comum/ipoliticaexecucaoeleitor.h"

#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "ecourna/api/security/irng.hpp"
#include "ecourna/api/uetypes.hpp"

namespace vota::impl {

// (original lines 11-26: content not recovered)
#line 27
class CPoliticaExecucaoEleitor : public IPoliticaExecucaoEleitor {
public:
    CPoliticaExecucaoEleitor();

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





CPoliticaExecucaoEleitor::CPoliticaExecucaoEleitor() = default;

} // namespace vota::impl
