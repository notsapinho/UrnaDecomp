#pragma once

// comum::CGeradorBUQRCode (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbuqrcode.cpp, its records' file; the
// header beside it is chosen) and comum::SQtdeAptos. Reconstruction notes, not TSE's text.
//
// RTTI gives CGeradorBUQRCode with no base, and its vtable (@1575912) has four slots: the D2 (fn 2251), 325 for the D0
// (an abstract class's) and two pure slots. No record or string names those two, so their names are chosen, Slot2 and
// Slot3 after their slots. Gera (fn 5604) calls both: slot 2 with this and its copy of the CCabecalhoQRCodeBuilder,
// whose fields the overrider (fn 11242, CGeradorBUQRCodeVota's) sets ("ORIG:{} " to "HREM:{} ", at the builder's +0 to
// +384), so it takes the builder by reference and returns nothing (no sret word comes before this); slot 3 with
// CCargos::GetCurrentEleicaoID's result, returning a std::string, so its parameter's type, TEleicaoID, is chosen.
//
// Recovered: the layout and the destructor. CGeradorBUQRCodeVota's constructor (fn 5603) holds this class's inlined: it
// copies a CCabecalhoQRCodeBuilder to +4 (fn 5608; 396 bytes), stores CRdvVota::GetInst()'s result (fn 555) at +400
// and moves to +404 the map that comum::CEleitores's slot 0 (fn 2824) returns, both computed before this class's vptr
// store, as arguments. The D2 (fn 2251) destroys the map's tree (fn 1405) and then the builder (fn 2885), the reverse
// of their offsets. GetQtdAptos (record cgeradorbuqrcode.cpp:80) looks the current post's coverage up in that map, and
// fn 3696 formats what it finds. The destructor is out of line, this class's key function: CGeradorBUQRCodeVota's D2
// (fn 11244) calls this D2, and with `virtual ~CGeradorBUQRCode() = default;` in the class clang inlines its body into
// that D2 (measured on cgeradorbuqrcodevota.cpp's object). The vtable (@1575912) lies in the run of this file's
// records, before line 80's. +400 is a reference to the base CRdv: GetCamposVotos (fn 5606) calls Nominais, Brancos,
// Nulos and Cargo through its vtable, where a reference to the final CRdvVota is called directly (src/units/155-*.mk
// has the measurement). The target's CRdvVota is final too: its D2 (fn 5734) first stores a member's vptr, not its
// own, and fn 11980 calls those four slots' CRdvVota bodies directly on CRdvVota::GetInst()'s result. Its being a
// reference, and every member's and the map's names, are chosen.
//
// Gera's helpers, each a stack frame of its own in fn 5604 (binaryen inlined each into its one caller), are members
// where they read the object (m_cabecalho, m_rdv, Slot2, Slot3) and free functions of cgeradorbuqrcode.cpp where they
// read nothing of it (DivideEmBlocos, CalculaHash); their names, Gera's, and the result's std::pair (a vector of the
// QR code's parts, which fn 1956 moves out, and the signature's hex, copied to +12) are chosen.
//
// SQtdeAptos: the map's mapped type. fn 2824 allocates its nodes with 24 bytes (a 16-byte node, the 4-byte key and 4
// bytes of value), zeroes the value and counts in the 16-bit words at +0 and +2 of it, and fn 3696 prints the first as
// "APTS:{} ", the second as "APTT:{} " and their sum as "APTA:{} ", so its members are named after those labels. Where it
// is declared is chosen: the lambdas of std::function<comum::SQtdeAptos()> (RTTI) return it too, and CEleitores's slot 0
// returns the map.

#include <cstddef>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "app/comum/asn/util.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/relatorios/ccabecalhoqrcodebuilder.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

class CRdv;

struct SQtdeAptos {
    ueword m_qtdeAptosDaSecao;
    ueword m_qtdeAptosTTE;
};

class CGeradorBUQRCode {
public:
    CGeradorBUQRCode(const CCabecalhoQRCodeBuilder& cabecalho, const CRdv& rdv,
                     std::map<md::ETipoAbrangencia, SQtdeAptos> qtdAptos);
    virtual ~CGeradorBUQRCode();

    std::pair<std::vector<std::string>, std::string> Gera(std::size_t tamanhoMaximo) const;

protected:
    virtual void Slot2(CCabecalhoQRCodeBuilder& cabecalho) const = 0;
    virtual std::string Slot3(TEleicaoID eleicao) const = 0;

    std::string GetCabecalho() const;
    std::string GetCorpo() const;
    std::string GetCamposEleicao() const;
    std::string GetCamposSecao() const;
    std::string GetCamposProporcional() const;
    std::string GetCamposCandidatosPartido(const std::vector<TCandidatoID>& candidatos) const;
    std::string GetCamposLegenda() const;
    std::string GetCamposVotosProporcional() const;
    std::string GetCamposMajoritario() const;
    std::string GetCamposConsulta() const;
    std::pair<std::vector<std::string>, std::string> MontaPartes(const std::vector<std::string>& blocos) const;
    std::string RetornaBlocoAssinado(const std::string& hash) const;

    std::string GetCamposAptos() const;
    std::string GetCamposVotos() const;
    const SQtdeAptos& GetQtdAptos(md::ETipoAbrangencia abrangencia) const;

    CCabecalhoQRCodeBuilder m_cabecalho;
    const CRdv& m_rdv;
    std::map<md::ETipoAbrangencia, SQtdeAptos> m_qtdAptos;
};

} // namespace comum
