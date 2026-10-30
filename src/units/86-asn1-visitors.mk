# ASN.1 runtime: BERDecoderPartial, PERDecoder, PEREncoder, ValidChecker, StrictlyValidChecker and DataFree, with the
# data classes' isValid and isStrictlyValid in the new src/asn1/ValidChecks.cxx. src/mk/asn1.mk builds and keeps these
# objects, so this fragment has no sources and no rules: it names what the generated roots leave out, and holds what
# docs/how-to-decompile.md step 3 asks a fragment to say.
#
# Pending, each written and in its source, none a trap:
# - 2182 notify: differs. The target holds three helpers wasm-opt inlined: a search of m_visitors behind a second
#   prologue, the path's construction, by its result pointer (l8 = l10 + 4) and its second read of size() in erase, and
#   a DataFree on a third prologue. The first two read private members, so they wait for two declarations in asn1.h. A
#   link with all three, before notify called visit unconditionally, gives score 15 over 346 against 172 over 376. Its
#   callers match by its name.
# - 8976, 8987 INTEGER's visitors: unresolved. INTEGER::isValid is defined in its class, so clang inlines it into
#   ValidChecker's visitor and isStrictlyValid keeps two callers, where the target holds the range check in both. Moved
#   out of line, 8976 differs in operands only; 8987 stays at 21 over 52 until isValid's body is one that gives the
#   target's br_table (an or of the two tests, or a switch: both do, in the object).
# - 2183, 3469 BERDecoderPartial's destructor and constructor: one row, a drop. Target 424, shared_ptr<ISeeder>'s
#   destructor among others, has no result; ours is one body with an RHVoice copy, and four of our RHVoice functions
#   (item::append, append_child, prepend, relation::append) read its result. Target 388 is a second copy that reads +4
#   and keeps its result, and 2650 calls it and drops that, so one body of ours cannot serve both. 8831 matches by their
#   names.
# - 8811 PERDecoder::do_visit(SEQUENCE_OF_Base&): differs. It calls 543, which is no body of ours
#   (docs/reference/facts/asn1.md A5), with one block more than the target around the vector growth wasm-opt inlined
#   from SEQUENCE_OF_Base::resize, which asn1.cxx holds.
# - 5034 DataFree's OpenData visitors: unresolved. The target holds default_delete<OpenBuf> inline, and it has three
#   call sites in our link, two of them OpenData's destructors in asn1.cxx.
#
# What the target decided:
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
# calls of every named function whose rows equal ours up to callees. 2182, 3464, 3469, 2247, 2650, 5054, 376, 220 and
# 2706 each pair with one symbol, and that symbol with them alone. A name frees callers, not bodies: 2182, 3469, 2247,
# 2650, 376, 220 and 2706 stay unmatched. _ZN4ASN1L14badEndOfStreamE is .bss, so no content places it: 14478, the static
# constructors, builds a string at 1914448 from the literal " bad end of stream", and five visitors read it there.
ASN1_ROOTS_EXCLUDE += _ZN4ASN17UTCTimeC1EPKc _ZN4ASN17UTCTimeC2EPKc _ZN4ASN115GeneralizedTimeC1EPKc _ZN4ASN115GeneralizedTimeC2EPKc \
                      _ZNK4ASN17INTEGER15isStrictlyValidEv _ZNK4ASN18OpenData7isValidEv _ZNK4ASN18OpenData15isStrictlyValidEv
