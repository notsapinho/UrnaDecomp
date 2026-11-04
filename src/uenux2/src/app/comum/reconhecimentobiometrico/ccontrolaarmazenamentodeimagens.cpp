// comum::CControlaArmazenamentoDeImagens (/home/rubio/tse/uenux2/src/app/comum/reconhecimentobiometrico/
// ccontrolaarmazenamentodeimagens.cpp): target fn 2725 and the static functions it holds. This header comment and the
// layout of the lines without a record are the reconstruction's; src/units/293-uenux2-ccontrolaarmazenamentodeimagens.mk
// says what each part rests on.
#include "app/comum/reconhecimentobiometrico/ccontrolaarmazenamentodeimagens.h"

#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include <sys/statfs.h>
#include <sys/time.h>

#include "api/hwil/ikernelhsm.h"
#include "api/hwil/iurna.h"
#include "api/io/cfile.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "api/util/cdatetime.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/clocal.h"
#include "app/comum/gravadores/asn/cconversorenvelopegenerico.h"
#include "app/comum/gravadores/md/cenvelopegenerico.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/cseguranca.h"
#include "app/comum/reconhecimentobiometrico/euecomumreconhecimentobiometricoerror.h"
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"
#include "asn1/modules/ModuloEnvelopeChave.h"
#include "ecourna/api/io/asn/serialization.hpp"
#include "ecourna/api/security/cepesc/ccepesccipher.hpp"
#include "ecourna/api/security/cepesc/cplaintext.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"
#include "ecourna/api/security/irng.hpp"
#include "ecourna/api/security/isymmetriccipher.hpp"

