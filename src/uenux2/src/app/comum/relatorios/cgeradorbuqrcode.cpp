// comum::CGeradorBUQRCode (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbuqrcode.cpp). This comment is the
// reconstruction's. The file's records are GetQtdAptos's (line 80, held by fn 3696, which binaryen inlined it into) and
// RetornaBlocoAssinado's (line 405, held by fn 5604: the default argument of CPolySingleton<IPkcs11>::instance()).
// Written here: the destructor (its D2 is fn 2251), GetQtdAptos, with its throw on its record's line, GetCamposAptos,
// fn 3696, GetCamposVotos, fn 5606, and Gera, fn 5604, with the functions binaryen inlined into it (each has one caller
// and a stack frame of its own in 5604): GetCabecalho, GetCorpo and the fields it gathers per post, DivideEmBlocos,
// MontaPartes, CalculaHash and RetornaBlocoAssinado. Only RetornaBlocoAssinado has a record; the other names and lines
// are chosen (src/units/155-uenux2-cgeradorbuqrcode.mk).
#include "app/comum/relatorios/cgeradorbuqrcode.h"

#include <algorithm>
#include <cctype>
#include <format>
#include <utility>

#include "api/gui/capplication.h"
#include "api/pattern/cpolysingleton.h"
#include "api/pkcs11/ipkcs11.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "ecourna/api/security/csha.hpp"
#include "ecourna/api/util/cstringutils.hpp"

// GetCorpo prints a post's type through a handle on table slot 2954 (target fn 536, the body every comum::SFormatoEnum
// instance shares): the formatter is chosen to be that one, and its place here.
template <>
struct std::formatter<comum::md::CCargo::ETipo> : comum::SFormatoEnum {};

namespace comum {

CGeradorBUQRCode::CGeradorBUQRCode(const CCabecalhoQRCodeBuilder& cabecalho, const CRdv& rdv,
                                   std::map<md::ETipoAbrangencia, SQtdeAptos> qtdAptos)
    : m_cabecalho(cabecalho), m_rdv(rdv), m_qtdAptos(std::move(qtdAptos))
{
}

CGeradorBUQRCode::~CGeradorBUQRCode() = default;

// (original lines 45-76: content not recovered)
#line 77
const SQtdeAptos& CGeradorBUQRCode::GetQtdAptos(md::ETipoAbrangencia abrangencia) const
{
    if (m_qtdAptos.find(abrangencia) == m_qtdAptos.end()) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9065, std::format("Abrangência não encontrada: {}", static_cast<int>(abrangencia)));
    }
    return m_qtdAptos.at(abrangencia);
}

std::string CGeradorBUQRCode::GetCamposAptos() const
{
    const SQtdeAptos& aptos = GetQtdAptos(CCargos::GetInst().GetCurrent().GetAbrangencia());
    std::string campos;
    campos += std::format("APTA:{} ", static_cast<ueword>(aptos.m_qtdeAptosDaSecao + aptos.m_qtdeAptosTTE));
    campos += std::format("APTS:{} ", aptos.m_qtdeAptosDaSecao);
    campos += std::format("APTT:{} ", aptos.m_qtdeAptosTTE);
    return campos;
}

std::string CGeradorBUQRCode::GetCamposVotos() const
{
    const md::TCargoID cargo = CCargos::GetInst().GetCurrent().GetID();
    const md::TQtdVoto nominais = m_rdv.Nominais(cargo);
    const md::TQtdVoto brancos = m_rdv.Brancos(cargo);
    const md::TQtdVoto nulos = m_rdv.Nulos(cargo);
    const md::TQtdVoto total = m_rdv.Cargo(cargo);
    std::string campos = GetCamposAptos();
    campos += std::format("NOMI:{} ", nominais);
    campos += std::format("BRAN:{} ", brancos);
    campos += std::format("NULO:{} ", nulos);
    campos += std::format("TOTC:{} ", total);
    return campos;
}


