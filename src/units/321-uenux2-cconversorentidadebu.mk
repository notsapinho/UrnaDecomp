# uenux2 comum::asn::CConversorEntidadeBU::DoConverte (target fn 10273,
# app/comum/gravadores/asn/cconversorentidadebu.cpp, the file its records name; the paths below are relative to
# src/uenux2/src/app/comum/gravadores, the sources' to src/uenux2), with what is inlined into it:
# - clang inlines the file's anonymous CriaVotosVotavel, CriaVotosCargo, CriaResultadoVotacao,
#   CriaResultadoVotacaoPorEleicao and CriaResultadosVotacoes (records :87, :110, :132, :164 and :175) and the class's
#   ConverteDadosSA (no record);
# - binaryen inlines, each with a frame of its own inside 10273's: the class's static ConverteTipoVoto and
#   ConverteTipoCargo (records :284 and :299) and ConverteDadosVota (no record); md::CEntidadeBU's GetDadosVota,
#   GetDadosSA and GetDetalhamentoComparecimento (md/centidadebu.cpp, records :186, :196 and :206) and
#   md::CDadosBUVota::GetDataHoraDesligamentoVotoImpresso (md/cdadosbuvota.cpp, record :37);
#   comum::asn::CAssinaVotavelBu:: Assinar (record :89) and the class's three hash members, both in
#   asn/cassinavotavelbu.cpp, with the class's other members and the SHA-512 helper the hash members call; and the
#   template copies IConversorASN's Converte (comum's for the post code and the vote history, ecourna's for the
#   attendance detail) and SEQUENCE_OF's operator= for three of the lists.
#
# Matched: 10273 (named by its srcloc-anchor) and the exit destructor of its file's static s_ultimoHash (10274), and
# from asn/cassinavotavelbu.cpp's object CAssinaVotavelBu::GetInst (fn 3603, a thunk of binaryen's shared 2900, named by
# 10273's call) and the exit destructors of the class's statics s_mutex (10280) and s_instancia (10281). The statics'
# names have the votes of 3603 and 10273, which match, and each a reader beside its destructor. The same object gives
# comum::asn::CalculaHashSha512 (fn 3602, no record, declared in unit 122's util.h; its name, its being a free function
# and its parameter's name are chosen), which hashes a string's bytes with a std::shared_ptr<IHash>(new CSha512): Reset,
# then Update of a vector the target frees after Finish (written as a named local), then Finish into the result; and the
# CSha512 control block it builds (10277, 10279; unit 102's fragment). Released: unit 62's
# CWasmLogd::escreve (fn 8327) matches, since its "{}|{}|{}" is the tail of "{}|{}|{}|{}|{}|{}|{}", which this unit's
# CalculaHashVotavel brings (unit 62's fragment). 10272, the inherited DoDesconverte, comes from
# cconversorentidadebu.cpp's object now, which emits the vtable with DoConverte, the key function (unit 159's fragment).
#
# What the bytes decided. Each number is `pnpm wasm score` against the target in the whole link, at this unit's state as
# it lands, with the one form changed, unless it says an earlier state. As it lands 10273 is 425 over 5378 rows, every
# one operand-only (calls, data and table slots), and step 9 matches it.
# - The lists are ASN1::SEQUENCE_OF<T>, built with the template's theInfo, as RTTI names the vtables the target stores
#   (1597676 and the other four: ledger/classes.json), and the parents' fieldInfos point at those templates' theInfo in
#   the converter's own data (1597636 and the others). So the BU module's nested value_type classes of those five lists
#   are typedefs of SEQUENCE_OF<T>, and ModuloRegistroDigitalVoto::HistoricoCodigosCarga (a SYNTHESIZED name) one of
#   SEQUENCE_OF<GeneralString> (vtable 1560540), their infos out of the modules' .cxx (src/asn1/README.md "The generated
#   modules"); the generated classes built each list through SEQUENCE_OF(n, T()), a T temporary and an insert of none.
# - The fields the target sets through a temporary of the field's type take x::const_reference in the module
#   (docs/reference/facts/asn1.md A3): qtdEleitoresCompareceram, quantidadeVotos, ordemGeracaoHash,
#   IdentificacaoVotavel's codigo and partido, numeroInternoUrnaOrigem and ResultadoVotacao's tipoCargo; and the CHOICE
#   dadosSecaoSA gets select_dadosSecao and select_dadosSA that take the value, since the target loads the CHOICE before
#   it builds the DadosSecao or DadosSA and selects after (a call's object is evaluated before its arguments).
# - The hash members are in CalculaHashSha512's TU: with CalculaHashSha512 in asn/util.cpp and the hash members in
#   asn/cassinavotavelbu.cpp, 429 over 5380 (2 inserted, 2 deleted), the initial hash's formatted text's long-string
#   byte read after CalculaHashSha512's call where the target reads it before (a reading: in one TU clang sees that the
#   callee only reads its argument). That TU is read as cassinavotavelbu.cpp's (a reading of the data): the table's
#   slots of the statics' exit destructors (4466, 4467) and of the CSha512 block's members 10279 and 10277 (4469, 4470)
#   lie after util.cpp's object, and the one record between those of the objects around them is cassinavotavelbu.cpp:89
#   (cassinavotavelbu.h has the slots and the records, and why GetInst is with its statics). The last hash
#   (s_ultimoHash, 1910004) is the converter's file static, passed to the hash members and to Assinar: its destructor's
#   slot (4476) heads this object's run, before its vtable's four (4477 to 4480).
# - The votable's hash is one conditional expression: written as an if over two assignments, 632 over 5390 (12 inserted,
#   9 deleted), GetInst called in each arm where the target calls it once before the test.
# - md::CEntidadeBU::GetLocal returns a ueword, the target's i32.load16_u of the 32-bit member at +168 (fn 11629 stores
#   it with i32.store): returning the member's TLocalID, 426 over 5378, an i32.load.
# - comum's IConversorASN<CodigoCargoConsulta, unsigned char>::Converte comes from src/app/roots_iconversorasn.cpp
#   (that root's comment says why): with the copy from this unit's object, 831 over 5399 (21 inserted, 22 deleted).
# - api::pkcs11::SResultadoAssinatura is 8-aligned (ipkcs11.h): with two 32-bit words at its head, Assinar's frame put
#   the result and the source_location 4 bytes higher than the target's (an earlier state of this unit: 431 over 5378,
#   the frame offsets the one difference that was no call, data or slot).
# - Read from the target and written so, not measured apart: the entity's header and urna converted into named locals
#   that live to the end (their destructors are DoConverte's last calls), the post code's converter a named local
#   declared before the votes (its vptr store first; a temporary at an earlier state moved it and the frame; const or
#   not gave the same link there), the history lists'
#   indexed loops (the target reloads the vector's begin), the codes' size() > 0 (the target loads the end first;
#   empty() gave the begin first at an earlier state), the votes' and identification's values read into locals before
#   their setters (the loads before the setters' calls), and the initial hash's text with the carga code (CUrna +52:
#   the correspondence's CCarga::GetCodigoCarga).
#
# Choices (the headers say what each is read from): every name no record gives (the hash members, ConverteDadosVota and
# ConverteDadosSA and their being static members, GetInst's and the statics' names, the last hash a file static and a
# parameter of the hash members, the getters, the members of md::CEntidadeBU, md::CDadosBUVota and md::CDadosBUSA),
# their access, the hash members' parameter types beyond the format's argument types, the place of the functions with
# no record in their files, and the paths of md/cdadosbuvota.h, md/cdadosbusa.h and asn/cassinavotavelbu.h. The records
# of md::CEntidadeBU::ValidaCriacao (centidadebu.cpp:159 to :177), which fn 11629 holds (unit 200's pending member),
# keep their lines blank.
#
# Not written: md::CEntidadeBU's and md::CDadosBUVota's constructors (comum::CGravadorBU::MontaEntidadeBU, record
# cgravadorbu.cpp:636, holds the first inlined into fn 11629, unit 200's pending member), so nothing may construct them.
CCONVERSORENTIDADEBU_SRCS := src/app/comum/gravadores/md/cdadosbuvota.cpp src/app/comum/gravadores/md/centidadebu.cpp \
  src/app/comum/gravadores/asn/cassinavotavelbu.cpp src/app/comum/gravadores/asn/cconversorentidadebu.cpp
UENUX2_SRCS += $(CCONVERSORENTIDADEBU_SRCS)
# the converter includes the ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CCONVERSORENTIDADEBU_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# cconversorentidadebu.cpp includes ecourna's app/dados/asn/cconversordetalhamentocomparecimento.hpp, which includes its
# ASN.1 module by its bare name, as the ecourna objects' include path finds it
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/asn/cconversorentidadebu.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
# cassinavotavelbu.cpp's CalculaHashSha512 includes ecourna/api/security/csha.hpp, which includes OpenSSL's evp.h
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/asn/cassinavotavelbu.cpp.o: UENUX2_CXXFLAGS += $(OPENSSL_INCLUDES)
