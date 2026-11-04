#pragma once

#include <string>

namespace comum::md {

// A date in the Justica Eleitoral's eight-digit form. The record of the constructor, md/cdataje.cpp:26, names the
// class, its file and the constructor's parameter (const std::string &). Recovered: the constructor, which
// comum::asn::CConversorEntidadeEleitores's slot 2 (target fn 11411) holds inlined behind a 480-byte frame of its own:
// it copies the text to +0 of a 12-byte object and throws 8002 with the parameter's text unless the copy is eight
// characters long and each a digit (one bit test per character against '0' to '9', unrolled eight times). The converter
// then hands that object's address to md::CEleitor's constructor as the voter's date of birth, a std::string. The
// layout is that string alone (a 12-byte frame slot of 11411's); its name, the accessor and its name, `explicit` and
// the test's spelling (find_first_not_of over the ten digits: libc++'s search is a memchr of that constant string,
// which LLVM turns into the bit test, a reading) are chosen, and so is this header's path, beside the .cpp.
class CDataJE {
public:
    explicit CDataJE(const std::string& data);

    const std::string& GetData() const { return m_data; }

private:
    std::string m_data;
};

} // namespace comum::md