std::string CGeradorBUQRCode::GetCabecalho() const
{
    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    const CLocal& local = CLocal::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    CCabecalhoQRCodeBuilder cabecalho(m_cabecalho);
    if (configuracao.GetOrigem() == md::ORIGEM_COMUNITARIA) {
        cabecalho.DefineOrigemProcessoEleitoralCOM();
    } else {
        cabecalho.DefineOrigemProcessoEleitoralLEG();
    }
    cabecalho.DefineProcessoEleitoral(configuracao.GetProcessoEleitoral());
    cabecalho.DefineDataPleito(configuracao.GetPleito().GetData());
    cabecalho.DefinePleito(configuracao.GetPleito().GetID());
    cabecalho.DefineTurno(geral.GetDadoCarga().GetTurno());
    cabecalho.DefineFase(geral.GetDadoCarga().GetFaseChar());
    cabecalho.DefineUF(local.GetUF());
    cabecalho.DefineVersaoSoftware("10.23.0.1 - DESENVOLVIMENTO");
    Slot2(cabecalho);
    return cabecalho.build();
}

std::string CGeradorBUQRCode::GetCamposEleicao() const
{
    const TEleicaoID eleicao = CCargos::GetInst().GetCurrentEleicaoID();
    std::string campos = std::format("IDEL:{} ", eleicao);
    campos += Slot3(eleicao);
    return campos;
}

std::string CGeradorBUQRCode::GetCamposSecao() const
{
    const md::TCargoID cargo = CCargos::GetInst().GetCurrent().GetID();
    const md::TQtdVoto votos = m_rdv.Cargo(cargo);
    std::string campos = GetCamposAptos();
    campos += std::format("CSEC:{} ", votos);
    return campos;
}

std::string CGeradorBUQRCode::GetCamposCandidatosPartido(const std::vector<TCandidatoID>& candidatos) const
{
    const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
    const md::TCargoID idCargo = cargo.GetID();
    const uebyte numeroDigitos = cargo.GetNumeroDigitos();
    CCandidaturas& candidaturas = CCandidaturas::GetInst();
    std::string campos;
    for (const TCandidatoID numero : candidatos) {
        const md::CCandidatura* candidatura = candidaturas.Busca(idCargo, numero);
        const md::TQtdVoto votos = m_rdv.Candidato(idCargo, candidatura->GetCandidatoID(), numeroDigitos);
        if (votos != 0) {
            campos += std::format("{}:{} ", candidatura->GetCandidatoID(), votos);
        }
    }
    return campos;
}

std::string CGeradorBUQRCode::GetCamposLegenda() const
{
    const md::TCargoID cargo = CCargos::GetInst().GetCurrent().GetID();
    const TPartidoID partido = CPartidos::GetInst().GetCurrent()->GetNumero();
    const md::TQtdVoto legenda = m_rdv.Legenda(cargo, partido);
    const md::TQtdVoto total = m_rdv.Partido(cargo, partido);
    std::string campos;
    campos += std::format("LEGP:{} ", legenda);
    campos += std::format("TOTP:{} ", total);
    return campos;
}

std::string CGeradorBUQRCode::GetCamposVotosProporcional() const
{
    const md::TCargoID cargo = CCargos::GetInst().GetCurrent().GetID();
    const md::TQtdVoto nominais = m_rdv.Nominais(cargo);
    const md::TQtdVoto legendas = m_rdv.Legendas(cargo);
    const md::TQtdVoto brancos = m_rdv.Brancos(cargo);
    const md::TQtdVoto nulos = m_rdv.Nulos(cargo);
    const md::TQtdVoto total = m_rdv.Cargo(cargo);
    std::string campos = GetCamposAptos();
    campos += std::format("NOMI:{} ", nominais);
    campos += std::format("LEGC:{} ", legendas);
    campos += std::format("BRAN:{} ", brancos);
    campos += std::format("NULO:{} ", nulos);
    campos += std::format("TOTC:{} ", total);
    return campos;
}

