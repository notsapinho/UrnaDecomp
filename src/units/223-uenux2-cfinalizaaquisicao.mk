# uenux2 vota::CFinalizaAquisicao (src/app/vota/eleitor/fimvotacao/cfinalizaaquisicao.{h,cpp}): its StartState, target
# fn 12113, matched, with the body binaryen merges it into, fn 6058.
#
# What the target fixes:
# - The class, its base comum::CAppState and its vtable are RTTI's (@1540308, [174, 144, 12113, 7480, 1661, 218, 425, 218,
#   425]): slot 2 is its own, the rest the base's or the shared bodies of states with no member (174, 144).
# - 12113 is `f6058(p0, 10)` and vota::CReinicioComparecimentoMesario::StartState (11917, unit 104) is `f6058(p0, 7)`:
#   6058 lies in the target's run of merge bodies (6007 to 6065, `byn$mgfn-shared$` matches but 6016 and 6037), so the
#   two StartStates are whole functions binaryen's merge-similar-functions joined, the constant made a parameter, `this`
#   kept first. Each stores vota::CAguardaMensagem::GetInst() (fn 1337) as the next state and then posts its constant to
#   vota::CThreadOperador's queue (fn 270 + 36, Post inlined, Insert fn 501): 6058's order. Written so, our link forms
#   the same merge, named after 11917 (unit 104's object comes first), and `pnpm wasm score` against the link reads
#   12113 `1 over 5 rows`, 11917 `1 over 5` and 6058 `3 over 29`, all operand-only; steps 7 to 9 match the three.
# - fn 7160 (vota::CAjusteInicial::StartState, unit 329) holds GetInst inlined: under the static std::mutex @1833444 it
#   allocates 12 bytes when the static std::unique_ptr @1833468 is empty, passes 0 to the base's constructor (fn 224),
#   stores the vptr and frees the old object with no call through the vtable (final, unit 104's shape). The statics'
#   exit destructors are 12114 (the mutex's) and 12115 (the pointer's).
#
# GetInst, the constructor and the statics are written in cfinalizaaquisicao.cpp in unit 104's shape, whose names they
# take (chosen), the constructor out of line as there; binaryen inlines GetInst into fn 7160, its one target caller.
# Only 7160 reads the statics' addresses among target functions, so their names, and the destructors 12114 and 12115,
# wait for its match (src/units/329-uenux2-cajusteinicial.mk). Since 7160 is in the link the state's builder is too, and
# the roots file that kept the vtable went.
#
# Chosen: the path, the file name (the class's in lower case) and the header beside it, by how-to step 3's rules 2 and
# 4: the vtable and typeinfo (@1540308, @1540352) lie between fimvotacao/ccopiaresultadoparamr.cpp's records (@1540116 to
# @1540196) and vota::CGeraBU's vtable (@1540364, cgerabu.cpp's records from @1540408), the directory's files in name
# order, which cfinalizaaquisicao.cpp fits; in link order 12115, 12114 and 12113 follow 12117 and 12116, the members of
# the std::__shared_ptr_emplace<comum::CCopiadorWSQMR> whose vtable (@1540268) lies in that run of the data after
# ccopiaresultadoparamr.cpp's records (that they are that file's copies is a reading). StartState as the key
# function, so this object emits the vtable; the statics' and GetInst's names (unit 104's convention).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CFINALIZAAQUISICAO_SRCS := src/app/vota/eleitor/fimvotacao/cfinalizaaquisicao.cpp
UENUX2_SRCS += $(CFINALIZAAQUISICAO_SRCS)
