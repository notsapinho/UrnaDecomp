// Roots: reach comum::asn::IConversorASN<ENTIDADE, DADO>'s Desconverte (app/comum/asn/iconversorasn.h) the way the
// target's callers do, until they land. Each instance has direct callers only, at least two call sites in the target
// (ledger/callgraph.tsv), and binaryen keeps it out of line for that, and merges those of one shape into fns 1563 and
// 1008, with the record and the entity's typeid text as parameters. No instance needs a stand-in now: w107_todos, which
// called the last two twice each (through w107_desconverte), went with them. The last Converte instance went: 2275's
// callers are all written.
// The callers each instance stood for:
//   3730, 3726, 3727 and 3736 need none: their callers 11411 and 10270, 11390 and 11394, 11391 and 11395, and 11424 and
//   11451, are written.
//   3737 and 3738 need none: their callers 11381, 11423 and 11452, and 11411, 10270 and 11457, are written. 3799 needs
//   none: its callers 10271, 10273 and 11587 are written.
//   2275 and 5688 need none: their callers 10266, 10271, 10273, 11458 and 11587, and 11359 and 11375, are written.
//   5692, 5691, 5696 and 5697 need none: their callers 11395 and 11398, 11394 and 11397, 11399 and 11403, and 11400 and
//   11404, are written.
//   5711 needs none: its caller 11448 (unit 159's, two calls) is written. 5705, 5713 and 5714 need none: their callers
//   5706 and 11423, and 11424 and 11451, are written.
//   5715 and 5716 need none: their callers 11423 and 11452 are written.
//   5828 needs none: its callers 11373 and 11445 (unit 159's) are written.
// 3823 needs none: its callers 2725 (unit 293's), 11412 and 11629 (unit 200's) are in the link, and w107_dados, which
// stood for 11629, went. 5672's call went: its callers 5741 and 11455 are written. 3712 needs none:
// its callers 11378, 11424 and 11451 are written. 5632 has one direct caller (11404) and a table slot (448), which 10205 passes to invoke_iiiii: its address is
// the reference the target has.
//
// The vtables are what the target keeps the converters by: slots 2 and 3, no direct caller. No sink is left: each went
// once a function that stores its vptr was in the link, one storer giving the reference the sink gave.
// CConversorSeguranca's: 10270, 10271 and 11411. CConversorDadoLocal's and CConversorDadoCarga's: 11397 and 11398.
// CConversorMunicipio's: 11423, 11424, 11451 and 11452. CConversorIdentificacaoAgregada's: 11453 and 11454.
// CConversorComplementoMunicipio's: 11381, 11423, 11424, 11451 and 11452. CConversorAbrangencia's: 11441, 11457 and
// 11458.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
int w5632(void*, void*, const void*, int) __asm__("_ZN5comum2md15estadoaplicacao10CDadoLocalC1ENSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEERKNS1_20CLocalidadeEleitoralENS_17ETipoLocalVotacaoE");
}

namespace {

const void* volatile w107_sink_vt;

struct SIConversorRoots {
    SIConversorRoots()
    {
        w107_sink_vt = reinterpret_cast<const void*>(&w5632);
    }
} w107_roots;

} // namespace