std::string CGeradorBUQRCode::GetCamposProporcional() const
{
    const md::TCargoID cargo = CCargos::GetInst().GetCurrent().GetID();
    CPartidos& partidos = CPartidos::GetInst();
    const CCandidaturas& candidaturas = CCandidaturas::GetInst();
    std::string campos;
    for (partidos.Reset(); !partidos.IsFim(); partidos.Next()) {
        const TPartidoID partido = partidos.GetCurrent()->GetNumero();
        if (m_rdv.Partido(cargo, partido) != 0) {
            campos += std::format("PART:{} ", partido);
            campos += GetCamposCandidatosPartido(candidaturas.GetCandidatosPartido(cargo, partido));
            campos += GetCamposLegenda();
        }
    }
    return campos + GetCamposVotosProporcional();
}

std::string CGeradorBUQRCode::GetCamposMajoritario() const
{
    const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
    const md::TCargoID idCargo = cargo.GetID();
    const uebyte numeroDigitos = cargo.GetNumeroDigitos();
    CCandidaturas& candidaturas = CCandidaturas::GetInst();
    std::string campos;
    for (candidaturas.Reset(); !candidaturas.IsFim(); candidaturas.Next()) {
        const md::CCandidatura* candidatura = candidaturas.GetCurrent();
        if (candidatura->GetCargoID() == idCargo) {
            const TCandidatoID numero = candidatura->GetCandidatoID();
            const md::TQtdVoto votos = m_rdv.Candidato(idCargo, numero, numeroDigitos);
            if (votos != 0) {
                campos += std::format("{}:{} ", numero, votos);
            }
        }
    }
    return campos + GetCamposVotos();
}

std::string CGeradorBUQRCode::GetCamposConsulta() const
{
    const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
    const md::TCargoID idCargo = cargo.GetID();
    const uebyte numeroDigitos = cargo.GetNumeroDigitos();
    md::TVectorRespostaConsulta respostas = cargo.GetDetalheConsulta().GetRespostas();
    std::sort(respostas.begin(), respostas.end(), [](const md::CRespostaConsulta& a, const md::CRespostaConsulta& b) {
        return a.GetNumero() < b.GetNumero();
    });
    std::string campos;
    for (const md::CRespostaConsulta& resposta : respostas) {
        const auto numero = resposta.GetNumero();
        const md::TQtdVoto votos = m_rdv.Candidato(idCargo, numero, numeroDigitos);
        if (votos != 0) {
            campos += std::format("{}:{} ", numero, votos);
        }
    }
    return campos + GetCamposVotos();
}

std::string CGeradorBUQRCode::GetCorpo() const
{
    CCargos& cargos = CCargos::GetInst();
    CCandidaturas& candidaturas = CCandidaturas::GetInst();
    cargos.OrdenaPorImpressao();
    std::string corpo;
    TEleicaoID eleicaoAnterior = 0;
    for (cargos.Reset(); !cargos.IsFim(); cargos.Next()) {
        const TEleicaoID eleicao = cargos.GetCurrentEleicao().GetID();
        if (eleicao != eleicaoAnterior) {
            corpo += GetCamposEleicao();
            eleicaoAnterior = eleicao;
        }
        const md::CCargo& cargo = cargos.GetCurrent();
        const std::vector<TCandidatoID> candidatos = candidaturas.GetCandidatos(cargo.GetID());
        corpo += std::format("CARG:{} ", cargo.GetID());
        corpo += std::format("TIPO:{} ", cargo.GetTipo());
        if (candidatos.size() == 0 && cargo.HasDetalheCandidato()) {
            const std::string versao = candidaturas.RecuperaVersaoPacote(cargo.GetID());
            corpo += std::format("VERC:{} ", versao);
            corpo += GetCamposSecao();
            continue;
        }
        if (cargo.HasDetalheCandidato()) {
            const std::string versao = candidaturas.RecuperaVersaoPacote(cargo.GetID());
            corpo += std::format("VERC:{} ", versao);
        }
        if (cargo.IsConsulta()) {
            const std::string versao = cargos.GetCurrentEleicaoVersaoPacote();
            corpo += std::format("VERC:{} ", versao);
        }
        if (cargo.IsProporcional()) {
            corpo += GetCamposProporcional();
        } else if (cargo.IsMajoritario()) {
            corpo += GetCamposMajoritario();
        } else {
            corpo += GetCamposConsulta();
        }
    }
    return corpo;
}

