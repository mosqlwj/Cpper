//
// Created by liwenjie on 2023/4/18.
//
#include <iostream>
#include <vector>

using namespace std;

void quick_sort(vector<int> &nums, int left, int right) {
    // 递归终止条件，当待排序的左右下标相等或者左下标大于右下标时，表示已经无需排序
    if (left >= right) {
        return;
    }
    // 初始化i和j指针，以及基准元素pivot的位置
    int i = left, j = right, pivot = nums[left];
    // 进入循环，直到i和j相遇
    while (i < j) {
        // 从右向左遍历数组，找到第一个小于基准元素的元素
        while (i < j && nums[j] >= pivot) {
            j--;
        }
        // 将该元素放到左侧序列中，并继续从左向右遍历数组
        nums[i] = nums[j];
        while (i < j && nums[i] <= pivot) {
            i++;
        }
        // 将该元素放到右侧序列中，继续从右向左遍历数组
        nums[j] = nums[i];
    }
    // 当i和j相遇时，将基准元素放在该位置上，完成一次划分
    nums[i] = pivot;
    // 递归排序左侧序列和右侧序列
    quick_sort(nums, left, i - 1);
    quick_sort(nums, i + 1, right);
}

int main() {
    vector<int> nums = {6, 10, 13, 5, 8, 3, 2, 11};
    // 调用快速排序算法
    quick_sort(nums, 0, nums.size() - 1);
    // 输出排好序的序列
    for (int num: nums) {
        cout << num << " ";
    }
    return 0;
}