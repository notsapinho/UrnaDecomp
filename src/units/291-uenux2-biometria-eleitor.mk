# uenux2: two of the biometry callees vota's identification states and comum's mesario states wait for, with no source
# of their own here; this unit's roots kept them in the link until their callers came into it, and went with the last:
# - comum::CEleitores::GetCurrentBiometriaEleitor (target fn 1393, 15 B, no record): `f1937(p0, f656(p1 + 4))`, the
#   current record's CEleitorDetalhe::GetBiometria (fn 1937, unit 98) returned through the result's address. Its six
#   callers (10425, 10465, 10474, 10478, 10500, 10512, vota's identification states; all six are in the link, 10425
#   written in unit 142) pass
#   CEleitores::GetInst()'s result (10500: `f1393(frame + 8, f326())`), and +4 is CEleitores' CDataMap base, whose
#   GetCurrent (fn 656) it calls: so a member of CEleitores, out of line, a reading. Its file, celeitores.cpp (unit 110's
#   source), is a reading too: in the target's link it comes before comum/justificativa/cjustificador.cpp's GetInst (fn
#   1391) in band 9, and celeitores.cpp's records come before cjustificador.cpp's. Its name (after
#   GetCurrentAbrangenciaEleitor's), its const and its line after GetCurrentAbrangenciaEleitor are chosen. It matched
#   through the scan's content pass (`source` content in step 9's first scan) once 1937 had its name. The roots' stand-in
#   for 10425 (BiometriasCorrentes) went when 10425 came into the link.
# - api::CPolySingleton<api::IFingerDetection>::instance (target fn 3615, 2126 B): the header's template (records
#   cpolysingleton.h:78 and cpolysingletonlist.h:99 and :105, [T = api::IFingerDetection]), whose copy matched from the
#   roots object, as IFingerMatcher's 1686 does from unit 135's, until unit 282's 10465 came into the link: it matches
#   from cpededigital.cpp.o now, the first object in link order to emit it. The target keeps it a body of its own, where
#   binaryen merged IFingerScanner's and IFingerMatcher's into 6013: `pnpm --silent wasm score
#   ../target/vota_web_wasm.wasm 3615 ../target/vota_web_wasm.wasm 6013` shows the copy of the typeid name built with
#   another allocation and other stores ("N3api16IFingerDetectionE", 24 characters, against 22), which no merge's
#   parameters cover. Its three callers (10316, 10451, 10465) are in the link (units 135, 221 and 282): the roots'
#   DetectaDigital, which called it once with an empty std::source_location for 10451 (as unit 135's ReconheceDigital
#   does), went with the roots file. The header api/hwil/ifingerdetection.h is new and says what its slots rest on.
# The roots object compiled at uenux2's flags ($(UENUX2_CXXFLAGS), with -fno-strict-aliasing): it emitted 3615, TSE
# code that matches. With strict aliasing on, the instance's code was the same: wasm-objdump -d of the function in the
# two objects, call and global indices masked, gave 154 identical lines.
# Chosen: the fragment, and every name and path the two notes above call chosen.
