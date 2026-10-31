#pragma once

#include "app/comum/relatorios/cimprimirextratocarga.h"

namespace comum {

// Reconstruction notes, not TSE's text. comum::CRelatorioTesteImpressora: RTTI names it, an si_class of
// comum::CImprimirExtratoCarga, and its vtable (@1576652) and typeinfo lie in crelatoriotesteimpressora.cpp's data, before
// the record of that file's line 173. Recovered: its 8-byte layout, from the constructor (fn 5586, which 11869 and 11911
// call on an object in their frames, the next local 8 bytes on), and its overrides, one per slot of the base that the
// vtable does not fill with a shared body (slots 2, 3, 5, 7 to 22). The destructor is implicit: slot 1 (fn 144) frees
// this and nothing else. No record names a member: the names are the base's (cimprimirextratocarga.h), and the data
// members' names and types are chosen. +4 is a byte the constructor stores 0 into before the vptr, and no slot reads it;
// +5 is the flag the constructor computes and slot 14 (fn 11191) tests: set when the urna's type for its turn is
// eUrnaContingencia, comum::CPE holds a second pleito and a date test on it (fns 1382, 1261) passes.
class CRelatorioTesteImpressora : public CImprimirExtratoCarga {
public:
    CRelatorioTesteImpressora();

    virtual bool EhTreinamento() const override;
    virtual bool TemHorarioVerao() const override;
    virtual std::string GetConteudoQRCode() const override;
    virtual const md::CHorarioVerao& GetHorarioVerao() const override;
    virtual bool EstaEmHorarioVerao() const override;
    virtual md::estadoaplicacao::CDadoCorrespondencia GetCorrespondencia() const override;
    virtual void InicializaTradutorFrase() const override;
    virtual const ecourna::app::dados::CParametrosUrna::TVectorTituloRelatorio& GetCabecalho() const override;
    virtual bool EhEleicaoComunitaria() const override;
    virtual std::string GetNomeEleicao() const override;
    virtual const md::CPleito& GetPleito() const override;
    virtual std::vector<std::string> GetDadosLocal() const override;
    virtual std::string GetUF() const override;
    virtual std::string GetTipoUrna() const override;
    virtual std::string GetMensagemEncerramento() const override;
    virtual std::string GetMensagemCondicoes() const override;
    virtual std::string GetSeparadorFase() const override;
    virtual std::string GetTitulo() const override;
    virtual bool EhModoDemonstracao() const override;

private:
    bool m_naoRecuperado;
    bool m_usaPleito2;
};

} // namespace comum
