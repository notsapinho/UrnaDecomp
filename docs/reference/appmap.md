# vota_web_wasm — application map

Target: `target/vota_web_wasm.wasm` (7,713,699 B; 14,343 defined functions, 136 imports, 4,224 data segments = 1,732,475 B at 1024..1811674).
Everything below is derived from the binary alone by the scripts in `tools/extract/` (run each with `python3 -I`); every number names the file it was read from.

| artefact | produced by | what it holds |
| --- | --- | --- |
| `ledger/strings.tsv` | `tools/extract/extract_strings.py` | 16375 NUL-terminated data strings: addr, len, encoding (ascii/latin1/utf8), text |
| `ledger/classes.json` | `tools/extract/rtti.py` | 2,162 typeinfo objects: name, kind (class/si_class/vmi_class/pointer/…), bases with offset/virtual/public |
| `ledger/vtables.json` | `tools/extract/rtti.py` | 1851 vtables: address, class, offset_to_top, table indices and resolved function indices |
| `ledger/func-strings.tsv` (ignored) | `tools/extract/func_refs.py` | per function: every data address it loads (i32.const or folded load/store offset) that is a string start, a vptr or a typeinfo |
| `ledger/callgraph.tsv` | `tools/extract/func_refs.py` | 113,299 direct `call` edges |
| `ledger/func-attribution.tsv` | `tools/extract/attribute.py` | every function → component, evidence (file/vtable/vptr/typeinfo/str/callers), detail |
| `target/fs/`, `target/fs-manifest.tsv` | `tools/setup/unpack_fs.mjs` | the 70 preloaded files (path, size, sha256) |
| `tools/extract/wasmmod.py` | — | the wasm reader the scripts share (sections, imports, elem table, data image) |

## 1. Components and their size

Function counts from `python3 -I tools/extract/attribute.py ledger/func-strings.tsv ledger/vtables.json ledger/classes.json target/vota_web_wasm.wasm ledger/func-attribution.tsv` (direct evidence = __FILE__ string, vtable slot, vptr store, typeinfo ref or owner-specific string; "propagated" = inherits the single component of all its attributed callers, iterated to a fixpoint):

| component | what it is | source files seen | functions (direct) | functions (after propagation) | RTTI classes |
| --- | --- | ---: | ---: | ---: | ---: |
| **vota** | uenux2 `src/app/vota`: the voting application (states, screens, operator flows) | 75 | 529 | 780 | 219 |
| **comum** | uenux2 `src/app/comum`: shared urna app code (model `comum::md`, ASN converters `comum::asn`, reports, DAO) | 184 | 377 | 599 | 239 |
| **api** | uenux2 `src/api/*`: GUI toolkit (form builders, fields), io, ipc, hwil, util, hash, uelog, persistencia, audio | 80 | 449 | 516 | 185 |
| **ecourna** | conan package `libecea1da310e5107` (`src/ecourna/{api,app}`): security (AES, SHA, siphash, HKDF, base64, CEPESC, ASN.1 key loader), sql/sqlite wrapper, compression (zip, lzma), io, util, `app/dados` model + ASN converters | 64 | 563 | 799 | 147 |
| **simulador** | the web-simulator shim (`CWasm*` devices implementing `api::I*`), `wasm/vota_web/vota_web_wasm.cpp` | 1 | 126 | 144 | 21 |
| **vota-web** | anonymous-namespace web engine (`CVotaWebEngine`, `CPoliticaExecucaoEleitorWeb`, `CSincronismoVotoEleitorWeb`, `CWasmSavd`) | — | 10 | 11 | 3 |
| asn1-modules | asnparser-generated ASN.1 types `Modulo*::` | — | 48 | 59 | ~110 |
| ASN1 | asnparser C++ runtime (`ASN1::`) | — | 281 | 362 | 64 |
| RHVoice | RHVoice text-to-speech engine | — | 470 | 666 | 295 |
| 7zip | 7-Zip C++ (NArchive::N7z, NCompress::NLzma/NLzma2, COM-style streams) | — | 601 | 878 | 102 |
| boost | signals2, regex (re_detail_600), lexical_cast, date_time gregorian, exception | — | 114 | 125 | 31 |
| openssl | OpenSSL 3 libcrypto incl. the complete default provider set | 347 | 1,504 | 2,381 | — |
| sqlite | SQLite 3.50.4 (source id 2025-07-30 19:33:53 4d8adfb30e03…) | (os_unix.c…) | 50 | 500 | — |
| libc++ / libc++abi | emscripten system libs (`/emsdk/emscripten/system/lib/libcxxabi/src/*`) | 5 | 1,314 + 174 | 1,564 + 234 | 576 (std) + 90 (demangler) + 9 |
| utf8cpp, rapidxml | header-only helpers | — | 10, 6 | 10, 6 | — |
| **unattributed** | musl libc, compiler-rt, small templates, library internals without strings | | 7,716 | 4,709 | |

