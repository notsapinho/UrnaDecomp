#pragma once
#include <memory>
#include <vector>

#include "ecourna/api/security/cepesc/cinfosalt.hpp"
#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::cepesc {

class CPlainText {
public:
    CPlainText(const uebyte tipoArquivo, const uebyte idCriptografia, const ueword identificadorUE, const ueword versao,
               std::vector<uebyte> tabelaCriptografiaUE, std::vector<uebyte> numeroAleatorioUE, std::vector<uebyte> chave,
               std::vector<uebyte> conteudo, std::shared_ptr<CInfoSalt> infoSalt);
    CPlainText(const uebyte tipoArquivo, const uebyte idCriptografia, const ueword identificadorUE, const ueword versao,
               std::vector<uebyte> tabelaCriptografiaUE, std::vector<uebyte> numeroAleatorioUE, std::vector<uebyte> chave,
               std::vector<uebyte> conteudo, const CInfoSalt& infoSalt);
    // Target fn 5168, no record: the 9-argument constructor (fn 9465, through invoke_*) with the file type 0, the
    // cipher id 1 and no salt, the four vectors moved into its by-value parameters, which a landing pad destroys. Its
    // callers, fn 2725 (comum::CControlaArmazenamentoDeImagens' cipher of a WSQ, which passes CLocal's zone and
    // section) and fn 11629 (comum::CGravadorBU), are not written. That it is a delegating constructor of this class
    // (it returns 9465's `this`), its parameters' names and types and its line in cplaintext.cpp are chosen.
    CPlainText(const ueword identificadorUE, const ueword versao, std::vector<uebyte> tabelaCriptografiaUE,
               std::vector<uebyte> numeroAleatorioUE, std::vector<uebyte> chave, std::vector<uebyte> conteudo);
    // No target function of its own: comum::CGravadorRCSecao::GravaResultado (fn 11616), its one caller, holds it behind
    // an 80-byte frame with landing pads (ecourna's code), which binaryen inlined. It builds two vectors of one zero
    // byte, moves the key and the content into the 9-argument constructor's by-value parameters with the file type, the
    // cipher id, the unit id and the version 0, and makes the salt shared with std::make_shared (CInfoSalt's copy
    // constructor, fn 9470, through invoke_*). That it is a delegating constructor of this class, its parameters' names,
    // types and order, and its line in cplaintext.cpp are chosen.
    CPlainText(std::vector<uebyte> chave, std::vector<uebyte> conteudo, CInfoSalt infoSalt);

    uebyte GetTipoArquivo() const { return m_tipoArquivo; }
    uebyte GetIdCriptografia() const { return m_idCriptografia; }
    ueword GetIdentificadorUE() const { return m_identificadorUE; }
    ueword GetVersao() const { return m_versao; }
    const std::vector<uebyte>& GetTabelaCriptografiaUE() const { return m_tabelaCriptografiaUE; }
    const std::vector<uebyte>& GetNumeroAleatorioUE() const { return m_numeroAleatorioUE; }
    const std::vector<uebyte>& GetChave() const { return m_chave; }
    const std::vector<uebyte>& GetConteudo() const { return m_conteudo; }
    const std::shared_ptr<CInfoSalt>& GetInfoSalt() const { return m_infoSalt; }

private:
    uebyte m_tipoArquivo;
    uebyte m_idCriptografia;
    ueword m_identificadorUE;
    ueword m_versao;
    std::vector<uebyte> m_tabelaCriptografiaUE;
    std::vector<uebyte> m_numeroAleatorioUE;
    std::vector<uebyte> m_chave;
    std::vector<uebyte> m_conteudo;
    std::shared_ptr<CInfoSalt> m_infoSalt;
};

} // namespace ecourna::api::cepesc
