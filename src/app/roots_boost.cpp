// The Boost lane's probe (the header-only parts the app instantiates) compiled as app code (see roots_7zip.cpp).
// It supplies no copy of the templates below, whose target copies are an -fexceptions object's code (landing pads in
// the target's bodies): declared extern template here, they come from the first ecourna object that emits them.
// - the app's signal (ICompressor's, src/units/06-ecourna-api-compression.mk): signal_impl's constructor (9536) and
//   sp_counted_impl_p<signal_impl>::dispose (9519) from api/compression/icompressor.cpp.o; make_shared of its
//   invocation_state from a copy (9558), its operator() (9583), connection_body_base::dec_slot_refcount over a lock of
//   a connection body (9575), the connection list's erase (9579) and the reserve_impl of the two auto_buffers, the
//   slot-call cache's tracked pointers (9563) and a lock's garbage (9572), from clzmacompress.cpp.o.
//   connection_body_base::disconnect (9570) is no template, so no line here keeps a copy of it out: the probe does not
//   call it (tools/libs/boost/probe.cpp), and clzmacompress.cpp.o's copy links.
// - Boost.Regex (CStringUtils::FindRegex's, src/units/00-ecourna-app-dados-identificadoreleitor.mk): basic_regex's
//   do_assign (9401), perl_matcher over std::string's iterators and throw_exception<std::logic_error> (9399) from
//   api/util/cstringutils.cpp.o.
#include <emscripten.h>
#undef EMSCRIPTEN_KEEPALIVE
#define EMSCRIPTEN_KEEPALIVE
#include <boost/regex.hpp>
#include <boost/signals2.hpp>
#include <map>
#include <string>
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
extern template void boost::detail::sp_counted_impl_p<UrnaSignalImpl>::dispose();
using UrnaBodyLock = boost::signals2::detail::garbage_collecting_lock<boost::signals2::detail::connection_body_base>;
extern template void boost::signals2::detail::connection_body_base::dec_slot_refcount(UrnaBodyLock &) const;
extern template UrnaSignalImpl::connection_list_type::iterator
UrnaSignalImpl::connection_list_type::erase(const UrnaSignalImpl::group_key_type &,
                                            const UrnaSignalImpl::connection_list_type::iterator &);
using UrnaTrackedPtrs = boost::signals2::detail::auto_buffer<boost::signals2::detail::void_shared_ptr_variant,
                                                             boost::signals2::detail::store_n_objects<10>>;
extern template void UrnaTrackedPtrs::reserve_impl(UrnaTrackedPtrs::size_type);
using UrnaGarbage =
    boost::signals2::detail::auto_buffer<boost::shared_ptr<void>, boost::signals2::detail::store_n_objects<10>>;
extern template void UrnaGarbage::reserve_impl(UrnaGarbage::size_type);
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
