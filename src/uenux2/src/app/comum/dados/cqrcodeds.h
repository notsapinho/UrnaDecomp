#pragma once

#include <string>
#include <utility>
#include <vector>

namespace comum {

namespace md {
class CPleito;
} // namespace md

// Reconstruction notes, not TSE's text. comum::CQRCodeDS: RTTI names it (typeinfo 1538388, a class with no base and no
// vtable), the callable that std::function<std::string()>'s __func<comum::CQRCodeDS> (vtable 1538324) holds; that
// __func's slot 6 (fn 12553) calls fn 5782, the call operator, and its clones (fns 12555, 12556) copy the object with
// fn 1300, std::vector's copy constructor. Recovered: the 12-byte layout, one std::vector of key and value pairs, and
// the members the target calls. Fns 11200 (comum::CRelatorioTesteImpressora's slot 5) and 3059 (a screen's builder)
// build one from the vector CEstadoGeral::GetDadosQRCode (fn 5636) returns, through fn 1300, and call fn 5783 on it,
// which adds the tag "ORIG", "T" for 0 and "I" for 1 and nothing for another value: 11200 passes 1, and 3059's callers
// (6592, 6595, 7787) hand it 0 or 2. The constructor is out of line in cqrcodeds.cpp, a thunk over fn 1300 that
// binaryen inlines into its callers: defined in the class instead, clang inlines the vector's copy into 11200, where
// the target calls 1300 (wasm-objdump -d of crelatoriotesteimpressora.cpp.o). Chosen: every name but the class's and
// operator()'s (SetOrigem from the tag, the enumerators from its two letters, MontaConteudo from what it returns), the
// alias, explicit, the const of operator() and of MontaConteudo, that MontaConteudo is a private member and takes the
// pleito, and that no enumerator is declared for 2.
class CQRCodeDS {
public:
    enum EOrigem {
        eOrigemTela,
        eOrigemImpressora,
    };

    using TTags = std::vector<std::pair<std::string, std::string>>;

    explicit CQRCodeDS(const TTags& tags);

    void SetOrigem(EOrigem origem);
    std::string operator()() const;

private:
    std::string MontaConteudo(const md::CPleito& pleito) const;

    TTags m_tags;
};

} // namespace comum
