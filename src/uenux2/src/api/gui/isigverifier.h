#pragma once

namespace api {

/**
 * Verificação da assinatura do que um relatório imprime, feita antes da impressão.
 */
// Recovered: the virtual destructor and Verify (slots 0-1 and 2 of comum::CSigVerifier's vtable, the one class that
// implements it; Verify's name and const from that class's record, csigverifier.cpp:32). The target has this class's
// typeinfo and no vtable: every member is inline or pure. The file's path is not in the target; the interface goes
// with the paper reports (api::IPaperRelatorios, whose vtable slot 7 takes it) in api/gui.
class ISigVerifier {
public:
    virtual ~ISigVerifier() = default;

    virtual void Verify() const = 0;
};

} // namespace api
