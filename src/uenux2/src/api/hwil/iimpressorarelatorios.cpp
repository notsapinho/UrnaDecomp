// api::IImpressoraRelatorios (/home/rubio/tse/uenux2/src/api/hwil/iimpressorarelatorios.cpp). Its target functions:
//   10881  SetStyle(ELPStyle)  (its throw is the record at line 22, column 15; the class's key function)
//   10880  GetColumns()        (slot 5; 10880 sits next to 10881 in their use band; its place in the file is chosen)

#include "api/hwil/iimpressorarelatorios.h"

namespace api {

// (original lines 9-18: content not recovered)
#line 19
void IImpressoraRelatorios::SetStyle(ELPStyle style)
{
    if (style == ELP_STYLE_NONE) {
        throw CUeCodedPrinterError(EUE_PRINTER_ESTILO_INVALIDO, "Invalid style", "no style", 2);
    }
    if (style != m_style) {
        ApplyStyle(style);
        m_style = style;
    }
}

int IImpressoraRelatorios::GetColumns()
{
    return m_style == ELP_STYLE_LARGURA_DUPLA ? 19 : 38;
}

} // namespace api
