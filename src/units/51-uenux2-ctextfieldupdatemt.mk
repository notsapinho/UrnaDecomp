# uenux2 api::CTextFieldUpdateMT::~CTextFieldUpdateMT: the base-object destructor (target fn 5411, slot 0 of the vtable
# @1590476) and the deleting one (fn 10549, slot 1), with Draw (fn 10548, slot 2), Show and Hide (fns 10546 and 10545,
# slots 3 and 4), the constructor (no target index) and the slots of its timer's lambda (__func's __clone 10544 and
# 10543, operator() 10542, target 10541, target_type 10540), in
# src/uenux2/src/app/vota/operador/comum/ctextfieldupdatemt.cpp; and vota::CPedeIdentidade's screens in
# telasoperador.cpp (below), which fn 652 holds inlined. No record names the class's files, so the path is
# chosen: the file name is the class's in lower case (the label of clusters 309 and 757 in ledger/tu-clusters.tsv,
# class-convention), and the directory is the one the recorded stretches beside those clusters give
# (docs/how-to-decompile.md step 3, rule 2). The D0 calls the D2 (13 B), so the destructor is defined out of line and
# the class's D0, Draw, Show and Hide (cluster 309, band 1) and D2 (cluster 757, band 2) are strong functions of the
# class's own object, not linkonce copies. Cluster 309 starts right after the last functions of
# app/vota/operador/comum/cinformacaothreadoperador.cpp (stretch 310, records) and comes before
# app/vota/operador/confirmaidentidade/ccontrolareconhecimento.cpp (304); cluster 757 sits between
# api/util/itimerscheduler.cpp (759) and the same confirmaidentidade file (756). The data order decides: the class's
# vtable (@1590476, 0x1844cc) follows cinformacaothreadoperador.cpp's data and comes before confirmaidentidade's
# (0x1846f4), while api/ objects link their data in runs of their own (api/gui's fields at 0x182544-0x182a78; their
# functions in band 1 stretches 366-400 and band 2 768-772). So the object linked among app/vota/operador/'s objects,
# not api/gui/'s; the subdirectory comum/ is chosen (confirmaidentidade/ fits the order as well). No record puts any
# other api:: class's member in an app/ file: this is the reconstruction's reading of the link order, not a record's.
# The header (ctextfieldupdatemt.h beside it, chosen) has the layout the constructor (inlined into
# fn 652), Draw (fn 10548) and the destructor give; the member names are chosen and the timer at +48 is a
# std::shared_ptr to a forward-declared api::ITimer, whose Start and Stop (chosen names, api/util/itimer.h) Show and
# Hide call. The destructor is user-declared and defined out of line, declared first among the class's virtual
# members, so it is the key function and ctextfieldupdatemt.o emits the vtable, the D2 and the D0; GetTypeName (slot 7,
# fn 11051) is IFormField<IScreenMT>'s inline one.
#
# The constructor has no target function: binaryen inlined it into the field adder below, which it inlined into fn
# 652, where its 32-byte frame is the second one inside the adder's. In the target's order it stores the position and
# the SharedIText, starts m_textoDesenhado with two byte stores (`m_textoDesenhado("")`, as unit 42's
# api::CTextFieldUpdate), makes the timer through slot 0 of api::ITimerScheduler::GetInst() (fn 1259, unit 101) with
# the interval and a lambda, and only then throws std::invalid_argument("CTextFieldUpdate - campo estava com o texto
# nulo", 129780, typeinfo 1526028) when the text is null. The lambda calls Atualiza, a member out of line: the target's
# operator() (10542) loads the capture before a frame prologue, binaryen's inlining of a callee clang left out of line
# (docs/reference/facts/reading.md R10), and Atualiza's body is IFormFieldBase::Invalidate under the test that the text
# changed. Atualiza, its name and its being a member are chosen, as unit 42's are. The lambda's __func members
# 10544, 10543, 10542, 10541 and 10540 match from this object (its destroy and destroy_deallocate are the shared 218 and
# 355); the file builds with strict aliasing (app/vota is in UENUX2_TBAA_DIRS), which unit 42's fragment measured the
# two __clone need.
#
# telasoperador.cpp: the code fn 652 holds beyond CPedeIdentidade's GetInst and constructor (unit 161), each behind a
# stack frame of its own inside 652, so each a function binaryen inlined into its one caller: MontaTelaPedeIdentidade
# (16 bytes: the by-value copy of the string it passes on), MontaTelaTreinamento (80), MontaTelaVotacao (448),
# TextoDigiteIdentificador (416) and api::CMTFormBuilder::AddTextFieldUpdate over api::CTextSource (16). Its path and
# name are chosen, and so are the functions' names, their being free functions of vota and the template's name. Why
# an object of its own, and why this one (each measured in the whole link, pnpm wasm score against our GetInst, or
# with -Rpass=inline on the compile):
# - In cpedeidentidade.cpp, beside the constructor, clang inlines MontaTelaPedeIdentidade into it (cost 165, threshold
#   250): the target's 16-byte frame says another object. Here the four others cost more than the threshold
#   (MontaTelaVotacao 2400 and MontaTelaTreinamento 1955 in MontaTelaPedeIdentidade, TextoDigiteIdentificador 1180 and
#   the adder 875 in MontaTelaVotacao) and stay out of line with external linkage (measured in cpedeidentidade.cpp:
#   with the four screen functions in an anonymous namespace clang inlines them into the constructor, one frame);
#   DescricaoTipoIdentificador (95) and TextoQuantidadeAptos (internal) are inlined by
#   clang, as the target's rows have them (out of line in another object, Descricao keeps a pointer local the target
#   lacks). DescricaoTipoIdentificador's external linkage is a choice: internal gives the same module byte for byte.
#   TextoQuantidadeAptos's internal linkage is measured: external, 652 scores 696 over 2091 rows.
# - The target tests the "%s" temporary for a long string after the adder returns. With the adder a plain member in
#   the object of MontaTelaVotacao that test is gone; as a template's instance it stays (a reading: the optimizer takes
#   nothing about the call from a linkonce_odr body). With the adder a plain member in ctextfieldupdatemt.cpp, beside
#   CTextFieldUpdateMT's constructor, the pointer `new` returned for the field is kept in two locals where the target
#   keeps one (a local.tee then a local.set after f137(56)). So the adder is a template instantiated beside
#   MontaTelaVotacao, in an object without the constructor.
# - The data agree, a reading: in the target, the copy of the CTextSource record (ctextsource.h:37) that fns 652, 1150
#   and 5397 share (@1590592) and the vtable of __shared_ptr_pointer<CTextFieldUpdateMT*, ...> (@1590608) come right
#   after CTextFieldUpdateMT's vtable and its lambda's, before CDataText<CTextSource>'s (@1590648); in the strings,
#   "TREINAMENTO DE ELEITORES" (538432), which 652 and 1150 load, comes after CTextFieldUpdateMT's typeinfo names and
#   before that __shared_ptr_pointer's. An object linked right after ctextfieldupdatemt.cpp's holds the screens' code,
#   1150's and 5397's too (not moved here), so telasoperador.cpp follows ctextfieldupdatemt.cpp in this list.
# - TITULO_TREINAMENTO: the target copies the title's 24 bytes with i64.load align=3 from a 16-byte-aligned address
#   outside the merged strings; a string literal gives align=0 from an address among them (measured: those rows). As a
#   named const char array it gets the target's rows; that clang aligns a large named array to 16 is a reading. Its
#   name and its scope are chosen.
# - The order of the definitions: with MontaTelaPedeIdentidade defined before MontaTelaTreinamento and
#   MontaTelaVotacao, and CPedeIdentidade::GetInst before its constructor in cpedeidentidade.cpp, fn 652 scores 144
#   over 2051 rows, every one an operand (calls, data, table slots). The instructions are the same in every order;
#   binaryen's choice of locals is not: with the constructor first, 243 or 250 over 2054 rows (3 inserted, 3 deleted),
#   and with GetInst first and MontaTelaPedeIdentidade last, 443 over 2063 (12 inserted, 12 deleted). The order was
#   found by running emcc's first wasm-opt command (EMCC_DEBUG=1 prints it) on emcc's saved pre-optimization module of
#   this link, disassembled with wasm-dis, the functions moved and assembled again (the unmoved module gives emcc's own
#   output, byte for byte): of the 24 orders of the four screens' functions after GetInst and the constructor, the 8
#   with MontaTelaPedeIdentidade ahead of both builders give the target's locals.
# What the screens hold, in the target's order of calls and stores: MontaTelaPedeIdentidade chooses by
# comum::CAppInfo::EhTreinamentoEleitor (fn 697). MontaTelaTreinamento: AddBuzz(51, 10), AddClock({33, 1}), the title at
# {1, 1}, "Votos:" at {30, 2}, the slots of vota::GetTextoComparecimento (4053) at {37, 2} and GetTextoAudio (4054) at
# {40, 3} right, "CORRIGE: outras opções" at {1, 4}, "CONFIRMA: votar" at {1, 4} right (the target's point), AddLed(0),
# AddInputControl and GetInteractiveForm("", true). MontaTelaVotacao: first the count of fn 2823 (its two 16-bit counts
# summed to 16 bits, an unsigned argument, type 6) formatted with "/{:04}" into a named string, then AddBuzz,
# AddClock, the "Digite {}" text at {1, 1}, GetTextoComparecimento at {32, 2}, the count at {36, 2}, GetTextoAudio at
# {40, 4} right, the adder over a CTextSource of the string at {1, 4} with 300 ms and "%s", AddLed(0),
# vota::AdicionaCampoNumerico (fn 1151) with 12, true and {1, 2}, and GetInteractiveForm("", true). That the counts'
# struct is a temporary is a reading of the frame (its 4 bytes at +60 later hold SPoint{1, 4}); the internal helper
# TextoQuantidadeAptos is the form chosen for it. TextoDigiteIdentificador: CConfiguracaoEleicao::GetInst (fn 187)
# before the names' vector is cleared (the reference to the kinds is bound first), each kind's name pushed with
# push_back(&&) (fn 376), api::Join (fn 1696) with " ou " into a named string (the " ou " temporary is freed before the
# format) and std::format("Digite {}"). The adder: a CDataTextFmt<CTextSource> with its default alignment (0 at +4), the
# CTextFieldUpdateMT, a copy pushed into the builder's vector with emplace_back inlined (clang: cost 320, threshold
# 325) and the field released.
#
# 652 itself is unit 161's row (unresolved, self-voted on CPedeIdentidade::s_inst: unit 161's fragment). The roots file
# went: its vtable sink stood for the constructor, which is in the link now, inlined through unit 161's GetInst.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CTEXTFIELDUPDATEMT_SRCS := src/app/vota/operador/comum/ctextfieldupdatemt.cpp \
    src/app/vota/operador/comum/telasoperador.cpp
UENUX2_SRCS += $(CTEXTFIELDUPDATEMT_SRCS)
# telasoperador.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/comum/telasoperador.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
