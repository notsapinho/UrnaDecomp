#pragma once

#include <filesystem>
#include <string>

#include "api/gui/isigverifier.h"
#include "app/comum/iinterfacesavd.h"

namespace comum {

/**
 * Valida no SAVD a assinatura do arquivo de um relatório antes que ele seja impresso.
 */
// Recovered: the constructor, the members it sets and Verify (record csigverifier.cpp:32, fn 11179). The destructor
// is implicit: the target's callers inline it, and its vtable slots (fns 11178, 11176) hold the compiler's bodies.
// Those store no vptr, which clang leaves out of a destructor that destroys members only when the class is final. The
// member and parameter names are not in the target. Verify passes m_aplic to comum::ValidarUE, with m_diretorio joined
// to m_pacote as the package and m_arquivo as the file (CImprimindoBEHB passes a path, "behb.dat" and "behb.vsu").
// The directory is a std::filesystem::path, parameter and member: the callers 2890, 11852 and 12068 build it with
// comum::CPath::GetPathTrab(EFlashOrigem) (fn 436, which returns the path fn 358's record gives) straight into the
// constructor's argument, with no conversion copy, and the constructor moves it into +8 as it moves the two strings
// (fn 1540's bytes are the same for either type; the mangled name is not).
class CSigVerifier final : public api::ISigVerifier {
public:
    CSigVerifier(ESavdAplic aplic, std::filesystem::path diretorio, std::string arquivo, std::string pacote);

    virtual void Verify() const override;

private:
    ESavdAplic m_aplic;
    std::filesystem::path m_diretorio;
    std::string m_arquivo;
    std::string m_pacote;
};

} // namespace comum