namespace comum {

// (original lines 44-67: content not recovered)
#line 68
std::tuple<uint32_t, std::string, std::string> CControlaArmazenamentoDeImagens::GerarCaminhosUnicos(
    const std::string& prefixo, const std::string& diretorio, const std::string& diretorioExterno)
{
    std::string caminho;
    std::string caminhoExterno;
    auto& rand = api::CPolySingleton<ecourna::api::security::IRng>::instance();
    uint32_t id;
    do {
        id = rand.GetInt() % ID_INVALIDO;
        const std::string nome = std::format("{}{:06}.wsq", prefixo, id);
        caminho = std::format("{}{}", diretorio, nome);
        caminhoExterno = std::format("{}{}", diretorioExterno, nome);
    } while (api::CSystem::ExistFile(caminho));
    return {id, caminho, caminhoExterno};
}

// (original lines 84-112: content not recovered)
#line 113
std::vector<uebyte> CControlaArmazenamentoDeImagens::LeChavePublica()
{
    const std::filesystem::path arquivo = std::format("{}{}", CPath::GetPathChave().c_str(), "wsq.pk1");
    if (!api::CSystem::ExistFile(arquivo)) {
        throw CUeComumReconhecimentoBiometricoError(EUE_COMUM_RECONHECIMENTO_BIOMETRICO_ARQUIVO_NAO_EXISTE,
                                                    "O arquivo " + arquivo.string() + " não existe");
    }

    ModuloEnvelopeChave::EntidadeChave entidade;
    ecourna::api::io::DeserializeFromFile(entidade, arquivo);
    const std::vector<uebyte> chaveCifrada(entidade.get_chave().begin(), entidade.get_chave().end());

    ecourna::api::security::CSymmetricCipherFactory fabrica;

    const std::vector<uebyte> senhas = api::CPolySingleton<api::IKernelHSM>::instance().GetSenha();
    const std::string senha(senhas.begin(), senhas.end());
    const std::shared_ptr<ecourna::api::security::ISymmetricCipher> cifra = fabrica.Create(senha);

    std::vector<uebyte> chave;
    cifra->Decrypt(chaveCifrada, chave);

    if (chave.empty()) {
        throw CUeComumReconhecimentoBiometricoError(EUE_COMUM_RECONHECIMENTO_BIOMETRICO_ARQUIVO_VAZIO,
                                                    "O arquivo " + arquivo.string() + " está vazio");
    }
    return chave;
}

// (original lines 141-143: content not recovered)
#line 144
ecourna::api::cepesc::CCipheredOut CControlaArmazenamentoDeImagens::CifrarWsq(const std::vector<uebyte>& wsq)
{
    const CLocal& local = CLocal::GetInst();
    uebyte tabelaCriptografia[1024];

    auto& hardwareUrna = api::CPolySingleton<api::IUrna>::instance();
    hardwareUrna.Slot4(tabelaCriptografia);
    std::vector<uebyte> numeroAleatorio(32);
    auto& rand = api::CPolySingleton<ecourna::api::security::IRng>::instance();
    rand.Generate(numeroAleatorio);
    const std::vector<uebyte> chave = LeChavePublica();
    const ecourna::api::cepesc::CPlainText texto(local.GetZonaID(), local.GetSecaoID(),
        std::vector<uebyte>(tabelaCriptografia, tabelaCriptografia + sizeof(tabelaCriptografia)), numeroAleatorio, chave,
        wsq);
    const ecourna::api::cepesc::CCepescCipher cifrador;
    return cifrador.Encrypt(texto);
}

void CControlaArmazenamentoDeImagens::GravaEnvelope(const std::string& caminho,
    const ecourna::api::cepesc::CCipheredOut& cifrado)
{
    api::CFile arquivo(caminho, "w+b", ecourna::api::io::FM_NOATIME);
    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    const md::CCabecalhoEntidade cabecalho(api::CDateTime(configuracao.GetPleito().GetData(), api::CTime(0, 0, 0)),
        configuracao.GetPleito().GetID(), md::TIPO_CABECALHO_PLEITO);
    const EUrnaFase fase = CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase();
    const CLocal& local = CLocal::GetInst();
    const md::CEnvelopeGenerico envelope(cabecalho, fase, local.GetMunicipio(), local.GetZonaID(),
        local.TemSecao() ? std::optional<TLocalID>(local.GetLocalID()) : std::nullopt, local.GetSecaoID(),
        md::CEnvelopeGenerico::ENVELOPE_IMAGEM_BIOMETRIA, md::CSeguranca(0, 1, cifrado.GetChave()),
        cifrado.GetConteudo(), eUrnaVota);
    asn::GravaArquivo(arquivo, envelope);
}

void CControlaArmazenamentoDeImagens::GravaWsqCifrado(const std::string& caminho, const std::vector<uebyte>& wsq)
{
    const ecourna::api::cepesc::CCipheredOut cifrado = CifrarWsq(wsq);
    GravaEnvelope(caminho, cifrado);
}

void CControlaArmazenamentoDeImagens::ZeraDataHora(const std::string& caminho)
{
    const struct timeval tempos[2] = {};
    utimes(caminho.c_str(), tempos);
}

uint32_t CControlaArmazenamentoDeImagens::ArmazenaImagem(const std::vector<uebyte>& wsq, const std::string&,
    const std::string& diretorio, const std::string& diretorioExterno, const std::string& prefixo)
{
    struct statfs estado;
    if (statfs(CPath::GetPathDinamico(FLASH_EXTERNA).c_str(), &estado) == 0) {
        if (!(static_cast<double>(estado.f_bavail) * estado.f_bsize >= 5 * 1024 * 1024)) {
            return ID_INVALIDO;
        }
    }
    const auto [id, caminho, caminhoExterno] = GerarCaminhosUnicos(prefixo, diretorio, diretorioExterno);
    const std::vector<uebyte> dados = vota::CConversorWsq::GetInst().PreparaWsq(wsq);
    if (dados.empty()) {
        return ID_INVALIDO;
    }
    GravaWsqCifrado(caminho, dados);
    ZeraDataHora(caminho);
    api::CSystem::CopyFile(caminho, caminhoExterno, true, true);
    return id;
}

} // namespace comum
