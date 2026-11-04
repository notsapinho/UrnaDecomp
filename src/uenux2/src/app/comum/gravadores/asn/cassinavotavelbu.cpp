// comum::asn::CAssinaVotavelBu (/home/rubio/tse/uenux2/src/app/comum/gravadores/asn/cassinavotavelbu.cpp). Assinar's
// record is a record of the target (line 89, column 21: the default argument of CPolySingleton<IPkcs11>::instance()),
// so its line is fixed; where it starts is a choice. Assinar has no index of its own: binaryen inlines it into its one
// caller, held by CConversorEntidadeBU::DoConverte (fn 10273), where it opens a frame. The class's other members are
// here too, with CalculaHashSha512 (fn 3602, util.h): the target's data place GetInst's statics and CalculaHashSha512
// in a window whose one record is this file's (a reading), and the hash members must share CalculaHashSha512's TU
// (cassinavotavelbu.h gives both). GetInst (fn 3603) precedes its statics, the form unit 111's fragment measures, and
// CalculaHashSha512, as their use band orders them; the rest's order and place above Assinar are chosen.

#include "app/comum/gravadores/asn/cassinavotavelbu.h"

#include <format>

#include "api/pattern/cpolysingleton.h"
#include "api/pkcs11/ipkcs11.h"
#include "app/comum/gravadores/asn/util.h"
#include "ecourna/api/security/csha.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::asn {

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

// (original lines 72-86: content not recovered)
#line 87
std::vector<uebyte> CAssinaVotavelBu::Assinar(const std::vector<uebyte>& hash) const
{
    auto& oPkcs11 = api::CPolySingleton<api::pkcs11::IPkcs11>::instance();
    oPkcs11.Slot23();
    const api::pkcs11::SResultadoAssinatura resultado = oPkcs11.Assina(hash);
    oPkcs11.Slot24();
    return resultado.GetAssinatura();
}

} // namespace comum::asn
