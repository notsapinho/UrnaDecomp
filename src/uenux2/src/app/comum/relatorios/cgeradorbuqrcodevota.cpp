// comum::CGeradorBUQRCodeVota (cgeradorbuqrcodevota.h says why this path). This comment is the reconstruction's. No record
// names this file or gives one of its lines, so every line is a choice. Written here: the constructor, fn 5603, the
// destructor, fns 11244 (D2) and 11243 (D0), the key function, and Slot3, fn 11241. Slot2 (fn 11242) is not
// reconstructed: it traps in src/units/155-uenux2-cgeradorbuqrcode-pending.cpp.
#include "app/comum/relatorios/cgeradorbuqrcodevota.h"

#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdvvota.h"

namespace comum {

CGeradorBUQRCodeVota::CGeradorBUQRCodeVota(const CCabecalhoQRCodeBuilder& cabecalho, ueword comparecimento,
                                           bool campo418, bool campo419, const api::CDateTime& dataHoraEmissao)
    : CGeradorBUQRCode(cabecalho, CRdvVota::GetInst(), CEleitores::GetInst().QuantidadeAptosPorAbrangencia()),
      m_comparecimento(comparecimento),
      m_campo418(campo418),
      m_campo419(campo419),
      m_dataHoraEmissao(dataHoraEmissao)
{
}

CGeradorBUQRCodeVota::~CGeradorBUQRCodeVota() = default;

std::string CGeradorBUQRCodeVota::Slot3(TEleicaoID) const
{
    return "";
}

} // namespace comum
