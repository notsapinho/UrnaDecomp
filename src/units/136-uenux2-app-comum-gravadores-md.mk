# uenux2 comum's result data classes, the converter of one of them, and the recorders' destructors, in the files the
# records name (paths relative to src/uenux2/src/app/comum):
# - md::CCarga (dados/md/correspondencia/ccarga.h, layout only): its implicit copy constructor (target fn 1557), which
#   the objects of curna.cpp, cenvelopegenerico.cpp and ccorrespondenciaresultado.cpp hold, the link keeping
#   curna.cpp.o's; md::CCorrespondenciaResultado's constructor (fn 2801, ValidaCriacao inlined by binaryen) in
#   dados/md/correspondencia/ccorrespondenciaresultado.cpp.
# - md::CUrna (gravadores/md/curna.{h,cpp}): both constructors (fns 2854, 2855), ValidaCriacao (fn 5862) and the implicit
#   destructor (fn 1394), which unit 160's cconversorenvelopegenerico.cpp.o emits (its DoDesconverte deletes a CUrna),
#   ahead of this unit's roots object; comum::ETipoArquivo is declared in curna.h.
# - md::CEnvelopeGenerico (gravadores/md/cenvelopegenerico.{h,cpp}): the three constructors (fns 3821, 5860, 5861) and
#   ValidaCriacao (fn 3822); the getters GetUrna, GetLocal and GetSeguranca (records :96, :106, :117), which binaryen
#   inlines into their one caller, CConversorEnvelopeGenerico::DoConverte (fn 10271, unit 160), as the target's does.
# - md::CEntidadeHashes::ValidaCriacao (fn 5855, gravadores/md/centidadehashes.{h,cpp}; the header holds the head of
#   the layout only).
# - md::CTipoApuracaoSA (gravadores/md/ctipoapuracaosa.{h,cpp}) and asn::CConversorTipoApuracaoSA
#   (gravadores/asn/cconversortipoapuracaosa.{h,cpp}): DoConverte (fn 10283, the four ConverteMotivo* inlined by
#   binaryen) and DoDesconverte (fn 10282, the data class's constructor and checks inlined).
# - The recorders' destructors, emitted with their vtables in 136-uenux2-app-comum-gravadores-md-pending.cpp, whose
#   traps are the classes' key functions (src/units/README.md "The key function pending"): IGravadorEnvelope's (fn
#   11625), CGravadorHashes's (5853, 11619), CGravadorRDV's (11586, and 11585, matched, below), CGravadorLog's (5823,
#   11583) and CGravadorVersoesArquivos's (11581, 11580), and binaryen's merge of the base-object destructors of
#   CGravadorRDV and IGravadorEnvelope (fn 6043, written, below; our link forms the same two-member merge,
#   byn$mgfn-shared$_ZN5comum12CGravadorRDVD2Ev). The class heads are unit 102's (gravadores/cgravador*.h,
#   igravadorenvelope.h); this unit adds their layouts and virtual members there. CGravadorRCSecao's deleting destructor
#   (fn 11615) is unit 122's. CGravadorEnvelopeArquivo's (fns 11622, 11621, matched, below) are emitted with its vtable
#   by unit 160's cgravadorenvelopearquivo.cpp, which holds its key function.
# - ModuloTiposResultadosEcoUrna (src/asn1/modules/): the records and RTTI name ModuloTiposResultadosEcoUrna::TipoApuracaoSA
#   (the converter's base, typeinfo @1596936) and MotivoApuracaoManual, MotivoApuracaoEletronica, MotivoApuracaoMistaComBU
#   and MotivoApuracaoMistaComMR (the four ConverteMotivo* records' result types), which the generated module held
#   nested as Urna::motivoUtilizacaoSA::value_type and the four motivoApuracao::value_type; they are classes at namespace
#   scope now, the fields' value_type a typedef of them (src/asn1/README.md "The generated modules"). The module's
#   object holds the same code and data bytes before and after (wasm-objdump -d and -s -j Data compared), its data
#   symbols renamed.
#
# Evidence: the records give each member's file, line, column and signature, the vtables and RTTI each class and slot,
# and the bodies the layouts (each header says from what), the codes and the messages. The recorders' layouts come from
# their destructors and from vota::CGravaResultado::StartState (fn 12098) and fn 5856, which build them.
# Chosen: every member, enumerator, parameter and getter name; the headers' paths (beside the .cpp their records name,
# or beside igravador.h); comum::EUrnaTipo (dados/md/estadoaplicacao/eurna.h) as the urna's type, the CBaseType
# identifiers of iresultado.h in CEnvelopeGenerico, ETipoArquivo's and CEnvelopeGenerico::Tipo's enumerator
# names, CTipoApuracaoSA's type as a nested enum with a formatter, the motivos as integer literals in the switches,
# the parameter forms beyond what the bodies copy (const references), the lines of every function with no record, the
# recorders' trivial members' types, the order of the md classes' constructors, and that the checks are private.
#
# Forms measured in this unit's link (pnpm wasm score, then the scan):
# - CCorrespondenciaResultado's identifiers are plain unsigned words: with iresultado.h's CBaseType aliases read through
#   Get(), the three unsigned throws store the format's argument types before its string, the target the reverse
#   (the header has the probe).
# - CConversorTipoApuracaoSA::DoConverte reads the type into a local before the switch, which the default's
#   std::format takes by address: written as dado.GetTipoApuracao() in both places, the store of the value moves into
#   the default case (7 rows inserted, 5 deleted against the target).
# - CTipoApuracaoSA::ValidaMotivoApuracao's cases run 1, 3, 4, 2: in the order 1, 2, 3, 4 the br_table differs.
# - CGravadorLog's destructor is declared in the class: implicit, its deleting destructor inlines the base-object body
#   (53 rows inserted), where the target calls it. CGravadorHashes's implicit destructor gives the target's call
#   shape (a reading: its base-object body, two shared_ptr releases more, costs more to inline), and so does
#   `~CGravadorHashes() override = default;` in the class: the pending object is byte-identical either way at the
#   tree's -O3. Implicit is the choice.
# - The phase tests of CEnvelopeGenerico and CEntidadeHashes are written `m_fase == '0' || m_fase > FASE_TREINAMENTO`,
#   the target's two compares (48 and 52, signed); no other spelling was measured.
# Same bytes: CGravadorHashes's destructor implicit or declared `= default` in the class (above); no other form here
# was measured to give the same bytes.
#
# CGravadorEnvelopeArquivo's destructors (fns 11622, 11621), CGravadorRDV's deleting destructor (11585) and the merge
# 6043 call md::estadoaplicacao::CDadoCorrespondencia's base-object destructor (fn 857) and drop the this it returns.
# They match while a function of our link uses that result, and with none they differ by that drop alone (pnpm wasm
# score: deleted 1, every other row operand-only). At -O2, CAppInfo's destructor in appinfo/cappinfosingleton.cpp.o
# used it at two of its three calls; at the tree's -O3 it calls the destructor once and drops it. The target's users of
# the result are fns 5532, 7787, 9873 and 11395; src/app/roots_vector.cpp holds the executable TU's copies of 5532 and
# 9873, which keep it (docs/reference/facts/splat.md §S10 item 17).
#
# Not matched, and what each waits for:
# - The converters of CUrna, CCorrespondenciaResultado and CEnvelopeGenerico (fns 10287, 10284, 10289, 10288, 10271,
#   10270) are unit 160's. Not written: CConversorEntidadeHashes::DoConverte (10266), which needs CEntidadeHashes's
#   members past +36.
# - IGravador's slots 2 to 6 (fns 11630 to 11634, unit 60's traps) are not this unit's. CCarga::ValidaCriacao (fn 5670)
#   is unit 157's (dados/md/correspondencia/ccarga.cpp), and matches.
GRAVADORES_MD_SRCS := src/app/comum/gravadores/md/curna.cpp src/app/comum/gravadores/md/cenvelopegenerico.cpp \
	src/app/comum/gravadores/md/centidadehashes.cpp src/app/comum/gravadores/md/ctipoapuracaosa.cpp \
	src/app/comum/dados/md/correspondencia/ccorrespondenciaresultado.cpp
