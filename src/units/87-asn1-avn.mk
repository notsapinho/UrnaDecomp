# ASN.1 runtime: AVNEncoder, AVNDecoder, InvalidTracer and the asn1.cxx members they reach. src/mk/asn1.mk builds these
# objects, so this fragment holds no sources: it holds what the generated roots leave out, the unit's roots file, and
# what docs/how-to-decompile.md step 3 asks a fragment to say. docs/reference/facts/asn1.md has the evidence (A5 the names,
# A7 the files).
#
# Pending, sources as written:
# - 208 and 2653 hold one drop after basic_ostream::put, and 2186 one constant argument to basic_istringstream's
#   constructor. 8890 holds one drop after __input_arithmetic_with_numeric_limits<int>, through operator>>(int&). Their
#   rows are the target's otherwise. Our RHVoice's userdict.cpp calls these through invoke_*, so each keeps a table slot
#   and with it its result or its mode parameter; the target's 9665 calls 2567 directly and 2567 and 2237 have no slot.
#   That is read from the slots, not measured by a link without them. Of 770 rows with a candidate from RHVoice, 3 target
#   bodies hold a landing pad and 192 of ours do.
# - 8887 holds one constant argument to basic_stringstream's constructor, table slot 1327, which roots_ecourna and Boost's
#   parse_iso_time in ecourna's datahoraasn object load.
# - 3559 and 9471, the destructors of AVNEncoder and AVNDecoder, are not the -Os copies their .cxx emits. Only 3559, 8903
#   and 9770 hold AVNEncoder's vptr and 8873, 9471 and 679 AVNDecoder's. 9770 and 679 are not written; by their calls they
#   read as CoderEnv's encode and decode templates, which is a reading. Which TU's copy the target keeps is not known:
#   against probes, before binaryen, 9471's rows are nearest at -O2 and -O3 (0.661) and 3559's are nearest at -Os and above (0.491).
# - GeneralizedTime::set (2185, 1698 B, not listed) is not written, so the bool at +44 keeps the constructors' true.
# - 1497 is libc++'s substring constructor, named for its caller 2184; ours is the sysroot's body and differs.
#
# Not this class: 10840 and 10822 are api::AudioCollector's destructors, not OBJECT_IDENTIFIER's (facts/splat.md S4).
#
# What the target decided:
# - No AVNPrinter: RTTI has none, so it and AbstractData::Print are gone from AVNEncoder.cxx. Their callers kept
#   vector<bool>::push_back and IntegerWithNamedNumber::getName out of line.
# - InvalidTracer's two time visitors test !isStrictlyValid(): 8929's i32.eqz. Upstream's test is inverted. 8928 also
#   prints value.get(): its second string goes through 2184.
# - GeneralizedTime holds a bool at +44: 5072 and 8928 read it, 8951 copies it, 8956 sets it, 2185 computes it, and
#   8951 and 8956 allocate 48 B. So isStrictlyValid() is that bool's accessor, inline in asn1.h.
# - GeneralizedTime::get (2184) is the fork's: snprintf into 64 B, a ".%07d" fraction cut with find_last_not_of('0'), and
#   "-%04d" or "+%04d". So millisec, upstream's name, holds units of 10^-7 s here.
# - UTCTime::isStrictlyValid (5076) checks days per month and leap years, and hour against 23. `case 2:` and not
#   `default:`: a default leaves a range check the target does not have.
# - find_first_invalid (3480) searches the sorted set per character. The target does not use find_first_not_of.
# - 8919 loads strm once, before getName. The form without the local gives one more row.
# - Inliners. wasm-opt, each a call in the object with one caller left: both setFromName into 8888 and 8889, get_id into
#   8882, both getName into 8919 and 8920, get_from_string into 5055 (behind a second prologue), vector<bool>::push_back
#   into 8906. clang inlines ENUMERATED::getName when it sees the body, and 8919 rereads value.asInt() after it as a call's
#   caller does, so getName is in another TU than AVNEncoder.cxx.
#
# Chosen, with the forms measured to give the same bytes (one function's rows, object-local numbers masked):
# - The file of AbstractData's constructor: any TU none of its 22 callers is in. ValidChecker.cxx, because its vtable lies
#   right before ValidChecker's and only 669 stores that vptr. The file of ENUMERATED::getName: asn1.cxx, any TU but
#   AVNEncoder.cxx.
# - The name of the bool at +44, `valid`.
# - 2184's spelling: strcpy(buf, "Z"); result.assign(buf); result.append(buf); result.append(fraction.substr(...)) each
#   give the same rows. Testing mindiff >= 0 first does not.
# - 8929 and 8928 with an early return true, or 8929 over a local bool. 8919 with name declared in the if.
# - 5076's leap test as a static helper gives the same rows as the test in place. The form with a local bool and
#   `leap ? 29 : 28` does not.
# - find_first_invalid in the class. An index loop, the search spelled in the loop's condition and std::find_if each
#   give other rows; its definition out of line in asn1.cxx was not measured.
#
ASN1_ROOTS_EXCLUDE += _ZN4ASN110ENUMERATED11setFromName _ZN4ASN122IntegerWithNamedNumber11setFromName _ZN4ASN16get_idE \
                      _ZN4ASN115get_from_string _ZN4ASN114get_value_fromE _ZN4ASN110get_stringE _ZNK4ASN110ENUMERATED7getName \
                      _ZNK4ASN122IntegerWithNamedNumber7getName _ZN4ASN18SEQUENCE11FieldVector \
                      _ZNK4ASN112AbstractData15asValueNotation _ZNK4ASN112AbstractData8print_on \
                      _ZN4ASN1lsERNSt3__213basic_ostreamIcNS0_11char_traitsIcEEEERKNS_12AbstractDataE \
                      _ZN4ASN112AbstractData20setFromValueNotation _ZN4ASN112AbstractData8get_from \
                      _ZN4ASN1rsERNSt3__213basic_istreamIcNS0_11char_traitsIcEEEERNS_12AbstractDataE

$(ROOT)/$(APP)/87-asn1-avn-roots.o: $(ROOT)/src/units/87-asn1-avn-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/87-asn1-avn.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/87-asn1-avn-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/87-asn1-avn-roots.o
