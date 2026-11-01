#pragma once

// (reconstruction note, not TSE's text) api::IPower, the power hardware's interface. Lines 354, 361, 409, 417 and 424
// are the throw records of target fns 8105, 8098, 8091, 8083 and 8074 (ledger/source-locations.tsv), which name this
// file, those five members and their signatures; every other line is placed to leave those where they are, and what
// the file holds between them is not recovered. RTTI names the class, a class with no base (typeinfo 1531032); the
// target has its typeinfo and no vtable of its own. Its one implementer in the wasm build is api::teste::CPowerMock
// (vtable @1530944, 17 slots), so the slots are read from that vtable: 0 to 12 are the members below, 13 and 14 the
// destructor's, 15 and 16 come after it.
//
// Evidence that the status block at +4 and the reads through slot 15 are this class's, not the mock's: comum's and
// vota's code holds only an IPower (the singleton of fn 862) and does the same call, `this->slot15(this + 4)`, then
// reads the block's fields, in fns 1898, 2774, 10226, 11107, 11188, 12017 and 12061. The callers show the calls and the
// block; that non-virtual inline members of this class hold that code is a reading (the same code in many callers, and
// binaryen inlines a function with one call site only), and only FoneDesconectado is reconstructed. Slots 0 to 6 have the same shape, so
// they are written here: that they are IPower's and not CPowerMock's is a reading too, and a CPowerMock that defines
// them gives the same bytes. Slot 7 reads the mock's own block (+32) without the call, so it is the mock's override,
// and pure here by choice; slots 15 and 16 are pure here by choice too.
//
// The block is 16 bytes of 32-bit words (fn 8071 copies it with i64 accesses of alignment 4). The target's loads say
// the fields share words: slot 2 tests a top half with `word < 65536`, slot 7 rewrites a low half with a 32-bit load and
// store, where uint16_t members give 16-bit accesses (measured: slots 2, 5 and 7 then differ). Bit-fields are a choice:
// four uint32_t words read with masks and shifts give the same bytes. Only the fields the members below read, and the
// ones the mock's initial value sets, are named. What the callers show of them:
// - word 0: bits 3-4 are the internal battery's status and bits 5-6 the external one's (fn 10226 passes them to
//   comum::CLogComum::LogaNivelBateria, fn 5875, with 1 and 2); bit 13 is slot 0's and nothing says what it is. Bits
//   1-2 hold 1 while the urn runs on its internal battery: fns 12017 and 12061 test `(word & 6) == 2`, and 12017 logs
//   "Tempo limite de espera usando bateria interna atingido" when its time limit passes; fn 2774 tests them for 2 and
//   then reads the external battery's bits. The field's name is chosen.
// - word 1: bit 1 is the headphone (fn 10226: set is "Fone de ouvido desconectado"); the top half is slot 1's.
// - word 2: the low half is slot 3's, the top half slot 4's.
// - word 3: the low half is what slot 2 signs and slot 5 scales, and the level of the mock's slot 7; the next byte is
//   slot 6's.
//
// Slot roles, from vota::CThreadMonitor::LogaStatusRedeAcBateria (its records sit in fn 10226), which divides each by
// 100 for "{} rede CA em [{:3.2f}V] e " and "na Bateria Interna com [{:2.2f}V/{}A]": slot 4 is the mains voltage, slot
// 1 the internal battery's, slot 3 the external battery's (taken instead of slot 1 when above 0), slot 2 the current.
// That caller reads them as signed (f64.convert_i32_s, i32.le_s), so they return int. Slot 2 is 0 with the internal
// battery's status at 3 and negative with no mains voltage. Slot 5 scales word 3's low half by a factor stepped on the
// battery voltage in use, the external one when it has one. Slot 7 is formatted as an unsigned ("{: >3}%", argument type
// 6, fn 11107) and masked to a byte, so it returns uebyte; an int return differs (measured). Slot 6's uebyte is chosen:
// int or unsigned give the same bytes. Every member name but the five records', every field name and the block's name
// are chosen: no record names them. Slots 0, 5, 6 and 16 have no caller that says what they are, so they keep their slot.
#include <cmath>
#include <cstdint>
#include <tuple>

#include "api/hwil/euehwilerror.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

class IPower {
public:
    struct SStatus {
        std::uint32_t : 1;
        std::uint32_t m_fonte : 2;
        std::uint32_t m_statusBatInt : 2;
        std::uint32_t m_statusBatExt : 2;
        std::uint32_t : 4;
        std::uint32_t m_bit11 : 1;
        std::uint32_t : 1;
        std::uint32_t m_bit13 : 1;
        std::uint32_t : 18;

        std::uint32_t : 1;
        std::uint32_t m_foneDesconectado : 1;
        std::uint32_t : 14;
        std::uint32_t m_tensaoBatInt : 16;

        std::uint32_t m_tensaoBatExt : 16;
        std::uint32_t m_tensaoRede : 16;

