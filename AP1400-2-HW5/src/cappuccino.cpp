#include "cappuccino.h"

Cappuccino::Cappuccino() {
    name = "Cappuccino";
    ingredients.push_back(new Espresso (2));
    ingredients.push_back(new Milk (2));
    ingredients.push_back(new MilkFoam (1));
}

Cappuccino::Cappuccino(const Cappuccino &cap)
    : EspressoBased(cap) {
    for (const auto& i : cap.side_items) {
        side_items.push_back(i->clone());
    }
}

Cappuccino& Cappuccino::operator=(const Cappuccino &cap) {
    Cappuccino tmp(cap);
    tmp.swap(*this);
    return *this;
}

double Cappuccino::price() {
    double sum = 0;
    for (const auto& i : ingredients) {
        sum += i->price();
    }
    for (const auto& i : side_items) {
        sum += i->price();
    }
    return sum;
}