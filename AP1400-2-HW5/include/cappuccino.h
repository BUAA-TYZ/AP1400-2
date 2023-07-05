#ifndef CAPPUCCINO
#define CAPPUCCINO

#include "espresso_based.h"

class Cappuccino : public EspressoBased {
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
    ~Cappuccino() override {
        for(const auto& i : side_items)
            delete i;
        side_items.clear();
    }
    Cappuccino& operator=(const Cappuccino& cap);

    std::string get_name() override { return "Cappuccino"; }
    double price() override;

    void add_side_item(Ingredient* side) { side_items.push_back(side); }
    std::vector<Ingredient*>& get_side_items() { return side_items; }

private:
    std::vector<Ingredient*> side_items{};

    void swap(Cappuccino& cap) {
        std::swap(name, cap.name);
        std::swap(ingredients, cap.ingredients);
        std::swap(side_items, cap.side_items);
    }
};

#endif // CAPPUCCINO