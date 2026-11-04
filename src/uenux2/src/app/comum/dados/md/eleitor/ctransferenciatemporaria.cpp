// Reconstruction: comum::md::CTransferenciaTemporaria's two constructors and ValidaConstrucao, which comum::asn::
// CConversorEntidadeEleitores's slot 2 (target fn 11411) holds inlined (ctransferenciatemporaria.h). The records place
// two throws, line 25, column 15, and line 35, column 19; every other line, the three-argument constructor's place
// after ValidaConstrucao, the tests' forms and the first throw's code are chosen.
#include "app/comum/dados/md/eleitor/ctransferenciatemporaria.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 11-21: content not recovered)
#line 22
CTransferenciaTemporaria::CTransferenciaTemporaria(ETransferenciaTemporaria tipo) : m_tipo(tipo), m_uf(""), m_municipio(0)
{
    if (tipo != SEM_TRANSFERENCIA) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8069, "Construtor exclusivo para sem transferência.");
    }
}


void CTransferenciaTemporaria::ValidaConstrucao(ETransferenciaTemporaria tipo)
{
    switch (tipo) {
        case SEM_TRANSFERENCIA:

            throw CUeComumDadosError(EUE_COMUM_DADOS_8070, "Construtor exclusivo para transferências de fato.");
        default:
            break;
    }
}

CTransferenciaTemporaria::CTransferenciaTemporaria(ETransferenciaTemporaria tipo, const std::string& uf, uedword municipio)
    : m_tipo(tipo), m_uf(uf), m_municipio(municipio)
{
    ValidaConstrucao(tipo);
}

} // namespace comum::md
