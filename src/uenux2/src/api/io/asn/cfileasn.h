// The reconstruction's notes. The records name four static members of api::CFileASN, each a member template over
// the ASN.1 entity it reads or writes (they print "[T = ...]"): ReadFromFile(const CFile &) at lines 48 and 60,
// ReadFromFile(const std::string &) at 78, DecodeObjectFunction(const std::vector<char> &, const std::string &) at
// 135 and 143, and CodeObjectFunction(std::vector<char> &, const T &, const std::string &) at 161 and 171. Only
// CodeObjectFunction is written, from target fn 2927, binaryen's merge of its instances for the four ESTADO GERAL
// entities, whose thunks 9801, 9702, 9695 and 9673 pass each instance's two records; the other members' record lines
// are left blank. src/units/229-asn1-coderenv.mk has the evidence. Chosen: that CFileASN is a class, the lines of
// every statement but the two throws, and the names of the locals.
#pragma once

#include <format>
#include <sstream>
#include <string>
#include <vector>

#include "api/io/eueioerror.h"
#include "asn1/asn1.h"

namespace api {

class CFileASN {
public:

    // (original lines 24-154: content not recovered)
#line 155
    template <typename T>
    static void CodeObjectFunction(std::vector<char>& buffer, const T& objeto, const std::string& nome)
    {
        if (!objeto.isValid()) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, "", objeto);
            throw CUeIoError(EUE_IO_OBJETO_INVALIDO, std::format("Objeto com conteúdo inválido para {}: {}", nome, erro.str()));
        }

        ASN1::CoderEnv env;
        env.set_ber();

        std::vector<char> codificado;
        const bool codificou = env.encode(objeto, std::back_inserter(codificado));

        if (!codificou) {
            throw CUeIoError(EUE_IO_OBJETO_NAO_CODIFICADO, "Arquivo não foi codificado para " + nome);
        }

        buffer.swap(codificado);
    }
};

} // namespace api

// <stubs>
// f5825 · 1308 B · unmatched · placement: link order · name unknown
// void f5825(i32, i32) { ... }

// f3791 · 3956 B · unmatched · placement: link order · name unknown
// void f3791(i32, i32) { ... }

// f5740 · 5775 B · unmatched · placement: link order · name unknown
// void f5740(i32) { ... }

// f5706 · 3258 B · unmatched · placement: link order · name unknown
// void f5706(i32, i32) { ... }

// f5778 · 10735 B · unmatched · placement: link order · name unknown
// void f5778(i32, i32, i32, i32, i32) { ... }

// f3735 · 3405 B · unmatched · placement: link order · name unknown
// void f3735(i32, i32) { ... }
// </stubs>
