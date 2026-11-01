#pragma once

// Reconstruction's note, not TSE's text. api::CApplicationContextGuard and api::CApplicationContextStack: the names are
// the record's (capplicationcontextstack.cpp 45:15,
// `api::CApplicationContextGuard::CApplicationContextGuard(CApplicationContextStack &, CApplicationContext)`), which
// prints the stack unqualified, so its namespace is chosen, and so are this header's path and every member's and
// parameter's name. src/units/193-uenux2-capplicationcontextstack.mk has the rest.

#include <vector>

#include "api/gui/capplicationcontext.h"

namespace api {

// The contexts in force, innermost last: a vector of CApplicationContext at +0 (the guard stores the stack's address,
// and the vector's three words lie at it); that the stack holds nothing else is chosen.
class CApplicationContextStack {
public:
    // A context whose word is set goes only on an empty stack or over another such context, any other always; the
    // result says whether it went.
    bool Push(CApplicationContext context);

    // Takes the context out, with every context pushed after it, searching from the innermost.
    void Pop(const CApplicationContext& context);

    std::vector<CApplicationContext> m_contextos;
};

// Pushes a context for its lifetime: +0 the stack, +4 the context (fn 676 stores both, fn 675 reads both).
class CApplicationContextGuard {
public:
    CApplicationContextGuard(CApplicationContextStack& stack, CApplicationContext context);
    ~CApplicationContextGuard();

private:
    CApplicationContextStack& m_stack;
    CApplicationContext m_context;
};

} // namespace api
