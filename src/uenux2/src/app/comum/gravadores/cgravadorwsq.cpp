// comum::CGravadorWSQ (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorwsq.cpp). Records of the target fix
// three throws: ValidaTipoBiometria's (line 73, column 15), inlined by clang into the constructor (fn 3796), and those
// of GetCaminhoCorretoInternal (175:19) and GetCaminhoCorretoExternal (192:19), which binaryen inlines into CompactaWsq
// (fn 5821), each with its own stack frame. Column 19 puts each throw 12 spaces in; case labels indented under the
// switch are the form chosen for that. No other function of this file has a record: the constructor's line is a choice
// above the member it calls, and Slot2, Slot6 and Slot3 (fns 11579, 11578, 11577) and CompactaWsq follow it in the order
// the use bands give (11579, 11578 and 11577 run that way in band 1), at lines chosen. The WSQ directories the two
// GetCaminhoCorreto members list are pathwsq.cpp's (src/units/122-uenux2-app-comum-gravadores.mk says why).

#include "app/comum/gravadores/cgravadorwsq.h"

#include <format>

#include "api/util/csystem.h"
#include "app/comum/cpath.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/gravadores/pathwsq.h"
#include "ecourna/api/compression/czip.hpp"

namespace comum {

// (original lines 23-55: content not recovered)
#line 56
CGravadorWSQ::CGravadorWSQ(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd, ETipoBiometria tipoBiometria,
    bool gravaMidiaExterna)
    : IGravador(municipio, zona, local, secao, fase, extensao, arquivoSavd), m_dataHora(dataHora),
      m_faseUrna(CGravadorUtil::ConverteFase(fase)), m_arquivoChave("wsq.pk1"), m_tipoBiometria(tipoBiometria),
      m_versao("10.23.0.1 - DESENVOLVIMENTO"), m_gravaMidiaExterna(gravaMidiaExterna)
{
    ValidaTipoBiometria();
}

// (original lines 66-69: content not recovered)
#line 70
void CGravadorWSQ::ValidaTipoBiometria() const
{
    if (m_tipoBiometria >= 3) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8651, "Argumento tipo de biometria inválido.");
    }
}

void CGravadorWSQ::Slot2()
{
    const std::filesystem::path destino = CPath::GetPathResult(FLASH_INTERNA) / m_nomeArquivo;
    CompactaWsq(false, destino);
}

void CGravadorWSQ::Slot6()
{
    if (m_gravaMidiaExterna) {
        const std::filesystem::path destino = CPath::GetPathResult(FLASH_EXTERNA) / m_nomeArquivo;
        CompactaWsq(true, destino);
    }
}

void CGravadorWSQ::Slot3()
{
    if (m_gravaMidiaExterna) {
        const std::filesystem::path destino = CPath::GetPathResult(FLASH_EXTERNA) / m_nomeArquivo;
        CompactaWsq(false, destino);
    }
}

void CGravadorWSQ::CompactaWsq(bool midiaExterna, const std::string& arquivo) const
{
    const std::vector<std::string> caminhos = !midiaExterna ? GetCaminhoCorretoInternal() : GetCaminhoCorretoExternal();
    bool vazio = true;
    for (const std::string& caminho : caminhos) {
        if (!api::CSystem::ExistDir(caminho)) {
            api::CreateDir(caminho);
        }
        vazio = vazio && api::CSystem::IsEmptyDir(caminho);
    }
    if (vazio) {
        ecourna::api::compression::CZip zip(arquivo, ecourna::api::compression::ENivelCompressao::PADRAO);
        zip.Close();
    } else {
        ecourna::api::compression::CZip zip(arquivo, ecourna::api::compression::ENivelCompressao::NENHUM);
        for (const std::string& caminho : caminhos) {
            zip.Add(caminho + "*.wsq");
        }
        zip.Close();
    }
}

// (original lines 121-164: content not recovered)
#line 165
std::vector<std::string> CGravadorWSQ::GetCaminhoCorretoInternal() const
{
    switch (m_tipoBiometria) {
        case TIPO_BIOMETRIA_HABILITADO:
            return {GetPathWsqHabilitado().string()};
        case TIPO_BIOMETRIA_NAO_HABILITADO:
            return {GetPathWsqNaoHabilitado().string()};
        case TIPO_BIOMETRIA_OPERADOR:
            return {GetPathWsqOperador().string()};
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8652, std::format("Tipo de biometria inválido: {}", m_tipoBiometria));
    }
}

// (original lines 179-181: content not recovered)
#line 182
std::vector<std::string> CGravadorWSQ::GetCaminhoCorretoExternal() const
{
    switch (m_tipoBiometria) {
        case TIPO_BIOMETRIA_HABILITADO:
            return {GetPathWsqHabilitadoExterno().string()};
        case TIPO_BIOMETRIA_NAO_HABILITADO:
            return {GetPathWsqNaoHabilitadoExterno().string()};
        case TIPO_BIOMETRIA_OPERADOR:
            return {GetPathWsqOperadorExterno().string()};
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8653, std::format("Tipo de biometria inválido: {}", m_tipoBiometria));
    }
}

} // namespace comum
