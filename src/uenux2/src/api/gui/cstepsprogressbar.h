#pragma once

// api::CStepsProgressBar (/home/rubio/tse/uenux2/src/api/gui/cstepsprogressbar.h, the file is chosen: no record names
// it). RTTI: an si_class of api::IFormField<api::IScreen> (ledger/classes.json); its vtable (@1581868) is
// [~D2 3665, ~D0 10973, Draw 5504, Show 218, Hide 218, Refresh 4118, SetForm 3037, GetTypeName 10969, Rect 10968,
// Move 10970]. The constructor's parameter types are its record's (cstepsprogressbar.cpp:428:15); the layout is what
// that constructor, inlined into vota::CPreShowProgressBar's slot 2 (fn 13550), stores and what Draw (fn 5504) and the
// destructor (fn 3665) read. Every name below (members, parameters, the two structs) is chosen: no evidence gives them.

#include <string>
#include <vector>

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

class IScreen;

/**
 * Um comando de um caminho desenhado na tela: Draw (fn 5504) monta o contorno de cada segmento com eles e o passa às
 * slots 17 e 18 da IScreen, que não estão recuperadas. 56 bytes: o tipo, depois seis doubles (x e y para mover e
 * traçar; x, y, os dois raios e os ângulos inicial e de varredura, em graus, para o arco).
 */
struct SPathCommand {
    enum EType : int {
        MOVE_TO = 0,
        LINE_TO = 1,
        ARC = 2,
        CLOSE = 3,
    };

    SPathCommand() = default;

    SPathCommand(EType tipo, double x, double y, double raioX = 0, double raioY = 0, double anguloInicial = 0,
                 double anguloVarredura = 0)
        : tipo(tipo)
        , x(x)
        , y(y)
        , raioX(raioX)
        , raioY(raioY)
        , anguloInicial(anguloInicial)
        , anguloVarredura(anguloVarredura)
    {
    }

    EType tipo = MOVE_TO;
    double x = 0;
    double y = 0;
    double raioX = 0;
    double raioY = 0;
    double anguloInicial = 0;
    double anguloVarredura = 0;
};

/**
 * Barra de progresso em passos: um segmento por passo, com o seu texto, colorido conforme o passo já foi feito, é o
 * atual ou ainda falta.
 */
class CStepsProgressBar : public IFormField<IScreen> {
public:
    /**
     * @throw CUeGuiError se @p passos estiver vazio
     */
    CStepsProgressBar(const uedword passoAtual, const std::vector<std::string>& passos, const SRect& rect,
                      const TColor corFundoFeito, const TColor corFundoAtual, const TColor corFundoPendente,
                      const TColor corTextoFeito, const TColor corTextoAtual, const TColor corTextoPendente,
                      const TColor corBorda);

    ~CStepsProgressBar() override;

    void Draw(IScreen& screen) const override;

    std::string GetTypeName() const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    void Recalcula(IScreen& screen) const;

    // a segment of the bar as Draw computes it (28 bytes: the vector at +0, the point at +12, the text at +16)
    struct SSegmento {
        std::vector<SPathCommand> contorno;
        SPoint posicaoTexto;
        std::string texto;
    };

    uedword m_passoAtual = 0;               // +24, at most m_passos.size()
    std::vector<std::string> m_passos;      // +28, the text of each step
    SRect m_rect;                           // +40, what Rect returns and Move changes (through fn 1915)
    // +48 .. +72: the seven colours. Their roles are Draw's (+48 / +52 / +56 fill a step done, the current one, one to
    // come; +60 / +64 / +68 write their text; +72 outlines every step); that the parameters come in this order is
    // presumed
    TColor m_corFundoFeito;
    TColor m_corFundoAtual;
    TColor m_corFundoPendente;
    TColor m_corTextoFeito;
    TColor m_corTextoAtual;
    TColor m_corTextoPendente;
    TColor m_corBorda;
    mutable bool m_recalcular = true;       // +76: Draw rebuilds m_segmentos when set, Move sets it
    mutable SFont m_font = {10, 1};         // +80: the font of the steps' text
    mutable std::vector<SSegmento> m_segmentos;   // +88
};

} // namespace api
