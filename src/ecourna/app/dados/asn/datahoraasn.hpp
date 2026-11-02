#pragma once
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>

namespace ecourna::app::dados::asn {

// The date-time spelling of the ASN.1 entities: "AAAAMMDDThhmmss" (std::format, fn 9220 = binaryen thunk to the
// merged body 6155) and back (fn 1877, which also takes a GeneralizedTime "AAAAMMDDhhmmssZ"). Names and file
// synthesised: no record names them; the formatter has one caller (9219), the parser several (9218, 9132, ...).
// FormataHora (fn 2686) gives the time of day as "hh:mm:ss"; its caller is vota::CImpressaoPU::StartState (fn 11902).
// Its name and its file are chosen: fragment 04 says why.
std::string ConverteDataHora(const boost::posix_time::ptime& dataHora);
std::string FormataHora(const boost::posix_time::ptime& dataHora);
boost::posix_time::ptime DesconverteDataHora(const std::string& dataHora);

} // namespace ecourna::app::dados::asn
