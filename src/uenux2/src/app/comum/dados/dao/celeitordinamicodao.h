#pragma once

#include <string>

#include "app/comum/dados/dao/ieleitordinamicodao.h"
#include "ecourna/api/sql/isqlconnection.hpp"

namespace comum::dao {

// The table eleitor_dinamico. The name and the base are RTTI's, ExcluirID the record's (celeitordinamicodao.cpp line
// 130). The header's path, beside that file, is chosen. The members with chosen names are the bases'
// (api/persistencia/idao.h, iuenuxgenericdao.h). Slots 0 and 1 are fns 1704 and 3767, shared with CJustificadorDAO and
// CComparecimentoMesarioDAO, so final and the destructor out of line follow as there
// (app/comum/justificativa/dao/cjustificadordao.h).
class CEleitorDinamicoDAO final : public IEleitorDinamicoDAO {
public:
    explicit CEleitorDinamicoDAO(const std::string& caminho);
    ~CEleitorDinamicoDAO() override;

    api::persistencia::IDAO* Clone() const override;
    void Inserir(const TDado& dado) const override;
    void ExcluirID(const TDadoID& id) const override;
    void Atualizar(const TDado& dado) const override;
    std::shared_ptr<TDado> RecuperarID(const TDadoID& id) const override;
    std::vector<TDado> RecuperarTodos() const override;

private:
    ecourna::api::sql::TSharedSqlConnection m_conexao;
};

} // namespace comum::dao
