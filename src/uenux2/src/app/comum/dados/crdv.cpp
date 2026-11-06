// comum::CRdv (/home/rubio/tse/uenux2/src/app/comum/dados/crdv.cpp). The reconstruction's own note: the records
// of CRdv's constructor (lines 90 and 93) and of comum::(anonymous namespace)::GetCifradorCryptoTable (lines 60 and
// 78), which fn 7787 holds inlined, are of functions not written, and their lines are blank. Every other line is
// chosen (src/units/381-uenux2-crdv.mk).

#include "app/comum/dados/crdv.h"

#include <filesystem>
#include <string>
#include <vector>

#include "api/io/cencryptedfile.h"
#include "app/comum/cpath.h"

namespace comum {
















































































std::string GetArquivoRdvInterno()
{
    return (CPath::GetPathTrab(FLASH_INTERNA) / "rdv.dat").string();
}

std::string GetArquivoRdvExterno()
{
    return (CPath::GetPathTrab(FLASH_EXTERNA) / "rdv.dat").string();
}

void CRdv::Salva(const std::string& arquivo) const
{
    api::CEncryptedFile cifrado(m_cifrador);
    const std::vector<uebyte> dados = Converte();
    cifrado.Write(dados);
    cifrado.Save(arquivo);
}

void CRdv::SalvaInterno() const
{
    Salva(GetArquivoRdvInterno());
}

void CRdv::SalvaExterno() const
{
    Salva(GetArquivoRdvExterno());
}

} // namespace comum
