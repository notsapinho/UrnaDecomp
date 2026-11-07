// Roots: reach unit 136's classes the way the target's callers do, until those callers land.
// The stand-in for comum::md::CEntidadeHashes::ValidaCriacao (fn 5855) went: its one target caller, fn 11620, which
// calls it twice, is in the link (cgravadorhashes.cpp). The stand-ins for comum::md::CCorrespondenciaResultado's
// constructor (fn 2801), md::CUrna's constructors (fns 2854 and 2855), md::CEnvelopeGenerico's constructors (fns 3821
// and 5861) and md::CUrna's implicit destructor (fn 1394) went when their last target caller not in the link,
// comum::CGravadorBU::GravaResultado (fn 11629, unit 200's), was written: their other callers (10288, 10284, 10270,
// 11587, 11626 and 2725) are in the link too. CCarga's copy constructor (fn 1557), CUrna::ValidaCriacao (fn 5862) and
// CEnvelopeGenerico::ValidaCriacao (fn 3822) have their callers among those constructors.
// The recorders comum::CGravadorHashes, CGravadorLog, CGravadorRDV and CGravadorVersoesArquivos: the target reaches
// their destructors only through their vtables, which their constructors store (inlined into
// vota::CGravaResultado::StartState, fn 12098, not written yet; the constructors are written, unrooted); so the vtables'
// addresses go into a sink, which stands for 12098, the reference the target has. CGravadorEnvelopeArquivo's vtable and IGravadorEnvelope's are stored by
// CGravadorEnvelopeArquivo's constructor (fn 5856, unit 160's) and destructors.
extern "C" {
extern const char w136_vt_hashes[] __asm__("_ZTVN5comum15CGravadorHashesE");
extern const char w136_vt_log[] __asm__("_ZTVN5comum12CGravadorLogE");
extern const char w136_vt_rdv[] __asm__("_ZTVN5comum12CGravadorRDVE");
extern const char w136_vt_versoes[] __asm__("_ZTVN5comum24CGravadorVersoesArquivosE");
}

namespace {

const void* volatile w136_sink_vt[4];

struct SW136Roots {
    SW136Roots()
    {
        w136_sink_vt[0] = w136_vt_hashes;
        w136_sink_vt[1] = w136_vt_log;
        w136_sink_vt[2] = w136_vt_rdv;
        w136_sink_vt[3] = w136_vt_versoes;
    }
} w136_roots;

} // namespace
