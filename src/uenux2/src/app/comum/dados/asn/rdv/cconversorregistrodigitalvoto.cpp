// Reconstruction: comum::asn::Codifica and Decodifica (target fn 5680), an RDV's votes to and from its BER bytes
// through the RDV's converter. No record names the file or its lines: cconversorregistrodigitalvoto.h says what places
// the two functions after asn/rdv/cconversoreleicoesvota.cpp's object, and what is chosen.

#include "app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.h"

#include "api/io/asn/cfileasn.h"

namespace comum::asn {

std::vector<uebyte> Codifica(
    const IConversorASN<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto, md::CVotosEleicoesVota>& conversor,
    const md::CVotosEleicoesVota& votos)
{
    const ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto entidade = conversor.Converte(votos);
    const std::vector<char> codificado = api::CFileASN::CodeObject(entidade);
    return std::vector<uebyte>(codificado.begin(), codificado.end());
}

md::CVotosEleicoesVota Decodifica(
    const IConversorASN<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto, md::CVotosEleicoesVota>& conversor,
    const std::vector<uebyte>& dados)
{
    const std::vector<char> codificado(dados.begin(), dados.end());
    const ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto entidade =
        api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto>(codificado);
    return conversor.Desconverte(entidade);
}

} // namespace comum::asn
