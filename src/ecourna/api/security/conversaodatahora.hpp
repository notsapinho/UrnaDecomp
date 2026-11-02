#pragma once
#include <string>

#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

namespace ecourna::api::security {

// A ptime's date as "DD/MM/AAAA" (target fn 2687) and a ptime as "AAAAMMDDhhmmss" (fn 2685). The date overload has no
// target function of its own: binaryen inlines it into its one caller, the ptime overload. The functions' names, their
// namespace and this file's path are chosen: no record names them (src/units/265-ecourna-boost-datetime.mk says why).
std::string FormataData(const boost::gregorian::date& data);
std::string FormataData(const boost::posix_time::ptime& dataHora);
std::string ConverteDataHoraSemSeparador(const boost::posix_time::ptime& dataHora);

} // namespace ecourna::api::security
