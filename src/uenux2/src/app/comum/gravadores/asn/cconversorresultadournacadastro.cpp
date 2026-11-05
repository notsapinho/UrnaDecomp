// Reconstruction: comum::asn::GravaArquivo for the voter-register result (target fn 5366) and
// CodificaDadosComparecimento, which binaryen inlines into its one caller, comum::CGravadorRCSecao::GravaResultado (fn
// 11616). No record names the file or its lines: the header's comments say what places them, and the lines are chosen.

#include "app/comum/gravadores/asn/cconversorresultadournacadastro.h"

#include "api/io/asn/cfileasn.h"
#include "ecourna/app/dados/asn/resultadournacadastro/cconversordadoscomparecimento.hpp"
#include "ecourna/app/dados/asn/resultadournacadastro/cconversorresultadournacadastro.hpp"

namespace comum::asn {

void GravaArquivo(const api::CFile& arquivo, const ecourna::app::dados::CResultadoUrnaCadastro& resultado)
{
    const ecourna::app::dados::asn::CConversorResultadoUrnaCadastro conversor;
    api::CFileASN::WriteToFile(arquivo, conversor.Converte(resultado));
}

std::vector<uebyte> CodificaDadosComparecimento(const ecourna::app::dados::CDadosComparecimento& dados)
{
    const ecourna::app::dados::asn::CConversorDadosComparecimento conversor;
    const std::vector<char> codificado = api::CFileASN::CodeObject(conversor.Converte(dados));
    return std::vector<uebyte>(codificado.begin(), codificado.end());
}

} // namespace comum::asn
