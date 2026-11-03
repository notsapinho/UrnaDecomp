#include "app/vota/eleitor/iniciovotacao/auxiliares/ledadosdisponiveiscarga.h"

#include "api/io/asn/cfileasn.h"
#include "app/comum/dados/asn/correspondencia/cconversordadosdisponiveiscarga.h"

namespace vota {

comum::md::CDadosDisponiveisCarga LeDadosDisponiveisCarga(const std::string& arquivo)
{
    comum::asn::CConversorDadosDisponiveisCarga conversor;
    return conversor.Desconverte(api::CFileASN::ReadFromFile<ModuloDadosDisponiveisCarga::DadosDisponiveisCarga>(arquivo));
}

} // namespace vota
