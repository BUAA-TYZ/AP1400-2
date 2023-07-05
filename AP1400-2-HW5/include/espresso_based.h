#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H

#include "ingredient.h"
#include "sub_ingredients.h"

class EspressoBased
{
public:
    virtual std::string get_name() = 0;
    virtual double price() = 0;

    void brew() {}
    std::vector<Ingredient*>& get_ingredients() { return ingredients; }

    virtual ~EspressoBased() {
        for(const auto& i : ingredients)
            delete i;
        ingredients.clear();
    }

protected:
    EspressoBased() = default;
    EspressoBased(const EspressoBased& esp);
    EspressoBased& operator=(const EspressoBased& esp);

    std::vector<Ingredient*> ingredients{};
    std::string name{};

};

#endif // ESPRESSO_BASED_H