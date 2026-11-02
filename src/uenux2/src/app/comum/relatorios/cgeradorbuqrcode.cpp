// comum::CGeradorBUQRCode (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbuqrcode.cpp). This comment is the
// reconstruction's. The file's records are GetQtdAptos's (line 80, held by fn 3696, which binaryen inlined it into) and
// RetornaBlocoAssinado's (line 405, held by fn 5604), which is not reconstructed: its line lies past the end of this
// file. Written here: the destructor (its D2 is fn 2251), GetQtdAptos, with its throw on its record's line,
// GetCamposAptos, fn 3696, and GetCamposVotos, fn 5606. The destructor, GetCamposAptos and GetCamposVotos have no record,
// and their lines are a choice.
#include "app/comum/relatorios/cgeradorbuqrcode.h"

#include <format>

#include "app/comum/dados/crdv.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

namespace comum {

CGeradorBUQRCode::~CGeradorBUQRCode() = default;

// (original lines 18-76: content not recovered)
#line 77
const SQtdeAptos& CGeradorBUQRCode::GetQtdAptos(md::ETipoAbrangencia abrangencia) const
{
    if (m_qtdAptos.find(abrangencia) == m_qtdAptos.end()) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9065, std::format("Abrangência não encontrada: {}", static_cast<int>(abrangencia)));
    }
    return m_qtdAptos.at(abrangencia);
}

std::string CGeradorBUQRCode::GetCamposAptos() const
{
    const SQtdeAptos& aptos = GetQtdAptos(CCargos::GetInst().GetCurrent().GetAbrangencia());
    std::string campos;
    campos += std::format("APTA:{} ", static_cast<ueword>(aptos.m_qtdeAptosDaSecao + aptos.m_qtdeAptosTTE));
    campos += std::format("APTS:{} ", aptos.m_qtdeAptosDaSecao);
    campos += std::format("APTT:{} ", aptos.m_qtdeAptosTTE);
    return campos;
}

std::string CGeradorBUQRCode::GetCamposVotos() const
{
    const md::TCargoID cargo = CCargos::GetInst().GetCurrent().GetID();
    const md::TQtdVoto nominais = m_rdv.Nominais(cargo);
    const md::TQtdVoto brancos = m_rdv.Brancos(cargo);
    const md::TQtdVoto nulos = m_rdv.Nulos(cargo);
    const md::TQtdVoto total = m_rdv.Cargo(cargo);
    std::string campos = GetCamposAptos();
    campos += std::format("NOMI:{} ", nominais);
    campos += std::format("BRAN:{} ", brancos);
    campos += std::format("NULO:{} ", nulos);
    campos += std::format("TOTC:{} ", total);
    return campos;
}

} // namespace comum