RTTI census (`tools/extract/rtti.py`): 2149 class-kind typeinfos; 1,756 classes have a vtable; vtables name 3,908 distinct functions.

## 2. Source tree

The TSE build machine had the uenux2 tree at `/home/rubio/tse/uenux2` and the ecourna conan package at `/home/rubio/.conan2/p/b/libecea1da310e5107/b`; OpenSSL was compiled in-tree so its `ERR` file strings are relative (`crypto/…`, `providers/…`). Only files that emit a `__FILE__` string are visible (asserts/uelog), so headers and silent TUs are missing. The shape:

- `uenux2/src/app/vota` (75 files): `eleitor/` 53 (voter flow: votaproporcional, votamajoritario, confirma*, justificativa…), `operador/` 17 (mesário flows: confirmaidentidade/cregistradigitaloperador, registramesarios, auxiliares/cmenuvisualizarcandidatos, votacao/cverificahorariozeresima…), `comum/` 2, `log/` 1, `monitor/` 1, 1 at the root; plus `uenux2/wasm/vota_web/vota_web_wasm.cpp`.
- `uenux2/src/app/comum` (184 files): `dados/` 86 (`md/` 47 — the domain model: candidaturas, cargos, eleitores, rdv/cvoto, fotos, abrangência; `asn/` 23 — CConversor* to/from the ASN.1 modules; `dao/` 1; 15 at its root), `gravadores/` 24, `comparecimentomesario/` 22, `relatorios/` 14 (BU, zerésima, RDV, QR codes), `md/` 9, `asn/` 7, `appinfo/` 4, `justificativa/` 2, `log/` 2, `util/` 2, `validamidia/` 2, `informacao/`, `nomearquivo/`, `reconhecimentobiometrico/` 1 each, 7 at the root.
- `uenux2/src/api` (80 files): `gui/` (39: capplication, cformbuilder, cinteractiveformbuilder, cpaperformbuilder, text/image/movie/qrcode/progress fields), `util/` (14), `io/` (7, asn file readers), `ipc/` (5), `hwil/` (4), `pattern/`, `hash/`, `uelog/`, `persistencia/`, `audio/alsa/cwavfile.cpp`.
- `ecourna/api` (26 files): `security/` (14: caescipher, cblockcipher.hpp, isymmetriccipher, ckey, csha, csiphashmac, imacalgorithm, chkdfseed, base64, asn1/ckeyloader, cepesc/{ccipheredin,ccipheredout,cinfosalt,cplaintext}), `compression/` (czip, clzmacompress, icompressor), `sql/sqlite/`, `io/cfile`, `util/`, `asn/iconversorasn.hpp`, `pattern/cbasetype.hpp`.
- `ecourna/app/dados` (35 files): the shared data model (CParametrosUrna, CConfiguracaoMunicipio, CFederacao, CInformacaoMidia, CResultadoUrnaCadastro, identificadores…) and its `asn/` converters.

