# uenux2: the target's copy of api::CPriorityMessageQueue<api::SMessage>::Insert (fn 501), written in unit 64's header
# api/ipc/cmessagequeue.h (unit 174 wrote Insert there), and what that copy instantiates: api::CSyncCtlGuard's
# destructor (5528), priority_queue::push (11076) and its __split_buffer's destructor (5523), with binaryen's merge body
# 2896, which that destructor and roots_coderenv.o's __split_buffer<char> destructor (2704) call. No source of its own:
# the target's copy is an -Oz -fexceptions object's, the executable TU's, whose three posts (unit 170's
# HabilitaAudioEleitor, LiberaEleitor and SinalizaSincronismo, each over Insert(const SMessage&), 7708) instantiate it,
# and that TU's object, first on the link line, gives it. Until those posts were written, the tree root
# src/app/roots_messagequeue.cpp emitted the instance at that TU's rule, VOTA_WEB_CXXFLAGS, after that TU's object and
# ahead of the uenux2 objects; it went with them (the link without it: unit 170's fragment). This file holds the
# evidence and the measurements, taken with the root.
#
# Matches (6, none lost, against 441ae041 by index, how-to step 10): 501 Insert, 5528 the guard's destructor, 11076 push
# (named by step 8 from 501's table slot), 5523 __split_buffer<SItem>'s destructor, 2896 (`no-candidate` before) and
# 2704 (unit 229's root's body, `differs` before): our link merges 5523 and 2704 into 2896's body. Match line renamed
# to a twin the root brings first (how-to step 10): 2239, libc++'s vector<locale::facet*>::__swap_out_circular_buffer,
# to vector<SItem>'s, the same body (table slot 238, which 11076 passes to invoke_vii).
#
# What the target's bodies give (pnpm wasm fn):
# - 501: m_sync (+24) stored in a frame word (+28) and locked through its slot 2 by a plain call; m_ordem (+28)
#   incremented; the item {message, priority, order} built at frame +8 and pushed through invoke_vii of table slot 237
#   (11076); m_semaforo (+20) unlocked through invoke_vi of its slot 3; 5528 on the frame word on both paths, then
#   __resumeException on the one landing pad both invokes share.
# - 5528: one parameter; its word's Unlock (slot 3) through invoke_vi, with a terminate pad (__cxa_find_matching_catch_3,
#   __clang_call_terminate): the guard's destructor, noexcept, kept out of line.
# - 11076: push_back with its growth inlined (5523 twice, table slot 238) and push_heap's sift-up.
# - Whose copy: landing pads say an -fexceptions object (uenux2 compiles none: docs/reference/facts/app-flags.md F6),
#   and -Oz: the same object compiled with -Os after the rule's flags inlines 5528 and push into Insert (wasm-objdump -x
#   -j Function on it), where the target keeps both. That the copy is the executable TU's was a reading; its posts,
#   written since by unit 170, instantiate it there.
#
# Forms, measured in whole links (docs/reference/facts/levels.md V4: the plain link's objects at 441ae041 with one
# object at VOTA_WEB_CXXFLAGS that instantiates Insert, scanned with the committed symbol file and matches; pnpm wasm
# score at the default depth, our function in that link):
# - Insert's item a named local, alive across both invokes: one landing pad, 501 9 over 93 rows, all operand-only (the
#   __THREW__ word's address and the table slots, which the scan re-points). The temporary unit 174 wrote,
#   m_fila.push(SItem{...}): a landing pad per invoke, which binaryen joins in another block, 16 over 95 (measured with
#   SItem::operator<, which only push's body involves). m_fila.push(std::move(item)) gives the same Insert and push (the
#   object's rows, call and global indices masked; push is then push(value_type&&), not push(const value_type&)).
# - The heap's comparator a function object (SComparaItem): 11076 7 over 296 rows, all operand-only. SItem::operator<
#   with std::less, as unit 64 wrote it: 76 over 317; clang leaves the sift-up's first compare a call (-Rpass-missed=
#   inline: cost 5, threshold 5) and inlines the loop's, and binaryen's inlining of that call then reloads the moved
#   item's fields, where the target's first compare is clang's (its loads reused for the item). operator< written
#   `a < b || (a == b && c > d)`: 77 over 317. operator< taking the other item by value: clang inlines both compares, 33
#   over 301, but the copy loads the order number before the compare, where the target loads it on each path. A friend
#   operator<(const SItem&, const SItem&): cost 5 at the first compare too (the remarks only). The function object's
#   call has one argument more, and clang inlines it at both compares (cost 0 and -10). In the uenux2 objects that use
#   the queue (Remove 2073 among them) the header's change moves no code: only push_back's and pop's symbols differ
#   (wasm-objdump -d of each object against 441ae041's, call and global indices masked).
# - The object's place: ahead of the executable TU's object (V4's place), the same instance takes 14 rows of other
#   classes out of match (form members of cmtformbuilder.cpp and cpaperformbuilder.cpp, CBuzzFieldMT and CBeepFieldMT's
#   Draw, a CWasmScreenMT local class's D0, roots_coderenv.o's ~basic_stringbuf); after it and after
#   roots_texttospeech.o, as the tree root sat, none.
#
# Hand lines: 501's callers+content line (unit 174's) went. A generated line names 501 (`call by:4464,7377,10210,11914`,
# none of them 501); with the hand line alone out and the match lines of 501, 7221 and 10763 (the callers it carried)
# out too, two scans beside a control give 11474 match rows each with no row moved, and splat-build on the copies
# verifies 11474 matches.
#
# Chosen: the function object's name, SComparaItem, and that it is nested in the class; the local's name; push(const&)
# over push(&&) (the same bytes).
#
# Matched since unit 170 wrote the executable TU's three posts: 7708 (`f501(p0, p1, 1)`, Insert(const SMessage&)'s -Oz
# copy) and 3903, binaryen's merge of the posts 10376, 11026 and 11100 (table slots 110, 57 and 55, each `f3903(p0, <5,
# 1 or 9>)`; its neighbours in its use band, 3900 to 3906, are merge bodies). Unit 170's fragment has the evidence.
