#include "mocha.h"

Mocha::Mocha() {
    name = "Mocha";
    ingredients.push_back(new Espresso (2));
    ingredients.push_back(new Milk (2));
    ingredients.push_back(new MilkFoam (1));
    ingredients.push_back(new Chocolate (1));
}

Mocha::Mocha(const Mocha &cap)
        : EspressoBased(cap) {
    for (const auto& i : cap.side_items) {
        side_items.push_back(i->clone());
    }
}

Mocha& Mocha::operator=(const Mocha &cap) {
    Mocha tmp(cap);
    tmp.swap(*this);
    return *this;
}

double Mocha::price() {
    double sum = 0;
    for (const auto& i : ingredients) {
        sum += i->price();
    }
    for (const auto& i : side_items) {
        sum += i->price();
    }
    return sum;
}

