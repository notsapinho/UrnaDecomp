# uenux2 comum::CAssinador in src/uenux2/src/app/comum/gravadores/cassinador.cpp: the destructor (target fn 1007,
# CAssinador vtable @1553252 slot 0) and its deleting destructor (fn 4694, slot 1), Assina (fn 1277, record 114:19) and
# the constructor (no target index). The file is the one the records of Assina and AssinaArquivosResultado name (lines
# 114 and 141-149), and the stubs' link-order placement gives the destructors. No record falls in the destructor or the
# constructors, so their lines are a choice; AssinaArquivosResultado (lines 138 to 168, records 141, 146 and 149) is
# written since (below). The destructor is the class's only virtual member, and the target's deleting destructor shows
# it is defined out of line: 4694 calls 1007 (`f1007(p0); f136(p0)`), which clang gives only for an out-of-line
# destructor (its D0 calls the D1, an alias of the D2 that is not inlined through); one defined in the class would have
# the D2's body inlined into the D0, the three frees and then the delete. Out of line, it is the key function, so
# cassinador.cpp emits the vtable and the RTTI. Its body stores the vptr, since vota::CAssinadorVota derives from the
# class, and frees the three std::string members (+36, +24, +12).
# With it: the class header (cassinador.h) and the ESavdPacote type of its +8 member, declared beside ESavdAplic in
# app/comum/iinterfacesavd.h. In the target the deleting destructor 4694 is also slot 1 of vota::CAssinadorVota's
# vtable (binaryen merged the two identical bodies); fragment 165 writes that class's destructor (7766), whose object
# links first, so 4694's match line names its D0.
#
# Added since:
# - Assina (1277): CPolySingleton<IInterfaceSavd>::instance() first (its default location is the record, 114:19; the
#   column is the one `auto& iSavd = ` gives at four spaces, a name chosen to that length), a CApplicationContextGuard
#   from CApplication::CriaContexto(11, "Erro na assinatura", "", "Ocorreu um erro durante a assinatura do arquivo: " +
#   DescricaoArquivo(arquivo)) (the order of the four arguments' temporaries is the target's), then comum::AssinarUE
#   (iinterfacesavd.cpp, unit 95's) with the ESavdAplic at +4, the command 66 and the file. binaryen inlined AssinarUE,
#   which has one caller, behind a stack frame of its own; the order of the two objects decides 1277's locals, so
#   cassinador.cpp is compiled by fragment 95 now, after iinterfacesavd.cpp (that fragment has the measurement).
# - The constructor CAssinador(ESavdAplic, ESavdPacote): binaryen inlined it into vota::CAssinadorVota's (fn 1501, unit
#   165's), its one caller, behind a stack frame of its own, and 1501 stores CAssinadorVota's vptr after that frame's
#   epilogue, so the constructor is out of line in another TU than CAssinadorVota's, a reading. It stores the ESavdAplic
#   at +4 and the package at +8, takes the package's entry of comum::CArquivosSavd (fn 275 on fn 1164's result), and
#   assigns api::GetDirName of it (fn 5462) with a '/' appended to +24 and api::GetFileName of it (fn 2763) to +12; +36
#   stays empty. That the ESavdAplic is a parameter (CAssinadorVota passes 1) and not the constructor's constant is a
#   choice, and so are the members' names.
# - The second constructor and AssinaArquivosResultado, neither with a target index: fn 12098
#   (vota::CGravaResultado::StartState) holds both, each behind a stack frame of its own (480 and 128 bytes, at lines
#   2388 and 3049 of pnpm wasm fn's folded readout of 12098: binaryen's inlining of a function with one caller), so they
#   match only with 12098. Unrooted, wasm-ld drops them (unit 95's fragment has the plain link, cmp-equal to the
#   base's).
# - CAssinador(ESavdAplic, ESavdPacote, TMunicipioID, TZonaID, TSecaoID, char): 12098 stores the vptr, the ESavdAplic 1
#   at +4 and the package at +8, zeroes +12 to +35, then builds +36 in place with std::format("{}{:05}{:04}{:04}") over
#   CLocal::GetUFMinuscula (fn 3753) and three numbers (argument types 13, 6, 6, 6), so +36 is a member initialized
#   from the format; it then calls CConfiguracaoEleicao::GetInst (fn 187) and reads the pleito's identifier at +28,
#   takes the package's entry of CArquivosSavd (fn 275) and the UF again, and formats the entry with std::vformat over
#   a char, the pleito, the UF and the three numbers (types 2, 6, 13, 6, 6, 6; libc++'s constant-folding test leaves
#   its loop over the entry, read by nothing), then assigns m_diretorio and m_caminho from that path as the first
#   constructor does, and frees the path, the UF and the entry in that order. std::make_format_args takes lvalues, so
#   the pleito, the entry and the UF are locals, declared in the order of their GetInst calls. The three numbers and the
#   char are 12098's locals from CLocal's GetMunicipio, GetZonaID and GetSecaoID (fns 1004, 1003, 1078) and
#   CDadoCarga::GetFaseChar (fn 2253), computed at its start: parameters, in the order
#   CGravadorUtil::DeterminaNomeArquivoSemLetra takes them (which formats the same six arguments), with its types; the
#   order, the types and the names are chosen. m_arquivo is m_local now: IInterfaceSavd::EnviarLocal sends it (a
#   chosen name too). Then 12098 stores vota::CAssinadorVota's vptr on the result: unit 165's fragment has that
#   class's second constructor. That this one is out of line in cassinador.cpp is a reading (the vptr stored on the
#   inlined C2's result, how-to step 3), as for the first.
# - AssinaArquivosResultado(const std::vector<ESavdArquivoUE>&) const: for an empty vector it throws 8636 with the text
#   at 137781 (a std::string temporary: fn 148; record 141:15); then CPolySingleton<IInterfaceSavd>::instance() (146:19)
#   and comum::EnviarAcaoHSM (fn 5889) with SAVD_CMD_HSM_INICIA_SESSAO (0); CPolySingleton<api::IUrna>::instance()
#   (149:25: the column fixes `api::IUrna& iUrna = ` at four spaces, a spelling chosen; `const auto& iUrna = ` has the
#   same length); CLogComum's LogaIniciaSessaoMSE when IUrna::Modelo() is 2020 or more, else LogaIniciaSessaoMSD
#   (unit 111's members; 12098 calls CLogComum::GetInst once, after Modelo, and this object's code hoists the two
#   branches' calls so too); IInterfaceSavd::EnviarLocal with m_aplic and m_local, its result dropped; for each file
#   (a range-for: 12098 loads the end once) a CApplicationContextGuard from CriaContexto(11, the text at 137736, "", the
#   text at 444224 + DescricaoArquivo(file)), as Assina's, and comum::AssinarEcourna with the command 128 (unit 95's
#   paragraph); then EnviarAcaoHSM with SAVD_CMD_HSM_FINALIZA_SESSAO (1), Modelo again and LogaFinalizaSessaoMSE or
#   ...MSD. This object's code holds those calls, constants and stores in the readout's order (wasm-objdump -d, read by
#   hand: with no target index, nothing scores it). Lines 138 to 168: the definition's line, the blank lines 143 to 145
#   and EnviarAcaoHSM's line (147) are a choice.
# - The lines: the file's header comment, the includes the two members need and the second constructor take lines of
#   the blank run above Assina, whose line stays (check_srcloc.py --strict on this object: every record the target's).
#   The second constructor's file needs Boost's include path (cconfiguracaoeleicao.h's ecourna headers): fragment 95's
#   rule for cassinador.cpp.o.
# cassinador.cpp is compiled by fragment 95, after iinterfacesavd.cpp (the paragraph above), so this fragment lists no
# source. Five of the destructor's callers are not reconstructed yet: 34-uenux2-cassinador-roots.cpp gives it two direct
# callers and takes their addresses
$(ROOT)/$(APP)/34-uenux2-cassinador-roots.o: $(ROOT)/src/units/34-uenux2-cassinador-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/34-uenux2-cassinador-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/34-uenux2-cassinador-roots.o
