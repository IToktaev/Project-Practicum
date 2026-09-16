#include <iostream>
#include <cmath>

int main()
{
    float a = 0.0f;
    float b = 0.0f;
    float c = 0.0f;

    std::cout << "Enter coefficients a, b and c for 'ax^2 + bx + c = 0': ";
    std::cin >> a >> b >> c;

    float D = b * b - 4 * a * c;

    if (D > 0) {
        float x1 = (-b + sqrt(D)) / (2 * a);
        float x2 = (-b - sqrt(D)) / (2 * a);

        std::cout << "Solutons: " << x1 << " " << x2 << "\n";
    } else if (D == 0) {
        float x = -b / (2 * a);

        std::cout << "Solution: " << x << "\n";
    } else {
        std::cout << "There are no solutions";
    }

    return 0;
}
