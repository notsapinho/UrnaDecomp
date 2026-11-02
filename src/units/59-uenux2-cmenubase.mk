# uenux2 comum::CMenuBase's destructors (target fns 12235 and 6188, vtable slots 0 and 1;
# vota::CMenuMaisInformacoesVota's vtable holds the same base-object destructor, and its deleting one is
# byte-identical to 6188), the compiler's code for the class definition in
# src/uenux2/src/app/comum/informacao/cmenubase.h. They destroy the std::string at +16 and the
# std::vector<std::shared_ptr<CItemMenu>> at +4 and store the vptr (the class is not final). The class has no base
# (RTTI), so its virtual destructor is declared, and it is defined inline in the header: the deleting destructor holds
# the base-object body, which neither a destructor defined out of line (its D0 calls the D1 alias) nor one defined in
# the class without `inline` gives (clang then gives the D2 no inline hint, and the D0 calls it: measured); an implicit
# destructor would, but a class without a base gets a virtual one only by declaring it. `inline virtual ~CMenuBase() =
# default;` in the class gives the same bytes.
# Chosen, where no evidence decides: the header's path (no record names a file of the class; its key function is
# linked between app/comum/informacao/cinformacaoeleicao.cpp's functions and app/comum/cinfomtlcd.cpp's,
# ledger/tu-clusters.tsv stretches 854, 853 and 851, and app/comum/ links its own files in name order, which would put
# a cmenubase.cpp after cinfomtlcd.cpp: so informacao/, not the stub comments' class-convention app/comum/dados/), the
# name MontaMenu of slot 2 (fn 5913, from its body), the members' names, and a reference for the +28
# api::CFormBuilder (a pointer gives the same bytes); cmenubase.h says what each comes from. CItemMenu's head is
# citemmenu.h's.
# MontaMenu, the key function, is written in cmenubase.cpp (below), so that object emits the vtable and both
# destructors, which the pending object emitted before (their symbols, and so their match lines, are the same); the
# pending file went with it. The constructor (inlined into fn 6599) is not reconstructed. Paths relative to src/uenux2.
# The class's source, app/comum/informacao/cmenubase.cpp (the chosen path above), holds AdicionaItem (fn 2285, a chosen
# name), which fn 6599 calls for each item, and AdicionaOpcao (a chosen name), which binaryen inlined into it in the
# target: the append to +16 sits after a stack prologue of its own inside fn 2285 (docs/reference/facts/reading.md
# R10), so it is written out of line in the same .cpp and left with its one caller. cmenubase.h says what each reads.
# AdicionaItem (2285) matches since unit 95 writes comum::ValidarUE (5890, record iinterfacesavd.cpp:886), which loads
# the 62-byte literal at 8090 ("Falha ao validar assinatura UE\npacote: ({})\nErro SAVD: ({})\n{}"): the target's
# `i32.const 8152` in 2285 is its "{}", that literal's tail, which our link held elsewhere before (body byte 140 of
# `splat-remap --against 2285`; 10 over 239 rows, all operand-only, in `pnpm wasm score`).
# MontaMenu (fn 5913, 1334 B, slot 2 of the class's vtable and of vota::CMenuMaisInformacoesVota's, which overrides
# nothing; its one direct caller, 6599, is not written), matched, with what its body holds:
# - For each item, a line "[{}] - {}" of the item's key and text (argument types 6 and 13), behind a stack prologue of
#   its own (docs/reference/facts/reading.md R10), so the format is an out-of-line function binaryen inlines:
#   FormataItem, a free function of this file (it reads the item's getters only; its name, its being free and not a
#   member, and its external linkage are chosen: a file-static function with one call clang would inline itself). Then
#   api::CFormBuilder::AddTextField (fn 202) on +28 with the item's point and font, copied into the frame (the getters
#   return by value, a reading), alignment 0 and the colours `slot 2 ? 2 : 5` and 1; the result is released.
# - After the loop, a copy of the last item's std::shared_ptr; its point and the font's size give the prompt's place:
#   the point's x and y + 2 * size, computed in int (the target loads them signed and sign-extends no sum), passed to a
#   member behind a stack prologue of its own that reads +28 and +16: AdicionaPergunta(int, int), its name chosen. It
#   adds "Escolha a sua opção:" at {x, y} in the api::SFont at 493212, then builds an api::COptionValidation of
#   +16 (its vtable, @1550952, follows CMenuBase's, @1550924, in this TU's data) under a
#   std::shared_ptr<api::IInputValidation>, and
#   an api::CInputField<api::CFramedText> of length 1 (true, true, false, false, false: fn 2024's arguments) at
#   {x + 208, y - 2} in that font under a std::shared_ptr<api::IInputField<api::IScreen>> (the control block's
#   deleter names that type), which it hands to AddField (fn 426). The target loads +28 for that call before it builds
#   the field, and copies the field's pointer into AddField's parameter (a count increment), which a file-local
#   helper taking the builder first gives: AdicionaCampoOpcao (anonymous namespace, its name chosen), which clang
#   inlines. `pnpm wasm score` against the link, three forms: the field built in a named local before
#   `m_form.AddField(campo)`, AdicionaPergunta over two api::TPosition and a third `true` among the flags, `225 over 622
#   rows (same 397, replaced 190 [175 operand-only], inserted 18, deleted 17)`; the helper and int parameters, `33 over
#   605 rows` (one row inserted and one deleted, the flag); the flags as above, `31 over 604 rows`, all operand-only.
# - The font: 493212 holds {20, 0} and lies right before CMenuBase's typeinfo name (493220), so a constant of this TU;
#   5913 is the only target function that loads it (`/usr/bin/grep -rlE 'i32\.const 493212($|[^0-9])'
#   build/out/splat/pieces/asm`). Our FONTE_PERGUNTA (its name and internal linkage chosen) re-points as
#   `address same-content 0x7869c` (`pnpm wasm splat-remap ... --against 5913`), the target's bytes, no name. CItemMenu's point (+20) and font (+24)
#   are added to citemmenu.h, their types AddTextField's parameters'.
CMENUBASE_SRCS := src/app/comum/informacao/cmenubase.cpp
UENUX2_SRCS += $(CMENUBASE_SRCS)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 59-uenux2-cmenubase-roots.cpp keeps the vtable, as the constructor inlined into fn 6599 does, and stands in for
# AdicionaItem's one caller, fn 6599 (not reconstructed)
$(ROOT)/$(APP)/59-uenux2-cmenubase-roots.o: $(ROOT)/src/units/59-uenux2-cmenubase-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/59-uenux2-cmenubase.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/informacao/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/59-uenux2-cmenubase-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/59-uenux2-cmenubase-roots.o
