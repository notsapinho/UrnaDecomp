# ASN.1 runtime's leftovers. src/mk/asn1.mk builds these objects, so this fragment holds no sources: it holds what the
# generated roots leave out, the unit's roots file, and what docs/how-to-decompile.md step 3 asks a fragment to say.
# docs/reference/facts/asn1.md A9 and A10 have the evidence. The target functions, by source:
#   asn1.cxx             GeneralizedTime::set (2185), its helper toInt (1519), create (8956), do_clone (8951),
#                        SEQUENCE::do_accept (8960, 8961), SEQUENCE_OF_Base's constructor (516) and getTypeName (9008),
#                        OCTET_STRING::do_compare (8964)
#   ValidChecker.cxx     AbstractData::getTypeName (5075), ConstVisitor::visit(const SEQUENCE&), inside 8960
#   ValidChecks.cxx      INTEGER::isValid, inside 8987, INTEGER::isStrictlyValid, inside 8976, lexicographic_compare_bytes,
#                        inside 8964
#   BERDecoderPartial    notify (2182) with makePath and findVisitor, inside it; addVisitor (8846, 8847), setVisitors (8824),
#                        and libc++'s instances over Visitante: 3476, 5049, 5050, 5058; the global destructor 8851
#   DataFree.cxx         the OpenData visitors (5034), the GeneralizedTime visitor (8749), freeData, inside 2182
#   CoderEnv.cxx         decode(seeder, val) (5060)
#   the roots object     SEQUENCE_OF<GeneralString>: operator= (5731) and the D0 (859)
# 9161 and 9182, ecourna's and a module's, match with 516's name: their bodies are unit 09's and unit 04's. 3323, std::stoi,
# is libc++'s, named here for 1519. 7867, messages<wchar_t>::do_get, is libc++'s, released: a caller these exclusions took
# away let its callee's name settle.
#
# What the target decided (evidence):
# - GeneralizedTime derives from AbstractData, not from UTCTime as upstream's does: its typeinfo (1149228) names base
#   1148580, AbstractData's, as UTCTime's does, and 8956 stores the vptr where UTCTime's create stores its own.
# - BERDecoderPartial::Visitante is a type libc++ marks trivially relocatable, not a plain class. 8846 and 8847 relocate
#   the vector with memory.copy, which libc++ does only for such a type; a class with these two members goes element by
#   element, 41 over 307 against 6 over 299. std::tuple gives the same bytes, so
#   std::pair<std::string, std::shared_ptr<IAbstractVisitor>> is chosen.
# - CoderEnv holds four rules and three more members. 679's br_table builds BERDecoder for 1, BERDecoderPartial for 2 and
#   PERDecoder for 3, so per_Basic_Aligned is 3. 5060 and 518 read +16, a vector of 20-B elements, and +28, a string, and
#   518 frees +4 with elements of 12 B whose shared_ptr sits at +4, so Modules' value is a shared_ptr.
# - INTEGER::isValid tests the type before the range, 8987's br_table [1 0 0 1]. Upstream's order gives other rows.
# - lexicographic_compare_bytes returns 0 at once for two null or two equal pointers: 8964's tests.
# - 5060 copies the log: 1700 is string::operator=(const string&), then the temporary's free. Moving it gives other rows.
# - findVisitor copies each path before it compares: f138 and the free are in the loop, in one loop condition.
# - 2185's bounds: the fraction under 20000000 and |mindiff| up to 1200 with minutes under 60, each a constant of the
#   target. The grammar it parses, date digits and then '.' or ',', '+' or '-', 'Z', is read from its tests. The name
#   millisec stays upstream's though it holds units of 10^-7 s (unit 87).
# - Files, as far as the target says. Clang inlines lexicographic_compare_bytes and hasOptionalField wherever it sees them,
#   and 8964 and 8960 hold them in wasm-opt's shape, so each is in another TU than its caller. AbstractData's vtable lies
#   right before ValidChecker's (A7), and getTypeName, its only non-pure out-of-line member, keeps it with the constructor.
# - Inliners. wasm-opt, each a call in the object: ConstVisitor::visit and Visitor::visit into 8960 and 8961,
#   lexicographic_compare_bytes into 8964, isValid and isStrictlyValid into 8987 and 8976, checkFields into 2185, makePath,
#   findVisitor and freeData into 2182 (their second and third prologues), default_delete into 5034. Each has one caller
#   once the words below leave the roots.
#
# Pending, none a trap, each with what it waits for (facts/asn1.md A10 has the measurements):
# - 1928, 3552: pair::~pair and vector<Visitante>::__destroy_vector at -Oz. A compile at -Oz -fexceptions holds pair::~pair as
#   a function of 1928's rows, and __destroy_vector calling it; -O2 and -O3 inline the destructor and -Os holds
#   allocator::destroy. So they are the executable TU's copies, and wait for that TU's reconstruction. 518 is
#   ~CoderEnv: 5706 stores the rule at +0 and passes that address to 679 and to 518. That it is the same -Oz copy, as its
#   call of 3552 suggests, is a reading. 3552 carries a hand edit for 2183's and 8851's sake.
# - 1843 find_first_not_of: the same, the rows -Oz gives; -Os, -O2 and -O3 do not. It matches from src/app/roots_vector.cpp's
#   minsize instance, which stands for the executable TU's copy; its census pair names it, so its hand edit went.
# - 1532: BER encoding through CoderEnv with landing pads, so an -fexceptions TU's, not the -Os runtime's. Its callers'
#   records name api::CFileASN.
# - 2706, 5282, 5290, 2704 and 2896: libc++ instances. 2706 is vector<char>::reserve, with landing pads, called by the
#   runtime's own 3464, 3472 and 5055. 5282 is a __split_buffer<char> constructor and 2704 and 2896 its destructor, with no
#   pad, whose copy came with 2706's. 5290 holds pads too. 2896 is the body of a merge of 2704, 2545, 4675 and 5523.
# - 2650 differs on one call: target 388, ours 424. Our link keeps one ~shared_ptr body where the target has two, and 2183
#   and 3469 match over it (unit 86's note).
# - 8902: calls 5056 and 1872, api's, and no runtime symbol.
#
# Chosen, with the forms measured to give the same bytes (one function's rows, object-local numbers masked):
# - The names ber_partial, toInt, checkFields, makePath, findVisitor, freeData, defaultVisitors, CoderEnv's visitors and log,
#   decode(seeder, val) as an overload of decode, and Visitante and Visitantes as typedefs. No record names them.
# - The file of each: lexicographic_compare_bytes in ValidChecks.cxx, ConstVisitor::visit in ValidChecker.cxx and
#   getTypeName of AbstractData there, each any TU the evidence above leaves. toInt is a file static, checkFields a private
#   member, makePath and findVisitor private members; a body wasm-opt inlines shows none of that.
# - CoderEnv::decode(const char*, ...) is a switch, 679's br_table. Its body is the target's only inside 679, not written.
# - 8987's body: `if (Unconstrained || Extendable) return true; return isStrictlyValid();` and a switch give the same rows
#   as the or written. Upstream's `isStrictlyValid() || ...` does not.
# - 8964's tests: the two swapped, or joined in one if, give the same rows.
# - 9008: `if (!name) return AbstractData::getTypeName(); return name;` gives the same rows; `name ? ... : ...` does not.
# - 5060: `const string text`, log.assign(text), and an early return of false each give the same rows.
# - 8846, 8847: push_back and emplace_back, each of Visitante(...) or make_pair(...), give the same rows. In-place
#   emplace_back(name, visitor) does not.
# - findVisitor: the condition in a for gives the same rows. A named local with a break, or no copy, does not.
# - notify's `consumed`: an int compared in the test gives the same rows.
# - 2185's loop: for (; !rest.empty(); ) and a direct-initialized digits give the same rows. erase(7) is not resize(7), the
#   two conditional strings are not an if over two assignments, and the rest's reset is not one ternary: each gives other
#   rows. 1519 with early returns, and checkFields' three range tests apart, give the same rows.
#
# The roots file: 859 and 5731 are template instances from the roots object. At APP_CXXFLAGS and at UENUX2_CXXFLAGS the object's
# functions are the same but __split_buffer<AbstractData*>::emplace_back, which the link takes from ecourna's object.
#
# splat/symbol_addrs.txt holds hand edits for this unit: 2650, 3323, 3552 and defaultVisitors, each with what it rests
# on. 2650 and 3552 name a body of ours that is not the target's, which is why no match can name them.
#
# Reading rule for the words below: a function stays in the roots if the target holds it. These are the functions the
# target holds nowhere, either inlined or never reached: BIT_STRING, BMPString, OpenData, Null and IntegerWithNamedNumber
# have no RTTI in ledger/classes.json, and each other word has no row in splat/scan.tsv. Rooted, they kept callers alive and
# merged bodies the target keeps apart: AbstractString's and BMPString's constructors joined 516's in a mgfn body.
# CoderEnv::decode(const char*, ...) stays: it stands for 679, and without it 1544, 2565, 3477, 5607, 7970, 8873, 8925 and
# 8927 leave match. OBJECT_IDENTIFIER has no RTTI either and stays: no row here needs it out, and the toolkit's AudioCollector
# tests read its vtable in our link. _ZN4ASN114AbstractStringC1EPKv is a substring of the two constructors 1521 and 2190, which
# the target holds, so the roots file takes those back.
ASN1_ROOTS_EXCLUDE += _ZN4ASN115GeneralizedTimeC1ERKS0_ _ZN4ASN115GeneralizedTimeC1EPKv _ZN4ASN115GeneralizedTimeC1Ev \
                      _ZN4ASN115GeneralizedTimeC1Eiiiiiiiib _ZN4ASN115GeneralizedTime10set_time_t \
                      _ZNK4ASN115GeneralizedTime10get_time_t _ZN4ASN115GeneralizedTime4swap \
                      _ZN4ASN17UTCTimeC1ERKS0_ _ZN4ASN17UTCTimeC1EPKv _ZN4ASN17UTCTimeC1Ev _ZN4ASN17UTCTimeC1Eiiiiiiib \
                      _ZN4ASN17UTCTime10set_time_t _ZNK4ASN17UTCTime10get_time_t _ZN4ASN17UTCTime4swap \
                      _ZN4ASN19BMPStringC1 _ZNK4ASN19BMPString10do_compare _ZNK4ASN19BMPString8do_clone \
                      _ZN4ASN19BMPString6create _ZNK4ASN19BMPString14legalCharacter \
                      _ZN4ASN110BIT_STRINGC1 _ZN4ASN110BIT_STRING9do_acceptERNS_7VisitorE _ZNK4ASN110BIT_STRING10do_compare \
                      _ZNK4ASN110BIT_STRING8do_clone _ZN4ASN110BIT_STRING6create \
                      _ZN4ASN18OpenDataC1 _ZN4ASN18OpenData9do_acceptERNS_7VisitorE _ZNK4ASN18OpenData8do_clone \
                      _ZNK4ASN18OpenData10do_compare _ZN4ASN18OpenData6create _ZN4ASN123TypeConstrainedOpenData6create \
                      _ZN4ASN14Null6create _ZNK4ASN14Null8do_clone _ZN4ASN14Null9do_acceptERNS_7VisitorE \
                      _ZN4ASN122IntegerWithNamedNumberC1 _ZN4ASN122IntegerWithNamedNumber6create \
                      _ZN4ASN17INTEGERC1EiPKv _ZN4ASN17BOOLEANC1 \
                      _ZN4ASN112ConstVisitor5visitERKNS_8SEQUENCEE _ZN4ASN17Visitor5visitERNS_8SEQUENCEE \
                      _ZN4ASN16CHOICE4swap _ZN4ASN18SEQUENCE4swap _ZN4ASN18SEQUENCE6BitMap5clear _ZN4ASN18SEQUENCE6BitMap3set \
                      _ZN4ASN116SEQUENCE_OF_Base6insert _ZN4ASN116SEQUENCE_OF_BaseaS _ZN4ASN127lexicographic_compare_bytes \
                      _ZN4ASN110PEREncoder10encodeByte _ZN4ASN110PERDecoder11setPosition _ZN4ASN110PERDecoder9byteAlign \
                      _ZNK4ASN110PERDecoder11getBitsLeft _ZNK4ASN110PERDecoder12getBytesLeft \
                      _ZN4ASN110BERDecoder11decodeBlock \
                      _ZN4ASN114AbstractStringC1EPKv _ZNK4ASN17INTEGER7isValidEv _ZNK4ASN115GeneralizedTime11checkFields \
                      _ZN4ASN117BERDecoderPartial8makePath _ZN4ASN117BERDecoderPartial11findVisitor _ZN4ASN18freeData

$(ROOT)/$(APP)/115-asn1-leftovers-roots.o: $(ROOT)/src/units/115-asn1-leftovers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/115-asn1-leftovers.mk $(wildcard $(ROOT)/src/asn1/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/115-asn1-leftovers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/115-asn1-leftovers-roots.o
