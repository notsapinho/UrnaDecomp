// comum's mesario registration: the voter's screen of the registration (target fn 1255) and its two fonts. The file is
// the one comum::CRegistrarMesarios's records name (line 68, GetControlador, which fns 10391 and 10392 hold inlined);
// that line stays blank, as nothing here writes the class, and what this file defines follows it, at lines that are a
// choice. That the screen's code is in this file is a choice: its fonts lie between CRegistrarMesarios's typeinfo name
// and CPedeTituloMesario's, an order that fits either file (src/units/247-uenux2-cregistrarmesarios.mk says why).
#include "app/comum/comparecimentomesario/estados/cregistrarmesarios.h"

#include "api/gui/cformbuilder.h"
#include "api/gui/iform.h"
#include "api/gui/itext.h"

// (original lines 12-60: content not recovered)
#line 61
// <stubs>
// f10392 · 209 B · unmatched · name unknown
// void f10392(i32) { ... }

// f10391 · 17 B · unmatched · name unknown
// void f10391(i32) { ... }
// </stubs>

namespace comum {

const api::SFont FONTE_TITULO_REGISTRO_MESARIOS{35, 0};
const api::SFont FONTE_TEXTO_REGISTRO_MESARIOS{25, 0};

std::shared_ptr<api::IForm<api::IScreen>> TelaRegistroMesarios()
{
    api::CFormBuilder builder;
    builder.AddStatusHeader(api::CFormBuilder::STATUS_DATA_HORA | api::CFormBuilder::STATUS_MODO |
                            api::CFormBuilder::STATUS_ICONE_BATERIA);
    builder.AddTextField("REGISTRO DE MESÁRIOS", api::SPoint(320, 150), FONTE_TITULO_REGISTRO_MESARIOS,
                         api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    builder.AddTextField("Siga as instruções no terminal do mesário.", api::SPoint(320, 250),
                         FONTE_TEXTO_REGISTRO_MESARIOS, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2),
                         static_cast<api::TColor>(1));
    return builder.GetForm("");
}

} // namespace comum

// <stubs>
// f3610 · 971 B · unmatched · placement: link order · name unknown
// ? f3610() { ... }
// </stubs>
