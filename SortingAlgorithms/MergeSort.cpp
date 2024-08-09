#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
void MergeSortNoR(vector<int> &nums);

int main()
{
    std::vector<int> nums = {38, 27, 43, 3, 9, 82, 10};
    cout << "before sort" << endl;
    for (int num : nums)
        std::cout << num << " ";
    cout << endl;

    MergeSortNoR(nums);

    cout << "after sort" << endl;
    for (int num : nums)
        std::cout << num << " ";
    std::cout << std::endl;
    return 0;
}

// 升序排列 非递归
void MergeSortNoR(vector<int> &nums)
{
    const int len = nums.size();
    vector<int> temp(len);
    int gap = 1;
    while (gap < len)
    {
        for (int left = 0; left < len; left += 2 * gap)
        {
            int b1 = left, e1 = b1 + gap - 1;
            int b2 = e1 + 1, e2 = b2 + gap - 1;

            if (b2 >= len)
                break;
            if (e2 >= len)
                e2 = len - 1;

            int temIdx = left;

            while (b1 <= e1 && b2 <= e2)
            {
                if (nums[b1] < nums[b2])
                    temp[temIdx++] = nums[b1++];
                else
                    temp[temIdx++] = nums[b2++];
            }
            while (b1 <= e1)
                temp[temIdx++] = nums[b1++];
            while (b2 <= e2)
                temp[temIdx++] = nums[b2++];

            std::copy(temp.begin() + left, temp.begin() + e2 + 1, nums.begin() + left);

            // cout << "after sort" << endl;
            // for (int num : temp)
            //     std::cout << num << " ";
            // std::cout << std::endl;
            // std::cout << std::endl;
        }
        gap *= 2;
    }
}
