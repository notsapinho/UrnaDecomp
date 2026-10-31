// api::CInputFieldMT::Draw (target fn 10726). This comment is the reconstruction's: no record names this file, and
// src/units/146-uenux2-cinputfieldmt.mk says why it is here and which forms the bytes fix.
#include "api/gui/cinputfieldmt.h"

#include <string>

#include "api/gui/cfixedtext.h"
#include "api/gui/iscreenmt.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace api {

void CInputFieldMT::Draw(IScreenMT& screen) const
{
    const size_t tamanho = m_length;
    const std::string digitado = m_texto;
    std::string texto;
    if (m_mascarado) {
        texto = std::string(digitado.size(), '*');
    } else {
        texto = std::string(digitado);
    }
    ecourna::api::util::CStringUtils::PreencheADireita(texto, '_', tamanho);
    if (m_ativo && digitado.size() < tamanho && !m_cursor) {
        texto[digitado.size()] = ' ';
    }
    screen.ShowText(m_posicao, CFixedText(texto));
}

} // namespace api
