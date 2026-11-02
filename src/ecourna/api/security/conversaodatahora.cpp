#include "ecourna/api/security/conversaodatahora.hpp"

#include <format>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace ecourna::api::security {

std::string FormataData(const boost::gregorian::date& data)
{
    return std::format("{:02}/{:02}/{:04}", data.day().as_number(), data.month().as_number(),
                       std::stoi(std::to_string(data.year())));
}

std::string FormataData(const boost::posix_time::ptime& dataHora)
{
    return FormataData(dataHora.date());
}

std::string ConverteDataHoraSemSeparador(const boost::posix_time::ptime& dataHora)
{
    return std::format("{:04}{:02}{:02}{:02}{:02}{:02}", std::stoi(std::to_string(dataHora.date().year())),
                       dataHora.date().month().as_number(), dataHora.date().day().as_number(),
                       dataHora.time_of_day().hours(), dataHora.time_of_day().minutes(), dataHora.time_of_day().seconds());
}

} // namespace ecourna::api::security
