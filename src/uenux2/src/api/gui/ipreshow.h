#pragma once

// api::IPreShow<MEDIA>: RTTI names IPreShow<IScreen>, IPreShow<IScreenMT> and IPreShow<IPaper>, each a class with no base
// and no vtable of its own in the target. Its implementations' vtables have 3 slots: the shared empty destructors (fns 174
// and 144) and slot 2 (api::CPreShowClearMT's is fn 11047). The header's path and the member's name and parameter are
// chosen: slot 2 takes one pointer besides this, and CPreShowClearMT's calls two of IScreenMT's slots through it.

namespace api {

template <typename MEDIA>
class IPreShow {
public:
    virtual ~IPreShow() = default;

    virtual void PreShow(MEDIA& media) = 0;
};

} // namespace api
