#pragma once

namespace comum {

// Recovered: only the type of the application a SAVD request is made for, which comum::ValidarUE, AssinarUE,
// AssinarEcourna and EnviarAcaoHSM take (their records in iinterfacesavd.cpp spell it ESavdAplic) and
// comum::CSigVerifier keeps. It is 4 bytes wide (CSigVerifier stores it with an i32.store), and EnviarAcaoHSM checks
// that it fits in a byte before sending it. Its enumerators, IInterfaceSavd and the other SAVD types are not
// recovered; the header's path follows iinterfacesavd.cpp.
enum ESavdAplic : int;

} // namespace comum
