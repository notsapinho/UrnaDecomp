#pragma once

#include <string>
#include <utility>
#include <vector>

#include "app/comum/dados/md/estadoaplicacao/cajustedatahora.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocarga.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/cdadolocal.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// The urna's state: the fields of ModuloEstadoGeralUrna::EstadoGeralUrna. The offsets come from the constructor (target
// fn 5637) and comum::asn::CConversorEstadoGeral::DoConverte (fn 11397), which reads the state from +0 (an EEstadoUrna,
// ConverteEstadoUrna's parameter in its record), idPE from +4, the locality from +8, the load from +32, the clock
// adjustment from +52, the correspondence from +60, the version from +156 and the packages' hash from +168. The layout
// is recovered, with the constructor and the getters the bodies read. The member and getter names follow the ASN.1
// fields; idPE is unsigned, the std::to_string(unsigned int) GetDadosQRCode (fn 5636) formats it with, and its width
// the bodies'. The locality's class is cdadolocal.h's, which has this layout.
class CEstadoGeral {
public:
    // Target fn 5637, out of line in cestadogeral.cpp: the state from its parts, each stored at its member's offset in
    // the parameters' order. Its one direct caller, comum::asn::CConversorEstadoGeral::DoDesconverte (fn 11398), passes
    // a copy of each part taken by value and its correspondence's local with no copy; the constructor moves the two
    // strings (the locality's and the version) and the hash, and copies the correspondence with CDadoCorrespondencia's
    // copy constructor (fn 1249). The by-value and reference forms are read from those copies and moves; `&&`
    // parameters with the copies spelled at the call were not measured. The parameter names are chosen.
    CEstadoGeral(EEstadoUrna estadoUrna, uedword idPE, CDadoLocal dadoLocal, CDadoCarga dadoCarga,
                 CAjusteDataHora ajusteDataHora, const CDadoCorrespondencia& correspondencia, std::string versao,
                 std::vector<uebyte> hashVersoesPacotes);

    EEstadoUrna GetEstadoUrna() const { return m_estadoUrna; }
    uedword GetIdPE() const { return m_idPE; }
    const CDadoLocal& GetDadoLocal() const { return m_dadoLocal; }
    const CDadoCarga& GetDadoCarga() const { return m_dadoCarga; }
    const CAjusteDataHora& GetAjusteDataHora() const { return m_ajusteDataHora; }
    const CDadoCorrespondencia& GetCorrespondencia() const { return m_correspondencia; }
    const std::string& GetVersao() const { return m_versao; }
    const std::vector<uebyte>& GetHashVersoesPacotes() const { return m_hashVersoesPacotes; }

    // Target fn 5636, out of line in cestadogeral.cpp: the state as key and value pairs, in this order, PROC (idPE),
    // TURN (1 or 2, but for an urna of type eUrnaContingencia or eUrnaContingenciaVotaRecupera in its turn), FASE (the
    // load's phase letter in upper case), UNFE, MUNI, ZONA, SECA (only for eUrnaVota and eUrnaContingenciaVota), IDUE,
    // MDUE, IDFL, IDCA, DTCA and HRCA (the load's date and time), NOME, SERT, SERI (the media generator) and ASSI (the
    // signature in hex). Its target callers, fns 11200 (comum::CRelatorioTesteImpressora's slot 5) and 3059, pass the
    // state comum::CAppInfo::GetGeral returns and build a comum::CQRCodeDS of the result. The name and its being a
    // member (it reads the members above) are chosen.
    std::vector<std::pair<std::string, std::string>> GetDadosQRCode() const;

    // Target fn 5635, out of line in cestadogeral.cpp, its record's name (static, std::vector<uebyte> by value, record
    // cestadogeral.cpp:147, the default argument of CPolySingleton<api::pkcs11::IPkcs11>::instance()): the certificate,
    // read through api::pkcs11::IPkcs11 the first time (slots 23, 10 and 24) and kept in a static vector (@1839076),
    // which only 5635 and its exit destructor, fn 11268, load (/usr/bin/grep -rlE 'i32\.const 1839076($|[^0-9])'
    // build/out/splat/pieces/asm prints the two); 5635 has no guard, so the static is no function-local one. Its name
    // s_certificado, its being a member and its access are chosen.
    static std::vector<uebyte> RecuperarCertificado();
    // Target fn 5634, out of line, after 5635 in cestadogeral.cpp (use band 2 puts it right after 5635 and before
    // cdadocarga.cpp's 5633; the file, 5635's, which it calls twice, is chosen): the certificate as QR code fields, one
    // list per part, each QRCE (the part's number from 1 and the count, "{}:{}", two unsigned), ISUE (the
    // correspondence's internal number, +60), MSUE (the load's model, +44) and CERT (the part's slice of the
    // certificate's hex text); with the bool set the count is twice the certificate's byte count over 1082, rounded up
    // in float arithmetic, else 1. Its callers are fn 12110 (vota::CGeraBU's slot 2, with true and the state
    // comum::CAppInfo::LeGeralInterno returns), not written, and fn 12039 (a callback in cmostraqrcodecertificado.cpp,
    // whose table slot fn 12040 stores; with false and CAppInfo::GetGeral's), written (unit 387). The name, the bool
    // and its being a member (it reads the members above) are chosen.
    std::vector<std::vector<std::pair<std::string, std::string>>> GetDadosQRCodeCertificado(bool dividido) const;

    // Target fn 3705, out of line in cestadogeral.cpp: its callers (7160, 7306, 10710) read the +52 adjustment inline,
    // change it with CAjusteDataHora::AdicionaDeltaT (fn 3702) and store it back through this call. The name is chosen:
    // no record, slot or RTTI names it.
    void SetAjusteDataHora(const CAjusteDataHora& ajusteDataHora);
    // Target fn 3703, out of line in cestadogeral.cpp: the first 8 characters of the packages' hash (+168) in base64,
    // ecourna::api::security::EncodeBase64 held inlined by binaryen (its records base64.cpp:247 and :267). Its target
    // callers are 3059, 7787 and 11222, which passes the state comum::CAppInfo::GetGeral returns and prints the result
    // after "Dados:" in the packages' versions report. The name and its being a member are chosen: no record, slot or
    // RTTI names it.
    std::string GetResumoHashVersoesPacotes() const;

private:
    static std::vector<uebyte> s_certificado;

    EEstadoUrna m_estadoUrna;
    uedword m_idPE;
    CDadoLocal m_dadoLocal;
    CDadoCarga m_dadoCarga;
    CAjusteDataHora m_ajusteDataHora;
    CDadoCorrespondencia m_correspondencia;
    std::string m_versao;
    std::vector<uebyte> m_hashVersoesPacotes;
};

} // namespace comum::md::estadoaplicacao
