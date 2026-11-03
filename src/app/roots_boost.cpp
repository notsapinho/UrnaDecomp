// The Boost lane's probe (the header-only parts the app instantiates) compiled as app code (see roots_7zip.cpp).
// It supplies no copy of the templates below, whose target copies are an -fexceptions object's code (landing pads in
// the target's bodies): declared extern template here, they come from the first ecourna object that emits them.
// - date_time (target fns 1376 and 9415): from_day_number from app/dados/asn/datahoraasn.cpp.o and
//   to_simple_string_type over a time_duration from api/sql/sqlite/csqlstatement.cpp.o
//   (src/units/265-ecourna-boost-datetime.mk has the evidence and the measurements).
// - the app's signal (ICompressor's, src/units/06-ecourna-api-compression.mk): signal_impl's constructor (9536) from
//   api/compression/icompressor.cpp.o, make_shared of its invocation_state from a copy (9558) and its operator() from
//   clzmacompress.cpp.o.
// - Boost.Regex (CStringUtils::FindRegex's, src/units/00-ecourna-app-dados-identificadoreleitor.mk): basic_regex's
//   do_assign (9401), perl_matcher over std::string's iterators and throw_exception<std::logic_error> (9399) from
//   api/util/cstringutils.cpp.o.
#include <emscripten.h>
#undef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/regex.hpp>
#include <boost/signals2.hpp>
#include <map>
#include <string>
using UrnaYmd = boost::date_time::year_month_day_base<boost::gregorian::greg_year, boost::gregorian::greg_month,
                                                      boost::gregorian::greg_day>;
extern template UrnaYmd boost::date_time::gregorian_calendar_base<UrnaYmd, unsigned int>::from_day_number(unsigned int);
extern template std::string boost::posix_time::to_simple_string_type<char>(boost::posix_time::time_duration);
using UrnaSignalImpl =
    boost::signals2::detail::signal_impl<void(unsigned long, unsigned long, const std::string &),
                                         boost::signals2::optional_last_value<void>, int, std::less<int>,
                                         boost::function<void(unsigned long, unsigned long, const std::string &)>,
                                         boost::function<void(const boost::signals2::connection &, unsigned long,
                                                              unsigned long, const std::string &)>,
                                         boost::signals2::mutex>;
extern template UrnaSignalImpl::signal_impl(const boost::signals2::optional_last_value<void> &, const std::less<int> &);
extern template boost::shared_ptr<UrnaSignalImpl::invocation_state>
boost::make_shared<UrnaSignalImpl::invocation_state, UrnaSignalImpl::invocation_state &,
                   UrnaSignalImpl::connection_list_type &>(UrnaSignalImpl::invocation_state &,
                                                           UrnaSignalImpl::connection_list_type &);
extern template void UrnaSignalImpl::operator()(unsigned long, unsigned long, const std::string &);
using UrnaRegexTraits = boost::regex_traits<char, boost::cpp_regex_traits<char>>;
using UrnaStrIt = std::string::const_iterator;
extern template boost::regex &boost::regex::do_assign(const char *, const char *, boost::regex::flag_type);
extern template class boost::re_detail_600::perl_matcher<UrnaStrIt, std::allocator<boost::sub_match<UrnaStrIt>>,
                                                         UrnaRegexTraits>;
// The probe's regex_match over a std::string reaches perl_matcher's match_imp, which no ecourna object instantiates
// (FindRegex only searches): without this instance the link stops on an undefined match_imp.
template bool boost::re_detail_600::perl_matcher<UrnaStrIt, std::allocator<boost::sub_match<UrnaStrIt>>,
                                                 UrnaRegexTraits>::match_imp();
extern template void boost::throw_exception<std::logic_error>(const std::logic_error &);
// std::map<std::string, std::string>'s lookup (src/units/00-ecourna-app-dados-identificadoreleitor.mk): the target's
// copy, fn 163, which RHVoice's 5263 and cpp_regex_traits' lookup_collatename (3498) call, is not ecourna's and
// matches from this root (a scratch TU of the instance, compared as objects: ecourna's flags give another body,
// uenux2's with and without strict aliasing this root's); its object in the target is not identified. The probe's
// regex code instantiated it here until do_assign went extern, and without this line 5263 leaves `match`.
template std::map<std::string, std::string>::const_iterator
std::map<std::string, std::string>::find(const std::string &) const;
#include "../../tools/libs/boost/probe.cpp"
