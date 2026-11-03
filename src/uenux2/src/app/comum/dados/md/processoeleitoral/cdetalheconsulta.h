#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/crespostaconsulta.h"

namespace comum::md {

// Recovered: the layout, 48 bytes, the one the record of the constructor gives (cdetalheconsulta.cpp:29, two strings, a
// TVectorRespostaConsulta and a string) and fn 11373 builds at CCargo +88, +100, +112 and +124. The first string is
// ModuloEleicao::DetalhePergunta's nome: CCargo's name getters return it for a consulta. The other names are chosen from
// that sequence's fields.
using TVectorRespostaConsulta = std::vector<CRespostaConsulta>;

class CDetalheConsulta {
public:
    CDetalheConsulta(const std::string& nome, const std::string& pergunta, const TVectorRespostaConsulta& respostas,
                     const std::string& textoFonetico);

    const std::string& GetNome() const { return m_nome; }
    // vota::CVotacaoStateAudio::FormataMensagem (fn 6999) copies the fourth string (+36), or the second (+12) when it
    // is empty. The accessors' names are chosen, as the members' are.
    const std::string& GetPergunta() const { return m_pergunta; }
    const std::string& GetTextoFonetico() const { return m_textoFonetico; }
    // The name is chosen: comum::CGeradorBUQRCode's consulta fields (inlined into target fn 5604) copy the vector at
    // +24 from CCargo::GetDetalheConsulta's result.
    const TVectorRespostaConsulta& GetRespostas() const { return m_respostas; }

private:
    std::string m_nome;
    std::string m_pergunta;
    TVectorRespostaConsulta m_respostas;
    std::string m_textoFonetico;
};

} // namespace comum::md
