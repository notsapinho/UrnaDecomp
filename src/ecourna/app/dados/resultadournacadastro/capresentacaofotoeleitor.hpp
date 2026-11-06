#pragma once

namespace ecourna::app::dados {

// How the voter's photo was shown: state and result, 8 bytes, trivially copyable (CEstadoComparecimento copies it
// as one i64). The constructor is out of line (capresentacaofotoeleitor.cpp): CConversorApresentacaoFotoEleitor's
// DoDeconverte (fn 9087) calls it, and binaryen folds its body into fn 1081 with other two-word constructors. Enumerators follow
// ModuloResultadoUrnaCadastro::{Estado,Resultado}ApresentacaoFotoEleitor; values synthesised (0-based).
class CApresentacaoFotoEleitor {
public:
    enum EEstado {
        EleitorSemFoto,
        Apresentada,
        NaoApresentadaPorErro,
    };

    enum EResultado {
        SemErro,
        ErroFormato,
        ErroFormacaoImagem,
        ErroResolucao,
        ErroCompressao,
        ErroProfundidadeCores,
        ErroApresentacao,
        ErroDecifrandoBuffer,
        ErroDesconhecidoDeCriptografia,
    };

    CApresentacaoFotoEleitor(EEstado estado, EResultado resultado);

    EEstado GetEstado() const { return m_estado; }
    EResultado GetResultado() const { return m_resultado; }

    // comum::md::CEleitorDinamico's equality (inlined into target fn 5761) compares the two words with no branch
    // between them, as an inline function of their own gives; the GetEstado and GetResultado tests written in place
    // keep a branch (src/units/383-uenux2-celeitores-dinamicos.mk). Defaulted is chosen.
    bool operator==(const CApresentacaoFotoEleitor&) const = default;

private:
    EEstado m_estado;
    EResultado m_resultado;
};

} // namespace ecourna::app::dados