GRAVADORES_ASN_SRCS := src/app/comum/gravadores/asn/cconversortipoapuracaosa.cpp
UENUX2_SRCS += $(GRAVADORES_MD_SRCS) $(GRAVADORES_ASN_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(GRAVADORES_ASN_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# not every caller is reconstructed: 136-uenux2-app-comum-gravadores-md-roots.cpp stands in for the others, two call
# sites each; it compiles with the tree's flags, since it emits CUrna's inline destructor (fn 1394), TSE code (the link
# keeps unit 160's copy, from cconversorenvelopegenerico.cpp.o, linked ahead of it)
$(ROOT)/$(APP)/136-uenux2-app-comum-gravadores-md-roots.o: $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/136-uenux2-app-comum-gravadores-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/136-uenux2-app-comum-gravadores-md-roots.o
# the recorders' key functions are not reconstructed: 136-uenux2-app-comum-gravadores-md-pending.cpp gives them trapping
# bodies, compiled with the tree's flags, and emits their vtables and implicit destructors
$(ROOT)/$(APP)/136-uenux2-app-comum-gravadores-md-pending.o: $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/136-uenux2-app-comum-gravadores-md.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/136-uenux2-app-comum-gravadores-md-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/136-uenux2-app-comum-gravadores-md-pending.o
