// Reconstruction: comum::md::estadoaplicacao::CDadoCorrespondencia's constructor (target fn 5630). No record names this
// file: the name is the class's and the directory the one its converter's mirrors.
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"

#include <utility>

namespace comum::md::estadoaplicacao {

CDadoCorrespondencia::CDadoCorrespondencia(uedword numeroInternoUrna, std::string numeroSerieFC,
                                           api::CDateTime dataHoraCarga, std::string codigoCarga,
                                           CLocalidadeEleitoral secaoCarga, std::vector<uebyte> assinatura,
                                           ecourna::app::dados::CIdentificadorGeradorMidia identificadorGeradorMidia)
    : m_numeroInternoUrna(numeroInternoUrna),
      m_numeroSerieFC(std::move(numeroSerieFC)),
      m_dataHoraCarga(dataHoraCarga),
      m_codigoCarga(std::move(codigoCarga)),
      m_secaoCarga(secaoCarga),
      m_assinatura(std::move(assinatura)),
      m_identificadorGeradorMidia(std::move(identificadorGeradorMidia))
{
}

} // namespace comum::md::estadoaplicacao
