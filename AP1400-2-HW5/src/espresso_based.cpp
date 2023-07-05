#include "espresso_based.h"

EspressoBased::EspressoBased(const EspressoBased &esp)
    : name(esp.name) {
    for (const auto& i : esp.ingredients) {
        ingredients.push_back(i->clone());
    }
}

EspressoBased& EspressoBased::operator=(const EspressoBased &esp) {
    if (this != &esp) {
        this->~EspressoBased();
        name = esp.name;
        for (const auto &i: esp.ingredients) {
            ingredients.push_back(i->clone());
        }
    }
    return *this;
}
