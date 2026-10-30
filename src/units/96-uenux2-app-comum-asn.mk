# uenux2 comum::asn::Utils in src/app/comum/asn/util.cpp, the records' file: ConverteFase, DesconverteFase,
# ConverteTipoLocalVotacao and DesconverteTipoLocalVotacao (target fns 1712, 2843, 3801, 3800), and DesconverteAbrangencia
# (5827), written and not matched. The class header app/comum/asn/util.h, the error header euecomumasnerror.h and the
# enum EUrnaFase (app/comum/eurnafase.h, which unit 60's cgravadorwsq.h includes in place of its opaque `: int`
# declaration: the target formats EUrnaFase through fn 536, formatter<unsigned int>).
#
# Evidence: the records give each member's name and signature, the throws' lines and columns (19 is a throw inside the
# switch, in a default:, for the two Fase members; 11 is a throw after the switch for the other three), and the
# codes, messages and bodies give the rest. A by-value TipoLocalVotacao is the address of the caller's copy (3800's p0).
# The switch tables 497848 and 497860 and the identity ranges give the enums' values.
# Chosen: the names of the enumerators, where ETipoLocalVotacao and md::ETipoAbrangencia are declared, EUrnaFase's
# comum:: scope, the header paths, and that one template over the underlying type formats the enums (util.h). `: int`
# with an explicit formatter<unsigned int> gives the same bodies.
#
# Forms that give the same function, measured in the object with the object-local numbers masked:
# - the switch's `return X::a;` against `return X(X::a);` and `{ X r; r.set_a(); return r; }` (1712, 3801);
# - `default: break;` against no default before the throw after the switch (5827, 3801, 3800);
# - `fase.asInt()` against `static_cast<int>(fase)` in the message (2843, 3800), and `switch (x)` against
#   `switch (x.asInt())` over the entity (2843, 3800);
# - an if chain against the switch in 5827;
# - the formatter's template against an explicit specialization per enum, E by value against `const E&`, and a template
#   context against std::format_context&.
# A local result assigned in the switch and returned after it does not give 1712 or 3801: the constructor moves ahead of
# the check. So the switch returns.
#
# Not matched, and what each waits for:
# - 5827 DesconverteAbrangencia is right apart from one name: it formats a generated `int` enum, so its handle is fn 1711,
#   formatter<int>, and the name 1711 has only this body's vote (`unresolved self-voted`). It matches when another
#   function that stores a slot of 1711 matches: 11450, 11416, 11373, 10284 or 10270.
# - 1713 DesconverteDataHoraJE is not written. It builds ModuloTiposEleitorais::DataJE and HoraJE, which RTTI names and
#   src/asn1/modules/ModuloTiposEleitorais.h does not declare, and calls fn 2276, whose callees 2765 and 3649 (api::CDate's
#   constructors) have no body of ours.
# - 731, the base's default DoConverte and DoDesconverte merged, and 11418, IConversorBiometriaASN's default DoConverte,
#   need -O3, which uenux2's flags do not have (docs/reference/facts/levels.md §V3). Their format strings are 44 and 47
#   bytes. In a body that is only such a throw, the object at -O2 keeps libc++'s search of the format string for a brace
#   (__try_constant_folding, inlined by clang) as a loop: a probe folds up to 36 bytes, and at -O3 up to 74. The target has
#   no such loop for these and keeps one for its strings of 79 bytes and more (10226, 11514, 10772). In a
#   private link with UENUX2_EXTRA=-O3 (facts/app-flags.md §F9 item 6), holding the defaults in iconversorasn.h and
#   comum::asn::CConversorHistoricoVotoImpresso for one inherited DoDesconverte, the shared body gives `target 731:
#   IDENTICAL` from splat-remap; thunks 11360 and 10275 differ in operands only, their call of 731; 11418's rows differ
#   in operands only and its first difference is the record, which a scratch file cannot hold; and every match of the
#   tree still verifies, sha256 the target's. The defaults stay as unit 47's specialization with their source in its
#   header, since the target's body is a merge thunk (src/units/README.md "An inherited template default").
# - 11437, 11438 and 11401 hold other members of this file inlined. 11437 and 11438 need fn 591, and 11438 needs fns 515
#   and 339 as well, none of them with a name, and 2654, which differs. 11401 calls fn 5693, which has no body of ours.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
COMUM_ASN_SRCS := src/app/comum/asn/util.cpp
UENUX2_SRCS += $(COMUM_ASN_SRCS)
# the converters that call these members are not reconstructed yet: 96-uenux2-app-comum-asn-roots.cpp gives each its
# second call site, the way the target reaches them
$(ROOT)/$(APP)/96-uenux2-app-comum-asn-roots.o: $(ROOT)/src/units/96-uenux2-app-comum-asn-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/96-uenux2-app-comum-asn.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/96-uenux2-app-comum-asn-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/96-uenux2-app-comum-asn-roots.o
