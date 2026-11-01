# uenux2 src/app/comum's root files over comum::EUeComumError, at the paths their std::source_location records name,
# listed in the name order the directory links in: comum::CArquivosResultado::operator[] (target fn 347) in
# carquivosresultado.cpp (record 99:11), comum::CArquivosSavd::operator[] (275, 680) in carquivossavd.cpp (49:15, 73:15),
# comum::CPacoteArquivos::RetornaNomeChave (5900) in cpacotearquivos.cpp (162:11) and
# comum::IInterfaceSavd::EnviarRequisicao (3830) in iinterfacesavd.cpp, which binaryen holds with the two static members
# the records name, DesconverteHeader (553:15, 559:15) and DesconverteMensagem (568:15, 574:15, 578:15), and with
# ConverteHeader; the class headers beside them and app/comum/euecomumerror.h, with the handle formatter of the three
# SAVD enums. The formatter's handle body (fn 536) is the one binaryen keeps for every such enum, ours named by the
# table vote of 275, 680 and 5900; it stays unresolved on libc++'s __fields_integral, and no match here waits for it.
# 480, CBaseError<comum::EUeComumError, ...>'s constructor, is named by the calls and matches with this header's enum:
# it is a thunk of 710, the body unit 94's form gives (the constructor in ecourna/api/exception/cbaseerror.hpp).
#
# comum::CPacoteArquivos::TrataErroPacote (5901, record 169:11), added after the unit landed: it throws code 7222 with
# the key's name (5900 on +24), the package's name (the std::string at +0) and IInterfaceSavd's code and text (+16, an
# int: argument type 3; +4); the getters on IInterfaceSavd and their names are chosen. Fn 4625 (not reconstructed)
# builds the object in its frame and gives the layout: +0 a std::string, +12 a std::vector (its begin and end compared,
# its elements walked), +24 the ESavdChaveValidar, +28 and +32 words. The vector's element type and every member's name
# are chosen; +28 and +32 are not declared, since nothing written reads them. The target's band (uses 2) has 5901
# ahead of 5900 in the link. A reading: 4625, whose records lie at lines 85 to 116 and whose body calls 5901 before
# 5900, is defined above both, and a function takes its place at its first mention; with 4625 not written our object
# has them the other way round.
#
# comum::CArquivosResultado::GetInst (348), its out-of-line constructor and destructor and its two statics are in this
# unit's files and belong to unit 111's measurement: its fragment says why GetInst sits above the statics.
#
# Not written: IInterfaceSavd's destructor (5503, slot 0 of its vtable and of the executable TU's CWasmSavd): its body
# calls the string's destructor, which -Oz gives and -O2 does not (a probe of the class's shape at both levels, not at -O3;
# docs/reference/facts/levels.md V1), so the copy the target kept is the executable TU's and no object here can
# match it. It has no stub: stubs.py counts a virtual member of a class our sources define as code of ours, though no
# object here emits this one (its row stays no-candidate). ValidarUE (5890) and EnviarAcaoHSM (5889) wait for 3831 and
# 3829, which no unit has.
#
# Evidence and choices. The records fix each throw's line and each function's name and types. Chosen, and marked where
# declared: every enumerator's name, ESavdChaveValidar's and EExtensaoArquivoResultado's enumerator names, the two
# request and response structs' members, IInterfaceSavd's slot and member names, EnviarRequisicao and ConverteHeader
# (no record: their roles), the maps' names and every header's path. EExtensaoArquivoResultado's enumerators are defined
# in carquivosresultado.h, the one reader of its values; iresultado.h keeps its opaque declaration. Chosen too, for its
# inline cost at the tree's -O3: that ConverteHeader fills in the request's mark and size from the data. Taking the
# request and the data, it costs 255 at its call and stays a call (-Rpass=inline -Rpass-missed=inline on this file), and
# 3830 scores 81 over 1168 rows in the whole link, all operand-only, and matches. With the two stores in
# EnviarRequisicao it costs 230 (3830: 331 over 1335 rows, 167 inserted), with the size passed for the data 235 (328
# over 1332): both are inlined at -O3, and both stayed calls at -O2's 225. No target body shows where the two stores
# belong: binaryen inlined the helper into 3830, where either form puts them. 3829 holds the same two stores where
# clang inlined them, the size taken from a std::vector, right before the same copy: a helper over a std::string cannot
# serve it, so 3829's landing decides the helper's real signature.
# What the bytes decide, measured on this unit's objects at -O2, the tree's level then, function by function with
# object-local numbers masked:
# - the `case` order of 347 and 5900: moving 347's first case or 5900's first or SEINT's case changes the br_table (the
#   target's [11 0 1 3 4 5 6 7 8 9 2] for 5900), so the order written is evidence, SEINT (59) after SECINP (51);
# - the format argument of 347 is an int (argument type 3), of 275, 680 and 5900 a handle (type 15);
# - EnviarRequisicao's `m_mensagem = ""`: the size is stored before the terminator; clear() stores them the other way;
# - ConverteHeader's std::copy into a std::back_inserter keeps the vector in memory through the loop, with the one
#   store of 0 before the allocation, as the target does; a push_back loop promotes it to locals (146 lines against 132);
# - ConverteHeader stays a call in 3830, at the tree's -O3: the target keeps it out of 3830 for binaryen, and clang
#   inlines it when its cost at the call is at most -O3's threshold of 250 (the chosen form above says how it stays out);
# - DesconverteMensagem's std::copy: an index loop and an iterator loop give other code;
# - the order of `if (header->tamanho)`'s two branches: the other gives other code;
# - the order of the definitions, measured in the whole link (pnpm wasm score, rows that differ of the body's rows):
#   ConverteHeader, DesconverteHeader, DesconverteMensagem, EnviarRequisicao 379 over 1191; ConverteHeader,
#   EnviarRequisicao, then the two Desconverte 130 over 1178; EnviarRequisicao, ConverteHeader, then the two Desconverte
#   81 over 1168, every one operand-only. EnviarRequisicao, the two Desconverte, then ConverteHeader gives the same module too, so what
#   decides is that the caller stands before all three helpers; ConverteHeader's place and the exact lines are a choice.
# Forms that give the same function (measured the same way), the one written first:
# - 275, 680: `const auto it` and `auto it`;
# - 347: the case falling out of the switch and `default: break;`; static_cast<int>, a C cast and unary +;
# - 275, 680, 5900: the formatter of iinterfacesavd.h, written as an explicit specialization with a template format,
#   with a format over std::format_context, as a template constrained on std::is_enum_v over formatter<unsigned int>,
#   and over the underlying type made unsigned. A template over the underlying type alone needs plain enums: over an
#   int enum it gives formatter<int>'s body, the target's 1711, not 536;
# - DesconverteHeader: `size != sizeof` and `sizeof != size`;
# - EnviarRequisicao: `m_mensagem = ""`, `= {}`, erase() and resize(0); `const uebyte erro` and `const bool erro = ... != 0`;
#   `if (header->tamanho)` and `!= 0`.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_SRCS := src/app/comum/carquivosresultado.cpp src/app/comum/carquivossavd.cpp src/app/comum/cpacotearquivos.cpp src/app/comum/iinterfacesavd.cpp
UENUX2_SRCS += $(APP_COMUM_SRCS)
# their callers are not reconstructed yet: 95-uenux2-app-comum-roots.cpp gives each two call sites
$(ROOT)/$(APP)/95-uenux2-app-comum-roots.o: $(ROOT)/src/units/95-uenux2-app-comum-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/95-uenux2-app-comum.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/95-uenux2-app-comum-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/95-uenux2-app-comum-roots.o
