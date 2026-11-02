// The Boost lane's probe (the header-only parts the app instantiates) compiled as app code (see roots_7zip.cpp).
// It supplies no copy of two date_time templates whose target copies are an -fexceptions object's code (landing pads in
// target fns 1376 and 9415): declared extern template here, they come from the first ecourna object that emits them,
// from_day_number from app/dados/asn/datahoraasn.cpp.o and to_simple_string_type over a time_duration from
// api/sql/sqlite/csqlstatement.cpp.o (src/units/265-ecourna-boost-datetime.mk has the evidence and the measurements).
#include <emscripten.h>
#undef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using UrnaYmd = boost::date_time::year_month_day_base<boost::gregorian::greg_year, boost::gregorian::greg_month,
                                                      boost::gregorian::greg_day>;
extern template UrnaYmd boost::date_time::gregorian_calendar_base<UrnaYmd, unsigned int>::from_day_number(unsigned int);
extern template std::string boost::posix_time::to_simple_string_type<char>(boost::posix_time::time_duration);
#include "../../tools/libs/boost/probe.cpp"
