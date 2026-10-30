#pragma once

namespace comum {

// Recovered: only the type of the application a SAVD request is made for, which comum::ValidarUE, AssinarUE,
// AssinarEcourna and EnviarAcaoHSM take (their records in iinterfacesavd.cpp spell it ESavdAplic) and
// comum::CSigVerifier keeps. It is 4 bytes wide (CSigVerifier stores it with an i32.store), and EnviarAcaoHSM checks
// that it fits in a byte before sending it. Its enumerators, IInterfaceSavd and the other SAVD types are not
// recovered; the header's path follows iinterfacesavd.cpp.
enum ESavdAplic : int;

// Recovered: only the type of the SAVD package that comum::CArquivosSavd::operator[] takes (its record in
// carquivossavd.cpp spells it ESavdPacote, fn 275) and comum::CAssinador keeps: vota::CAssinadorVota's constructor
// (fn 1501) stores its argument in the inlined CAssinador's +8 member with an i32.store and passes it to that
// operator. Its enumerators are not recovered, and that it is declared beside ESavdAplic is a choice.
enum ESavdPacote : int;

} // namespace comum
