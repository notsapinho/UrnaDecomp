# uenux2 api::CSubReport: its constructor (target fn 3660) and the one it delegates to (inlined into 3660, no target
# function) in src/uenux2/src/api/gui/csubreport.cpp, the class header api/gui/csubreport.h and the api::ISubReport
# interface api/gui/isubreport.h (RTTI: CSubReport an si_class of ISubReport). No record names the class: the directory
# and the file are those of the constructor's place in the link, among the api/gui objects (fn 3660 lies between
# api::CQRCodeImage's functions, 3661-3662, and the CTextFieldDoubleLine constructor, 3659, in the link order of its use
# band, ledger/ordinals.tsv ordinals 5291-5294; ledger/tu-clusters.tsv stretch 984 and stretch 603's class-convention
# guess csubreport.cpp agree), not api/gui/reports/, whose creport.cpp (3654) comes after cinputmenufield.cpp. Chosen,
# with no evidence for them: the header names, the member names (GetTitulo, GetSubtitulo, TemTitulo, TemParte,
# ImprimeParte, Habilitado for slots 2 to 7, and the members they read), the parameter names, the four-argument
# constructor's parameter order and the members' constness (csubreport.h and isubreport.h say what each is read from).
# The class's virtual members are all defined in the class and its destructor is implicit (the target's D0, 12013, holds
# the D2's body); the target keeps their copies from the first object that uses the vtable, vota::CRelVotaUtil's. The D2
# (fn 12014) does not match: the target's is a thunk into fn 3904, binaryen's merge of it with RHVoice's
# resource_info<voice> and <language> D2s (9597, 9810), and our two RHVoice D2s, whose bodies carry exception-handling
# code the target's lack, merge only with each other. Paths relative to src/uenux2; the generic uenux2 rule depends on
# the source and every uenux2 header.
CSUBREPORT_SRCS := src/api/gui/csubreport.cpp
UENUX2_SRCS += $(CSUBREPORT_SRCS)
# ImprimeParte (fn 12009) is defined in the class like the other slots. Defined out of line in csubreport.cpp it has the
# same bytes (a probe with uenux2's flags, as has `(*m_parte).Imprime()` or `m_parte.get()->Imprime()` in the class), but
# it would be the key function and the vtable strong, where the data order above shows a linkonce copy: that is what
# makes the class form the choice. The constructor's three target callers, 2882 (vota::CRelVotaUtil::CortaPapel,
# unit 246), 3671 (api::CPaperFormBuilder::Show, unit 31) and 11908 (unit 176's vota::CImpressaoListaEleitores::
# StartState, through fragment 317's api::CReport), are in the link, and the unit has no roots. The vtable, the implicit
# destructors (fns 12014, 12013) and the inline slots are emitted with the constructor, in csubreport.cpp's object, and
# with 2882, in crelvotautil.cpp's, which links first (fragment 246 sorts before 57) and gives the copies the link keeps
# (the object column of build/out/wasm-map/vota_web/names.tsv), as the target keeps CRelVotaUtil's object's; both come
# before the ecourna csha object in the link: slot 2, a twin of CSha::GetAlgoritmo, is GetTitulo's body now.
