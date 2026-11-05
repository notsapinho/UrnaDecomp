# uenux2 api::CImageFieldUpdate's destructors (target fns 5531 and 11086, vtable slots 0 and 1) and GetTypeName (11085,
# slot 7), all three defined inline in the class header src/uenux2/src/api/gui/cimagefieldupdate.h (new). The class
# derives from api::IFormField<api::IScreen> (RTTI), not from api::CImageField: its base-object destructor stores no
# CImageField vptr. The destructor is declared and defaulted in the class: the deleting destructor 11086 is
# free(D2(this)), the shape of a D2 called directly and not inlined, which neither an out-of-line destructor (called
# through the D1 alias: D2(this); free(this)) nor an implicit one (inline-specified, so inlined into the D0) gives
# with these flags. GetTypeName follows the deleting destructor in the target's function order (ledger/ordinals.tsv),
# with the members the vtable emission creates, so it is inline too. The header's comment gives the layout (from 5531
# and the constructor that binaryen inlined into fn 3059) and the evidence for each member; the member names are
# chosen. The file the records name, src/uenux2/src/api/gui/cimagefieldupdate.cpp (the constructor's throw at line 32,
# Rect's at line 80), holds Show and Hide (fns 11089, 11088, slots 3 and 4: Start and Stop of the timer, whose class it
# includes, api/util/itimer.h, through api/util/itimerscheduler.h) at lines that are a choice, above line 80 in the
# band's order, and Move (one of the five functions of target fn 2241, see 27-uenux2-ctextfield.mk, which lists the
# forms) below it, a choice. Paths relative to src/uenux2.
# The constructor is written at its record (line 32, column 15: the throw of api::EUE_GUI_IMAGEFIELDUPDATE_IMAGEM_NULA,
# 4921, "Campo estava com a imagem nula", whose enumerator eueguierror.h adds, its name chosen from the message). It has
# no target index: binaryen inlines it into its one caller, vota::AdicionaTelaQRCode (fn 3059, unit 110's
# ctelasvota.cpp), behind a 48-byte stack frame of its own, after std::make_shared's control block. Its body there: the
# base's zeroes and this class's vptr, the position, the image's copy, the anchor and the null m_tamanho, then
# ITimerScheduler::GetInst's slot 0 (CreateTimer) with the interval and a std::function<void()> over a lambda of the
# constructor, then the test of the image. The member-initializer list is written in api::CTextFieldUpdate's
# constructor's shape (unit 42's), a choice. The lambda calls IFormField's Invalidate on the captured `this` (fn 11082,
# slot 6 of its __func: the form's visible flag under its mutex, then the field's flag and the form's Refresh), and
# the __func's slots 2, 3, 6, 7 and 8 (fns 11084, 11083, 11082, 11081, 11080) match from this object. The lambda's
# body, the members' order in the initializer list and the constructor's lines above 32 (the include it adds,
# eueguierror.h, took a blank line of the run above Draw, and itimerscheduler.h, which includes itimer.h, replaces
# that include: a layout of ours) are chosen. The roots file that took the vtable's address, standing for the
# constructor's vptr store, went: the constructor is in the link through 3059 (unit 110).
# Draw (target fn 11090, slot 2), the class's key function, is in cimagefieldupdate.cpp above Show, in the band's order,
# at lines that are a choice, so that object emits the vtable and with it the destructors and GetTypeName. Testing
# m_tamanho for null first is evidence: testing it != nullptr first swaps the two calls. Same object code, by the
# function's disassembly with the object-local numbers masked: `!m_tamanho`, and a `return` after the first call in
# place of the `else`; so those spellings are choices. Rect (11087) is CImageField's without the null test: the
# constructor throws on a null image.
CIMAGEFIELDUPDATE_SRCS := src/api/gui/cimagefieldupdate.cpp
UENUX2_SRCS += $(CIMAGEFIELDUPDATE_SRCS)
