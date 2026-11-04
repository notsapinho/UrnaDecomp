// Roots: keep the api/compression units' functions in the skeleton link the way the target keeps them (table
// slots through invoke_*, virtual slots, or callers in uenux2 TUs not reconstructed yet): address-taken from a static
// constructor, declared through asm labels with the wasm-level signatures (tools/round/gen_try_roots.py output, minus the
// functions the target inlines: ICompressor::Add(const path&), CZip::ConvertToOpen, CZip::AssertZipIsOpened, the 7-Zip
// context ctor; plus the CLzmaCompress destructors the header defines inline). Compiled as uenux2 code.
// Not taken here, since every target reference to them is in the link with comum::CGravadorLog::GravaResultado (fn
// 11584, unit 136), which these lines stood for: ICompressor::Add(map), CZip::SafeClose and CZip::CreateZipFile, reached
// only through the invoke_* slots 6050, 6122 and 6119, whose users are 11584 and, for 6119, CZip's constructor (fn
// 5193); ICompressor's constructor (fn 5192), called by 5193 and 11584, which no table slot holds; and ICompressor's
// destructor (fn 1526, called by 2690, 5193, 9540, 9581, 9582 and 11584), CZip::Close (2691) and CZip's destructor
// (2690, both called twice by 5821 and once by 11584), which the vtables 5192 and 5193 store hold too.
extern "C" {
void rcomp_root_1(int, int) __asm__("_ZN7ecourna3api11compression11ICompressor3AddERKNSt3__26vectorINS3_10filesystem4pathENS3_9allocatorIS6_EEEE");
void rcomp_root_3(int) __asm__("_ZN7ecourna3api11compression11ICompressorD0Ev");
void rcomp_root_6(int, long long, long long, int) __asm__("_ZN7ecourna3api11compression4CZip17AtualizaProgressoEyyRKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
int rcomp_root_7(int) __asm__("_ZN7ecourna3api11compression4CZip22ConvertToCompressLevelEv");
void rcomp_root_9(int, int, int) __asm__("_ZN7ecourna3api11compression4CZip5DoAddERKNSt3__210filesystem4pathES7_");
void rcomp_root_11(int) __asm__("_ZN7ecourna3api11compression4CZipD0Ev");
void rcomp_root_13(int, long long, int) __asm__("_ZN7ecourna3api11compression13CLzmaCompress17AtualizaProgressoEyRKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
void rcomp_root_14(int, int, int) __asm__("_ZN7ecourna3api11compression13CLzmaCompress5DoAddERKNSt3__210filesystem4pathES7_");
int rcomp_root_15(int, int, int, int, int, int) __asm__("_ZN4lzma8CompactaERNS_9CContextoERKNSt3__26vectorINS2_12basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEENS7_IS9_EEEERKS9_SD_bNS2_8functionIFvySF_EEE");
int rcomp_root_16(int) __asm__("_ZN4lzma9CContextoD1Ev");
void rcomp_root_17(int) __asm__("_ZN7ecourna3api11compression13CLzmaCompressD0Ev");
int rcomp_root_18(int) __asm__("_ZN7ecourna3api11compression13CLzmaCompressD2Ev");
}

namespace {

void* volatile rcomp_sink;

struct SRcompRoots {
    SRcompRoots()
    {
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_1);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_3);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_6);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_7);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_9);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_11);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_13);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_14);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_15);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_16);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_17);
        rcomp_sink = reinterpret_cast<void*>(&rcomp_root_18);
    }
} rcomp_roots;

} // namespace
