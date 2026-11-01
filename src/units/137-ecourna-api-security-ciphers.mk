# ecourna api/security: CPrng, CTrng, CSymmetricCipherFactory with the CBlockCipher<CAesCipher, CTrng> it builds,
# and cepesc::CCepescCipher, in api/security/{cprng,ctrng,csymmetriccipherfactory}.cpp and
# api/security/cepesc/ccepesccipher.cpp.
# Matched: CPrng's constructor (target fn 9503), GetByte (9502), Generate(dados) (9499), Generate(dados, tamanho) (5178)
# and Boost's mt19937::twist (5179); CTrng's GetByte (9477), GetInt (9476), Generate (9475, 5173) and the exit
# destructor of its device name (9478), with libc++'s std::random_device constructor (2544) and operator() (3331), which
# libc++.a brings once these call them; CSymmetricCipherFactory::Create(const CAesKey&) (9489), and from its object
# CBlockCipher's D0 (9488) and CAesCipher's implicit destructor (9486, the unwind path of the cipher's Encrypt);
# CCepescCipher::Encrypt (2681) and Decrypt (5171), whose call of the executable TU's vector<uebyte> exception-guard
# destructor (306) src/app/roots_vector.cpp gives the link; CBlockCipher's Encrypt and Decrypt (9487, 9485), thunks
# into a merged body (6154) our link forms too (byn$mgfn-shared$ of Encrypt, called by both), which pass CAesCipher's
# Encrypt and Decrypt (9493, 9491) by table slot: those two names come from hand lines in splat/symbol_addrs.txt
# (fragment 11 says what the lines rest on and what 9493 and 9491 wait for), and without them both thunks are
# `unresolved self-voted`.
# No record names any of these files. What the target shows:
# - The classes, their bases and their slots are RTTI's and the vtables' (1113168 CPrng, 1114660 CTrng, 1113832 the
#   factory, 1114996 CCepescCipher). The data place the first three in api/security/: CPrng's vtable lies between
#   ckey.cpp's records and csha.cpp's, the factory's and CTrng's between caescipher.cpp's records and imacalgorithm.cpp's.
#   CCepescCipher's lies between asn1/ckeyloader.cpp's record (1114980) and cepesc/ccipheredin.cpp's (1115240), so its
#   directory is chosen: cepesc/, where its namespace's other classes are. The file names are the class names (how-to
#   step 3, rule 4): chosen. A CTrng without a key function, its members inline and its vtable copied into the
#   factory's object, also fits the data; out of line in ctrng.cpp is chosen.
# - CPrng runs Boost's mt19937 (Boost.Random): a 2500-byte engine on the stack seeded by the 1812433253 recurrence
#   with the index stored at each step, then Boost's normalize_state (x[396] ^ x[623] folded into x[0], the all-zero
#   fix), and 5179, its twist() with the split loops (to 222, 227, 623), matches as Boost's. GetByte and Generate seed
#   it with the member's low byte (i32.load8_u in 9502 and 5178, i32.load in 9500): `static_cast<uebyte>` is chosen,
#   `& 0xFF` gives the same object function. GetByte's value is the tempered word shifted right by 24: Boost's
#   uniform_int_distribution<uebyte>, Boost's <int>(0, 255) and `gerador() >> 24` give the same object function,
#   libc++'s std::uniform_int_distribution another. Boost's <uebyte> is written.
# - CTrng builds a libc++ std::random_device from a namespace-scope std::string, "/dev/urandom" (1911784, built in the
#   static initializer, destroyed by 9478): the string's name and its anonymous namespace are chosen. Its GetByte keeps
#   the low byte: libc++'s distribution over (0, 255) and a plain cast give the same object function, and Boost's
#   distribution shifts by 24 instead. Its GetInt: libc++'s and Boost's distributions give the same object function.
#   In Generate, libc++'s distribution and a plain cast give the same object function. libc++'s is written in all three.
#   Generate's try catches std::exception (typeinfo 1525848) and returns -1; the device is built inside it (an invoke).
# - GetInt's bounds, -2147483647 and 2147483646 (a rejection of words above 0xFFFFFFFD, then 0x7FFFFFFF subtracted),
#   are the target's; their spelling through numeric_limits is chosen.
# - Both Generate(dados, tamanho) return 1 for tamanho 0, 2 for a shorter vector, 0 otherwise, and build the generator
#   before the tests. `tamanho > dados.size()`: `dados.size() < tamanho` puts the size after tamanho in both objects,
#   and in the lone link (try-tu --single) of 5178 scores 7 over 486 with a row inserted and one deleted, where the form
#   written is BYTE-EXACT alone and matches in the link.
# - CPrng and CTrng are final: 9499 and 9475 call slot 5 directly; without final, 9499 calls through the vtable (lone, 3
#   rows inserted: the load of slot 5 and call_indirect in the object). A qualified call would be direct as well (a
#   reading, not measured), so CPrng's final is a choice; CTrng's is its control block's (ctrng.hpp). CPrng's
#   constructor is out of line: it is table slot 114, which the executable TU's main (10307) passes to invoke_iii with a
#   seed of 0. The member's name and its int type are chosen (the constructor stores its 32-bit argument at +4).
# - The factory is not final: 1884 calls slot 3 through the vtable. 9489 allocates a 36-byte CBlockCipher and wraps it
#   in a shared_ptr<ISymmetricCipher>, whose __shared_ptr_pointer vptr it stores. Both slots' names, and that slot 2
#   takes a password, are chosen; 1884 hashes it with CSha512 and takes the digest's bytes 16 to 48 as an AES-256 key.
# - CCepescCipher::Encrypt (2681) returns a CCipheredOut over a zeroed 32-byte key and the plaintext's content, with
#   its salt when it has one; Decrypt (5171) returns the ciphered content. The member names and their const are chosen.
# Written and not matched yet, each with what it waits for:
# - CPrng::GetInt (9500), `differs` in its locals: clang leaves Boost's generate_uniform_int<mt19937, int> out of line
#   (-Rpass-missed=inline: cost 285, threshold 250) and binaryen inlines it into its one caller, so ours reloads the
#   engine's index where the target keeps the seeding loop's in a local (a reading: binaryen does not forward a store
#   to a load, so the target's copy is clang's inlining). Out of line in every form tried: the distribution named or
#   temporary, through variate_generator, over long, and libc++'s (cost 325). No form that clang inlines is found.
# - Create(const std::string&) (1884) calls the executable TU's vector<uebyte> exception-guard destructor (306), which
#   src/app/roots_vector.cpp holds, as 2681 and 5171 do, which match with it in the link. 1884 keeps 3 rows (53 over 515
#   at the tree's flags, the rest operand-only): the target loads the digest's address before the key vector's zero
#   stores, ours after them (the object has the same order). A data() + 16 range gives the same object function; the key
#   built in the return, or over a temporary vector, scores worse alone (155 over 582 and 213 over 603, against 125 over
#   582 as written).
# - The merged body of CBlockCipher's Encrypt and Decrypt (6154) waits for CAesCipher's constructor's name (9495).
# Roots: 137-ecourna-api-security-ciphers-roots.cpp (its header says how). Unit 100's roots include
# isymmetriccipherfactory.hpp, which gains the two pure slots and its private NonCopyable base: unit 100's and unit
# 102's objects are byte-identical before and after (cmp).
CIPHERS_SRCS := api/security/cprng.cpp api/security/ctrng.cpp api/security/csymmetriccipherfactory.cpp \
    api/security/cepesc/ccepesccipher.cpp
ECOURNA_SRCS += $(CIPHERS_SRCS)
$(ROOT)/$(APP)/137-ecourna-api-security-ciphers-roots.o: $(ROOT)/src/units/137-ecourna-api-security-ciphers-roots.cpp \
    $(ROOT)/src/Makefile $(ROOT)/src/units/137-ecourna-api-security-ciphers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/137-ecourna-api-security-ciphers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/137-ecourna-api-security-ciphers-roots.o
