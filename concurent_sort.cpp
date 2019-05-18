#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using std::vector;
using std::cout;

std::mutex increment;

void countEven(const std::vector<int> & numbers, int & num) {
    for (const auto x: numbers) {
        if (x % 2 == 0) {
            increment.lock();
            ++num;
            increment.unlock();
        }
    }
}

vector<int>* twoSum(vector<int>& nums, int target) {
        int i = 0;
        int j = nums.size()-1;
        vector<int> *a = new vector<int>(2);
        while (i < j) {
            if (nums[i] + nums[j] < target)
                ++i;
            else if (nums[i] + nums[j] > target)
                --j;
            else {
                (*a)[0] = i;
                (*a)[1] = j;
                break;
            }
        }
        return a;
}
int main() {
    std::vector<int> numbers1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> numbers2 = {11, 12, 13, 14, 15, 16, 17, 18};

    int numEven = 0;

    std::thread t1(countEven, std::ref(numbers1), std::ref(numEven));
    std::thread t2(countEven, std::ref(numbers2), std::ref(numEven));

    t1.join();
    t2.join();

    std::cout << "Total number of even numbers is: " << numEven << std::endl;*/
    vector <int> num;
    num.push_back(2);
    num.push_back(4);
    num.push_back(5);
    num.push_back(7);
    num.push_back(10);
    for (int x: num)
        cout << x << " ";
    vector <int> *a = twoSum(num, 11);
    cout << "\n";
    for (int x: *a)
        cout << x << " ";
    return 0;
}
