# uenux2: two of the biometry callees vota's identification states and comum's mesario states wait for, kept in the link
# by this unit's roots (291-uenux2-biometria-eleitor-roots.cpp), with no source of their own here:
# - comum::CEleitores::GetCurrentBiometriaEleitor (target fn 1393, 15 B, no record): `f1937(p0, f656(p1 + 4))`, the
#   current record's CEleitorDetalhe::GetBiometria (fn 1937, unit 98) returned through the result's address. Its six
#   callers (10425, 10465, 10474, 10478, 10500, 10512, vota's identification states; 10474 and 10478, unit 282's, and
#   10512, unit 161's, are in the link) pass
#   CEleitores::GetInst()'s result (10500: `f1393(frame + 8, f326())`), and +4 is CEleitores' CDataMap base, whose
#   GetCurrent (fn 656) it calls: so a member of CEleitores, out of line, a reading. Its file, celeitores.cpp (unit 110's
#   source), is a reading too: in the target's link it comes before comum/justificativa/cjustificador.cpp's GetInst (fn
#   1391) in band 9, and celeitores.cpp's records come before cjustificador.cpp's. Its name (after
#   GetCurrentAbrangenciaEleitor's), its const and its line after GetCurrentAbrangenciaEleitor are chosen. It matched
#   through the scan's content pass (`source` content in step 9's first scan) once 1937 had its name; BiometriasCorrentes
#   in the roots stands in for the three callers not written (10425, 10465, 10500), two calls on two objects, reading
#   both results.
# - api::CPolySingleton<api::IFingerDetection>::instance (target fn 3615, 2126 B): the header's template (records
#   cpolysingleton.h:78 and cpolysingletonlist.h:99 and :105, [T = api::IFingerDetection]), whose copy matches from the
#   roots object, as IFingerMatcher's 1686 does from unit 135's. The target keeps it a body of its own, where binaryen
#   merged IFingerScanner's and IFingerMatcher's into 6013: `pnpm --silent wasm score ../target/vota_web_wasm.wasm 3615
#   ../target/vota_web_wasm.wasm 6013` shows the copy of the typeid name built with another allocation and other stores
#   ("N3api16IFingerDetectionE", 24 characters, against 22), which no merge's parameters cover. Its three callers (10316, 10451, 10465) are not written:
#   DetectaDigital calls it twice with an empty std::source_location (unit 135's ReconheceDigital does the same). The
#   head api/hwil/ifingerdetection.h is new and says what its slots rest on.
# The roots object compiles at uenux2's flags ($(UENUX2_CXXFLAGS), with -fno-strict-aliasing), since it emits 3615, TSE
# code that matches. With strict aliasing on, the instance's code is the same: wasm-objdump -d of the function in the
# two objects, call and global indices masked, gives 154 identical lines.
# Chosen: the fragment, the roots' stand-ins, and every name and path the two notes above call chosen.
$(ROOT)/$(APP)/291-uenux2-biometria-eleitor-roots.o: $(ROOT)/src/units/291-uenux2-biometria-eleitor-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/291-uenux2-biometria-eleitor.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/291-uenux2-biometria-eleitor-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/291-uenux2-biometria-eleitor-roots.o