std::vector<std::string> DivideEmBlocos(const std::string& conteudo, std::size_t tamanhoMaximo)
{
    const std::size_t tamanhoBloco = tamanhoMaximo - 277;
    std::vector<std::string> blocos;
    const std::size_t tamanhoTotal = conteudo.size();
    for (std::size_t posicao = 0; posicao != tamanhoTotal;) {
        std::string bloco = conteudo.substr(posicao, tamanhoBloco);
        std::size_t tamanho = bloco.size();
        if (tamanho >= tamanhoBloco && bloco.back() != ' ') {
            tamanho = bloco.rfind(' ');
            bloco = conteudo.substr(posicao, tamanho);
        }
        blocos.push_back(ecourna::api::util::CStringUtils::Trim(std::as_const(bloco)));
        posicao += tamanho;
    }
    return blocos;
}

std::string CalculaHash(const std::string& conteudo)
{
    ecourna::api::security::CSha512 sha;
    sha.Reset();
    for (std::size_t posicao = 0; posicao < conteudo.size(); posicao += 512) {
        sha.Update(std::vector<uebyte>(conteudo.begin() + posicao,
                                       conteudo.begin() + std::min(conteudo.size(), posicao + 512)));
    }
    return ecourna::api::util::CStringUtils::BytesToHexString(sha.Finish());
}

// (original lines 324-401: content not recovered)
#line 402
std::string CGeradorBUQRCode::RetornaBlocoAssinado(const std::string& hash) const
{
    const std::vector<uebyte> dados = ecourna::api::util::CStringUtils::HexStringToBytes(hash);
    auto& oPkcs11 = api::CPolySingleton<api::pkcs11::IPkcs11>::instance();
    oPkcs11.Slot23();
    const std::vector<uebyte> assinatura = oPkcs11.Assina(dados).GetAssinatura();
    oPkcs11.Slot24();
    return ecourna::api::util::CStringUtils::BytesToHexString(assinatura);
}

std::pair<std::vector<std::string>, std::string> CGeradorBUQRCode::MontaPartes(const std::vector<std::string>& blocos) const
{
    using namespace std::string_view_literals;
    const std::size_t total = blocos.size();
    std::vector<std::string> partes;
    std::vector<std::string> blocosComHash;
    std::string assinatura;
    for (std::size_t indice = 0; indice < total; ++indice) {
        std::string conteudo;
        if (indice > 0) {
            const std::string anteriores = api::Join(blocosComHash, " ");
            conteudo = std::format("{} {}", anteriores, blocos.at(indice));
        } else {
            conteudo = blocos.at(indice);
        }
        const std::string hash = CalculaHash(conteudo);
        blocosComHash.push_back(std::format("{} HASH:{}", blocos.at(indice), hash));
        std::string parte = std::format("QRBU:{}:{} VRQR:{} {}", indice + 1, total, "6.0"sv, blocosComHash.at(indice));
        if (indice == total - 1) {
            assinatura = RetornaBlocoAssinado(hash);
            parte += std::format(" ASSI:{}", assinatura);
        }
        partes.push_back(parte);
    }
    return {partes, assinatura};
}

std::pair<std::vector<std::string>, std::string> CGeradorBUQRCode::Gera(std::size_t tamanhoMaximo) const
{
    const std::string conteudo = GetCabecalho() + GetCorpo();
    const std::vector<std::string> blocos = DivideEmBlocos(conteudo, tamanhoMaximo);
    return MontaPartes(blocos);
}

} // namespace comum
