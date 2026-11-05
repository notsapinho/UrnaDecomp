// Reconstruction: comum::asn::CConversorBiometriaEleitorCifrada's slot 3 (target fn 11419) and the two members it holds
// inlined by binaryen behind frames of their own, Decifra (no record) and LeChave (records at lines 91, 101 and 109),
// fragment 335. The records place LeChave's throws (line 91 and 109, column 15) and the singleton's call (line 101,
// column 40); every other line of this file is chosen. DoDesconverte first is measured (fragment 335); Decifra above
// LeChave is chosen: DoDesconverte, LeChave, Decifra compiles to the same object.
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitorcifrada.h"

#include <filesystem>
#include <memory>
#include <string>

#include "api/hwil/ikernelhsm.h"
#include "api/io/asn/cfileasn.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/asn/eleitor/cconversorbiometriaeleitor.h"
#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/eleitor/cparametro.h"
#include "asn1/modules/ModuloEnvelopeChave.h"
#include "ecourna/api/io/asn/serialization.hpp"
#include "ecourna/api/security/cepesc/ccepesccipher.hpp"
#include "ecourna/api/security/csymmetriccipherfactory.hpp"

namespace comum::asn {

CConversorBiometriaEleitorCifrada::TDado CConversorBiometriaEleitorCifrada::DoDesconverte(
    const TEntidade& entidade, const md::CParametro& parametro) const
{
    ModuloEleitores::BiometriaEleitor biometria;
    const std::vector<uebyte> chaveSessao(parametro.GetBiometria().begin(), parametro.GetBiometria().end());
    const std::vector<uebyte> conteudo = Decifra(entidade, parametro, chaveSessao);
    const std::vector<char> dados(conteudo.begin(), conteudo.end());
    biometria = api::CFileASN::DecodeObject<ModuloEleitores::BiometriaEleitor>(dados);
    CConversorBiometriaEleitor conversor;
    return conversor.Desconverte(biometria);
}

std::vector<uebyte> CConversorBiometriaEleitorCifrada::Decifra(const TEntidade& entidade, const md::CParametro& parametro,
                                                                 const std::vector<uebyte>& chaveSessao) const
{
    const std::vector<uebyte> conteudo(entidade.get_conteudo().begin(), entidade.get_conteudo().end());
    const std::vector<uebyte> chave = LeChave();
    const std::vector<uebyte> salt(entidade.get_salt().begin(), entidade.get_salt().end());
    const std::string& identificador = parametro.GetIdentidade().GetIdentificador();
    const std::vector<uebyte> idEleitor(identificador.begin(), identificador.end());
    const ecourna::api::cepesc::CInfoSalt infoSalt(salt, idEleitor);
    const ecourna::api::cepesc::CCipheredIn entrada(0, 1, 0, chaveSessao, chave, conteudo, infoSalt);
    const ecourna::api::cepesc::CCepescCipher cepesc;
    return cepesc.Decrypt(entrada);
}

// (original lines 53-84: content not recovered)
#line 85
std::vector<uebyte> CConversorBiometriaEleitorCifrada::LeChave() const
{
    const std::filesystem::path arquivo = CPath::GetPathChave() / "bio.sk1";


    if (!api::CSystem::ExistFile(arquivo)) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7894, "O arquivo " + arquivo.string() + " não existe");
    }

    ModuloEnvelopeChave::EntidadeChave entidade;
    ecourna::api::io::DeserializeFromFile(entidade, arquivo);
    const std::vector<uebyte> chaveCifrada(entidade.get_chave().begin(), entidade.get_chave().end());


    ecourna::api::security::CSymmetricCipherFactory fabrica;

    std::vector<uebyte> senhaArquivo = api::CPolySingleton<api::IKernelHSM>::instance().GetSenha();
    const std::string senha(senhaArquivo.begin(), senhaArquivo.end());
    const std::shared_ptr<ecourna::api::security::ISymmetricCipher> cifrador = fabrica.Create(senha);
    std::vector<uebyte> chave;
    cifrador->Decrypt(chaveCifrada, chave);


    if (chave.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7895, "O arquivo " + arquivo.string() + " está vazio");
    }
    return chave;
}

} // namespace comum::asn
