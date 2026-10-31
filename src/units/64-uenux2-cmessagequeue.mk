# uenux2 api::CPriorityMessageQueue<api::SMessage>, a class template in the new header api/ipc/cmessagequeue.h: Remove
# (target fn 2073, record cmessagequeue.h:153:19) and the destructor's D2 and D0 (3162, 3157; slots 0 and 1 of the
# vtable @1534764), with api::SMessage and the 6228 enumerator of EUeIpcError. The unit has no source of its own and no
# companion: unit 116's vota::CMessageEleitor and CMessageOperador instantiate the template, with its constructor
# (inlined into 316 and 270, records at lines 113-114), and call Remove from 4337 and 4343. Its callers 4349 and 10204 are
# not reconstructed. The D2 and D0 match under vota::CMessageEleitor's names, the twin that links first.
#
# What the evidence gives:
# - +4: std::priority_queue, the +16 byte its empty comparator. The constructor in 316 stores the vector's three words
#   and nothing at +16 (l0+52 there, the queue being at l0+36), so that word is no counter. And Remove's body holds
#   priority_queue::pop as an out-of-line function that binaryen inlined: its heap code and the vector's end
#   decrement sit under a second stack-pointer read with no write-back, a leaf's red-zone frame of 16 bytes. A plain
#   vector does not give that: std::pop_heap and pop_back written in Remove leave no such function (clang inlines the
#   heap code, 363 lines of disassembly against the object's 78), and written in a private member of the class they
#   stay out of line but differ from 2073 at body byte 11. A hand-written wrapper at +4 with its own pop was not
#   tried, so std::priority_queue is the reading that fits.
# - +20 std::unique_ptr<ISemaphore> and +24 std::unique_ptr<ISyncCtl>: 4343 calls slot 5 of +20,
#   ISemaphore::Wait(size_t); Remove calls slots 2 and 3 of +24; the constructor's records sit beside the singletons
#   of IGenericFactory<ISemaphore> and IGenericFactory<ISyncCtl> (1534812 to 1534892). The D2 frees both through
#   slot 1, +24 first.
# - +28: Remove zeroes it when the queue is left empty. No insert is identified, so that it is the counter the
#   element's +12 is taken from is a reading, and its name and type are a choice.
# - The element: 8 bytes of message, an int at +8 (i32.lt_s) and an unsigned at +12. The order of the comparator's
#   tests is evidence and its spelling a choice: `<` then `>` on the int, then `>` on the unsigned, each with this
#   element on the left, is what pop's bytes show. The forms below list what changes them and what does not.
# - The destructor is in the class: 3157 holds the D2's body, and the class has no base. `inline virtual ... = default`
#   gives the same object. An empty body in the class gives the same bodies, not the same object: the D0 moves and the
#   module grows 2 B, with all three matches still IDENTICAL.
# - Remove in the class is a choice the column fits: 19 is `throw` at 12 spaces (class, body, if). The same body after
#   the class, with or without `inline`, gives the same object, and a nested block there would give the column too.
#
# Chosen, no evidence names them: the enumerator EUE_IPC_FILA_VAZIA (from its message); SMessage's file and fields;
# SItem, its fields and that it is nested; m_fila, m_semaforo, m_sync, m_ordem. Every line of the header but 153 is a
# choice too.
#
# Forms measured against this one when a roots object held the instances, comparing the object's Remove, pop, D2 and D0
# (em++ with uenux2's flags); a body byte is where the form, linked in that object's place, first differs from 2073:
# - the same bytes: a functor as priority_queue's third argument for operator< with std::less (only pop's symbol
#   differs, and it is inlined); the comparator as if/else if/else or as nested ?:; size_t for the two unsigned; a
#   reference, or an RAII guard that holds the reference, for the pointer `sync`; with -fno-strict-aliasing or without
#   it, and these bodies now compile at uenux2's flags in cthreadeleitor.cpp.o. No evidence names a guard class, so none
#   is invented, although one would explain why the throw path does not Unlock: uenux2 compiles no landing pads, so a
#   guard's destructor leaves no code on that path.
# - other bytes: `a < b || (a == b && c > d)`, `>` tested before `<`, and `a > b` written `b < a`: pop stays out of line
#   and differs from 2073 at body bytes 196, 174 and 206. `==` or `!=` tested first, `std::tie` and `<=>`: clang inlines
#   pop into Remove, and the frame is 32 bytes.
#
# The header's includes need no extra path: UENUX2_PREFIX_MAP rewrites the relative src/uenux2 spelling too, so the
# record's file is /home/rubio/tse/uenux2/src/api/ipc/cmessagequeue.h.
