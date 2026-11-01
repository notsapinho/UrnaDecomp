#pragma once

#include "api/gui/ipreshow.h"
#include "api/gui/iscreen.h"
#include "api/gui/primitives.h"

namespace api {

// RTTI: an si_class of IPreShow<IScreen>, vtable @1577888 [174, 144, 11139]. fn 11140 builds it as a
// std::shared_ptr<IPreShow<IScreen>>. No key function: its vtable and typeinfo (1577888, 1577908) lie in
// cformbuilder.cpp's data, after that file's record at 1577872 and beside CPreShowNothing<IScreen>'s, a copy in a user's
// object. So PreShow is inline. Slot 2 (fn 11139) calls IScreen's slot 4, Clear(TColor), with 1. The path is chosen,
// beside ipreshow.h and cpreshowclearmt.h, and so is the parameter's name.
class CPreShowClearScreen : public IPreShow<IScreen> {
public:
    void PreShow(IScreen& tela) override { tela.Clear(static_cast<TColor>(1)); }
};

} // namespace api