        std::uint32_t m_carga : 16;
        std::uint32_t m_byte14 : 8;
        std::uint32_t : 8;
    };

    virtual bool Slot0()
    {
        ReadStatus(m_status);
        return !m_status.m_bit13;
    }

    virtual int BatIntVoltage()
    {
        ReadStatus(m_status);
        return m_status.m_tensaoBatInt;
    }

    virtual int BatCurrent()
    {
        ReadStatus(m_status);
        if (m_status.m_statusBatInt == 3) {
            return 0;
        }
        const int carga = m_status.m_carga;
        return m_status.m_tensaoRede != 0 ? carga : -carga;
    }

    virtual int BatExtVoltage()
    {
        ReadStatus(m_status);
        return m_status.m_tensaoBatExt;
    }

    virtual int AcVoltage()
    {
        ReadStatus(m_status);
        return m_status.m_tensaoRede;
    }

    virtual int Slot5()
    {
        ReadStatus(m_status);
        const std::uint16_t tensao = m_status.m_tensaoBatExt != 0 ? m_status.m_tensaoBatExt : m_status.m_tensaoBatInt;
        double fator;
        if (tensao < 281) {
            fator = 1.0;
        } else if (tensao < 480) {
            fator = 0.035;
        } else if (tensao < 680) {
            fator = 0.055;
        } else if (tensao < 820) {
            fator = 0.086;
        } else if (tensao < 940) {
            fator = 0.0133;
        } else if (tensao < 1020) {
            fator = 0.0208;
        } else if (tensao < 1060) {
            fator = 0.29;
        } else if (tensao < 1080) {
            fator = 0.357;
        } else if (tensao < 1100) {
            fator = 0.392;
        } else if (tensao < 1120) {
            fator = 0.416;
        } else if (tensao < 1140) {
            fator = 0.439;
        } else if (tensao < 1160) {
            fator = 0.467;
        } else if (tensao < 1180) {
            fator = 0.502;
        } else if (tensao < 1200) {
            fator = 0.537;
        } else if (tensao < 1220) {
            fator = 0.584;
        } else if (tensao < 1240) {
            fator = 0.635;
        } else if (tensao < 1260) {
            fator = 0.694;
        } else if (tensao < 1280) {
            fator = 0.769;
        } else if (tensao < 1300) {
            fator = 0.863;
        } else {
            fator = 0.98;
        }
        return static_cast<int>(std::round(fator * m_status.m_carga));
    }

    virtual uebyte Slot6()
    {
        ReadStatus(m_status);
        return m_status.m_byte14;
    }

    virtual uebyte BatLevel() = 0;

    // (original lines 170-351: content not recovered)
#line 352
    virtual float BatIntMaxSocValue()
    {
        throw CUeHwilError(EUE_HWIL_BATINTMAXSOCVALUE_NAO_SUPORTADO, "Not supported");
    }

    // (original lines 357-358: content not recovered)
#line 359
    virtual void SetBatIntMaxSocValue(float)
    {
        throw CUeHwilError(EUE_HWIL_SETBATINTMAXSOCVALUE_NAO_SUPORTADO, "Not supported");
    }

    // (original lines 364-406: content not recovered)
#line 407
    virtual std::tuple<bool, float> BatIntStorageMode()
    {
        throw CUeHwilError(EUE_HWIL_BATINTSTORAGEMODE_NAO_SUPORTADO, "Not supported");
    }

    // (original lines 412-414: content not recovered)
#line 415
    virtual void EnableBatIntStorageMode(float)
    {
        throw CUeHwilError(EUE_HWIL_ENABLEBATINTSTORAGEMODE_NAO_SUPORTADO, "Not supported");
    }

    // (original lines 420-421: content not recovered)
#line 422
    virtual void DisableBatIntStorageMode()
    {
        throw CUeHwilError(EUE_HWIL_DISABLEBATINTSTORAGEMODE_NAO_SUPORTADO, "Not supported");
    }

    virtual ~IPower() = default;

    // Fn 1898's slot-15 call and read of bit 1 of word 1. The member and its name are chosen, and the statements written
    // in the caller give the same object: src/units/116-uenux2-cthreads.mk lists the forms.
    bool FoneDesconectado()
    {
        ReadStatus(m_status);
        return m_status.m_foneDesconectado;
    }

    // The slot-15 call and test of word 0's bits 1-2 that vota::CExibeAlertaDesligamento::ProcessTick (fn 12017) and
    // vota::CEstadoComDesligamentoAutomatico::ProcessTick's lambda (fn 12061) hold inlined. The member and its name are
    // chosen, as FoneDesconectado's are.
    bool UsandoBateriaInterna()
    {
        ReadStatus(m_status);
        return m_status.m_fonte == 1;
    }

protected:
    virtual void ReadStatus(SStatus& status) = 0;
    virtual bool Slot16() = 0;

    SStatus m_status{};
};

} // namespace api
