# uenux2 comum::asn::CVisitanteFoto::~CVisitanteFoto: the D2 (target fn 5709, vtable @1562436 slot 0) and the D0 (fn
# 11443, slot 1), and visit (fn 11442, slot 2), in src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp, the file
# visit's records (lines 40-63) name; no record falls in the destructor, so its line is not evidence. The class (RTTI: an
# si_class of ASN1::IAbstractVisitor, src/asn1/asn1.h) is declared in cvisitantefoto.h beside it, and the element of its
# vector in src/app/comum/dados/md/candidatura/cindicesfotos.h: a std::string and an SIndiceFoto (20 bytes, what the
# D2 destroys), presumed to be comum::md::CIndiceFoto (no record names either header: the file names are the classes',
# the md one the cindicesfotos.cpp record's). Only the layout reaches the destructors' bytes; the member names are
# not recovered.
# visit: its records give its declaration (ASN1::IAbstractVisitor::EVisitorResult visit(int, const std::string &,
# ASN1::AbstractData &, size_t, size_t)), so src/asn1/asn1.h declares the base's slot so (the runtime's objects compiled
# before and after that edit are cmp-equal: BERDecoderPartial.o, roots_asn1.o, unit 124's cindexadorfotos.cpp.o), the
# four throws' lines, codes (7883 to 7886, EUeComumDadosError's) and messages. The two paths it tests are the target's
# i64 constants ("EntidadeFotosCandidatos.fotos.OF", 32 bytes, and "...fotos.codigoCandidato", 45). Measured with
# pnpm wasm score: the position and length stored through SIndiceFoto's constructor (cindicesfotos.h) give the target's
# one i64 store after the sequencer's; an aggregate, the two members assigned one by one, or a named local all give two
# i32 stores ahead of it (54 over 530 rows in the whole link). The code is copied from the AbstractString's c_str()
# (strlen, then a copy) into a named md::CIndiceFoto, which push_back copies, as the target does (a call of the string
# copy); push_back of a temporary gives another body (912 against 946 rows of the object's visit). Chosen: the
# parameters' and the local's names, and EVisitorResult's enumerators (CONSUMIDO is 1, what BERDecoderPartial::notify
# tests). Same bytes, listed: the sequencer's store after the index's assignment, and SIndiceFoto{posicao, tamanho}
# through the constructor; the order written and the parenthesized call are chosen.
# The destructor is user-declared and defined out of line before visit, so it is the class's key function and the
# vtable is emitted here. Evidence: in the target's uses-1 band visit (11442) comes right before the D0 (11443), so the
# D0 has the lower link ordinal (docs/reference/link-order.md section 1, for ordinals of one digit count, as
# ledger/ordinals.tsv's 3857 and 3856 are): the D0 is emitted before visit. clang emits D2, D0, visit for a destructor
# defined before visit, and visit, D2, D0 for an implicit one (emitted with the vtable) or one defined after visit.
# The D2 stores the vptr, so the class is not final. Paths relative to src/uenux2; the generic uenux2 rule depends on
# the source and every uenux2 header.
CVISITANTEFOTO_SRCS := src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp
UENUX2_SRCS += $(CVISITANTEFOTO_SRCS)
# visit's declaration is src/asn1/asn1.h's IAbstractVisitor slot, a header the generic uenux2 rule does not depend on
$(foreach u,$(CVISITANTEFOTO_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h)))
# the visitor's user is not reconstructed yet: 36-uenux2-cvisitantefoto-roots.cpp keeps its vtable the way the target
# reaches it
$(ROOT)/$(APP)/36-uenux2-cvisitantefoto-roots.o: $(ROOT)/src/units/36-uenux2-cvisitantefoto-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/36-uenux2-cvisitantefoto.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/36-uenux2-cvisitantefoto-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/36-uenux2-cvisitantefoto-roots.o
