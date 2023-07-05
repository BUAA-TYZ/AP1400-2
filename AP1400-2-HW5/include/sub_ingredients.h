#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

#define DEFCLASS(X, Y)                                  \
class X : public Ingredient {                           \
public:                                                 \
    explicit X (size_t units) : Ingredient{Y, units} {  \
        name = #X;                                     \
    }                                                   \
    std::string get_name() override { return name; }    \
    Ingredient* clone () override {                     \
        return new X (*this);                           \
    }                                                   \
};

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H