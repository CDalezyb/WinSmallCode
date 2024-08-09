#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

template <class T>
void QuickSort(vector<T> &nums, int start, int end);

int main()
{
  std::vector<int> nums = {38, 27, 43, 3, 9, 82, 10};
  cout << "before sort" << endl;
  for (int num : nums)
    std::cout << num << " ";
  std::cout << std::endl;

  QuickSort<int>(nums, 0, nums.size() - 1);

  cout << "after sort" << endl;
  for (int num : nums)
    std::cout << num << " ";
  std::cout << std::endl;
  return 0;
}

// 升序排列
template <class T>
void QuickSort(vector<T> &nums, int start, int end)
{
  if (start >= end)
    return;

  int left = start, right = end;
  T base = nums[left];
  while (left < right)
  {
    while (left < right && nums[right] >= base)
      right--;
    nums[left] = nums[right];
    while (left < right && nums[left] < base)
      left++;
    nums[right] = nums[left];
  }

  nums[left] = base;

  QuickSort<T>(nums, start, left - 1);
  QuickSort<T>(nums, left + 1, end);
}
