// The anonymous-namespace helpers of /home/rubio/tse/uenux2/src/app/comum/nomearquivo/cnomearquivo.cpp, and the file's
// name builders. The helpers' throws are records of the target, so their positions in this file are fixed:
//   2828  FormataFase(EUrnaFase)                   record at line 38, column 19
//   1161  FormataNumero(uedword, uedword)          record at line 48, column 15
//   3773  FormataUF(const std::string &)           record at line 73, column 15
// and ajustaAbrangenciaUFMunicipio's at line 208, column 11, inlined into NomeArquivoAbrangencia, which fn 3744 holds.
// The builders have no record: their names and lines are chosen (src/units/131-uenux2-cnomearquivo.mk, fragment 388).

#include "app/comum/nomearquivo/cnomearquivo.h"

#include <format>

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/nomearquivo/euecomumnomearquivoerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

namespace {

// (original lines 21-27: content not recovered)
#line 28
std::string FormataFase(EUrnaFase fase)
{
    switch (fase) {
        case FASE_OFICIAL:
            return "o";
        case FASE_SIMULADO:
            return "s";
        case FASE_TREINAMENTO:
            return "t";
        default:
            throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_FASE_INVALIDA, std::format("Fase inválida: {}", fase));
    }
}

// (original lines 42-43: content not recovered)
#line 44
std::string FormataNumero(uedword numero, uedword casas)
{
    std::string texto = std::format("{:0{}}", numero, casas);
    if (texto.size() > casas) {
        throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_NUMERO_EXCEDE_CASAS,
            std::format("Número ultrapassou o tamanho máximo de {} casas em [{}]", casas, texto));
    }
    return texto;
}

// (original lines 54-69: content not recovered)
#line 70
std::string FormataUF(const std::string& uf)
{
    if (uf.size() != 2) {
        throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_UF_INVALIDA, std::format("UF inválida: [{}]", uf));
    }
    return ecourna::api::util::CStringUtils::ToLower(uf);
}

} // namespace

std::string NomeArquivoPE(EUrnaFase fase, uedword idPE, const std::string& tipo, const std::string& extensao)
{
    return FormataFase(fase) + FormataNumero(idPE, 5) + ("-" + tipo) + "." + extensao;
}

std::string CNomeArquivo::NomeArquivoUF(EUrnaFase fase, uedword pleito, const std::string& uf, const std::string& tipo,
    const std::string& extensao)
{
    return FormataFase(fase) + FormataNumero(pleito, 5) + FormataUF(uf) + ("-" + tipo) + "." + extensao;
}

std::string CNomeArquivo::NomeArquivoSecao(EUrnaFase fase, uedword pleito, const std::string& uf, uedword municipio,
    uedword zona, uedword secao, const std::string& tipo, const std::string& extensao)
{
    return FormataFase(fase) + FormataNumero(pleito, 5) + FormataUF(uf) + FormataNumero(municipio, 5) +
           FormataNumero(zona, 4) + FormataNumero(secao, 4) + ("-" + tipo) + "." + extensao;
}

std::string CNomeArquivo::NomeArquivoLocal(uedword municipio, uedword zona, uedword secao, const std::string& tipo,
    const std::string& extensao)
{
    return FormataNumero(municipio, 5) + FormataNumero(zona, 4) + FormataNumero(secao, 4) + ("-" + tipo) + "." + extensao;
}

// (original lines 104-192: content not recovered)
#line 193
namespace {

void ajustaAbrangenciaUFMunicipio(TMunicipioID& municipio, std::string& uf, const md::ETipoAbrangencia& abrangencia)
{
    switch (abrangencia) {
        case md::ABRANGENCIA_MUNICIPAL:
            return;
        case md::ABRANGENCIA_ESTADUAL:
            municipio = 0;
            return;
        case md::ABRANGENCIA_FEDERAL:
            municipio = 0;
            uf = "BR";
            return;
    }
    throw CUeComumNomeArquivoError(EUE_NOMEARQUIVO_ABRANGENCIA_INVALIDA,
        std::format("Abrangência inválida: {}", static_cast<int>(abrangencia)));
}

} // namespace

std::string CNomeArquivo::NomeArquivoAbrangencia(EUrnaFase fase, uedword idEleicao, const std::string& uf,
    TMunicipioID municipio, md::ETipoAbrangencia abrangencia, const std::string& tipo, const std::string& extensao)
{
    std::string ufArquivo = uf;
    ajustaAbrangenciaUFMunicipio(municipio, ufArquivo, abrangencia);
    return FormataFase(fase) + FormataNumero(idEleicao, 5) + FormataUF(ufArquivo) + FormataNumero(municipio, 5) +
           ("-" + tipo) + "." + extensao;
}

} // namespace comum
