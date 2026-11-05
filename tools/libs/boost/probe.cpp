// Boost probe: the header-only parts the vota app instantiates (docs/reference/facts/libraries.md §B7: regex with
// re_detail_600::parser_buf<char>, signals2, function, optional, and date_time's greg_weekday for a toolkit test),
// instantiated the way an app would and kept alive through exported entry points.
// No date parsing, clock or lexical_cast call: what the app links of them comes from its own objects, and the probe's
// calls changed it. Boost's parse_iso_time<ptime> (target fn 5851, uenux2's copy, which only 11616 calls directly)
// holds parse_undelimited_date, gregorian::date's constructor from a year, a month and a day, and
// lcast_ret_unsigned<..., unsigned int, char>::convert inlined, and the probe gave each a second caller in the app link
// (from_undelimited_string the first, its two clocks the second, its lexical_cast<int> and <unsigned> the third); its
// lexical_cast calls from other source types kept that type a parameter of bad_lexical_cast's constructor (2849), which
// the target holds as std::string's typeinfo; and the copies of the two other converters (3811, 5833) it gave
// src/app/roots_boost.o, at APP_CXXFLAGS, linked ahead of uenux2's, which are the target's
// (src/units/122-uenux2-app-comum-gravadores.mk has the measurements). That date and lexical_cast code also emitted
// wrapexcept<std::runtime_error>, whose target copies are ecourna's
// (src/units/00-ecourna-app-dados-identificadoreleitor.mk), and the other date_time copies the app links are ecourna's
// too (src/units/265-ecourna-boost-datetime.mk).
#include <emscripten.h>

#include <boost/date_time/gregorian/greg_weekday.hpp>
#include <boost/function.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>
#include <boost/make_shared.hpp>
#include <boost/signals2.hpp>
#include <boost/weak_ptr.hpp>
#include <string>

extern "C" {

EMSCRIPTEN_KEEPALIVE int probe_regex(const char *pattern, const char *text) {
  boost::regex re(pattern);
  boost::cmatch cm;
  int r = boost::regex_search(text, cm, re) ? (int)cm.size() : -1;
  std::string s(text);
  boost::smatch sm;
  if (boost::regex_match(s, sm, re)) {
    r += (int)sm[0].length();
  }
  std::string replaced = boost::regex_replace(s, re, std::string("$1"));
  boost::sregex_iterator it(s.begin(), s.end(), re), end;
  for (; it != end; ++it) {
    r += (int)it->position();
  }
  boost::regex ic(pattern, boost::regex::icase | boost::regex::perl);
  r += boost::regex_search(s, ic) ? 1 : 0;
  return r + (int)replaced.size();
}

// the app's own signal type (target RTTI: signals2::signal<void (unsigned long, unsigned long, std::string const&)>,
// sp_counted_impl_p<signals2::mutex>, sp_counted_impl_p<optional_last_value<void>>, sp_ms_deleter<signal_impl<...>>)
using app_signal = boost::signals2::signal<void(unsigned long, unsigned long, const std::string &)>;

EMSCRIPTEN_KEEPALIVE int probe_app_signal(unsigned long a, unsigned long b, const char *text) {
  app_signal sig;
  std::size_t acc = 0;
  boost::signals2::connection c = sig.connect([&acc](unsigned long x, unsigned long y, const std::string &s) { acc += x + y + s.size(); });
  sig(a, b, std::string(text));
  app_signal *heap = new app_signal;
  heap->connect([&acc](unsigned long, unsigned long, const std::string &s) { acc += s.size(); });
  (*heap)(a, b, std::string(text));
  delete heap;
  // no c.disconnect(), here or in probe_signals: connection_body_base::disconnect is no template, so the tree root that
  // includes this file (src/app/roots_boost.cpp) cannot declare it extern, and its copy, without landing pads, would
  // take the place of ecourna's (target fn 9570) in the app link (src/units/06-ecourna-api-compression.mk)
  boost::shared_ptr<std::string> sp = boost::make_shared<std::string>(text);
  boost::weak_ptr<std::string> wp(sp);
  if (boost::shared_ptr<std::string> l = wp.lock()) {
    acc += l->size();
  }
  return (int)acc + (int)sig.num_slots();
}

EMSCRIPTEN_KEEPALIVE int probe_signals(int x) {
  boost::signals2::signal<void()> sig;
  int acc = 0;
  sig.connect([&acc] { acc++; });
  boost::signals2::connection c = sig.connect([&acc] { acc += 2; });
  sig();
  sig();
  boost::signals2::signal<void(int)> sig2;
  sig2.connect([&acc](int v) { acc += v; });
  sig2(x);
  boost::signals2::signal<int(int)> sig3;
  sig3.connect([](int v) { return v * 2; });
  boost::optional<int> last = sig3(x);
  return acc + (last ? *last : 0);
}

// greg_weekday's range check, which throws boost::gregorian::bad_weekday (splat/symbol_addrs.txt names no bad_weekday
// object of the target) and constructs no date. It keeps bad_weekday's typeinfo in the app link, which
// asmlift-wasm/test/splat-symbols.test.ts ("offers every place of read-only content it finds more than once") reads
// (asmlift-wasm/README.md "Tests": a real-link case's object stays in for the test).
EMSCRIPTEN_KEEPALIVE int probe_weekday(int x) {
  return boost::gregorian::greg_weekday(static_cast<unsigned short>(x)).as_number();
}

EMSCRIPTEN_KEEPALIVE int probe_function(int x) {
  boost::function<int(int)> f;
  boost::optional<int> o;
  if (!o) {
    o = x;
  }
  if (f.empty()) {
    f = [](int v) { return v + 1; };
  }
  boost::function<void()> g;
  int r = f(*o);
  try {
    g();
  } catch (const boost::bad_function_call &) {
    r++;
  }
  return r;
}
}
