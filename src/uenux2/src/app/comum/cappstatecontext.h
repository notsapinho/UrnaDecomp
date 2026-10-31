#pragma once

// comum::CAppStateContext: the head alone. Its vtable @1551304 holds the shared bodies 174 and 144, so the class has a
// virtual destructor that destroys nothing. vota::CThreadVota holds one in a std::unique_ptr at +32, which fn 2126 frees
// through slot 1, and the threads' Run build it (fn 3844 in 7061 and 10204). No record names this header, so its path
// is chosen, beside app/comum/cappstate.h, whose vtable and typeinfo lie just before this class's. Its constructor and
// members (fn 3842 and the code inlined into fn 4349) are not reconstructed, so nothing may construct it yet.

namespace comum {

class CAppStateContext {
public:
    virtual ~CAppStateContext() = default;
};

} // namespace comum
