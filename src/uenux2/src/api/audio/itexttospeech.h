#pragma once

#include <format>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace api {

class CWavFile;

// Recovered: RTTI names api::ITextToSpeech (typeinfo 1526340), a polymorphic class with no base, and its two
// implementers simulador::CWasmNullTextToSpeech and api::CRHVoiceTextToSpeech (vtables @1528696 and @1585548, 12 slots
// each, as its own @1526520). Slots 0 to 8 hold the same nine functions in all three vtables, so they are this class's
// own bodies. Slot 9 and 10 are its destructors (fn 11489 returns this and destroys the members below; its slot 10 is
// fn 325, `unreachable`, the deleting destructor of an abstract class), and slot 11 is pure (fn 12143).
// The class has no key function: its typeinfo and its vtable lie inside vota_web_wasm.cpp's data (both between that
// file's records at 1526324 and 1526664), a copy in a TU that uses the class, where a key function would have put them
// in that function's own TU. So every virtual member is inline or pure.
// That TU is compiled with exceptions: the copies of slot 0 (fn 11530, which calls through invoke_*) and of the
// destructor (fn 11489, which calls fn 149 for the string where fns 9427 and 5441 inline it) are its code.
// The layout comes from the implicit constructor (fn 13877, in the table for the invoke_ii of std::make_unique in fn
// 7840, which zeroes 96 bytes first; inlined into fn 8302 after operator new(96)) and from the destructor:
// - +4 is an object of 36 bytes with its own destructor (fn 3764, called with this + 4), the recent-audio cache below:
//   the int 256 at its +0, a std::list at its +4 (fn 5754 reads a node's std::shared_ptr at +20) and a std::unordered_map
//   from string to list node at its +16;
// - +40 is a std::unordered_map from string to std::shared_ptr (fn 3746; 13877 stores its load factor 1.0f at +56);
// - +60 the speed (default 2), +64 a std::string, +76 (50), +80 (100), +84 the rate (100, the speed's * 20 + 60), +88 an
//   8-byte integer (0). fn 7242 passes slot 4 the same 2; fn 7248 reads slot 5, calls slot 6 or 7 and reads slot 5 again.
// Slots 0 and 11: fn 11530 copies +64, +84, +80, +76 and +88 into a local of 32 bytes, in that order, which is slot 11's
// last argument: SOptions. It makes a key of them with the format "{}:{}:{}:{}:{}" (fn 5758: the text, +12 and +16 as
// `unsigned`, the arg type 6 of fn 2270, +0 between them and +24 as `long long`, arg type 4), looks it up in both
// containers (fn 5754) and, if it is in neither, calls slot 11 and stores the result (fn 5750), so slot 11 is what
// synthesizes. It returns a std::shared_ptr through a hidden result: fn 1204 hands slot 0's result to ISound's slot 4,
// Play(std::shared_ptr<CWavFile>, EModo). CRHVoiceTextToSpeech's slot 11 (fn 10841) reads the options' +0 as the voice,
// and sets +12 and +16, converted from unsigned and divided by 100.0, and then a constant 1.0 on three properties in a
// row: RHVoice's relative rate, pitch and volume, so +84 is the rate and +80 the pitch. No target body reads +76 but to
// copy it.
// No record, symbol or string names this file or a member. All of these are chosen: the path (beside api/audio/isound.h),
// every member and data member name, SOptions, SRecentCache, TEntry and its being a std::pair (a struct with a
// constructor gives the same bodies), and the types int and long long where the wasm type alone
// says i32 or i64. Synthesize / DoSynthesize follows the project's Converte / DoConverte (comum::asn::IConversorASN's
// records); volume is the third of RHVoice's three, by elimination; SetTag is named for what the body does with the value,
// since slot 8 has no caller in the target (no call_indirect of its type (i32, i64)->() goes through +32). 4 and 0, the
// limits of slots 6 and 7, have no name.
// Synthesize (slot 0) and its helpers, from the executable TU's copies (src/app/roots_texttospeech.cpp gives them at
// that TU's rule; src/units/237-uenux2-itexttospeech.mk has the measurements):
// - Synthesize: fn 11530 builds the options, makes the key through table slot 207 (fn 5758), looks it up through slot
//   208 (fn 5754) into its result and returns when the pointer is not null. Otherwise it destroys that empty result
//   (fn 388) and calls slot 11 into the same address, then stores a copy through slot 209 (fn 5750) with 0 as the last
//   argument; two named results in one return slot, as written here, give those rows. The options' address is held in
//   a local before the string copy and the fields are stored through the copy's returned this, read as a function of
//   its own that binaryen inlined (how-to step 3's signs), GetOptions here; the same initializer written in Synthesize,
//   and a constructor of SOptions, give other rows.
// - MakeKey (fn 5758): std::format of the text, the rate, the voice, the pitch and the tag. The tag is copied into a
//   temporary of the frame before the format, which a prvalue argument gives and options.tag alone does not. Its
//   second parameter is the object, which both callers, 11530 and fn 921, pass and it never reads.
// - Lookup (fn 5754): the kept map's find, then the cache's Get, which binaryen inlined (Get's code written in Lookup
//   gives other rows).
// - Store (fn 5750): its last argument is compared with 1: 11530 passes 0 (the cache) and fn 921 passes 1 (the kept
//   map). A bool there gives other rows. The kept map's operator[] is slot 210 (fn 11447) and its assignment a copy
//   (fn 5707); the shared_ptr comes by value (5750 destroys it on both paths).
// - SRecentCache::Put (fn 11436, slot 211, called with this + 4): find and then operator[] of the index (fns 2808 and
//   3732); when the index holds `capacity` keys, a copy of the last entry, its key erased (slot 212, fn 11353) and the
//   entry popped (slot 213, fn 11346); then emplace_front of the key and the file (the pair's constructor is slot 218, fn
//   11342) and the index set to the new first entry.
// Cache (fn 921), in no slot, a uenux2 TU's copy (no landing pads; src/units/237-uenux2-itexttospeech-roots.cpp gives
// it at that TU's flags):
// - the same options, key and Lookup, called directly (fns 5758 and 5754); a file found becomes the kept map's entry
//   (operator[] and the copy assignment inlined, a direct call of fn 5685), else slot 11 synthesizes it and Store (fn
//   5750) keeps it, called with 1 (eCacheKept), a constant of the target's body. Written in Cache, eCacheKept lets
//   clang inline Store (cost 210, threshold 250), where the target calls it; as Cache's parameter, Store costs 280 and
//   stays a call. So the kind is read as a parameter that every caller passes as 1 and binaryen's dead-argument
//   elimination folded into the body (how-to step 2).
// - Its one target caller is fn 7787, 14 times, all inside a frame of their own there that loads the records of
//   vota::CInstrucaoVotacaoAcessibilidade::CacheInstructionAudio (cinstrucaovotacaoacessibilidade.cpp:157 and :161),
//   read as that member, which binaryen inlined into 7787 (how-to step 3's signs): so 921 is read as that file's TU's
//   copy.
// Chosen as well: the names GetOptions, MakeKey, Lookup, Store, Cache, ECache and its enumerators, Get and Put; ECache
// an enum (an int compared with 1 gives the same rows), and public, declared ahead of Cache, whose parameter names it;
// Cache's default argument for the kind; MakeKey a member (how-to step 3: its callers pass an object it never
// reads; a free function that takes the object first gives the same rows); the cast that makes the tag a prvalue (a
// C-style cast gives the same rows), which converts nothing on the chosen long long and may stand for a conversion from
// the original member's type. src/units/237-uenux2-itexttospeech.mk lists the other forms measured.
class ITextToSpeech {
public:
    struct SOptions {
        std::string voice;
        unsigned rate;
        unsigned pitch;
        unsigned volume;
        long long tag;
    };
    enum ECache { eCacheRecent, eCacheKept };

