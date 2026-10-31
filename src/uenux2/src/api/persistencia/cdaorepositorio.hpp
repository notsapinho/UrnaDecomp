// The reconstruction's note, not TSE's text. api::persistencia::CDAORepositorio, the registry the DAOs are handed out
// from. The records give the class, the names, `static`, the template parameters and the signatures of Registrar and
// Entregar, and the lines of their throws: 35 and 52 (Registrar, held by fn 7787, which inlines it) and 79 (Entregar,
// held by fns 815 and 3742, which inline it). Registrar is not written: its lines stay blank. Entregar's throw stands at
// column 15, which a member defined in its class with the throw at its body's top level fits (a reading).
//
// Read from the bytes of 3742 and 815: the key is the typeid name of I_DOMINIO_DAO, with I_ORIGEM's appended when the
// two differ; both names live to the end of the function (their frees come last). The registry maps the key to a
// std::shared_ptr<IDAO> (fn 3845, the map's destroy, releases a shared_ptr at the node's +28), and Entregar hands out
// the found DAO's Clone (IDAO's slot 2) cast to I_DOMINIO_DAO, in a std::shared_ptr<I_DOMINIO_DAO> of its own (the
// control block's typeinfo names shared_ptr<I_DOMINIO_DAO>'s default deleter), deleting the clone when the cast fails.
// The map is initialized in __wasm_call_ctors with no guard, so it is defined in one .cpp (cdaorepositorio.cpp).
//
// Chosen, no evidence names them: s_daos and its being a static data member, the locals' names, I_ORIGEM's default;
// and Entregar's spelling: no other spelling of its statements was compared.
#pragma once
#include <format>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

#include "api/persistencia/euepersistenciaerror.h"
#include "api/persistencia/idao.h"

namespace api::persistencia {

class CDAORepositorio {
public:

    // (original lines 31-57: content not recovered)
#line 58
    template <typename I_DOMINIO_DAO, typename I_ORIGEM = I_DOMINIO_DAO>
    static std::shared_ptr<I_DOMINIO_DAO> Entregar()
    {
        const std::string dominio = typeid(I_DOMINIO_DAO).name();
        const std::string origem = typeid(I_ORIGEM).name();
        std::string chave = dominio;
        if (dominio != origem) {
            chave = dominio + origem;
        }

        const auto it = s_daos.find(chave);
        if (it != s_daos.end()) {
            IDAO* copia = it->second->Clone();
            if (copia != nullptr) {
                I_DOMINIO_DAO* dao = dynamic_cast<I_DOMINIO_DAO*>(copia);
                if (dao != nullptr) {
                    return std::shared_ptr<I_DOMINIO_DAO>(dao);
                }
                delete copia;
            }
        }
        throw CUePersistenciaError(EUE_PERSISTENCIA_DAO_NAO_REGISTRADA, std::format("Classe DAO {} não foi registrada.", chave));
    }

private:
    static std::map<std::string, std::shared_ptr<IDAO>> s_daos;
};

} // namespace api::persistencia
