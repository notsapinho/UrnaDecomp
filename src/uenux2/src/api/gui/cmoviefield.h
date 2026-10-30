#pragma once

// api::CMovieField (/home/rubio/tse/uenux2/src/api/gui/cmoviefield.h; the header's name is the class's, no record
// names it). RTTI: an si_class of IFormField<IScreen> (typeinfo 1579496), 56 bytes: fn 5543, which holds
// std::make_shared<CMovieField> with the constructor inlined, allocates 68, 12 of them the control block. The layout
// is what the bodies give:
//   +24/+28 the std::shared_ptr<CMovie> the constructor copies (Draw, fn 11064, passes the movie to IScreen's slot 26;
//           Show, fn 11061, rewinds it to its first frame)
//   +32 the SPoint and +36 the EAnchorPoint Draw passes with it (fn 5543 stores the anchor as the constant 7)
//   +40 a 4-byte member: Show stores 1, Hide (fn 11060) and the constructor 0, each with a 32-bit store, so it is not a
//       bool; nothing in the target reads it
//   +44 a byte the constructor zeroes; nothing else in the target touches it
//   +48/+52 the std::shared_ptr that slot 0 of ITimerScheduler::GetInst() (fn 1259) returns for a std::function
//           holding the constructor's lambda (its __func vtable is @1579508), an api::ITimer: Hide calls its slot 3
//           (Stop), the lambda (fn 11056) its slot 5 (SetInterval) with the time the current frame has left
// The destructor (fn 5524) stops the timer (Hide inlined), then releases +48 and +24. The member names, and the types
// of +40 and +44, are chosen: no evidence gives them. CMovie and ITimer are only declared here, though
// api/gui/cmovie.h and api/util/itimer.h define them.

#include <memory>
#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/iimage.h"
#include "api/gui/primitives.h"

namespace api {

class CMovie;
class IScreen;
class ITimer;

/**
 * Campo que exibe um filme numa posição da tela, quadro a quadro, enquanto está visível.
 */
class CMovieField : public IFormField<IScreen> {
public:
    CMovieField(const SPoint& posicao, const std::shared_ptr<CMovie>& movie, EAnchorPoint ancora);

    ~CMovieField() override;

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

    void Show() override;

    void Hide() override;

    std::string GetTypeName() const override;

private:
    std::shared_ptr<CMovie> m_movie;
    SPoint m_posicao;
    EAnchorPoint m_ancora;
    int m_visivel;
    bool m_pausado;
    std::shared_ptr<ITimer> m_timer;
};

} // namespace api