    virtual std::shared_ptr<CWavFile> Synthesize(const std::string& text)
    {
        SOptions options = GetOptions();
        std::string key = MakeKey(text, options);
        if (std::shared_ptr<CWavFile> wav = Lookup(key))
            return wav;
        std::shared_ptr<CWavFile> wav = DoSynthesize(text, options);
        Store(key, wav, eCacheRecent);
        return wav;
    }
    void Cache(const std::string& text, ECache cache = eCacheKept)
    {
        SOptions options = GetOptions();
        std::string key = MakeKey(text, options);
        if (std::shared_ptr<CWavFile> wav = Lookup(key)) {
            m_kept[key] = wav;
            return;
        }
        std::shared_ptr<CWavFile> wav = DoSynthesize(text, options);
        Store(key, wav, cache);
    }
    virtual void SetVoice(const std::string& voice) { m_voice = voice; }
    virtual void SetPitch(unsigned pitch) { m_pitch = pitch; }
    virtual void SetVolume(unsigned volume) { m_volume = volume; }
    virtual void SetSpeed(int speed)
    {
        m_speed = speed;
        m_rate = speed * 20 + 60;
    }
    virtual int GetSpeed() { return m_speed; }
    virtual void IncreaseSpeed()
    {
        m_speed = m_speed == 4 ? 4 : m_speed + 1;
        m_rate = m_speed * 20 + 60;
    }
    virtual void DecreaseSpeed()
    {
        m_speed = m_speed != 0 ? m_speed - 1 : 0;
        m_rate = m_speed * 20 + 60;
    }
    virtual void SetTag(long long tag) { m_tag = tag; }
    virtual ~ITextToSpeech() = default;
    virtual std::shared_ptr<CWavFile> DoSynthesize(const std::string& text, const SOptions& options) = 0;

private:
    struct SRecentCache {
        using TEntry = std::pair<std::string, std::shared_ptr<CWavFile>>;