## 3. Main subsystems

### 3.1 Voting-flow state machine
`api::CState` is the root (199 descendants, the largest hierarchy); `comum::CAppState` (9 virtual slots) has **132 direct subclasses**, each one screen/step of the flow. Examples (vtables.json → function indices): `vota::CPedeDigital` (vtable @1591888, slots [2739, 10469, 10468, 7480, 1661, 10467, 425, 10466, 10465]), `vota::CAguardaInicio`, `CDefineRotaPreVotacao`, `CDigitalReconhecida`/`CDigitalNaoReconhecida*`, `CEleitorEncontrado`, `CConfirmaVotoNominal`, `CCompletaProporcional`, `CConfereVotoEmCargo<State, ETelaVotacao N>` (10 template instantiations: candidato inapto/inexistente, voto legenda/nominal, majoritário branco/nulo/repetido/válido, proporcional branco/nulo), `CConfirmaEncerramento`, `CCopiaResultadoParaMR`, mesário registration states in `comum::` (`CPedeTituloMesario`, `CPedeDigitalMesario`, `CRegistrarMesarios`, `CMesarioRegistrado`…). `comum::CAppStateContext` / `api::CStateContext<comum::…>` drive them; `vota::CControladorRegistraMesariosVota` has the largest app vtable (37 slots). Operator/voter threads: `vota::CThreadEleitor`, `vota::impl::CInformacaoThreadOperador` (31 slots), `vota::CThreadMonitor`, `api::CThread`.
The string `vota::CVotacaoStateAudio::PlayKey(const char) const` and the `CConfirmaAudio`/`CDesabilitaAudioEleitor` states show the audio-assisted voting path; `IQRCodeBUDS`, `CGeradorBUQRCodeVota` the BU QR output.

### 3.2 GUI: form builders and fields
`api::IScreen` (39 virtual slots) is implemented only by `simulador::CWasmScreen` (drawing goes to the JS canvas through the EM_JS imports js_fill/js_line/js_text/js_image/js_round_rect/js_path/js_gray_gradient/js_circle). `api::CFormBuilder`, `api::CInteractiveFormBuilder`, `api::CPaperFormBuilder` (printer/paper variant), `api::IFormFieldBase<IScreen|IScreenMT|IPaper>` (24+11+5 descendants: CTextField*, CImageField, CMovieField, CQRCodeImage, CProgressBar, CStepsProgressBar, CInputField/CInputMenuField, CMaskedTextField, battery icon data sources), `api::IText` (19), `api::CDataText<…>/CDataTextFmt<…>/CDataImage<…>` templates binding model objects to fields. `CTelasVota::CriaTela*` lambdas (pretty strings) build the voter screens.

### 3.3 Persistence: SQLite DAO
`ecourna::api::sql::sqlite::{CSqlConnection(10 slots), CSqlStatement, CSqlResultSet}` over SQLite 3.50.4; `api::persistencia::IDAO` (9 descendants) and `comum` DAOs (`CEleitores`, RDV `comum::CRdvVota`, `CGeradorBUBase<CRdvVota, CEleitores>`). SQL text lives in `ledger/strings.tsv` (CREATE/INSERT/SELECT strings).

### 3.4 ASN.1
Runtime `ASN1::` (AVN/BER/PER encoders and decoders, `BERDecoderPartial` 28 slots, Constrained_INTEGER/SEQUENCE_OF templates, Visitor/ConstVisitor) with generated modules `ModuloTiposEleitorais`, `ModuloResultadoUrnaCadastro`, `ModuloBoletimUrna`, `ModuloRegistroDigitalVoto`, `ModuloEleitores`, `ModuloEstadoGeralUrna`/`Gap`, `ModuloParametrizacaoUrna`, `ModuloFederacoes`, `ModuloInformacaoMidia`, `ModuloConfiguracaoMunicipios`, `ModuloTiposEcoUrna`, `ModuloTiposResultadosEcoUrna`. Converters: `comum::asn::CConversor*` (uenux2 side) and `ecourna::app::dados::asn::CConversor*` via `ecourna::api::asn::IConversorASN<Asn, Model>` (~45 instantiations). `api::io::asn` reads packages (`cfileasn.h`, `cpartialfileasn.h`).

