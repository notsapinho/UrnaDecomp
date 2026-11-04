#pragma once

// comum::asn::CAssinaVotavelBu: the chained hash of the BU's votables and its signature. The record of Assinar
// (cassinavotavelbu.cpp:89, inlined into target fn 10273) names the class, the member and its types. A one-byte
// object: fn 3603, which comum::asn::CConversorEntidadeBU::DoConverte (fn 10273) calls before each hash it computes and
// before Assinar, dropping its result, is GetInst, one of the four thunks of fn 2900 that allocate one byte and keep it
// in a static std::unique_ptr (at 1910000) under a static std::mutex (at 1909976), as comum::CLogComum::GetInst does
// (clogcomum.h), with the constructor and the destructor out of line as there. GetInst, the statics and the three hash
// members are defined in gravadores/asn/util.cpp, not in cassinavotavelbu.cpp: 3603 lies between util.cpp's 3604 and
// 3602 in their use band (ledger/ordinals.tsv), its statics' destructors' table slots (4466, 4467) in the run of
// util.cpp's (the CSha512 control block its CalculaHashSha512 builds, 4469 and 4470), and the hash members, which
// binaryen inlines into fn 10273 (each frame opens after 3603's call), read the formatted text's long-string byte before
// CalculaHashSha512's call only when they are in its TU (measured: unit 321's fragment). Their bodies are what those
// frames hold: a std::format of the election's or the votable's fields, the previous hash first as BytesToHexString's
// text, and its SHA-512. The previous hash is a parameter: fn 10273 passes its file's static vector (at 1910004), the
// constant dead-argument elimination folds into each body. Chosen: the hash members' names, their being members (3603's
// call before each), their parameter types beyond what the format's argument types show (unsigned, but the vote type an
// int), the previous hash as a parameter, GetInst's and the statics' names, and this header's path, beside
// cassinavotavelbu.cpp.

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "app/comum/dados/md/candidatura/ccandidatura.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::asn {

class CAssinaVotavelBu {
public:
    ~CAssinaVotavelBu();

    static CAssinaVotavelBu& GetInst();

    std::vector<uebyte> CalculaHashInicial(uedword pleito, uedword eleicao, TMunicipioID municipio, TZonaID zona,
        TSecaoID secao, const std::string& numeroSerie) const;
    std::vector<uebyte> CalculaHashVotavel(const std::vector<uebyte>& hashAnterior, ueword ordem, md::TCargoID cargo,
        int tipoVoto, ueword quantidade, TCandidatoID codigo, TPartidoID partido) const;
    std::vector<uebyte> CalculaHashVotavel(const std::vector<uebyte>& hashAnterior, ueword ordem, md::TCargoID cargo,
        int tipoVoto, ueword quantidade) const;
    std::vector<uebyte> Assinar(const std::vector<uebyte>& hash) const;

private:
    CAssinaVotavelBu();

    static std::unique_ptr<CAssinaVotavelBu> s_instancia;
    static std::mutex s_mutex;
};

} // namespace comum::asn
