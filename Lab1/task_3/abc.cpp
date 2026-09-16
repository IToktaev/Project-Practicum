#include <iostream>

int main()
{
    std::cout << "Enter 3 int numbers\n";

    int numOne, numTwo, numThree;
    std::cin >> numOne >> numTwo >> numThree;

    std::cout << "Sum: " << numOne + numTwo + numThree << "\n";

    return 0;
}