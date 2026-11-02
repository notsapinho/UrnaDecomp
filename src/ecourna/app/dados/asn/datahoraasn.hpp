#pragma once
#include <string>

#include <boost/date_time/posix_time/ptime.hpp>

namespace ecourna::app::dados::asn {

// The date-time spelling of the ASN.1 entities: "AAAAMMDDThhmmss" (std::format, fn 9220 = binaryen thunk to the
// body 6155, merged with api/security's ConverteDataHoraSemSeparador, fn 2685) and back (fn 1877, which also takes a
// GeneralizedTime "AAAAMMDDhhmmssZ"). Names and file synthesised: no record names them; five converters' DoConverte
// pass the formatter's table slot (9110, 9133, 9201, 9203, 9219), and the parser has several callers (9218, 9132, ...).
// FormataHora (fn 2686) gives the time of day as "hh:mm:ss"; its caller is vota::CImpressaoPU::StartState (fn 11902).
// Its name and its file are chosen: fragment 04 says why.
std::string ConverteDataHora(const boost::posix_time::ptime& dataHora);
std::string FormataHora(const boost::posix_time::ptime& dataHora);
boost::posix_time::ptime DesconverteDataHora(const std::string& dataHora);

} // namespace ecourna::app::dados::asn
