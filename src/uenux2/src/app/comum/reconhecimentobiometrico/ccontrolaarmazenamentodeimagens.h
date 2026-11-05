#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include "ecourna/api/security/cepesc/ccipheredout.hpp"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// comum::CControlaArmazenamentoDeImagens: target fn 2725 and what it holds (src/units/293-uenux2-
// ccontrolaarmazenamentodeimagens.mk). Recovered: the class's name and the names, signatures and `static` of
// GerarCaminhosUnicos, LeChavePublica and CifrarWsq, from their records (ccontrolaarmazenamentodeimagens.cpp:73, :117,
// :127, :135, :149, :152), which fn 2725 holds inlined; no record names a data member, so the class declares none.
// Chosen: ArmazenaImagem's name (fn 2725), GravaWsqCifrado's, GravaEnvelope's and ZeraDataHora's (inlined into it),
// their being static members, the parameters' names and the types the records do not spell, the unused file name's
// place among ArmazenaImagem's parameters, ID_INVALIDO's name and type (the 999999 2725 returns and its callers
// compare with) and each member's access.
class CControlaArmazenamentoDeImagens {
public:
    static constexpr uint32_t ID_INVALIDO = 999999;

    static uint32_t ArmazenaImagem(const std::vector<uebyte>& wsq, const std::string& nomeArquivo,
        const std::string& diretorio, const std::string& diretorioExterno, const std::string& prefixo);

private:
    static std::tuple<uint32_t, std::string, std::string> GerarCaminhosUnicos(const std::string& prefixo,
        const std::string& diretorio, const std::string& diretorioExterno);
    static std::vector<uebyte> LeChavePublica();
    static ecourna::api::cepesc::CCipheredOut CifrarWsq(const std::vector<uebyte>& wsq);
    static void GravaWsqCifrado(const std::string& caminho, const std::vector<uebyte>& wsq);
    static void GravaEnvelope(const std::string& caminho, const ecourna::api::cepesc::CCipheredOut& cifrado);
    static void ZeraDataHora(const std::string& caminho);
};

} // namespace comum
