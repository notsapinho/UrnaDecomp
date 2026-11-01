#pragma once

#include <compare>
#include <string>

namespace comum::md {

class CVoto {
public:
    // ModuloRegistroDigitalVoto::TipoVoto
    enum ETipo {
        LEGENDA = 1,
        NOMINAL,
        BRANCO,
        NULO,
        BRANCO_APOS_SUSPENSAO,
        NULO_APOS_SUSPENSAO,
        NULO_POR_REPETICAO,
        NULO_CARGO_SEM_CANDIDATO,
        NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO,
    };

    CVoto(ETipo tipo, const std::string& numero);

    ETipo GetTipo() const { return m_tipo; }
    const std::string& GetNumero() const { return m_numero; }

    bool EhNominal() const;
    bool EhLegenda() const;
    // Inline is a choice for the call: the target's copy (fn 11316, the one md::CVotosCargos::Nulos passes) calls the
    // static EhNulo (fn 5645), as this form gives; defined in cvoto.cpp beside the static, it held the static inlined
    // (9 over 13 rows, 8 inserted). The target's run 11315 to 11318 (EhBranco, this one, EhLegenda, EhNominal) puts its
    // copy among cvoto.cpp's members, and ours is emitted by cvotoscargos.cpp: neither form tried gives both.
    bool EhNulo() const { return EhNulo(m_tipo); }
    bool EhBranco() const;

    static bool EhNulo(ETipo tipo);

    // Out of line: f11496 holds it inlined by binaryen, a strong_ordering returned from a call (its i32.extend8_s).
    std::strong_ordering operator<=>(const CVoto& outro) const;

private:
    ETipo m_tipo;
    std::string m_numero;
};

} // namespace comum::md
