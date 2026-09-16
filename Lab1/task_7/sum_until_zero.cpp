#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    std::cout << "Enter int numbers until 0:\n";

    bool isExit = false;
    int num = 0;
    int amountOfNums = 0;
    int sum = 0;

    while (!isExit) {
        std::cin >> num;

        if (num == 0) {
            isExit = true;
        } else {
            amountOfNums++;
            sum += num;
        }
    }

    if (amountOfNums == 0) {
        std::cout << "Error!\n";
        return 1;
    } else {
        for (int i = 0; i < amountOfNums; i++) {
            std::cout << "*";
        }
        std::cout << "\n";
        std::cout << "Sum: " << sum << "\n"; 
        std::cout << "Amount: " << amountOfNums << "\n";
    }

    return 0;
}
