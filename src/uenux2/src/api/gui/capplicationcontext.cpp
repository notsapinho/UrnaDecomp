// Reconstruction's note, not TSE's text: api::CApplicationContext's constructor from its five members (target fn 5557)
// and Actions (fn 5555). No record names this file: its path, every line and the include order are chosen, and
// src/units/193-uenux2-capplicationcontextstack.mk says why Actions is apart from the factories Cria and CriaPadrao.
#include "api/gui/capplicationcontext.h"

#include <format>

namespace api {

CApplicationContext::CApplicationContext(std::string titulo, std::string descricao, std::string detalhe,
                                         std::vector<std::string> acoes, int padrao)
    : m_titulo(std::move(titulo)), m_descricao(std::move(descricao)), m_detalhe(std::move(detalhe)),
      m_acoes(std::move(acoes)), m_padrao(padrao)
{
}

std::vector<std::string> CApplicationContext::Actions(int tipo)
{
    switch (tipo) {
    case 0:
        return {"Desligue a urna."};
    case 1:
        return {"Desligue e ligue a urna."};
    case 2:
        return {"Desligue e ligue a urna.", "Se o erro persistir, substitua a urna."};
    case 3:
        return {"Desligue a urna, confira o encaixe da impressora e ligue novamente.",
                "Se o erro persistir, substitua o módulo impressor."};
    case 4:
        return {"Desligue e ligue a urna.", "Se o erro persistir, substitua a mídia de votação."};
    case 5:
        return {"Desligue e ligue a urna.", "Se o erro persistir, substitua a mídia externa."};
    case 6:
        return {"Desligue e ligue a urna.", "Se o erro persistir, substitua a mídia de aplicação."};
    case 7:
        return {"Desligue e ligue a urna.", "Se o erro persistir, substitua a mídia interna."};
    case 8:
        return {"Desligue e ligue a urna.", "Se o erro persistir, substitua a mídia de resultados."};
    case 9:
        return {"Desligue e ligue a urna.", "Se o erro persistir, faça a apuração em outra urna."};
    case 10:
        return {"Desligue a urna eletrônica e envie-a para a Junta Eleitoral."};
    case 11:
        return {"Desligue e ligue a urna.",
                "Se o erro persistir, tire uma foto dessa tela em que apareça o QR Code ao lado e envie para a equipe "
                "de suporte para receber auxílio para resolução do problema."};
    case 12:
        return {"Desligue a urna e faça uma nova carga."};
    case 13:
        return {"Desligue a urna, insira uma mídia de votação usada de outra urna que apresentou problema e "
                "tente novamente."};
    case 14:
        return {"Desligue a urna, insira uma mídia de votação válida e tente novamente."};
    case 15:
        return {"Desligue a urna e substitua-a."};
    case 16:
        return {"Desligue a urna, retire a mídia de votação e a mídia de resultado e utilize o ADH para "
                "ajustar o horário desta urna, ou leve a mídia de votação e a mídia de resultado para "
                "outra urna de contingência com horário correto."};
    default:
        return {std::format("Actions({}) - não reconhecida", tipo)};
    }
}

} // namespace api
