# ASN.1 runtime: the executable TU's copies of ASN1::CoderEnv::encode over a
# std::back_insert_iterator<std::vector<char>> and of what it instantiates, from the tree root
# src/app/roots_coderenv.cpp, with the fork's encode in src/asn1/asn1.h. The fragment holds no source: the root is in
# APP_OBJS (its rule is in src/Makefile, beside the executable TU's, at that TU's VOTA_WEB_CXXFLAGS), and this file
# holds the evidence. Matches, 13 target functions:
#   - 9770, CoderEnv::encode<back_insert_iterator<vector<char>>>, with encodePER and encodeAVN inlined, and 1532, its
#     encodeBER.
#   - 3559, ~AVNEncoder (the D2), which encodeAVN calls on both of its paths.
#   - 5290, std::copy from vector<char>'s iterators and from string's into the back_insert_iterator: two instances, one
#     body, table slots 485 and 486. 2706, vector<char>::reserve, which BEREncoder's and PEREncoder's constructors call
#     through slot 484. 5282 (__split_buffer<char>'s constructor), 9722 (vector<char>::__swap_out_circular_buffer) and
#     3656 (vector<char>::__recommend): the growth 2706 and 5290 share.
#   - 220, 1001, 10998, 11016, 11235: basic_ostringstream's constructor and D1, basic_stringbuf's constructor and str(),
#     basic_ostream's constructor, from encodeAVN's ostringstream (DECLARE_STRSTREAM).
#   9770 has no line in splat/symbol_addrs.txt: the census pairs it with the instance (tier `shape`), and its match
#   line names it. The other twelve have generated lines.
#
# Evidence, from the target's bodies (pnpm wasm fn and lift of each):
# - 9770 tests the rule at +0 of its first argument with a br_table, [2 1 1 0] and 3: rule 3 builds a PEREncoder (vptr
#   1151424) over a vector reserved to 256, rules 1 and 2 call 1532, rule 0 builds an ostringstream and an AVNEncoder
#   (vptr 1149612) and copies the stream's string through slot 486, and any other rule returns false. That is
#   CoderEnv::encode with encodePER and encodeAVN inlined. Its only reference is table slot 482, which 2927 (the merge
#   body of CFileASN's CodeObjectFunction instances, not written) passes to invoke_iiii. 1532 builds a BEREncoder (vptr
#   1151152) over a vector reserved to 256, calls the value's virtual slot 5 with it (accept) and copies the buffer
#   through slot 485 when that returns true: encodeBER. Its other callers' records name
#   CFileASN::CodeObjectFunction(std::vector<char> &, ...) (cfileasn.h 161 and 171, fns 11488 and 11587), and 5290
#   appends each byte to the vector its third argument points at, growing it as push_back does: so the iterator is a
#   back_insert_iterator over a vector<char> (read from those two).
# - Whose copy: 9770, 1532, 2706 and 5290 have landing pads, so they are an -fexceptions object's, where the ASN.1
#   runtime compiles at -Os without them (docs/reference/facts/asn1.md A1, A2) and uenux2 without -fexceptions; and 3559
#   matched a probe at -Oz -fexceptions and not at uenux2's flags (docs/reference/facts/levels.md V4). The executable TU
#   compiles at those flags and is first on the link line, so the root takes its rule; that the copies are that TU's is
#   a reading (unit 206's fragment has a lead, from IServicoEstado's saves, to mock/app/comum/cappinfobuilder.cpp at the
#   same flags). The root's place in APP_OBJS, after the other tree roots, is a choice: there it takes no copy they
#   give, since the first object's copy wins.
# - asn1.h's encode sends ber_partial to encodeBER as it does ber. Upstream's test, `== ber` alone, gives the br_table
#   [2 1 3 0] (measured on a probe link, every other row of 9770 operand-only).
#
# Measured on the whole link (pnpm wasm score), stand-ins and what each holds:
# - urna_roots_coderenv takes 9770's address, for 2927's slot, and calls 1532 once more, for its seven direct target
#   callers (11488 11582 11587 11616 11629 5366 6006), none in our link: without that call no function of
#   build/out/wasm-map/vota_web/names.tsv is encodeBER (binaryen inlined it into 9770).
# - It calls 3656 too, for its target callers 1681 and 5496: 1681 is not in our link and 5496 is inlined into 10949, its
#   one caller there. Without that call binaryen inlined 3656 into 5290, which scored 47 over 158 rows (27 inserted).
# - An explicit instantiation of __recommend beside the label gave a byte-identical link, so the file has none.
#
# What the root changes elsewhere:
# - Unit 87's sink of AVNEncoder's vtable went: it stood for 9770's vptr store, which is in the link now. Steps 7 to 9
#   on the link without it move no row.
# - Two hand lines of unit 86 went from splat/symbol_addrs.txt, 220's and 2706's (callers+content, written while our
#   bodies differed): with each out, and with both, a scan run twice beside a control moves no row, and splat-build on
#   the copies verifies 11139 matches. Step 8 names both by generated lines now (220 `call`, 2706 `table` by 1532).
# - Step 8 drops the vptr-anchor lines of 3464 (PEREncoder::encodeAnyType) and 5152 (CWasmCanaisLog::Escreve), since
#   9770 also stores PEREncoder's vptr and 220 the ostringstream's (a reading of which store each anchor read); both
#   stay matched by their match lines, and 3464 keeps unit 86's hand line. 5152's callees 3501 and 5150 lose their
#   `call by:5152` names, their rows unchanged.
# - 2704, __split_buffer<char>'s destructor, gets a `call` name from 2706 and 5290 and stays `differs`: our body is the
#   whole destructor, and the target's 2704 is a 9-B thunk into 2896, binaryen's merge of four such destructors (its
#   thunks pass 1, 12, 8 and 16, the step of its loop; the other three, 2545, 4675 and 5523, are not in our link).
#
# Chosen: the root's file name, its stand-in's name and labels, their argument offsets, and the `||` in encode, which a
# switch over the four rules gives as well (encode's rows in the root's object, relocated constants masked, the same).
