#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/asn/util.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/igravador.h"
#include "app/comum/gravadores/md/cdadosbusa.h"
#include "app/comum/gravadores/md/cdadosbuvota.h"
#include "app/comum/gravadores/md/centidadebu.h"
#include "app/comum/gravadores/md/cresultadovotacaoporeleicao.h"
#include "app/comum/gravadores/md/ctipoapuracaosa.h"
#include "app/comum/gravadores/md/curna.h"
#include "app/comum/gravadores/md/cvotosvotavel.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/relatorios/cgeradorbuqrcode.h"
#include "ecourna/api/uetypes.hpp"
#include "ecourna/app/dados/cdetalhamentocomparecimento.hpp"

namespace comum {

class CRdv;

namespace md {
class CCargo;
}

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorBU), whose control block's __on_zero_shared is the shared call through the
// vtable (fn 172), so the class is not final. Recovered: the layout, 304 bytes (12098 allocates it with f137(304)), and
// the virtual members. The constructor is not written: 12098 holds it inlined, after IGravador's constructor (fn 1396,
// with the extension 4 and the SAVD file 35): it stores this vptr (@1554132 + 8), copies the api::CDateTime it also
// passes CGravadorEnvelopeArquivo's constructor to +40 and 12 more bytes to +52, stores ConverteFase(fase) at +64 and
// 49 at +68, copies a md::estadoaplicacao::CDadoCorrespondencia to +72 (fn 1249), moves a vector to +168 and a map to
// +180, stores a byte at +192, a 16-bit word at +194 and a word at +196, builds the string "bu.pk1" at +200, stores 1
// at +212, copies three 12-byte objects to +216 (44 bytes), +260 and +272, fills the map at +284 in a loop over
// comum::CCargos (a node of 16 bytes: the post's byte at +13 and a counter's byte at +14; that the counter is the post's
// order is a reading) and copies 8 bytes, 2-aligned, to +296. The destructor is not declared (implicit; one defined in
// the class was not measured): the base-object one (fn 5857, slot 0) stores this vptr, then destroys the map at +284
// (fn 3814), the string at +200, the map at +180 (fn 1405, the destroy of std::map<md::ETipoAbrangencia, SQtdeAptos>'s
// tree, the one cgeradorbuqrcode.h's map has), the strings of the vector at +168 and the vector, the correspondencia
// (fn 857), and holds IResultado's (its vptr, the string at +20); the deleting one (fn 11628, slot 1) frees what that
// one returns, the shape of a destructor whose base-object body is too large to inline (docs/how-to-decompile.md step
// 5). GravaResultado (slot 7, fn 11629, records cgravadorbu.cpp:484 and :485) is out of line, so it is the key function
// (cgravadorbu.cpp). LeChavePublica and MontaEntidadeBU are its two private members, whose records (cgravadorbu.cpp:542
// to :560 and :636) print them const members of this class; fn 11629 holds both, each behind a frame of its own.
// AcrescentaVotoVotavel (fn 3820) is in cgravadorbu.cpp: its record (cgravadorbu.cpp:221) prints it static and spells
// its parameter types, TVetorVotosVotaveis and TQtdEleitor among them. The vector's element is the 24-byte
// CVotosVotavel its push_back (fn 1944) copies. TQtdEleitor is a 16-bit count the body passes on unmasked to
// CVotosVotavel's constructors, which take a ueword: as ueword it gives the target's rows, and as ecourna's CBaseType
// the count is masked where the target's is not (src/units/200-uenux2-cgravadorbu.mk); the spelling ueword is chosen.
// That the aliases are the class's and the member public (cgravadorbu.cpp's helpers, free functions, call it) is
// chosen, and so is the forward declaration of md::CCargo.
// Evidence for the types, from fn 11629 unless said: +40 is the api::CDateTime of the BU's header (md::CCabecalhoEntidade's
// constructor, fn 1945, takes its address; fn 12098 passes the same object to CGravadorEnvelopeArquivo's constructor),
// +52 the entity's 12-byte issue date-time; +64 the envelope's and the entity's EUrnaFase; +68 the ETipoArquivo of
// md::CUrna's constructors (fns 2855 and 2854; 49 is TIPO_ARQUIVO_VOTACAO_UE, as in cgravadorrdv.h); +72 the
// correspondence (the load's and the section's fields that CGravadorRDV's and IGravadorEnvelope's reads read too, and
// its copy constructor's call in 12098); +168 the std::vector<std::string> that becomes the entity's history of load
// codes (MontaEntidadeBU's fourth parameter); +180 the map from the election's abrangencia to its voters (map::at over
// a node key compared signed and a 4-byte value read 2-aligned, md::CResultadoVotacaoPorEleicao's +4; +180's tree
// destroy); +192 a bool that picks the entity's constructor with the attendance detail at +296 (tested `== 1`, as the
// optionals' flags are); +194 the entity's 16-bit attendance; +196 a pointer to the CRdv whose slot 10 gives each post's
// attendance (and which fn 3819 reads); +212 a bool that, with the configuration's CParametrosUrna::GetCriptografarBU,
// decides whether the BU is encrypted; +216, +260 and +272 a std::optional<md::CDadosBUVota> (engaged at +256), a
// std::optional<md::CTipoApuracaoSA> (engaged at +268, handed to the md::CUrna constructor that takes one, as in
// cgravadorrdv.h) and a std::optional<md::CDadosBUSA> (engaged at +280), whose values MontaEntidadeBU copies into the
// entity when engaged; +284's node and its unsigned compare of the post (md::TCargoID is a byte); +296 the 6-byte
// attendance detail copied into the entity, an optional of 8 bytes by 12098's 2-aligned copy. Chosen: +192 and +212
// as bool and +194 as ueword (the plainest types of their widths and uses), +196 as a pointer to a const CRdv (a
// reference compiles the same), the byte value of +284's map, +296 as a std::optional (fn 11629 never tests its flag),
// and every member name. The string at +200 (built "bu.pk1" by 12098) has no reader here: LeChavePublica builds its
// path from the literal.
class CGravadorBU : public IGravador {
public:
    using TVetorVotosVotaveis = std::vector<md::CVotosVotavel>;
    using TQtdEleitor = ueword;

