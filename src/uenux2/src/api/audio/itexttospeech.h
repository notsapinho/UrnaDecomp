#pragma once

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
// The class has no key function: its typeinfo and its vtable lie inside vota_web_wasm.cpp's data (the typeinfo between
// that file's records at 1526324 and 1526348, the vtable before its record at 1526584), a copy in a TU that uses the
// class, where a key function would have put them in that function's own TU. So every virtual member is inline or pure.
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
// every member and data member name, SOptions, SRecentCache, and the types int and long long where the wasm type alone
// says i32 or i64. Synthesize / DoSynthesize follows the project's Converte / DoConverte (comum::asn::IConversorASN's
// records); volume is the third of RHVoice's three, by elimination; SetTag is named for what the body does with the value,
// since slot 8 has no caller in the target (no call_indirect of its type (i32, i64)->() goes through +32). 4 and 0, the
// limits of slots 6 and 7, have no name.
// Synthesize is inline in the original, like every other member. It is declared here without a body and trapped in
// src/units/82-uenux2-cwasmnulltexttospeech-pending.cpp until its callees exist (that file says which), and moves into
// the class with its body.
class ITextToSpeech {
public:
    struct SOptions {
        std::string voice;
        unsigned rate;
        unsigned pitch;
        unsigned volume;
        long long tag;
    };

    virtual std::shared_ptr<CWavFile> Synthesize(const std::string& text);
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

        unsigned capacity = 256;
        std::list<TEntry> entries;
        std::unordered_map<std::string, std::list<TEntry>::iterator> index;
    };

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
