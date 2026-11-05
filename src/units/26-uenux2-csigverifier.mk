# uenux2 comum::CSigVerifier constructor (target fn 1540) in src/uenux2/src/app/comum/relatorios/csigverifier.cpp, the
# file the record of its Verify names (line 32 col 19); the constructor has no record of its own, its class is the
# vptr it stores (_ZTVN5comum12CSigVerifierE). With it: the class header (csigverifier.h), the api::ISigVerifier
# interface it implements (api/gui/isigverifier.h; RTTI names the base, no record names its file: it goes with the
# paper reports that take it) and the ESavdAplic type of its +4 member (app/comum/iinterfacesavd.h, beside the file
# whose records spell it). That +4 member is a constructor parameter that wasm-opt's dead-argument elimination folded
# (every caller passes 1), so the target's signature has no trace of it: its position in the parameter list (first,
# before the directory and the two strings) is a choice no evidence fixes, and only our symbol's mangling depends on
# it, not the bytes. The directory is a std::filesystem::path, parameter and member (csigverifier.h says what shows
# it): the match line of 1540 follows the symbol, whose body is the same. The destructor is implicit (the target's callers inline it): its bodies (fns 11178, 11176, vtable slots 0
# and 1) are the compiler's, emitted with the vtable in the TU of the key function Verify, csigverifier.cpp's. They
# store no vptr, so the class is final (csigverifier.h says why). Paths relative to src/uenux2; the generic uenux2
# rule depends on the source and every uenux2 header.
#
# Verify (target fn 11179, vtable slot 2): it takes IInterfaceSavd's singleton (the record at line 32 col 19 is
# CPolySingleton<IInterfaceSavd>::instance()'s default argument, fn 1822) and calls comum::ValidarUE over a file
# (iinterfacesavd.cpp, record 898:15) with m_aplic, (m_diretorio / m_pacote).string() and m_arquivo. 11179 loads +4
# before it builds the path, the order those arguments are written in, and holds libc++'s operator/ inlined around
# path::operator/= (fn 183). binaryen inlined that ValidarUE into 11179, its one caller, behind a frame of its own (544
# bytes), and 11179 calls the request ValidarUE makes, IInterfaceSavd::VerificarArquivo (fn 5892, unit 95's). Chosen:
# the local's name and `auto&`.
#
# The source is compiled from unit 95's list (src/units/95-uenux2-app-comum.mk), after iinterfacesavd.cpp and
# cassinador.cpp: the target's data has iinterfacesavd.cpp's records (1552548) ahead of this file's (1576892), and
# 11179 holds iinterfacesavd.cpp's ValidarUE. With csigverifier.cpp.o in this fragment's place, ahead of
# iinterfacesavd.cpp.o (the first link of these sources), 11179 scores 55 over 436 rows (2 inserted, 2 deleted: local
# numbers at the call of 5892), and after it 26 over 434, all operand-only, and it matches (pnpm wasm score; unit 95's
# fragment has the links). This fragment holds no rule.
# the constructor's seven target callers are all in the link (2890, 11852, 11855, 11991, 12068, 12071 and 12074:
# units 156, 104 and 315), each passing the same ESavdAplic, so it needs no roots: the stand-ins that gave it two
# direct callers went
