# uenux2 comum::CGeradorBUQRCode (app/comum/relatorios/cgeradorbuqrcode.cpp, its records' file, and a chosen
# cgeradorbuqrcode.h) and comum::CGeradorBUQRCodeVota (cgeradorbuqrcodevota.{h,cpp}, chosen paths; the headers say what
# the data show of them). Paths relative to src/uenux2.
#
# Matched:
# - CGeradorBUQRCode's D2 (target fn 2251), its key function, with the two destructors it calls: the destroy of the tree
#   of the map at +404 (fn 1405, std::map<md::ETipoAbrangencia, SQtdeAptos>'s; in the target it calls itself and has
#   five more callers, 2251, 5603, 5857, 11968 and 12098, and before this unit our link's candidate for it was another
#   tree's) and CCabecalhoQRCodeBuilder's implicit destructor (fn 2885), which clang keeps out of line, a weak function
#   of this object.
# - GetCamposAptos (fn 3696), which formats the coverage counts of the current post; it calls GetQtdAptos (record
#   cgeradorbuqrcode.cpp:80), out of line in the object, and binaryen inlines that into its one caller, as the target's
#   second stack frame inside 3696 shows (docs/reference/facts/reading.md R10).
# - CGeradorBUQRCodeVota's D2 (fn 11244), which only calls the base's, its D0 (fn 11243), and Slot3 (fn 11241), which
#   returns an empty string.
# - GetCamposVotos (fn 5606, no record; its stub was in src/ecourna/unplaced.cpp), which formats the current post's
#   votes after GetCamposAptos's fields: it calls GetCamposAptos (fn 3696) on its own this and slots 6, 9, 8 and 10 of
#   the object at +400 (comum::CRdv's Nominais, Brancos, Nulos and Cargo, crdv.h) with the byte at +0 of
#   CCargos::GetCurrent()'s CCargo, and prints them as "NOMI:{} ", "BRAN:{} ", "NULO:{} " and "TOTC:{} " (argument type
#   6, unsigned: md::TQtdVoto is a ueword). Its one target caller is fn 5604, which calls it twice.
# - CGeradorBUQRCodeVota's constructor (fn 5603), with CGeradorBUQRCode's (inlined, of cgeradorbuqrcode.cpp: one caller,
#   no frame), and CCabecalhoQRCodeBuilder's implicit copy constructor (fn 5608, a weak function of this file's objects;
#   its callers 5603 and 5604 are both here). cgeradorbuqrcodevota.h says why the constructor takes two flags its
#   callers pass as false.
# - Of Gera (fn 5604, below): preBuild's lambda (fn 2791, record ccabecalhoqrcodebuilder.cpp:284, unit 93's file),
#   api::CPolySingleton<api::pkcs11::IPkcs11>::instance (fn 3704, a template instance of this object; its records are
#   the header's), and std::sort's instances over the consulta's answers with GetCamposConsulta's comparator lambda:
#   __introsort (5605), __insertion_sort_incomplete (2790), __sort4 (1920) and iter_swap (248). 2790, 1920 and 248 are
#   also called by fn 5610 (another introsort of the same element, fn 11253's, not written); binaryen merges the
#   identical instances, so these are ours.
#
# Written, not matching: Gera (fn 5604, 22805 B, `no-candidate`: its records name no body that differs, since
# srcloc-anchor pairs bodies of the same opcodes only, docs/reference/splat.md section 2).
# It builds the boletim's QR code: the header (GetCabecalho: a copy of the builder, eight setters of unit 93's file,
# Slot2, build), the body (GetCorpo: per post, in print order, "IDEL"/Slot3 when the election changes, "CARG", "TIPO",
# "VERC" from the candidacies' or the election's package version, and the coverage and vote fields of a proportional,
# majoritarian or consulta post), cut into parts of at most its argument less 277 bytes at a space (DivideEmBlocos),
# each part's SHA-512 chained over the earlier parts (CalculaHash), and the last part's hash signed through IPkcs11
# (RetornaBlocoAssinado, record cgeradorbuqrcode.cpp:405, the instance() call). Each helper is a frame of its own in
# 5604, so each is a function binaryen inlined into its one caller. The target's body holds 10253 instructions and ours
# 10255, with the same direct calls and format strings in the same order but for one free (read from `pnpm wasm fn`'s
# folded readouts of both). pnpm wasm score: 3113 over 10484 rows (230 inserted, 228 deleted, 2590 of 2655 replaced rows
# operand-only); a diff of the two disassemblies with locals renamed by first use has 758 hunks: 584 differ in local
# numbers, call targets or data addresses alone, 94 only in local.get, local.set and local.tee rows, 20 only in one
# table slot operand (the target's 148, our 43), and 60 in more. What differs beyond locals, measured and not explained:
# GetCorpo's post loops reload the post's id and digit count where the target holds them in locals before the loop;
# DivideEmBlocos keeps the content's size and long flag in locals where the target reloads them in substr's check and
# bounds the loop by the size read before it; the frees of the label strings after preBuild's first table run in another
# order.
#
# Chosen: the names Slot2, Slot3, GetCamposAptos, GetCamposVotos, Gera and its helpers' (GetCabecalho, GetCorpo,
# GetCamposEleicao, GetCamposSecao, GetCamposProporcional, GetCamposCandidatosPartido, GetCamposLegenda,
# GetCamposVotosProporcional, GetCamposMajoritario, GetCamposConsulta, MontaPartes, DivideEmBlocos, CalculaHash), and
# every data member's; the helpers' being members where they read the object and free functions where they do not;
# Gera's std::pair result; SQtdeAptos's place and its members' names (from the labels 3696 prints); TEleicaoID for
# Slot3's parameter; the members' access; every line but the records' (80, 405); the "6.0" version and the 277 as
# literals; std::as_const in DivideEmBlocos, which picks CStringUtils::Trim's copying overload (fn 1374, as the target
# calls) on a string the loop assigns; md::CCargo::ETipo's std::formatter (comum::SFormatoEnum, as the other enums'), in
# cgeradorbuqrcode.cpp. md::CCargo gains the accessor GetAbrangencia (app/comum/dados/md/processoeleitoral/ccargo.h, a
# chosen name) for 3696's read of +8; api/pkcs11/ipkcs11.h is new (its header says what is chosen).
#
# Evidence, and what was measured (GetQtdAptos, Slot3, the destructors, GetCamposVotos):
# - The layouts and the destructors' forms are in the two headers. GetQtdAptos searches the map twice in the target, the
#   second time with map::at's out_of_range ("map::at:  key not found", fn 1239): a find tested against end() and then
#   at(). Its format argument is stored as type 3, an int, so the enum is cast. GetCamposAptos builds the string in the
#   result's place after GetQtdAptos returns (the target zeroes the result's 12 bytes after the inlined frame).
# - Forms that give the same function, compared by function with the object-local numbers masked: Slot3's
#   `return "";` and `return std::string("");` (`return std::string();` and `return {};` differ in 6 rows); `= default`
#   and `{}` for each class's destructor (CGeradorBUQRCode's D1 and D0, CGeradorBUQRCodeVota's D1 and D0). A test of
#   `m_qtdAptos.count(abrangencia) == 0` in place of find differs from the written GetQtdAptos in 72 rows.
# - The +400 member's type, from GetCamposVotos: the target calls the four slots through the vtable. As a reference to
#   CRdvVota, which crdvvota.h declares final, clang calls CRdvVota::Nominais and the others directly in the object
#   (tools/round/try-tu.sh --symbols, wasm-objdump -d: four `call`s); as a reference to the base CRdv the four are
#   `call_indirect`, as in the target. So the member is a `const CRdv&`, which the constructor stores
#   CRdvVota::GetInst()'s result in. GetCamposVotos matched by content when it landed.
#
# Not reconstructed: CGeradorBUQRCodeVota's Slot2 (fn 11242), a trap in 155-uenux2-cgeradorbuqrcode-pending.cpp, whose
# header says what it waits for.
CGERADORBUQRCODE_SRCS := src/app/comum/relatorios/cgeradorbuqrcode.cpp src/app/comum/relatorios/cgeradorbuqrcodevota.cpp
UENUX2_SRCS += $(CGERADORBUQRCODE_SRCS)
# cgeradorbuqrcode.cpp includes cconfiguracaoeleicao.h, whose ecourna CConfiguracaoMunicipio holds a CHorariosUrna of
# Boost ptimes, and ecourna/api/security/csha.hpp, which includes OpenSSL's evp.h; UENUX2_CXXFLAGS has neither path
# (unit 88 gives ccargos.cpp the Boost one, unit 122 gravadores/asn/util.cpp the OpenSSL one). An include path is not a
# flag of the code (asmlift-wasm/benchmark/README.md "The compile setups").
$(ROOT)/$(APP)/uenux2/src/app/comum/relatorios/cgeradorbuqrcode.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR) $(OPENSSL_INCLUDES)
W155_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# the member the vtable needs that is not reconstructed traps here, at the tree's flags
$(ROOT)/$(APP)/155-uenux2-cgeradorbuqrcode-pending.o: $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode.mk $(W155_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/155-uenux2-cgeradorbuqrcode-pending.cpp -o $(R)
# the roots declare what they reach through __asm__ labels and include no header
$(ROOT)/$(APP)/155-uenux2-cgeradorbuqrcode-roots.o: $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/155-uenux2-cgeradorbuqrcode-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/155-uenux2-cgeradorbuqrcode-pending.o $(APP)/155-uenux2-cgeradorbuqrcode-roots.o
