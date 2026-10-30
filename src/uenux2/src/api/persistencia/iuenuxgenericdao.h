#pragma once
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "api/persistencia/euepersistenciaerror.h"
#include "api/persistencia/idao.h"

namespace api::persistencia {

// The DAO of one data class, DADO, and its key, ID: the template parameters, the typedefs and the signatures of
// Excluir, ExcluirID and Atualizar are the records' (lines 41, 49 and 57 of this file). Slots 3, 7 and 8 have no
// record: their names are chosen, Inserir from the INSERT each override runs, RecuperarID and RecuperarTodos from
// their SELECTs (slot 7's has a WHERE on the key, slot 8's none); their const follows the three recorded members.
// Their parameters and results are what fns 11473, 11470 and 11469 use: a const reference to the data; a
// std::shared_ptr that takes a `new` copy of the row; a std::vector filled row by row. Pure is chosen: the three
// DAOs override them, and the target has no vtable of this template to show the slots.
//
// The three defaults: all five instantiated ones are thunks into fn 2297, binaryen's merge of them. The name's string
// is built before __cxa_allocate_exception, so it is a local of the function and not a temporary of the throw, and
// the local is an lvalue: fn 2297 calls the out-of-line operator+(const char*, const std::string&) (fn 345).
template <typename DADO, typename ID>
class IUenuxGenericDAO : public IDAO {
public:
    typedef DADO TDado;
    typedef ID TDadoID;

    virtual void Inserir(const TDado& dado) const = 0;

    // (original lines 31-37: content not recovered)
#line 38
    virtual void Excluir(const TDado&) const
    {
        const std::string entidade = typeid(DADO).name();
        throw CUePersistenciaError(EUE_PERSISTENCIA_EXCLUIR_NAO_IMPLEMENTADA, "Excluir não implementada para entidade " + entidade);
    }

    // (original lines 44-45: content not recovered)
#line 46
    virtual void ExcluirID(const TDadoID&) const
    {
        const std::string entidade = typeid(DADO).name();
        throw CUePersistenciaError(EUE_PERSISTENCIA_EXCLUIR_ID_NAO_IMPLEMENTADA, "ExcluirID não implementada para entidade " + entidade);
    }

    // (original lines 52-53: content not recovered)
#line 54
    virtual void Atualizar(const TDado&) const
    {
        const std::string entidade = typeid(DADO).name();
        throw CUePersistenciaError(EUE_PERSISTENCIA_ATUALIZAR_NAO_IMPLEMENTADA, "Atualizar não implementada para entidade " + entidade);
    }

    virtual std::shared_ptr<TDado> RecuperarID(const TDadoID& id) const = 0;
    virtual std::vector<TDado> RecuperarTodos() const = 0;
};

} // namespace api::persistencia
