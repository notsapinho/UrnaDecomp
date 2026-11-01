// std::basic_regex<char>'s copies that are ecourna's code in the target: its constructor from a C string (target fn
// 2416, called by ecourna::app::dados::CSerialMidia::ValidaSerial, fn 9258, and by uenux2's 5492 and 6999) and what that
// constructor instantiates (the parser, the states' members, the destructor). Before uenux2 used std::regex, ecourna's
// objects gave those rows: 51 matched from api_compression_icompressor.cpp.o and 4 from app_dados_cserialmidia.cpp.o
// (splat/scan.tsv's object column at 9202406). api::CMenuItem::GetTextoFormatado (fn 5492, cinputmenufield.cpp) uses
// std::regex too, and uenux2's objects link ahead of ecourna's, so its copies, at uenux2's flags, took those rows: 8 of
// them then differed or left the link. This object, ahead of both trees, holds the copies at ECOURNA_CXXFLAGS, the flags
// of the objects that gave them. It only instantiates: urna_regex has no caller and leaves the link.
// src/units/84-uenux2-cinputmenufield.mk has the rows.
#include <regex>

void urna_regex(const char* padrao)
{
    const std::regex re(padrao);
}
