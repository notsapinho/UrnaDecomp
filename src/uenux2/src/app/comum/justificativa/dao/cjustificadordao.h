#pragma once
#include "app/comum/justificativa/dao/ijustificadordao.h"
#include "ecourna/api/sql/isqlconnection.hpp"

namespace comum::dao {

// The justified absences, table registro_justificativa. The name and the base are RTTI's, ExcluirID and Atualizar the
// records' (cjustificadordao.cpp lines 56 and 63). The header's path, beside that file, is chosen. The members with
// chosen names are the bases' (api/persistencia/idao.h, iuenuxgenericdao.h).
//
// final: the destructor (fn 1704) stores no vptr (docs/reference/facts/reading.md R4). Out of line: the deleting
// destructor (fn 3767) calls it and then frees this (R5); in the class or implicit, the D0 holds the D2 (measured).
// `~CJustificadorDAO() final` in a class not marked final gives the same code. 1704 and 3767 fill slots 0 and 1 of
// all three DAOs' vtables: binaryen merged three bodies that release one std::shared_ptr at +8. The object is 12 bytes
// (`new` of 12 in fn 3894 and where fn 7787 builds it).
//
// The constructor is not written: fn 7787 holds it with a stack prologue of its own, so it is out of line in the
// original (reading.md R10), and it has no target function. It opens the connection and creates the table.
//
// Clone is written as a trap in src/units/66-uenux2-cjustificadordao-pending.cpp. In the three DAOs its function
// comes after the file's other members and before the base's defaults, the place of an inline member or of the file's
// last one (reading.md R9): which of the two is open.
class CJustificadorDAO final : public IJustificadorDAO {
public:
    ~CJustificadorDAO() override;

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
