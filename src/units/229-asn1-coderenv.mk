# ASN.1 runtime: the executable TU's copies of ASN1::CoderEnv::encode over a
# std::back_insert_iterator<std::vector<char>> and of what it instantiates, from the tree root
# src/app/roots_coderenv.cpp, with the fork's encode in src/asn1/asn1.h. The fragment holds no source: the root is in
# APP_OBJS (its rule is in src/Makefile, beside the executable TU's, at that TU's VOTA_WEB_CXXFLAGS), and this file
# holds the evidence. Matches, 13 target functions from the encode side (and 11 from CFileASN's writer, at the end):
#   Since unit 206 those copies come from mock/app/comum/cappinfobuilder.cpp's object (unit 253, at the same rule and
#   ahead of this root on the link line), which instantiates encode and CodeObjectFunction through IServicoEstado's
#   save; the root's instances of the two and its stand-in for CodeObjectFunction's slots went, and steps 7 to 9 on the
#   link without them moved no row. The evidence below is the same code's; the root keeps the encodeBER call below and
#   std::vector<std::string>'s instance (5585). What is said below of "the root's copies" was measured while it held
#   them.
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
#   The root's copies also give matches the link had from elsewhere, the same code: 3666 (~basic_stringbuf), 3694
#   (basic_ios::init) and 10983 (string::resize), libc++.a's before; and, first in APP_OBJS (below), 674
#   (basic_stringbuf<char>::__init_buf_ptrs), which differed from roots_iconversorasn.o, and 520 and 4967 (~vector and
#   __destroy_vector::operator()), roots_vector.o's vector<unsigned char> bodies, whose match lines carried
#   vector<char>'s names until mock/app/comum/cappinfobuilder.cpp's object, linked ahead of this root at the same rule
#   (unit 253), gave the link its vector<unsigned char> copies of the two, the same code, and step 9 renamed the lines
#   back. 3656's and 2769's (__vallocate) bodies are the executable TU's object's, of
#   vector<unsigned char>, the same code: step 9 renamed those two lines to that type's names when the root moved.
#
# Evidence, from the target's bodies (pnpm wasm fn and lift of each):
# - 9770 tests the rule at +0 of its first argument with a br_table, [2 1 1 0] and 3: rule 3 builds a PEREncoder (vptr
#   1151424) over a vector reserved to 256, rules 1 and 2 call 1532, rule 0 builds an ostringstream and an AVNEncoder
#   (vptr 1149612) and copies the stream's string through slot 486, and any other rule returns false. That is
#   CoderEnv::encode with encodePER and encodeAVN inlined. Its only reference is table slot 482, which 2927 (the merge
#   body of CFileASN's CodeObjectFunction instances, at the end) passes to invoke_iiii. 1532 builds a BEREncoder (vptr
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
#   same flags; that file is unit 253's, at this rule, and its written members do not reach CoderEnv). The root's place
#   in APP_OBJS is the target's, by 674: first, right after the executable TU's object, its copy of
#   basic_stringbuf<char>::__init_buf_ptrs wins over roots_iconversorasn.o's, at uenux2's flags, and 674 matches; after
#   the other tree roots it differed. No row leaves match in either place (whole link, steps 7 to 9).
# - asn1.h's encode sends ber_partial to encodeBER as it does ber. Upstream's test, `== ber` alone, gives the br_table
#   [2 1 3 0] (measured on a probe link, every other row of 9770 operand-only).
#
# Measured on the whole link (pnpm wasm score), stand-ins and what each holds:
# - urna_roots_coderenv calls 1532 once more (it took 9770's address until 2927 was in the link), for its direct target
#   caller 11488, not in our link (11582 is, unit 122's, 6006, unit 293's merge of the two writers, 11587, unit 305's,
#   11616 and 5366, unit 122's, and 11629, unit 200's): without that call, before 11582 and 6006 were in the link, no
#   function of
#   build/out/wasm-map/vota_web/names.tsv was encodeBER (inlined into 9770).
# - It called 3656 too, for its target callers 1681 and 5496, while 1681 was not in our link and 5496 was inlined into
#   10949, its one caller there: without that call binaryen inlined 3656 into 5290, which scored 47 over 158 rows (27
#   inserted). Both are out of line now and call 3656: 5496 with its other caller, 5702 (fragment 335), in the link,
#   and 1681 from src/app/roots_vector.cpp (unit 11). The call went; the merge that took it out moved no row besides
#   unit 11's own (steps 7 to 9).
# - While that call stood, an explicit instantiation of __recommend beside its label gave a byte-identical link.
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
# - 2704, __split_buffer<char>'s destructor, is a 9-B thunk into 2896 in the target, binaryen's merge of four such
#   destructors (its thunks pass 1, 12, 8 and 16, the step of its loop). Both match since unit 269's root brings 5523,
#   the step 16: our link merges the two into 2896's body (2545 and 4675 are not in our link) and names 2704 by its
#   census pair.
#
# Chosen: the root's file name, its stand-in's name and labels, their argument offsets, and the `||` in encode, which a
# switch over the four rules gives as well (encode's rows in the root's object, relocated constants masked, the same).
#
# CFileASN's writer for the four ESTADO GERAL entities, and ~CoderEnv, from the same root: 11 target functions, none
# lost (steps 7 to 9 against the commit before):
# - 2927, binaryen's merge of api::CFileASN::CodeObjectFunction<T> (src/uenux2/src/api/io/asn/cfileasn.h) for
#   EstadoGeralUrna, -Gap, -SA and -Vota, and its thunks 9801, 9702, 9695 and 9673, which pass each instance's two
#   records (cfileasn.h 171 and 161, which print T). The root instantiates the four and our link merges them the same
#   way: 2927's match line names that merge body, byn$mgfn-shared$ and the Urna instance, a name our link derives
#   (how-to step 9, "Hand edits"); the thunks' lines name the instances.
# - 9790, std::__format_arg_store's constructor for the format's two std::string arguments, which 2927 calls out of
#   line, and 518, ~CoderEnv, which 2927 calls on both of its paths: the -Oz copy docs/reference/facts/asn1.md A10 read
#   as the executable TU's, which no object emitted before.
# - Rows they release: 3552, vector<Visitante>::__destroy_vector, which ~CoderEnv calls, from this root, ahead of
#   BERDecoderPartial.o's -Os copy; 1928's line, which named roots_texttospeech.o's pair<string,
#   shared_ptr<api::CWavFile>> destructor, renamed by step 9 to this root's pair<string, shared_ptr<IAbstractVisitor>>
#   one, the same body, which links first (3552 calls it); 2650, BERDecoderPartial.o's allocator<Visitante>::destroy,
#   whose call of ~shared_ptr<IAbstractVisitor> now reaches 388's body (this root's -Oz copy keeps its result and
#   links ahead of the runtime's); and 210, CBaseError<api::EUeIoError>'s constructor, which 2927 invokes and which
#   differed against roots_uenux2.o's copy (`i32.const 483` against `call 710`): it matches from this root's.
# - Evidence, from 2927 (pnpm wasm fn and lift): it calls isValid (221) on the entity, and when that fails builds an
#   ostringstream, passes it to ASN1::trace_invalid (208, slot 443) with the empty string at 450187, takes its str()
#   (11016, slot 98) and throws code 5955 (CBaseError<api::EUeIoError>, typeinfo 1528172, constructor 210 through slot
#   481) with std::format over "Objeto com conteúdo inválido para {}: {}" (3405, 40 B), the name and that string, at
#   the thunk's fifth argument, record 161. Else it clears 36 bytes of a CoderEnv on its stack and sets its rule to 1
#   (ber), then clears a vector<char>, calls encode (9770, slot 482) over a back_insert_iterator into it, throws 5956
#   with "Arquivo não foi codificado para " + the name (345, slot 62) at the fourth argument, record 171, when that
#   fails, and swaps the vector's three words with the first argument's before destroying it (520) and the CoderEnv
#   (518). Its calls that can throw while a local lives go through invoke_* with landing pads (trace_invalid, str(), the
#   format, the constructor, the throw, encode): an -fexceptions object's code, so this rule's
#   (mock/app/comum/cappinfobuilder.cpp, whose saves reach this writer through 2892 and 2891 in the target, compiles
#   at this rule too, unit 253; that the copies are that TU's or the executable TU's is a reading).
# - Measured forms (CodeObjectFunction<EstadoGeralUrna>'s rows in a probe object at this rule, object-local numbers
#   masked): the encode call in the if, set_encodingRule(ber) for set_ber() and std::swap for the member swap give the
#   same function; move-assigning the vector, or declaring it before the CoderEnv (its clearing then comes first,
#   where 2927 clears the CoderEnv first), give other rows. The four instances' ld_index runs Urna, Gap, SA, Vota
#   (652, 663, 664, 665), as the thunks' target indices run downwards.
# - Stand-ins: urna_roots_cfileasn took the four instances' addresses, for 2891's thunks (9820, 9703, 9701, 9684),
#   which pass their table slots (478, 488, 489, 490); it went with unit 206, which writes those thunks. Two stand-ins went, whose callers are in the link
#   now: urna_roots_coderenv's address of 9770 (for 2927's slot) and unit 237's w237_par (for 3552, the reader of
#   1928's result); a link without both moves no row (steps 7 to 9).
# - The hand lines of 2650 and 3552 (unit 115's, callers+content) went: both have generated lines now, and with the
#   two out two scans give 11479 match rows beside the control and splat-build verifies 11479.
# - 5366, another entity's CodeObjectFunction held by uenux2's code (no landing pad), which lost its stub to cfileasn.h's
#   lines 161 and 171 (docs/reference/facts/placing.md P1), is unit 122's (gravadores/asn/cconversorresultadournacadastro.cpp),
#   and matches. The root also stands for 5585's target users, 11332 and 9586 (its comment). 5367 and 2724, the hashes' and the
#   envelope's writers, are written (units 293 and 160) and match with their merge, 6006. ReadFromFile and
#   DecodeObjectFunction are unit 206's (3791 holds them).
# - Chosen: the codes' enumerator names (api/io/eueioerror.h), that CFileASN is a class, the lines of every statement
#   in cfileasn.h but the two throws, and the locals' names.
