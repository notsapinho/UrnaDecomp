# uenux2 comum::md's identity-number rules, the three classes derived from comum::md::IRegraIdentidade:
# CRegraIdentidadeLivre's Formata (target fn 11274, slot 3 of its vtable @1574644), CRegraTitulo's
# ValidaDigitoVerificador and Formata (fns 11272 and 11271, slots 4 and 3 of its vtable @1574692) and CRegraCPF's (fns
# 11270 and 11269, vtable @1574732), in src/app/comum/dados/md/cregraidentidadelivre.cpp, cregratitulo.cpp and
# cregracpf.cpp, with their headers and the base's, iregraidentidade.h. The vtables' other slots hold bodies binaryen
# merges with other classes' and that match already: the implicit destructors, which destroy nothing (fns 174 and 144),
# GetTipo (fns 11273, 434 and 2254: return 3, 1 and 2) and CRegraIdentidadeLivre's ValidaDigitoVerificador (fn 371:
# return true). The constructors (inlined into fn 7787) are not written. IRegraIdentidade::Valida (inlined into fn 566)
# and EhValida are unit 178's. No record names these classes, files or members (docs/how-to-decompile.md step 3, "When no record names the
# file"):
# - the directory md/ is rule 3's choice from the family's one record, md/iregraidentidade.cpp:23, and the data speak
#   against it. In the uses-1 band the functions linked right before the family are md/rdv/'s (fns 11275 to 11339: CVoto
#   and the std::function bodies of CVotos and CVotosEleicoesVota), and the data order agrees: CRegraIdentidadeLivre's
#   vtable follows __func<CVotosEleicoesVota::Cargo>'s (@1574580), and CRegraCPF's typeinfo (@1574760) precedes
#   md/estadoaplicacao/cestadogeral.cpp's first record (@1574772). That refutes md/processoeleitoral/, the
#   class-convention guess of link-order clusters 426 to 428: its files run in name order at @1572748-1573260, and
#   nothing of the family lies where cregra* sorts, before crespostaconsulta.cpp. It speaks against md/ too: md/'s own
#   files run in name order at @1571564-1571948, and nothing of the family lies where cregra* sorts, before
#   csecaoeleitoral.cpp. So the original directory is one no record names, or the head of the unsorted
#   md/estadoaplicacao/. No byte and no record depends on the path;
# - the file names are the classes' in lower case (rule 4), and one class per file is a choice that fits the data: the
#   vtable and typeinfo pairs lie in the order Livre, Titulo, CPF, and two probes of one TU holding the three put CPF
#   first;
# - the sources are in the target's link order. Read in link order, the uses-1 band has 11274 11273, 11272 11271, 11270
#   11269, so ValidaDigitoVerificador comes before Formata in CRegraTitulo and CRegraCPF. CREGRA_SRCS lists the objects
#   in that order and the two .cpp files define the members in it, and our link's indices take the same order;
# - the member names are chosen (iregraidentidade.h says from what), and so are the base's slots being pure and the
#   file-static helpers Digitos, Soma and CalculaDV of cregratitulo.cpp and cregracpf.cpp (names and linkage).
# Key functions: the classes have them, since the TU that builds the rules, app/comum/dados/cconfiguracaoeleicao.cpp
# (the switch in fn 7787 throws its record, line 239, by default), holds no vtable of theirs in its data (@1558624 to
# @1558720). CRegraIdentidadeLivre's Formata comes before its GetTipo in link order, so it is out of line, and it is
# that class's key function. In CRegraTitulo and CRegraCPF the key function is not recovered. Here both members are
# defined out of line, which makes Formata, declared first, the key function, as in the free rule: that is our choice.
# Formata defined in the class, with ValidaDigitoVerificador the key function, gives the same bodies and the same order.
# Other choices that give the same bytes, measured as 0 differing rows in the object or as splat-remap's IDENTICAL in a
# whole link (tools/round/try-tu.sh, then pnpm wasm splat-remap):
# - the padded string can be a local of any inlined function: the file-static Digitos (here), one with an out-parameter,
#   a template or a lambda (0 rows in 11272). Written as a scoped local of ValidaDigitoVerificador itself, the frame
#   puts it below the digits and 11272 differs;
# - the sums can be the loop of the inlined Soma (here, with int or size_t counters), a run of soma += statements or one
#   expression assigned to a ueword (0 rows in 11270 and 11272). In 11272 the expression can also be CalculaDV's
#   argument (0 rows), and a loop in the method is IDENTICAL too. In 11270 a loop in the method differs (body byte 345:
#   the first two digits' terms swap), and so does Soma(digitos, 10, 11) for the second sum. Soma is our choice over the
#   expressions: the weights are plain runs (9 to 2, 10 to 2, 11 to 3), which is how a mod-11 check is usually written,
#   and these files have helpers already. 11272's second sum stays an expression: its three digits are not a run from
#   the start of the number;
# - 11270's second sum can name dv1 or digitos[9] (0 rows).
# Not free: 11270's check digit is a uebyte (its compare masks it with 255) and 11272's an int.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CREGRA_SRCS := src/app/comum/dados/md/cregraidentidadelivre.cpp src/app/comum/dados/md/cregratitulo.cpp \
  src/app/comum/dados/md/cregracpf.cpp
UENUX2_SRCS += $(CREGRA_SRCS)
# the rules' user is not reconstructed yet: 63-uenux2-app-comum-dados-md-roots.cpp keeps the three vtables the way the
# target reaches them
$(ROOT)/$(APP)/63-uenux2-app-comum-dados-md-roots.o: $(ROOT)/src/units/63-uenux2-app-comum-dados-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/63-uenux2-app-comum-dados-md.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/63-uenux2-app-comum-dados-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/63-uenux2-app-comum-dados-md-roots.o
