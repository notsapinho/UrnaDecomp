// comum::asn's serial-number helpers (/home/rubio/tse/uenux2/src/app/comum/gravadores/asn/util.cpp), then
// comum::asn::CAssinaVotavelBu's GetInst (target fn 3603), its statics, constructor and destructor, then the SHA-512
// helper CalculaHashSha512 (fn 3602), and last CAssinaVotavelBu's three hash members, which have no index (binaryen
// inlines each into fn 10273). None of those has a record: GetInst and CalculaHashSha512 take their use band's places
// (3604, 3603, 3602), the hash members' place after CalculaHashSha512 is a choice, and every name is chosen
// (cassinavotavelbu.h says why the class's members are here). The serial helpers' throws are records of the target,
// so their positions in this file are fixed:
//   3605  ConverteSerialFlash     records at lines 26 and 31, column 15
//   3604  DesconverteSerialFlash  record at line 54, column 15

#include "app/comum/gravadores/asn/util.h"

#include <format>

#include "app/comum/gravadores/asn/cassinavotavelbu.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "ecourna/api/security/csha.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::asn {


std::vector<char> ConverteSerialFlash(const std::string& serial)
{
    if (serial.size() != 8) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8631, "Serial inválido [" + serial + "]");
    }


    if (serial.find_first_not_of("0123456789ABCDEFabcdef") != std::string::npos) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8632, "Serial inválido [" + serial + "]");
    }

    std::vector<char> resultado;
    for (std::size_t i = 0; i < 4; ++i) {
        char byte[3] = {0};
        byte[0] = serial[2 * i];
        byte[1] = serial[2 * i + 1];
        const char valor = static_cast<char>(ecourna::api::util::CStringUtils::HexToInt(byte));
        resultado.push_back(valor);
    }
    return resultado;
}


std::string DesconverteSerialFlash(const std::vector<char>& serial)
{
    std::string resultado;
    for (std::size_t i = 0; i < serial.size(); ++i) {
        resultado += std::format("{:02X}", static_cast<uebyte>(serial[i]));
    }

    if (serial.size() != 4) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8633, "Serial inválido [" + resultado + "]");
    }
    return resultado;
}


CAssinaVotavelBu& CAssinaVotavelBu::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_instancia) {
        s_instancia.reset(new CAssinaVotavelBu);
    }
    return *s_instancia;
}

std::unique_ptr<CAssinaVotavelBu> CAssinaVotavelBu::s_instancia;
std::mutex CAssinaVotavelBu::s_mutex;

CAssinaVotavelBu::CAssinaVotavelBu() = default;

CAssinaVotavelBu::~CAssinaVotavelBu() = default;

std::vector<uebyte> CalculaHashSha512(const std::string& texto)
{
    std::shared_ptr<ecourna::api::security::IHash> hash(new ecourna::api::security::CSha512());
    hash->Reset();
    const std::vector<uebyte> dados(texto.begin(), texto.end());
    hash->Update(dados);
    return hash->Finish();
}

std::vector<uebyte> CAssinaVotavelBu::CalculaHashInicial(uedword pleito, uedword eleicao, TMunicipioID municipio,
    TZonaID zona, TSecaoID secao, const std::string& numeroSerie) const
{
    const std::string texto = std::format("{:05}|{:05}|{:05}|{:04}|{:04}|{:24}", pleito, eleicao, municipio, zona, secao,
        numeroSerie);
    return CalculaHashSha512(texto);
}

std::vector<uebyte> CAssinaVotavelBu::CalculaHashVotavel(const std::vector<uebyte>& hashAnterior, ueword ordem,
    md::TCargoID cargo, int tipoVoto, ueword quantidade, TCandidatoID codigo, TPartidoID partido) const
{
    const std::string texto = std::format("{}|{}|{}|{}|{}|{}|{}",
        ecourna::api::util::CStringUtils::BytesToHexString(hashAnterior), ordem, cargo, tipoVoto, quantidade, codigo,
        partido);
    return CalculaHashSha512(texto);
}

std::vector<uebyte> CAssinaVotavelBu::CalculaHashVotavel(const std::vector<uebyte>& hashAnterior, ueword ordem,
    md::TCargoID cargo, int tipoVoto, ueword quantidade) const
{
    const std::string texto = std::format("{}|{}|{}|{}|{}",
        ecourna::api::util::CStringUtils::BytesToHexString(hashAnterior), ordem, cargo, tipoVoto, quantidade);
    return CalculaHashSha512(texto);
}

} // namespace comum::asn