### 3.5 Security
`ecourna::api::security`: `CBlockCipher<CAesCipher, CTrng>` (ISymmetricCipher), `CSymmetricCipherFactory`, `CSiphashMac`, `CPrng`/`CTrng` (IRng), `cepesc/` (CCipheredIn/Out — the CEPESC cipher streams), `asn1/ckeyloader`, SHA/HKDF/base64; `comum::CAssinador`, `vota::CAssinadorVota` (signing), `api::hash` (CHashArquivo, CHashDiretorio, CMontadorHash). All on OpenSSL 3 (EVP, provider API; RSA/EC/DSA/DH, PKCS7/PKCS12, every default-provider algorithm is linked).

### 3.6 Devices (hwil) and the web shim
`api::I{Input,Sound,Timer,TimerScheduler,SystemDateTime,Paper,Impressora,TextToSpeech,EsperaAudio}` each have exactly one real implementation in `simulador::CWasm*` (CWasmInputKbd/MT, CWasmWebSound/NullSound, CWasmTimer(Scheduler), CWasmSystemDateTime, CWasmNullPaper/NullPrinter, CWasmNullTextToSpeech, CWasmBeep, CWasmLogd, CWasmResource, CWasmThread, CWasmImageSurfaceOps, CFingerPrepareSimulador). `api::CRHVoiceTextToSpeech` wraps RHVoice (linked, no voice data in the payload). `api::teste::CPowerMock`/`CUrnaMock` (test doubles) are linked too.

## 4. Preloaded filesystem (`target/fs/`, `target/fs-manifest.tsv`)
70 files, 14,855,585 B: 12 animated GIF sign-language avatars (`/resource/gifs/*Mulher4.gif`, 249×240, 14.36 MB = 97%), `/font-variable.ttf` (65,072 B, the only font), 54 images under `/uenux/app/img/` (JPEG/SVG/XBM/XCF battery, biometrics, marcaJE, armas, confirmado/cancelado), 3 empty `/etc/*.properties|vst`. No database, no ASN.1 package, no voice data: TSE data is synthesised in the simulator (`target/manifest.json` scenarios). Fonts/images are decoded by the browser (js_image/js_text), not by C++.

## 5. Encodings and strings
Of 16375 strings 14,353 are ASCII, 2,010 Latin-1 (`Conteúdo inválido para {}:{}`), **1 UTF-8** (`Turno inválido.` @367628) → sources are ISO-8859-1 except the TU emitting that string. Format strings are `{}`-style (fmt/std::format) in the app, `%` in OpenSSL/SQLite.

## 6. What remains unattributed, and known blind spots
- 4,709 functions (33%) have no owner: musl, compiler-rt, printf/locale internals, libc++ templates without RTTI, OpenSSL/SQLite helpers. Function **index order is sorted by use count** (binaryen reorder-functions at -Oz; ties by descending decimal string of the link ordinal, names stripped) — see [facts/link-order.md](facts/link-order.md) §L1; within a use-count band neighbours are link-order neighbours up to a digit scramble, which can be used to attribute the rest.
- The 1,382 `__PRETTY_FUNCTION__` strings are referenced by nothing (no i32.const, no load offset, no data word): their call sites were optimised away but the bytes remain — the rebuild needs the same macro usage to re-emit them.
- vtables name the class of 3,908 functions but not their slot's meaning; slot→method names need the headers (comum::CAppState has 9 slots: dtor pair, OnEnter/OnExit/ProcessTick/… per the pretty strings `virtual void vota::CPedeDigital::ProcessTick(uebyte)`).
- Indirect calls (`call_indirect`) are not in the call graph; 12,854 table entries.

---
