// The reconstruction's note, not TSE's text: the registry's map, which __wasm_call_ctors initializes with no guard, so one
// .cpp defines it. No record names this file: its path, beside cdaorepositorio.hpp, and the map's name are chosen.
#include "api/persistencia/cdaorepositorio.hpp"

namespace api::persistencia {

std::map<std::string, std::shared_ptr<IDAO>> CDAORepositorio::s_daos;

} // namespace api::persistencia
