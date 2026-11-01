// api::BatteryIconDataSource's constructor and UpdateBatteryIcon (/home/rubio/tse/uenux2/src/api/gui/cpowerinformation.cpp),
// and the map of icons they read. The reconstruction's notes are in cpowerinformation.h and
// src/units/164-uenux2-cpowerinformation.mk.
// The records of the target in this file:
//   119:16  BatteryIconDataSource<Orientation>::BatteryIconDataSource(), both orientations (inlined into fns 502, 5904)
//   131:24  BatteryIconDataSource<Orientation>::UpdateBatteryIcon(), both orientations (inlined into fns 10981, 10987)
// Every other line's place is a choice; the blank lines hold what is not recovered.

#include "api/gui/cpowerinformation.h"

#include <chrono>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "api/gui/cfixedimage.h"
#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/itimerscheduler.h"

namespace api {

namespace {

std::map<int, std::vector<SharedIImage>> s_icones;

std::vector<SharedIImage> CriaIcones(const std::string& horizontal, const std::string& vertical)
{
    return {std::make_shared<CFixedImage>(horizontal), std::make_shared<CFixedImage>(vertical)};
}

} // namespace

void CarregaIcones()
{
    s_icones = {
        {0, CriaIcones(":/resource/images/bateria/img-ac-bateria-full-hor.jpg", ":/resource/images/bateria/img-ac-bateria-full.jpg")},
        {1, CriaIcones(":/resource/images/bateria/img-ac-bateria-parcial-hor.jpg", ":/resource/images/bateria/img-ac-bateria-parcial.jpg")},
        {2, CriaIcones(":/resource/images/bateria/img-ac-bateria-critical-h.jpg", ":/resource/images/bateria/img-ac-bateria-critical.jpg")},
        {3, CriaIcones(":/resource/images/bateria/img-ac-sem-bateria-hor.jpg", ":/resource/images/bateria/img-ac-sem-bateria.jpg")},
        {4, CriaIcones(":/resource/images/bateria/img-bateria-full-hor.jpg", ":/resource/images/bateria/img-bateria-full.jpg")},
        {5, CriaIcones(":/resource/images/bateria/img-bateria-parcial-hor.jpg", ":/resource/images/bateria/img-bateria-parcial.jpg")},
        {6, CriaIcones(":/resource/images/bateria/img-bateria-critical-hor.jpg", ":/resource/images/bateria/img-bateria-critical.jpg")},
        {7, CriaIcones(":/resource/images/bateria/img-bateria-ext-full-hor.jpg", ":/resource/images/bateria/img-bateria-ext-full.jpg")},
        {8, CriaIcones(":/resource/images/bateria/img-bateria-ext-parc-hor.jpg", ":/resource/images/bateria/img-bateria-ext-parcial.jpg")},
        {9, CriaIcones(":/resource/images/bateria/img-bateria-ext-crit-hor.jpg", ":/resource/images/bateria/img-bateria-ext-critical.jpg")},
    };
}

namespace {

inline SharedIImage GetIcone(int estado, CPowerInformation::IconOrientation orientacao)
{
    if (s_icones.empty()) {
        CarregaIcones();
    }
    const auto icones = s_icones.find(estado);
    if (icones == s_icones.end()) {
        return nullptr;
    }
    return icones->second[static_cast<size_t>(orientacao)];
}

} // namespace

// (original lines 68-115: content not recovered)
#line 116
template <CPowerInformation::IconOrientation Orientation>
BatteryIconDataSource<Orientation>::BatteryIconDataSource()
    : m_timer(ITimerScheduler::GetInst().CreateTimer(std::chrono::milliseconds(1000), [this]() { UpdateBatteryIcon(); }))
    , m_estado(CPolySingleton<IPower>::instance().GetEstadoBateria())
{
    {
        const SharedIImage icone = GetIcone(m_estado, Orientation);
        std::lock_guard<std::mutex> lock(m_mutex);
        m_valor = icone;
    }
    m_timer->Start();
}
template <CPowerInformation::IconOrientation Orientation>
void BatteryIconDataSource<Orientation>::UpdateBatteryIcon()
{
    const int estado = CPolySingleton<IPower>::instance().GetEstadoBateria();
    if (estado != m_estado) {
        m_estado = estado;
        SetValor(GetIcone(estado, Orientation));
    }
}

template BatteryIconDataSource<CPowerInformation::IconOrientation::Vertical>::BatteryIconDataSource();
template BatteryIconDataSource<CPowerInformation::IconOrientation::Horizontal>::BatteryIconDataSource();

} // namespace api
