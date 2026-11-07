# ASN.1 runtime: BERDecoderPartial, PERDecoder, PEREncoder, ValidChecker, StrictlyValidChecker and DataFree, with the
# data classes' isValid and isStrictlyValid in the new src/asn1/ValidChecks.cxx. src/mk/asn1.mk builds and keeps these
# objects, so this fragment has no sources and no rules: it names what the generated roots leave out, and holds what
# docs/how-to-decompile.md step 3 asks a fragment to say.
#
# Pending, each written and in its source, none a trap:
# - 2650 allocator<Visitante>::destroy matches since unit 229's root. It differed by one call, 3 over 19 rows: target 424,
#   shared_ptr<ISeeder>'s destructor among others, has no result, and BERDecoderPartial's destructor and constructor
#   (2183, 3469) match over it; target 388 is a second copy that reads +4 and keeps its result, and 2650 calls it and
#   drops that, so one body of ours could not serve both. Since unit 237 our link has both bodies (388 matches from the
#   executable TU's object, its result read by 11530), and since unit 229's root emits ~shared_ptr<IAbstractVisitor> at
#   that TU's rule, ahead of the runtime, our 2650's call reaches 388's body.
#
# What the target decided:
# - The runtime's object order: asn1.o links first among the runtime's objects (src/mk/asn1.mk), and with it 8811
#   PERDecoder::do_visit(SEQUENCE_OF_Base&) matches. 8811 holds SEQUENCE_OF_Base::resize, asn1.cxx's, inlined by
#   wasm-opt. With asn1.o in the name order, after PERDecoder.o, 8811 scores 94 over 382 rows (18 inserted, 15 deleted:
#   local numbers, the order of some operands and one block more than the target), at 9f0245ef; 543, the callee this
#   note once named as the cause, matches since unit 89 (docs/reference/facts/asn1.md A5). With asn1.o first it scores 6
#   over 364, every row a call, and matches. The target's data give the place: ranked by the addresses the symbol file
#   gives the vtables and typeinfos each object emits in .rodata (the runtime builds without -fPIC), asn1.o is first
#   (0x1183b8), then ValidChecker.o, AVNDecoder.o, InvalidTracer.o, AVNEncoder.o, BERDecoderPartial.o, BERDecoder.o,
#   PERDecoder.o, BEREncoder.o, PEREncoder.o, DataLengthCounter.o and DataFree.o. docs/reference/facts/codegen.md C4's
#   count, over the objects with .rodata vtables and typeinfos alone (C4's script ranks .data.rel.ro and records; this
#   one that segment's _ZT[VI] names, records left out), on 9f0245ef's plain link.cmd: 12 objects out of the data's
#   order against asn1.o in the name order, 1 at the head of the runtime's list (RHVoice's language.cpp.o,
#   RHVOICE_BEFORE_ASN1, whose .rodata lies after the runtime's), rising by one with each ranked object passed to 9
#   right before PERDecoder.o; 0 before language.cpp.o, outside the runtime's list (src/units/README.md "Names": not
#   taken). The head is taken.
# - BERDecoderPartial::decodeHeader (995) writes the type's name in the one << chain: the target builds the string
#   between " on type " and " on position ". A named string before the chain moves 11 rows.
# - decodeTime reads len once: 8828 and 8829 compare twice over that one read, which is LLVM sinking one compare to its
#   two uses. The compare written twice reads len again, in 96 rows against 92.
# - preVisitExtensionRoots (8827) tests m_path.size() == 0: empty() gives begin == end, the target's end == begin. It
#   pushes an lvalue, twice: 5054 and 938 are the push_back(const&) overloads, and the first string dies before the
#   next takes its frame slot. endPosition reads tell() first: `len + tell()` gives other rows.
# - visitExtensionRoot (8826) accepts once in the source. That single accept, with the sequence branch notifying before
#   it and the others after, gives the target's order of calls, which two accepts do not.
# - notify calls visit whatever mayFree says: the target's `or` of the two tests has no branch between them.
# - PERDecoder::do_revisit (8808) only tests its data: 8808 has no decoder, and reads buf before data. In the other
#   order the rows differ.
# - ValidChecks.cxx: the data classes' isValid and isStrictlyValid are in another TU than the two checkers and
#   AbstractData::isValid. Clang inlines CHOICE::isStrictlyValid into its visitor and AbstractData::isValid into the
#   members when it sees them, and the target calls 1067 from 8970 and 221 and 231 from the members. Moved, 8968, 8969,
#   8970, 8977 and 8978 match, with 1067 and 1068.
# - Inliners, by the object and the link: wasm-opt, each a call in the object and gone from the link, took
#   decodeChoicePreamle into 8812 and 8836, decodeTime into 8828 and 8829, SEQUENCE::BitMap::resize into 8802,
#   SEQUENCE_OF_Base::resize into 8811, and the checks of BMPString, AbstractString, SEQUENCE_OF_Base and OpenData into
#   their visitors. The names below keep the roots from taking their addresses, which would stop it.
#
# Chosen, with the forms measured to give the same bytes (one function's rows, object-local numbers masked):
# - asn1.o's place ahead of PERDecoder.o: right before PERDecoder.o (a scratch link of the plain link.cmd, the object
#   moved) gives 8811 the head's body but for two call operands, the callees' indices, and the same 6 over 364; the
#   places between were not linked. The head is the count's choice, above. The other runtime objects keep the name
#   order, which leaves some of them out of the data's order against each other: no row measured needs another.
# - src/asn1/ValidChecks.cxx: no evidence names it. The band puts 1068 and 1067 before asn1.o's first function, and the
#   target's checker vtables lie among asn1.o's, so asn1.cxx may hold the checkers. Which of the two TUs is which is not
#   decided. The members moved as one block, though only those above are measured to need it. Members in
#   ValidChecker.cxx with the checkers in asn1.cxx, and members in asn1.cxx with the checkers kept, each lost no match in a
#   private scan, so no byte needs this file, and the visitors 8968 to 8987 lie inside the target's run of asn1.o.
# - visitExtensionRoot: `sequence` is a chosen local, so the tag tested once is a choice: the test written twice gives the
#   same bytes. Its branch order is not free: the pop_back in the else gives other rows.
# - preVisitExtensionRoots' typeName: `string typeName(...)` and `const string& typeName = ...` give the same bytes.
# - decodeTime's bool: it holds the compare by choice, and an early `return false` gives the same bytes.
# - notify's `consumed`: an int result compared in the test gives the same bytes.
# - PERDecoder::do_revisit: `if (!has_buf() || !has_data()) return false; return true;` gives the same bytes.
# - DataFree: `delete value.release_data()` in place of the second asn_ptr gives the same bytes.
# - AbstractString::isValid's `invalid`: a bool of the compare gives the same bytes.
#
# splat/symbol_addrs.txt holds hand edits for this unit, by the method of docs/reference/facts/asn1.md A5: pair the
# calls of every named function whose rows equal ours up to callees. 2182, 3464, 3469, 2650, 5054, 376, 220 and
# 2706 each pair with one symbol, and that symbol with them alone. A name frees callers, not bodies: 2650 stayed
# unmatched until unit 229's root (its hand edit went then: a generated line names it), 376 matches from unit 109
# (its hand edit went when unit 179's 11172, a caller, matched: removed alone it moved no row of a scan run twice
# and the build verified, as the generated `call` line names it), 2182, 5034, 8976 and 8987 with unit 115's edits, 2247 from
# src/app/roots_vector.cpp's minsize instance, whose census pair names it now, so its hand edit went, and 220 and 2706
# from unit 229's root, whose generated lines name them now, so their hand edits went too.
# _ZN4ASN1L14badEndOfStreamE is .bss, so no content places it: 14478, the static
# constructors, builds a string at 1914448 from the literal " bad end of stream", and five visitors read it there.
ASN1_ROOTS_EXCLUDE += _ZN4ASN17UTCTimeC1EPKc _ZN4ASN17UTCTimeC2EPKc _ZN4ASN115GeneralizedTimeC1EPKc _ZN4ASN115GeneralizedTimeC2EPKc \
                      _ZNK4ASN17INTEGER15isStrictlyValidEv _ZNK4ASN18OpenData7isValidEv _ZNK4ASN18OpenData15isStrictlyValidEv
