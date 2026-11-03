#include "app/comum/dados/crespostas.h"

#include <format>

#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/crespostasds.h"
#include "ecourna/api/pattern/singleton.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

using ecourna::api::util::CStringUtils;

// (original lines 14-27: content not recovered)
#line 28
SINGLETON_IMPL_GET_INST(CRespostas, s_mutex, s_instancia)






std::unique_ptr<CRespostas> CRespostas::s_instancia;
std::mutex CRespostas::s_mutex;

CRespostas::~CRespostas() = default;

std::string CRespostasDSNumero::operator()() const
{
    return std::format("{:0{}}", CRespostas::GetInst().GetCurrent()->GetNumero(), m_digitos);
}

std::string RespostaCorrente()
{
    return CRespostas::GetInst().GetCurrent()->GetResposta();
}

std::string LinhaRespostaCorrente()
{
    const uebyte digitos = CCargos::GetInst().GetCurrent().GetNumeroDigitos();
    const md::CRespostaConsulta* resposta = CRespostas::GetInst().GetCurrent();
    const std::string numero = std::format("{:0{}}", resposta->GetNumero(), digitos);
    return "  " + CStringUtils::PreencheADireita(resposta->GetResposta(), ' ', 26) + CStringUtils::PreencheAEsquerda(numero, ' ', 10);
}

std::vector<TCandidatoID> CRespostas::GetNumeros(TCargoID cargo) const
{
    std::vector<TCandidatoID> numeros;
    const uedword primeira = cargo * 1000000;
    const uedword ultima = static_cast<TCargoID>(cargo + 1) * 1000000;
    for (const auto& [chave, resposta] : m_registros) {
        if (chave >= primeira && chave < ultima) {
            numeros.push_back(resposta.GetNumero());
        }
    }
    return numeros;
}

md::CRespostaConsulta* CRespostas::Busca(TCargoID cargo, TCandidatoID numero)
{
    return Find(cargo * 1000000 + numero);
}

uedword ChaveResposta(md::TCargoID cargo, TCandidatoID numero)
{
    return cargo * 1000000 + numero;
}

} // namespace comum
