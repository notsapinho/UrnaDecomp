#pragma once

// api::CTextFieldUpdateMT (/home/rubio/tse/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.h; no record names
// the class's files: the header's name is the class's and its directory the source's, both chosen, see
// src/units/51-uenux2-ctextfieldupdatemt.mk). RTTI: an si_class of IFormField<IScreenMT> (ledger/classes.json), 56
// bytes: the constructor, inlined into fn 652 with f137(56), stores the position at +24 and the SharedIText at +28,
// starts the string at +36 empty and puts at +48 the timer that slot 0 of ITimerScheduler::GetInst() (fn 1259)
// creates with the interval and a lambda; the constructor's parameters are the ones the RTTI name of that lambda's
// std::function spells (vtable @1590528). Draw (fn 10548) draws the text at +24 and keeps the text it drew at +36;
// Show and Hide (fns 10546, 10545) call slots 2 and 3 of the timer, Start and Stop in api/util/itimer.h; the
// destructor (fn 5411) releases +48, +36 and +28 in that order. The member names are chosen; the timer's type is only
// declared here.

#include <chrono>
#include <memory>
#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreenMT;
class ITimer;

class CTextFieldUpdateMT : public IFormField<IScreenMT> {
public:
    CTextFieldUpdateMT(const SPoint& posicao, const SharedIText& text, const std::chrono::milliseconds& intervalo);

    ~CTextFieldUpdateMT() override;

    void Draw(IScreenMT& screen) const override;

    void Show() override;

    void Hide() override;

private:
    SPoint m_posicao;
    SharedIText m_text;
    mutable std::string m_textoDesenhado;
    std::shared_ptr<ITimer> m_timer;
};

} // namespace api
