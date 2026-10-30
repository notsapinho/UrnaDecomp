# uenux2 api::CPriorityMessageQueue<api::SMessage>, a class template in the new header api/ipc/cmessagequeue.h: Remove
# (target fn 2073, record cmessagequeue.h:153:19) and the destructor's D2 and D0 (3162, 3157; slots 0 and 1 of the
# vtable @1534764), with api::SMessage and the 6228 enumerator of EUeIpcError. The unit has no source of its own: the
# roots file instantiates the template (see its header). Remove's callers (4337, 4343, 4349, 10204) and the constructor
# (inlined into 316 and 270, records at lines 113-114, which stay blank) are not reconstructed.
#
# What the evidence gives:
# - +4: std::priority_queue, the +16 byte its empty comparator. The constructor in 316 stores the vector's three words
#   and nothing at +16 (l0+52 there, the queue being at l0+36), so that word is no counter. And Remove's body holds
#   priority_queue::pop as an out-of-line function that binaryen inlined: its heap code and the vector's end
#   decrement sit under a second stack-pointer read with no write-back, a leaf's red-zone frame of 16 bytes. A plain
#   vector with std::pop_heap and pop_back leaves no such function: clang inlines the heap code into Remove (363 lines
#   of disassembly against the object's 78).
# - +20 std::unique_ptr<ISemaphore> and +24 std::unique_ptr<ISyncCtl>: 4343 calls slot 5 of +20,
#   ISemaphore::Wait(size_t); Remove calls slots 2 and 3 of +24; the constructor's records sit beside the singletons
#   of IGenericFactory<ISemaphore> and IGenericFactory<ISyncCtl> (1534812 to 1534892). The D2 frees both through
#   slot 1, +24 first.
# - +28: Remove zeroes it when the queue is left empty. No insert is identified, so that it is the counter the
#   element's +12 is taken from is a reading, and its name and type are a choice.
# - The element: 8 bytes of message, an int at +8 (i32.lt_s) and an unsigned at +12. The comparator's three-way shape
#   is what leaves pop out of line, so its form is evidence: see below.
# - The destructor is in the class: 3157 holds the D2's body, and the class has no base. `inline virtual ... = default`
#   and an empty body in the class give the same object.
# - Remove in the class is a choice the column fits: 19 is `throw` at 12 spaces (class, body, if). The same body after
#   the class, with or without `inline`, gives the same object, and a nested block there would give the column too.
#
# Chosen, no evidence names them: the enumerator EUE_IPC_FILA_VAZIA (from its message); SMessage's file and fields;
# SItem, its fields and that it is nested; m_fila, m_semaforo, m_sync, m_ordem. Every line of the header but 153 is a
# choice too.
#
# Forms measured against this one, comparing the object's Remove, pop, D2 and D0 (em++ with uenux2's flags):
# - the same bytes: a functor as priority_queue's third argument for operator< with std::less (only pop's symbol
#   differs, and it is inlined); the comparator as if/else if/else or as nested ?:; size_t for the two unsigned; a
#   reference, or an RAII guard that holds the reference, for the pointer `sync`; with -fno-strict-aliasing or without
#   it, so the roots object takes APP_CXXFLAGS as every roots object does. No evidence names a guard class, so none
#   is invented, although one would explain why the throw path does not Unlock: uenux2 compiles no landing pads, so a
#   guard's destructor leaves no code on that path.
# - other bytes: `a < b || (a == b && c > d)` and testing `>` before `<` (pop differs); testing `==` or `!=` first
#   (clang then inlines pop into Remove, and the frame is 32 bytes).
#
# The header's includes need no extra path: UENUX2_PREFIX_MAP rewrites the relative src/uenux2 spelling too, so the
# record's file is /home/rubio/tse/uenux2/src/api/ipc/cmessagequeue.h.
$(ROOT)/$(APP)/64-uenux2-cmessagequeue-roots.o: $(ROOT)/src/units/64-uenux2-cmessagequeue-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/64-uenux2-cmessagequeue.mk $(wildcard $(ROOT)/src/uenux2/src/api/ipc/*.h $(ROOT)/src/ecourna/api/exception/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/64-uenux2-cmessagequeue-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/64-uenux2-cmessagequeue-roots.o
