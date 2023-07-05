#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1 {
    const double PRECISION = 1e-5;

    double gradient_descent(double i_val, double step, std::function<double(double)> func) {
        // gradient order1 -> 0
        // gradient order2 > 0
        const double LIMIT = step;
        double gradient_1, gradient_2 = -1;
        auto calculate_gradient = [&func] (double val, double step) {
            return (func(val + step) - func(val)) / step;
        };
        do {
            gradient_1 = calculate_gradient(i_val, PRECISION);
            if (abs(gradient_1) > 1.1 * LIMIT) {
                i_val = (gradient_1 > 0) ? i_val - step : i_val + step;
                continue;
            }
            // for calculating gradient order2
            double gradient_1_2 = calculate_gradient(i_val + PRECISION, PRECISION);
            gradient_2 = (gradient_1_2 - gradient_1) / PRECISION;
            i_val = (gradient_1 > 0) ? i_val - step : i_val + step;
        } while (gradient_2 < 0);
        return i_val;
    }

    template<typename T, typename Func>
    T gradient_descent(T i_val, T step) {
        return gradient_descent(i_val, step, Func());
    }
}

#endif //Q1_H