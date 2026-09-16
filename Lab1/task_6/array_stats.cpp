#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    int n;
    std::cout << "Enter amount of numbers:\n";
    std::cin >> n;

    std::vector<int> nums = {};

    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;    
        nums.push_back(num);
    }


    float average = 0.0f;
    int min = nums[0];
    int max = nums[0];
    float sum = 0.0f;

    for (int i = 0; i < nums.size(); i++) {
        if (min > nums[i]) {
            min = nums[i];
        }

        if (max < nums[i]) {
            max = nums[i];
        }

        sum += nums[i];
    }

    average = sum / nums.size();

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Min: " << min << "\n";
    std::cout << "Max: " << max << "\n";
    std::cout << "Average: " << average << "\n";


    return 0;
}