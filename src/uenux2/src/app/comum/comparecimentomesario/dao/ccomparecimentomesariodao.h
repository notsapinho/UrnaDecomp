#pragma once

#include "app/comum/comparecimentomesario/dao/icomparecimentomesariodao.h"
#include "ecourna/api/sql/isqlconnection.hpp"

namespace comum::dao {

// The table comparecimento_mesario. The name and the base are RTTI's. The header's path, beside the file its records
// name, is chosen. The members with chosen names are the bases' (api/persistencia/idao.h, iuenuxgenericdao.h). Slots 0
// and 1 are fns 1704 and 3767, shared with CJustificadorDAO and CEleitorDinamicoDAO, so final and the destructor out of
// line follow as there (app/comum/justificativa/dao/cjustificadordao.h). The constructor is not written: fn 7787 holds
// it. Excluir, ExcluirID and Atualizar are the base's defaults.
class CComparecimentoMesarioDAO final : public IComparecimentoMesarioDAO {
public:
    ~CComparecimentoMesarioDAO() override;

    api::persistencia::IDAO* Clone() const override;
    void Inserir(const TDado& dado) const override;
    std::shared_ptr<TDado> RecuperarID(const TDadoID& id) const override;
    std::vector<TDado> RecuperarTodos() const override;

private:
    ecourna::api::sql::TSharedSqlConnection m_conexao;
};

} // namespace comum::dao
