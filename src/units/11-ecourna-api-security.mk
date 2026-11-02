# ecourna api/security OpenSSL wrappers. The ecourna compile rule has only -Isrc; these TUs include <openssl/*.h>.
ECOURNA_CXXFLAGS += $(OPENSSL_INCLUDES)
ECOURNA_SRCS += api/security/csha.cpp api/security/csiphashmac.cpp api/security/chkdfseed.cpp api/security/ckey.cpp \
    api/security/imacalgorithm.cpp api/security/isymmetriccipher.cpp api/security/caescipher.cpp
# IMacAlgorithm's default constructor is declared in the class and defined in imacalgorithm.cpp: fn 3700
# (comum::CCalculaCV::CalculaCodigo, unit 121), the one target function that stores CSiphashMac's vptr, stores
# IMacAlgorithm's (1114744) and then CSiphashMac's (1113604) to the same word, back to back, so the base's constructor
# was a call when clang compiled 3700 (binaryen inlined it). Measured with `pnpm wasm score` in the whole link: with
# both constructors inline in the headers 3700 held one store (21 rows inserted and 23 deleted), with both out of line
# both stores (13 and 13; unit 121's fragment has the rest). CSiphashMac's own constructor is defaulted in its header:
# defined out of line in csiphashmac.cpp it gives the same bytes in the whole link (no scan row moves), so its form is
# a choice. `= default` in imacalgorithm.cpp, the public access of IMacAlgorithm's constructor and its line, before
# Mac, are chosen; `{}` was not linked.
# The roots no longer take IMacAlgorithm::Mac's, DoMac's and DoVerify's addresses: the roots file says why.
# CSha::Reset holds EVP_DigestInit_ex2's result in a named local before testing it: the local's lifetime-end cleanup on the
# throw path gives the landing-pad layout 5177 has, and the call in the condition does not (-Xclang
# -disable-lifetime-markers turns the local form back into the other). The local's name and type are chosen: an int, a
# bool or an if-initializer give the same bytes.
# CSha::Finish (3518) holds EVP_DigestFinal_ex's result in a named local the same way. Measured in the link: with the call
# in the condition it is `differs` (59 over 240 rows, 10 inserted and 9 deleted; first at +0x3d, a `block` of the
# target's where ours has `local.get 2`), with the local 33 over 230, all operand rows, and a match. Its name and type are chosen: `const int`, `int`,
# `const auto`, `const bool` and an if-initializer give the same object code for Finish (compiled at ECOURNA_CXXFLAGS,
# its disassembly compared with call and global indices masked), and the call in the condition does not. Its line, 43,
# is one of the two the base left blank before the test (the record is 45:15): chosen.
# CSha512's constructor (2684) holds CSha's inlined, and its call of Reset is direct (invoke_vi through Reset's slot
# 6236): CSha's constructor calls it qualified, `CSha::Reset()`. The unqualified call loads the slot from the vtable
# (lone, try-tu --single: 19 over 112 rows, 3 inserted and 1 deleted; qualified: 16 over 109, operand rows only, and a
# match in the link); -fstrict-vtable-pointers, a flag this tree does not have, gives the same lone rows as the
# qualified call.
# CAesKey's three-argument constructor is declared `inline`: CSymmetricCipherFactory::Create(const std::string&) (1884)
# holds it inlined (the key's 32 bytes copied straight from the digest), and without the keyword clang keeps it out of
# line there (-Rpass-missed=inline: cost 320, threshold 250; with it, cost 320 and threshold 325). Two constructors
# without the default argument are inlined too (object); not compared further.
# CAesCipher's constructor, SetKey, Encrypt and Decrypt (9495, 9494, 9493, 9491; records caescipher.cpp:54, 70, 79,
# 119) match, with the exit destructor of the file's std::map of modes, (anonymous namespace)::CIFRAS (9496), and that
# map's __tree destroy (2682). Each form below was measured on the whole link (`pnpm wasm score` against the target
# function, ours from names.tsv after `make -C src link-map`), with the two callees below in the link:
# - SetKey reads the key's size into a named local before it calls EVP_CIPHER_get_key_length: the target reloads the
#   key's bounds for the copy, read as the size being read before the call, and the local gives the throw path's blocks.
#   With the size in the condition the target's `unreachable` after __cxa_throw is a block of its own where ours shared
#   the one after __resumeException: 26 over 161 rows (1 inserted, 2 deleted); with the local, 19 over 160, operand rows
#   only. The local's name and type are chosen: `const int` with the cast and `const auto` (size_t) give the same wasm.
# - Encrypt and Decrypt declare `erro` among their locals and assign ERR_get_error's result in the test. With the
#   if-initializer (`if (const unsigned long erro = ERR_get_error(); erro != 0)`) ERR_get_error's call gets a landing
#   pad of its own, read as the local's lifetime-end cleanup, which clang pushes before the initializer runs
#   (`em++ <ECOURNA_CXXFLAGS> -S -emit-llvm`: `invoke @ERR_get_error ... unwind label %151` where EVP_DecryptUpdate's
#   unwinds to `%87`); the target's call shares the function's catch block. That gave 209 over 852 rows (21 inserted)
#   and 220 over 969 (24 inserted); `erro` declared after the IV's code, before EVP_EncryptInit_ex, 192 over 846 (15).
#   Declared before the IV is filled (after `tamanhoFinal`, before `tamanho`, or between the vectors `iv` and `dados`),
#   with `= 0` or without, the wasm is the same and every row of both is an operand row. The name, the type, the
#   initializer and the place among those are chosen.
# - The output's end is `buffer.get() + tamanhoFinal + tamanho`: the target adds Update's count (frame +56, loaded
#   first) to the buffer plus Final's (+52). `buffer.get() + tamanho + tamanhoFinal` and
#   `buffer.get() + (tamanho + tamanhoFinal)` load the two the other way round; `buffer.get() + (tamanhoFinal +
#   tamanho)` gives the same wasm as the form written; `tamanho += tamanhoFinal` before the call stores the sum back,
#   and a named `const int` total moves the frame offsets and the throw paths' blocks (186 over 952 rows for 9491).
# - Their callees std::vector<uebyte>::__assign_with_size over uebyte* (1681) and over __wrap_iter<const uebyte*> (1158)
#   come from src/app/roots_vector.cpp, whose comment says why, at the levels the target keeps: the link's copies
#   before, ckey.cpp.o's and this object's, scored 68 over 162 and 39 over 175 rows. Which level keeps 1681's three
#   calls: `std::vector<unsigned char>::assign(unsigned char*, unsigned char*)` alone in a TU, compiled at -O3 with
#   uenux2's and with ecourna's other flags, calls operator new and delete in __assign_with_size; at -Oz -fexceptions,
#   with -fPIC and without, it calls __vdeallocate, __recommend and __vallocate, three calls as the target's 1681 makes
#   them (5493, then 2769 over 3656's result). -O2 (with -fexceptions, and with -fPIC without it) calls operator new and
#   delete as -O3 does, and -Os keeps __vdeallocate and __vallocate but not __recommend. -Oz is the executable TU's
#   level (docs/reference/facts/levels.md V1), so the target's 1681 reads as that TU's copy: a reading, from the first
#   object's linkonce copy winning the link.
# - The constructor is 30 over 277 rows, operand rows only, as it was; it read `unresolved self-voted` on 1911776,
#   CIFRAS's root word, whose name only its own vote gives (`evidence:vote:3 by:9495`). It holds through 9496, which
#   reads the same object (docs/reference/splat.md section 3, "No circular evidence", as 5158 holds through 9402).
#   9496's one call is 2682, which no generated name reaches: its callers are 14478, the static constructors, which do
#   not match, and 9496. A hand line below the marker of splat/symbol_addrs.txt names it (callers+content: 14478 builds
#   the map at 1911772 by calling 5174, the same __tree's __find_equal, named by pair-fingerprint, and calls 2682 on
#   that object on its unwind path). Weighed: with the line out and the match lines of 2682, 9496 and 9495 out, a scan
#   run twice beside a control over the same match list has 11472 match rows against 11475, those three fewer, and
#   splat-build on each pair of copies gives the target's sha256 with 11472 and 11475 matches; written `evidence:call
#   by:9496` instead, the line refuses nothing (11475).
# - 9493's and 9491's names are step 8's (srcloc-anchor) now. The two callers+content hand lines that named them for
#   CBlockCipher's thunks (9487, 9485, unit 137) went: the scan and splat-build of the committed files, without them,
#   keep 11475 matches.
# - The roots no longer take the four members' addresses: the target reaches each only through one table slot, which
#   CBlockCipher's Encrypt and Decrypt (9487, 9485) and their merged body (6154) hold, and unit 137's objects give our
#   link those. Steps 7 to 9 on the link without the four move no row (the scan joined with the one before them prints
#   nothing), and the splat build verifies 11475 matches.
# CHKDFSeed's D2 and D0 (11498, 11497) are code chkdfseed.hpp defines, and match from the roots object (its header).
# At ECOURNA_CXXFLAGS both differ (66 and 68 rows against 56 and 58, the address arithmetic): the target's copies are
# crdv.cpp's, a uenux2 object (their vtable lies among that file's records).
# the units' bodies have no caller in the skeleton yet: 11-ecourna-api-security-roots.cpp address-takes them (same mechanism as 05-ecourna-api-security-cepesc-roots.cpp)
$(ROOT)/$(APP)/11-ecourna-api-security-roots.o: $(ROOT)/src/units/11-ecourna-api-security-roots.cpp $(ROOT)/src/Makefile \
    $(ROOT)/src/units/11-ecourna-api-security.mk $(wildcard $(ROOT)/src/ecourna/api/*.hpp $(ROOT)/src/ecourna/api/security/*.hpp)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/11-ecourna-api-security-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/11-ecourna-api-security-roots.o
