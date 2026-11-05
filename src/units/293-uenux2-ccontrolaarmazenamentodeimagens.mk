# uenux2 comum::CControlaArmazenamentoDeImagens' fn 2725 (5103 B, ccontrolaarmazenamentodeimagens.cpp's records at
# lines 73 to 152; written, not matched: below) and its callees that other target functions call too, paths relative to
# src/uenux2. Matched (steps 7 to 9 on this link):
# - api::CPolySingleton<api::IKernelHSM>::instance (target fn 2279, records cpolysingleton.h:78 and
#   cpolysingletonlist.h:99 and :105), over the head of api::IKernelHSM this unit adds (src/api/hwil/ikernelhsm.h, its
#   notes there);
# - ecourna::api::io::DeserializeFromFile<ModuloEnvelopeChave::EntidadeChave> (fn 2280, the records of
#   DeserializeFromBuffer, serialization.hpp:44 and :47, which binaryen inlines into it);
# - comum::asn::GravaArquivo for md::CEntidadeHashes (fn 5367), in the new
#   src/app/comum/gravadores/asn/cconversorentidadehashes.cpp, and its merge with unit 160's GravaArquivo for the
#   envelope (fn 2724): fn 6006, which forms once both are in the link (both writers' notes are in their headers);
# - libc's __futimesat (fn 6236, the body of utimes, which binaryen inlines into its callers) and SQLite's dotlockLock
#   (fn 12674), its other caller, from the libraries: with a second caller of utimes (the roots' stand-in, now 2725)
#   binaryen keeps __futimesat out of line, as the target does, where it inlined it into dotlockLock before.
# - std::filesystem::path::string() (fn 1555, 49 B), which 2725 calls out of line for each throw's message.
# CBaseError<comum::EUeComumReconhecimentoBiometricoError, ...>'s constructor (fn 5369, unit 186) comes from
# ccontrolaarmazenamentodeimagens.cpp.o, the first object to instantiate it in our link (unit 186's gave it before, with
# the same body). The two templates' instances come from cgravadorbu.cpp.o (unit 200's) now, the first object to
# instantiate them in our link since comum::CGravadorBU::LeChavePublica (held by fn 11629) is written; that the target's
# copies are cgravadorbu.cpp's is a reading of the data (their records lie in that object's run of the data, before
# IGravadorEnvelope's vtable @1554456), a uenux2 object without strict aliasing, the flags both
# ccontrolaarmazenamentodeimagens.cpp.o and the roots rule below compile with. serialization.hpp's ReadWholeFile is
# static, so each TU that includes the header has its own (the ODR question above): three include it now (this unit's
# two and cgravadorbu.cpp), and the link keeps cgravadorbu.cpp.o's instance of DeserializeFromFile, which calls that
# TU's copy.
#
# Measured on this link (pnpm wasm score against the target, then the scan):
# - 2280 with the file read in DeserializeFromFile's own scope, the CFile alive across the decode: 117 over 319 rows
#   (67 replaced, all operand-only, 25 inserted, 25 deleted: the CFile destroyed after the decode, and the locals
#   numbered otherwise), where the target destroys the CFile before the decode and builds the buffer in the stack slot
#   of the mode string, which died before it. With the read in a static helper that returns the buffer
#   (serialization.hpp's ReadWholeFile, inlined by clang: internal linkage, one call), 33 over 294, every row an operand
#   (calls, data addresses, the error's table slot), and the scan matches it. The helper inline (not static) and an
#   immediately called lambda each stayed out of line, and clang then inlined DeserializeFromFile into the roots'
#   stand-in (names.tsv lists the helper and DeserializeFromBuffer, and no DeserializeFromFile). The helper's name and
#   linkage are chosen; no record names it. `static inline` and an anonymous namespace give this unit's roots object
#   byte for byte, and `inline` alone keeps the helper out of line and DeserializeFromFile inlined into the stand-in
#   (each compiled at the roots' rule from a copy of the header found first and prefix-mapped to the tree's path, the
#   unchanged copy's object cmp-equal to the link's). `static` stays. By [basic.def.odr] a name in a template's
#   definition must refer to the same entity in every TU that defines the template, so a function of internal linkage
#   that DeserializeFromFile calls makes the program ill-formed (no diagnostic required) as soon as a second TU includes
#   the header, whether it instantiates the template or not; the failure one would see, the one instance the linker
#   keeps calling one TU's helper, needs two TUs to instantiate the same specialization. Only this unit's roots include
#   the header now, so it is harmless today.
# - 2279 82 over 900 rows, 5367 and 2724 6 over 10 each, 6006 58 over 712, every row an operand.
# - 6236 against our __futimesat: with the stand-in reading the result, 11 over 69 rows (its i32 result, which the
#   target's type lacks); dropping it, as both target callers do, 3 over 67, operands only, and dotlockLock 4 over 54
#   (5 over 55 with the stand-in that read it: a drop after the call).
#
# Fn 2725, CControlaArmazenamentoDeImagens::ArmazenaImagem (a chosen name; a static member, as the records' functions
# are), in src/app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.cpp with the header beside it:
# written, not matched. It returns 999999 (ID_INVALIDO) when statfs on CPath::GetPathDinamico(FLASH_EXTERNA) succeeds
# and the external flash has less than 5 MiB free; else it takes an id and the two paths from GerarCaminhosUnicos
# (record :73: the RNG's instance, `GetInt() % 999999`, "{}{:06}.wsq" with the prefix, "{}{}" with each directory,
# until api::CSystem::ExistFile fails), calls vota::CConversorWsq::GetInst (fn 2742) and copies the image (the
# inline PreparaWsq this unit adds to cparametrosimagemdigital.h: the target drops GetInst's result and copies the
# vector in place), returns 999999 for an empty image, and else ciphers it (CifrarWsq, records :149 and :152: IUrna's
# slot 4 fills a 1024-byte table, the RNG 32 random bytes, LeChavePublica, records :117, :127 and :135, decrypts the
# key of "wsq.pk1" in CPath::GetPathChave() with the password the HSM's slot 3 gives, throwing 9000 or 9001 with "O
# arquivo ", the path and " não existe" or " está vazio"; then CPlainText over the zone and section of CLocal and
# CCepescCipher::Encrypt), writes it as a CEnvelopeGenerico of type ENVELOPE_IMAGEM_BIOMETRIA over the pleito's date
# at midnight, the phase, CLocal's municipality, zone, location (when TemSecao) and section and CSeguranca(0, 1, the
# ciphered key) with comum::asn::GravaArquivo into a CFile ("w+b", FM_NOATIME), clears the file's times with utimes,
# and copies it to the external flash (CopyFile, true for the bool the target keeps); it returns the id.
# - Each of its parts is a function of its own in the target, behind a stack frame of its own in 2725 (432, 1168, 480,
#   32, 320 and 32 bytes), which binaryen inlined, its one caller: GerarCaminhosUnicos, CifrarWsq and LeChavePublica
#   by their records, GravaWsqCifrado (CifrarWsq then GravaEnvelope) and GravaEnvelope (chosen names), and a function
#   that zeroes two struct timeval and calls utimes, whose file is not known: here it is ZeraDataHora (chosen) in this
#   file, which clang inlines (the object's ArmazenaImagem calls utimes), so the two timevals are in 2725's own frame.
# - Its first parameter after the image, a file name both target callers build and 2725 never reads (binaryen's
#   dead-argument elimination dropped it: 5382 and 10425 each build a name, pass the rest and free it), is a reading;
#   its place among the parameters is chosen.
# - Measured in the whole link (pnpm wasm score against the target): `417 over 2361 rows (same 1944, replaced 293
#   [272 operand-only], inserted 53, deleted 71)`. The scan stops at +0x314 on the "{}{}" format string, which the
#   target holds as the tail of "{:05}{:04}{:04}{}{}{}{}" (@1071), a literal no function of our link holds yet
#   (`string tail occurs 4098 times`); the free-space test differs (ours `f64.lt` where the target has `f64.ge`): 5371
#   took the target's test with the threshold as a parameter (unit 214's fragment), a form not tried here; and the
#   frames: 2725's own is 160 bytes against 112, ZeraDataHora's timevals among them,
#   GravaEnvelope's 304 against 320. The rest is not explained.
# - Its name: a callers+content hand line in splat/symbol_addrs.txt, led by the six records only 2725 loads, whose
#   copies only our ArmazenaImagem loads (`check_srcloc.py --strict` lists them as the target's); 5382 (unit 135),
#   its one caller in our link, needs it, and falls without it (weighed by removal: unit 135's fragment). Its other
#   caller, fn 10425 (vota::CMostraEleitorVotando's, not written), has a stand-in in the roots.
# - Chosen besides: the names of GravaWsqCifrado, GravaEnvelope and ZeraDataHora, their being static members,
#   ID_INVALIDO and its type, every local's name, PreparaWsq's name and its being an inline member of
#   vota::CConversorWsq, the access of each member, and the lines and order of the functions without a record (after
#   CifrarWsq: GravaEnvelope, GravaWsqCifrado, ZeraDataHora, ArmazenaImagem).
#
# The roots stand in for 2725's other caller, fn 10425, and for the other callers of the instances above
# (293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp). The stand-in for 2725's call of utimes went: 2725 is in the
# link, beside SQLite's dotlockLock, and libc's __futimesat (6236) still matches.
CCONTROLAARMAZENAMENTO_SRCS := src/app/comum/gravadores/asn/cconversorentidadehashes.cpp \
    src/app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.cpp
UENUX2_SRCS += $(CCONTROLAARMAZENAMENTO_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CCONTROLAARMAZENAMENTO_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# ccontrolaarmazenamentodeimagens.cpp reads comum::CConfiguracaoEleicao, whose header includes Boost's ptime
$(ROOT)/$(APP)/uenux2/src/app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# 293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp stands in for the callers not written; it compiles with the
# tree's flags, the flags of the object whose template copies the target keeps
$(ROOT)/$(APP)/293-uenux2-ccontrolaarmazenamentodeimagens-roots.o: $(ROOT)/src/units/293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/293-uenux2-ccontrolaarmazenamentodeimagens.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null) $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/293-uenux2-ccontrolaarmazenamentodeimagens-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/293-uenux2-ccontrolaarmazenamentodeimagens-roots.o