        std::shared_ptr<CWavFile> Get(const std::string& key)
        {
            if (index.find(key) == index.end())
                return nullptr;
            auto entry = index[key];
            entries.splice(entries.begin(), entries, entry);
            return entry->second;
        }

        void Put(const std::string& key, const std::shared_ptr<CWavFile>& wav)
        {
            if (index.find(key) != index.end()) {
                auto entry = index[key];
                entry->second = wav;
                entries.splice(entries.begin(), entries, entry);
                return;
            }
            if (index.size() == capacity) {
                TEntry last = entries.back();
                index.erase(last.first);
                entries.pop_back();
            }
            entries.emplace_front(key, wav);
            index[key] = entries.begin();
        }

        unsigned capacity = 256;
        std::list<TEntry> entries;
        std::unordered_map<std::string, std::list<TEntry>::iterator> index;
    };

    SOptions GetOptions() { return {m_voice, m_rate, m_pitch, m_volume, m_tag}; }

    std::string MakeKey(const std::string& text, const SOptions& options)
    {
        return std::format("{}:{}:{}:{}:{}", text, options.rate, options.voice, options.pitch,
                           static_cast<long long>(options.tag));
    }

    std::shared_ptr<CWavFile> Lookup(const std::string& key)
    {
        auto kept = m_kept.find(key);
        if (kept != m_kept.end())
            return kept->second;
        return m_recent.Get(key);
    }

    void Store(const std::string& key, std::shared_ptr<CWavFile> wav, ECache cache)
    {
        if (cache == eCacheKept)
            m_kept[key] = wav;
        else
            m_recent.Put(key, wav);
    }

    SRecentCache m_recent;
    std::unordered_map<std::string, std::shared_ptr<CWavFile>> m_kept;
    int m_speed = 2;
    std::string m_voice;
    unsigned m_volume = 50;
    unsigned m_pitch = 100;
    unsigned m_rate = 100;
    long long m_tag = 0;
};

} // namespace api