    virtual void GravaResultado(api::CFile& arquivo) const override;

    static void AcrescentaVotoVotavel(TVetorVotosVotaveis& votos, md::CVoto::ETipo tipo, TCandidatoID candidato,
        TQtdEleitor quantidade, const md::CCargo& cargo);

private:
    std::vector<uebyte> LeChavePublica() const;
    md::CEntidadeBU MontaEntidadeBU(const md::CCabecalhoEntidade& cabecalho, const md::CUrna& urna,
        const std::vector<md::CResultadoVotacaoPorEleicao>& resultados,
        const std::vector<std::string>& historicoCodigosCarga) const;

    api::CDateTime m_dataHora;
    api::CDateTime m_dataHoraEmissao;
    EUrnaFase m_faseUrna;
    ETipoArquivo m_tipoArquivo;
    md::estadoaplicacao::CDadoCorrespondencia m_correspondencia;
    std::vector<std::string> m_historicoCodigosCarga;
    std::map<md::ETipoAbrangencia, SQtdeAptos> m_qtdAptos;
    bool m_temDetalhamento;
    ueword m_qtdEleitoresCompareceram;
    const CRdv* m_rdv;
    std::string m_arquivoChave;
    bool m_criptografa;
    std::optional<md::CDadosBUVota> m_dadosVota;
    std::optional<md::CTipoApuracaoSA> m_tipoApuracao;
    std::optional<md::CDadosBUSA> m_dadosSA;
    std::map<md::TCargoID, uebyte> m_ordemCargos;
    std::optional<ecourna::app::dados::CDetalhamentoComparecimento> m_detalhamento;
};

} // namespace comum
