# uenux2 api::CFileSeeder, all of its vtable @1564400 (an si_class of ASN1::ISeeder), in the header the records name,
# api/io/asn/cpartialfileasn.h: eof (target fn 11434), decodeByte (11433), decodeBlock (11432), seek (11431), skip
# (11430), size (2587, a body binaryen shares with three other slots, whose match line takes unit 50's
# GetEstadoBiometria, that object coming first in link order), remaining (11429), tell (11428) and resize (3037, the
# body of IFormFieldBase's SetForm, kept under that name). Slots 0 and 1 are the shared empty destructors (174, 144).
# With it the 5957 to 5961 enumerators of EUeIoError, the __get_deleter of the __shared_ptr_pointer the target builds
# around the object (11427), and the ISeeder and ASN1::BufferSeeder changes below.
#
# The unit has no source of its own, and this fragment is its header comment only: the class has no key function, and
# the TU that builds it emits the vtable, its members, the typeinfos and the control block. That TU is
# app/comum/dados/carregaarquivo.cpp's (unit 280's file), whose LeEleitores instantiates api::CPartialFileASN::
# ReadFromFile for ModuloEleitores::EntidadeEleitores (fn 11523 holds it; src/units/310-uenux2-cconversorentidadeeleitores.mk),
# where the target's data put this class's vtable and records too (after that instance's record of line 182). The
# other builder, fn 7787, is not written. A roots file emitted them until then (an unrooted optnone builder and a sink
# of the two vtables); it went when that builder was in the link. carregaarquivo.cpp.o compiles at uenux2's flags with
# -fno-strict-aliasing; the members' rows are the same with strict aliasing or without it (below).
#
# ISeeder's names. The records of slots 3 to 6 read decodeByte(), decodeBlock(char *, size_t), seek(size_t) and
# skip(size_t). asn1.h had read(), read(char*, unsigned), seek(unsigned) and skip(unsigned), so its declarations,
# BufferSeeder's overriders and the seventeen calls in BERDecoderPartial.cxx took the records' spelling, and the match
# lines of 8897, 8898 and 8900 follow the new symbols (their compiled rows are what they were, and those of every other
# function of the object but 8899). No record names ISeeder's other slots: eof, size, remaining, tell and resize keep
# their chosen names and unsigned types.
#
# ASN1::BufferSeeder::decodeBlock (8899, differs until this unit): the last store reads the cursor again after the copy,
# and `m_current += size;` gives that where `m_current = current + size;` adds the value read before it. Reading the
# size first, `const size_t count = (m_current + size > m_end) ? m_end - m_current : size;` above the memcpy, gives the
# same object (cmp).
#
# Evidence: each throw's line and column, its function text (the records, so the header puts them on lines 52, 75, 88,
# 94 and 106 with the `throw` at 12 spaces), its code, its format string and its argument types (one string in
# decodeByte; an unsigned and a string in the others); the offsets; which calls are virtual (eof in decodeByte, seek in
# skip: `final`, or a call of CFile::Eof or of CFileSeeder::seek by name, gives other bytes). decodeBlock formats the
# clamped count and passes it to RawRead; seek and skip format their argument.
#
# Chosen, no evidence names them: the enumerators (from their messages), m_arquivo, m_tamanho, the names of slots 2 and 7
# to 10, the constructor's explicit and that it takes a reference (the records of ReadFromFile, which call it, spell
# const CFile &). The file as a reference and not a pointer is a choice too. Every line of the header but the five with
# a record is a choice, the members being in the class among them: the same seek after the class, `inline`, gives the
# same rows, and a nested block there would give the column.
#
# Forms measured against this one, per function, comparing the rows of the object with uenux2's flags and the record's
# data offset masked:
# - the same bytes: the file as a pointer; with -fstrict-aliasing or without it; `byte` above the `if`; the position as
#   long or unsigned; an if that assigns the count or the parameter for the ?:, and the ?: inverted with <=;
#   size + posicao for posicao + size; the target of skip as size + Position(); seek's second test as == false; an else
#   around decodeByte's read; RawRead's result kept in an unused local; the -1 as a default member initializer; a throw
#   broken over two lines; seek after the class; for the implicit destructor, one in the class, `~CFileSeeder()
#   override = default;`, `override {}` or `inline` with `= default` (the roots object cmp-identical).
# - other bytes: `byte` initialized; std::min for the ?: (decodeBlock); m_tamanho < position for position > m_tamanho, a
#   copy of the name for GetNome() (seek); tell() in skip; size() - tell(), or the position read first into a local, in
#   remaining (the target loads the size before the call).
#
# 5483, api::CIniKey::operator= (unit 01), turns match with this unit and none of its code changed: its call of
# CBaseError<EUeIoError>'s constructor was the only vote for that name (210), `unresolved (self-voted)` in the scan
# (docs/glossary.md), and the five throws here are other callers.
