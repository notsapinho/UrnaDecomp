// comum::CCalculaCV (/home/rubio/tse/uenux2/src/app/comum/relatorios/ccalculacv.cpp). This comment is the
// reconstruction's. The file's records are the constructor's (lines 58, 65 and 74, held by fn 12110, which inlines it)
// and IncluiString's (line 109, fns 942 and 5967). Written here: IncluiString, fn 942, its throw on its record's line;
// Reinicia (fn 5615) and the destructor (fn 5614); DestroyInst, which fn 3698 (comum::CGeradorBU's destructor) holds
// inlined by binaryen and which has no target function of its own; CalculaCodigo (fn 3700) and GeraMacHexa, which 3700
// holds inlined by binaryen. The constructor is not reconstructed, and its lines stay blank. The functions after the
// records have no record, and their names and lines are a choice, except one order: CalculaCodigo before GeraMacHexa,
// which src/units/121-uenux2-datasources.mk measures. src/units/139-uenux2-cgeradorbu.mk says what places DestroyInst in
// another TU than its caller.
#include "app/comum/relatorios/ccalculacv.h"

#include <format>
#include <typeinfo>

#include "api/pattern/cpolysingletonlist.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"
#include "ecourna/api/security/csiphashmac.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

// (original lines 22-105: content not recovered)
#line 106
void CCalculaCV::IncluiString(const std::string& str)
{
    if (str.empty()) {
        throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9054, "String vazia");
    }
    m_texto.append(str);
}

void CCalculaCV::Reinicia(const std::string& valor)
{
    m_texto = m_tipo;
    m_texto.append(m_identificacao);
    m_texto.append(valor);
    m_resultado = valor;
}





CCalculaCV::~CCalculaCV() = default;

void CCalculaCV::DestroyInst()
{
    api::TPolySingletonsInfo& info = api::g_polySingletonsInfo();
    api::CPolySingletonList::remove(typeid(CCalculaCV).name(), info);
}

std::string CCalculaCV::CalculaCodigo()
{
    ++m_contador;
    m_texto.append(std::to_string(m_contador));
    const std::string mac = GeraMacHexa(m_texto);
    const ueqword valor = ecourna::api::util::CStringUtils::HexToQWord(mac);
    Reinicia(std::to_string(valor));
    return std::format("{:010}", valor % 10000000000ULL);
}

std::string CCalculaCV::GeraMacHexa(const std::string& texto) const
{
    const ecourna::api::security::CSiphashMac siphash;
    const std::vector<uebyte> dados(texto.begin(), texto.end());
    std::vector<uebyte> mac;
    siphash.Mac(dados, mac, m_chave);
    std::string hexa;
    for (size_t i = 0; i < mac.size(); ++i) {
        hexa += std::format("{:02x}", mac[i]);
    }
    return hexa;
}

} // namespace comum
