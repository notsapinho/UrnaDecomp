#include "ibeep.h"

namespace api {

std::vector<std::pair<int, int>> IBeep::ConfirmTones()
{
    return {{2300, 10}, {2200, 10}};
}

std::vector<std::pair<int, int>> IBeep::ErrorTones()
{
    std::vector<std::pair<int, int>> tones;
    tones.push_back({392, 50});
    tones.push_back({370, 50});
    tones.push_back({349, 50});
    for (int i = 0; i < 3; ++i) {
        tones.push_back({329, 10});
        tones.push_back({334, 10});
        tones.push_back({329, 10});
        tones.push_back({324, 10});
    }
    tones.push_back({329, 10});
    return tones;
}

std::vector<std::pair<int, int>> IBeep::AlertTones()
{
    return {{1244, 20}, {830, 20},  {1046, 20}, {1244, 20}, {1661, 10}, {1568, 10}, {1661, 15}, {5, 5},    {1864, 10},
            {1661, 10}, {1864, 15}, {5, 5},     {2489, 10}, {2349, 10}, {2489, 10}, {2349, 10}, {2489, 40}};
}

std::vector<std::pair<int, int>> IBeep::DiscardTones()
{
    return {{2489, 11}, {2349, 11}, {1864, 11}, {1568, 11}, {1244, 11}, {1174, 11}, {1244, 69}};
}

} // namespace api
