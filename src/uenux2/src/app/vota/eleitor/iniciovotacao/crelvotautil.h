#pragma once

// vota::CRelVotaUtil: the name of the class and of CortaPapel comes from the RTTI of the lambda CortaPapel builds
// (vota::CRelVotaUtil::CortaPapel()::$_0, typeinfo 1543288; its std::function's vtable @1543232 is stored by fn 2882,
// which is CortaPapel), and the lambda RTTI of CriaCabecalho (fn 5977, not written) names the second member. A class of
// static members, as comum::CRelUtil is (its records read `static`), is chosen: the mangled name does not tell a class
// from a namespace, and CortaPapel takes no object (fn 2882 is ()->()). This header's path and the file's are chosen:
// src/units/246-uenux2-crelvotautil.mk says why.

namespace vota {

class CRelVotaUtil {
public:
    static void CortaPapel();
};

} // namespace vota
