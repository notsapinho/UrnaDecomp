# uenux2 simulador::CWasmNullTextToSpeech, the wasm build's api::ITextToSpeech, in
# src/uenux2/mock/app/simulador/wasm/cwasmnulltexttospeech.cpp (+ .h), with the api::ITextToSpeech interface
# (src/uenux2/src/api/audio/itexttospeech.h, whose comment gives the evidence of the class):
# - slot 11 of the vtable @1528696 (target fn 9436), DoSynthesize, the key function, so the object emits the vtable;
# - ITextToSpeech's inline members in slots 2 to 8, which that vtable names, so the same object emits them: SetPitch
#   11511, SetVolume 11507, SetSpeed 11505, GetSpeed 11504, IncreaseSpeed 11500, DecreaseSpeed 11494 and SetTag 11491.
#   Their target copies are the executable TU's (the class has no key function); they are the same code at the uenux2
#   flags, and matched from this object until unit 237's tree root, src/app/roots_texttospeech.cpp, which linked ahead
#   of it at that TU's rule, gave them (the census paired them with that object at tier `byte`); the executable TU's
#   object gives them since its votaInit.
# Evidence of form: IncreaseSpeed tests equality with 4 and DecreaseSpeed compares with 0. On the target's rows `m_speed
# < 4`, signed or unsigned, and std::min differ, and so do signed `m_speed > 0` and std::max. Both store m_speed
# unconditionally, which rules out `if (m_speed != 4) ++m_speed;` (the store goes inside the branch). A bare virtual
# SetSpeed(...) from them does not give it either: it stays a call_indirect.
# Choices, each measured to give the same bytes: the ternaries with their arms the other way round (`m_speed != 4 ?
# m_speed + 1 : 4`, `m_speed == 0 ? 0 : m_speed - 1`); `ITextToSpeech::SetSpeed(...)` of that value, qualified; a local
# `int s = m_speed; if (s != 4) ++s;` handed to the same call; `m_speed -= m_speed != 0`; an unsigned m_speed, which
# adds `m_speed > 0 ? m_speed - 1 : 0`. In SetSpeed, m_rate stored before m_speed, `(speed + 3) * 20` and `60 + 20 *
# speed`. In DoSynthesize, `return {};`, `return std::shared_ptr<api::CWavFile>();` and a returned empty local. `final`
# on the class. Choices that change the symbol and no byte: int or unsigned in SetPitch, SetVolume, SetSpeed and
# GetSpeed, GetSpeed const, and long long, unsigned long long or time_t in SetTag (the options' field is `long long`,
# arg type 4 in fn 5758, which says nothing of this member's own type). A member defined after the class with `inline`
# is the same object as the member defined in it.
# Choices of path: no record names itexttospeech.h or cwasmnulltexttospeech.cpp. The first sits beside
# api/audio/isound.h. The second is the file ledger/tu-clusters.tsv's stretch 210 guesses for fns 9427 and 9436
# (class-convention, so the class's own name), in the directory where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp). The data place the object, not its name: the vtable @1528696 follows
# cwasmwebsound.cpp's data, and 9436 follows that file's 9459, 9448 and 9445 in the uses=1 band (`awk -F'\t' 'NR>1 &&
# $2==1 && $1>=9427 && $1<=9459' ledger/ordinals.tsv`, the index in reverse link order). The class in another file gives
# the same bytes.
# Matched since unit 237, from its tree root at the executable TU's rule (that fragment has the link); what this unit
# measured while they were `differs` from this object:
# - SetVoice (target fn 11518, slot 1): the target's copy is the executable TU's, and only there does `m_voice = voice`
#   stay a call of std::string::operator= (fn 1700). At -Oz -fexceptions this header compiles to the target's rows; at
#   the uenux2 flags clang inlines the call (cost=125, threshold=225), and `m_voice.assign(voice)` gives the same object.
# - ITextToSpeech's D2 (target fn 11489, slot 9), the executable TU's copy too: at -Oz -fexceptions this header gives
#   the target's rows, with the string's destructor as a call (fn 149), which the uenux2 flags inline.
# This class's D0 (target fn 9427, slot 10) matches at the tree's -O3 since unit 158, whose fragment says how its two
# callees are named; what was measured before, at -O2 and -O3:
# - 9427 (`differs` at -O2). The target's holds the
#   D2 with the string's destructor inlined
#   and the cache's destructor (fn 3764) as a call, as fn 5441 does. At -O2 clang inlines that destructor into the D2
#   (cost=210, threshold=325: it is implicit, so hinted; `= default` in the class prints the same cost, threshold=225),
#   and the D2 is then too big for the D0 (cost=320, threshold=225). No form of the class changes that at -O2: the
#   cache's destructor implicit or `= default`, the cache a class or a template, a pair or a struct in the list;
#   `inline` on ITextToSpeech's only inlines the D2, cache and all, into the D0. At the tree's -O3
#   this header gives the target's rows, with `= default`, `{}` or `inline` on ITextToSpeech's destructor (the same
#   object): std::list's clear goes inline into the cache's destructor (cost=240, threshold=250), and that one stays a
#   call (cost=450, threshold=325). 9427 is then 5 over 27 rows, all operand-only; its callees, 3746 and 3764, were named
#   by its own votes alone (`unresolved self-voted`), and 3764 is the executable TU's copy (invoke_vii).
# Synthesize (target fn 11530, slot 0) was this unit's one pending member, trapped in 82-uenux2-cwasmnulltexttospeech-
# pending.cpp; unit 237 writes it in the header, and the trap, the pending file and its rule went.
# Not written: the implicit constructor (fn 13877), the executable TU's (std::make_unique through invoke_ii in fn 7840).
# `std::make_unique<simulador::CWasmNullTextToSpeech>()` at -Oz -fexceptions compiles this header's default member
# initializers to ITextToSpeech's constructor, out of line, with 13877's stores in 13877's order, and to a derived
# constructor that calls it and stores its own vptr; binaryen inlining the one into the other gives 13877's two vptr
# stores. So the initializers' values and order are evidence; that they are initializers and not a constructor's list is
# a choice.
# Paths relative to src/uenux2; the generic uenux2 rule compiles mock/ too and depends on the source and every uenux2
# header.
CWASMNULLTEXTTOSPEECH_SRCS := mock/app/simulador/wasm/cwasmnulltexttospeech.cpp
UENUX2_SRCS += $(CWASMNULLTEXTTOSPEECH_SRCS)
# No roots: the target reaches every member through the vtable only, and fn 8302 (unit 188), which holds a copy of the
# implicit constructor inlined, stores its vptr and is in the link (13877, the executable TU's copy, is the other
# storer), so the roots file and its sink went.
