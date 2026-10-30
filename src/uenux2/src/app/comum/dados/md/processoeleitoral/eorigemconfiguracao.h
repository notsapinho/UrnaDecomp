#pragma once

namespace comum::md {

// Where a configuration came from. CConversorOrigemConfiguracao::DoDesconverte (target fn 11366) returns the ASN.1
// value 1 or 2 unchanged, and DoConverte fixes ORIGEM_COMUNITARIA = 2; the enumerator names are not in the target.
enum EOrigemConfiguracao {
    ORIGEM_OFICIAL = 1,
    ORIGEM_COMUNITARIA = 2,
};

} // namespace comum::md
