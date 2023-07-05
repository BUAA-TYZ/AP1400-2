#ifndef MOCHA_H
#define MOCHA_H

#include "espresso_based.h"

class Mocha : public EspressoBased {
public:
    Mocha();
    Mocha(const Mocha& cap);
    ~Mocha() override {
        for(const auto& i : side_items)
            delete i;
        side_items.clear();
    }
    Mocha& operator=(const Mocha& cap);

    std::string get_name() override { return "Mocha"; }
    double price() override;

    void add_side_item(Ingredient* side) { side_items.push_back(side); }
    std::vector<Ingredient*>& get_side_items() { return side_items; }

private:
    std::vector<Ingredient*> side_items{};

    void swap(Mocha& cap) {
        std::swap(name, cap.name);
        std::swap(ingredients, cap.ingredients);
        std::swap(side_items, cap.side_items);
    }
};

#endif // MOCHA_H