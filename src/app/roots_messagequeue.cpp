// The executable TU's copy of api::CPriorityMessageQueue<api::SMessage>::Insert (api/ipc/cmessagequeue.h; target fn
// 501) and of what it instantiates: api::CSyncCtlGuard's destructor (5528), priority_queue::push (11076, table slot
// 237, which 501 passes to invoke_vii) and the destructor of push's __split_buffer (5523, a thunk into binaryen's merge
// body 2896, which roots_coderenv.o's __split_buffer<char> destructor, 2704, calls too).
// src/units/269-uenux2-cmessagequeue-insert.mk has the evidence and the measurements.
// - Whose copy. 501 and 11076 have landing pads and 5528 is out of line with a terminate pad, so an -fexceptions
//   object's at -Oz: uenux2 compiles without -fexceptions, and at -Os clang inlines 5528 and push into Insert. So this
//   file compiles at VOTA_WEB_CXXFLAGS, the executable TU's rule, after that TU's object (ahead of it, the same
//   instance takes 14 rows of other classes out of match); its place among the roots at that rule is chosen, since
//   first among them or last in APP_OBJS gives the same matches. That the copy is that TU's is a
//   reading: the code that calls Insert at that level is not written, Insert(const SMessage&) (7708, `f501(p0, p1, 1)`)
//   and over it 3903, read as a body binaryen merged from three posts (10376, 11026 and 11100, table slots 110, 57, 55).
// - Insert's target callers our link holds (7178, 7221, 11914, 11994 and the other matched states, uenux2 objects) call
//   it as the target's do, so the explicit instantiation needs no caller stand-in. It goes when the code above is
//   written.
#include "api/ipc/cmessagequeue.h"

template void api::CPriorityMessageQueue<api::SMessage>::Insert(const api::SMessage&, int);
