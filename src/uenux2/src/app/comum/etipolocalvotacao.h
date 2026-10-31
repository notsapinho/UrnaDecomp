#pragma once

namespace comum {

// The enumerators are chosen: only their values are evidence, the range comum::asn::Utils's conversions accept. No
// record names this header; its path is chosen, beside eurnafase.h.
enum ETipoLocalVotacao {
    LOCAL_VOTACAO_NORMAL = 1,
    LOCAL_VOTACAO_EM_TRANSITO,
    LOCAL_VOTACAO_PRESO_PROVISORIO,
    LOCAL_VOTACAO_TEMPORARIO,
};

} // namespace comum
