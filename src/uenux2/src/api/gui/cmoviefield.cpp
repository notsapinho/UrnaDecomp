// api::CMovieField (/home/rubio/tse/uenux2/src/api/gui/cmoviefield.cpp, the file Rect's record names).
// Target functions of this file:
//   5524 / 11065  ~CMovieField() (base-object / deleting)   (here; out of line: the D0 calls the D2 and drops its
//                 result; written as a call to Hide: Hide's two stores spelled out give the same object)
//   11064 Draw(IScreen&) const                                    (here)
//   11063 Rect() const   record at line 53, column 12                               (here)
//   11062 Move(const SPoint&), 11061 Show(), 11060 Hide()         (here)
//   11059 GetTypeName() const   a thunk into binaryen's merge 2904 (here)
// The constructor (inlined, with std::make_shared, into fn 5543; its lambda's std::function members are fns 11054-11058)
// is not reconstructed: it calls ITimerScheduler::GetInst (fn 1259). The definitions follow the target's order (the
// uses-1 band 11059-11065 of ledger/ordinals.tsv: D0, Draw, Rect, Move, Show, Hide, GetTypeName); no record falls in
// them, so their lines are a choice: the destructor and Draw above Rect's line 53, the others below it.

#include "api/gui/cmoviefield.h"

#include "api/gui/cmovie.h"
#include "api/gui/iform.h"
#include "api/gui/iimagesurfaceops.h"
#include "api/gui/iscreen.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/itimer.h"

namespace api {

// (original lines 25-37: content not recovered)
#line 38
CMovieField::~CMovieField()
{
    Hide();
}


void CMovieField::Draw(IScreen& screen) const
{
    screen.DrawMovie(m_posicao, *m_movie, m_ancora);
}


SRect CMovieField::Rect() const
{
    const SPoint& tamanho = m_movie->Tamanho();
    return CPolySingleton<IScreen>::instance().GetImageSurfaceOps().ImageRect(tamanho.x, tamanho.y, m_posicao, m_ancora);
}


void CMovieField::Move(const SPoint& posicao)
{
    if (posicao.x == m_posicao.x && posicao.y == m_posicao.y) {
        return;
    }

    m_posicao = posicao;

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

void CMovieField::Show()
{
    m_visivel = 1;
    m_movie->Rewind();

    if (m_form != nullptr && m_form->IsVisible()) {
        m_alterado = true;
        m_form->Refresh();
    }
}

void CMovieField::Hide()
{
    m_timer->Stop();
    m_visivel = 0;
}

std::string CMovieField::GetTypeName() const
{
    return "CMovieField";
}

} // namespace api
