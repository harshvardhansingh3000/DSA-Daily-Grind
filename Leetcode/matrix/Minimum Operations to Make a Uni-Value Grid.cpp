/*
🔹 Problem: 2033. Minimum Operations to Make a Uni-Value Grid
🔹 Source: LeetCode

============================================================
💡 PROBLEM UNDERSTANDING

We are given:
    - A grid of size m x n
    - An integer x

Operation allowed:
    - Add x or subtract x from any element

Goal:
    - Make all elements equal (uni-value grid)
    - Return minimum number of operations
    - If impossible → return -1

============================================================
🧠 KEY OBSERVATIONS

1️⃣ FEASIBILITY CONDITION

We can only convert a number 'a' to 'b' if:
    (a - b) % x == 0

So:
    👉 All elements must have the SAME remainder when divided by x
    👉 Otherwise → return -1

------------------------------------------------------------

2️⃣ WHAT VALUE SHOULD WE CONVERT ALL ELEMENTS TO?

We want to minimize:
    sum of operations

Each operation changes value by x:
    operations = |a[i] - k| / x

Ignoring division by x:
    minimize → sum |a[i] - k|

👉 This is minimized when k = MEDIAN

============================================================
🟥 1. BASIC SOLUTION (SORTING)

Steps:
    1. Flatten grid into array
    2. Sort the array
    3. Take median
    4. Check feasibility
    5. Compute operations

------------------------------------------------------------
⏱ Complexity:

Flatten: O(n)
Sort:    O(n log n)
Loop:    O(n)

Total:   O(n log n)

------------------------------------------------------------
⚠️ Drawback:

We only need MEDIAN, but sorting:
    → fully orders array (extra work)
============================================================
*/

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;

        // Step 1: Flatten grid
        for (auto &row : grid) {
            for (int val : row) {
                nums.push_back(val);
            }
        }

        // Step 2: Sort
        sort(nums.begin(), nums.end());

        int n = nums.size();
        int median = nums[n / 2];

        int operations = 0;

        // Step 3: Check feasibility + count operations
        for (int num : nums) {
            if (num % x != median % x) return -1;
            operations += abs(num - median) / x;
        }

        return operations;
    }
};

/*
============================================================
🟨 2. OPTIMIZED APPROACH USING nth_element

------------------------------------------------------------
🧠 WHAT IS nth_element?

Syntax:
    nth_element(begin, begin + k, end)

Guarantees:
    - Element at index k is correct (same as sorted array)
    - Elements before it are ≤ it
    - Elements after it are ≥ it
    - Entire array is NOT sorted

------------------------------------------------------------
📌 Example:

nums = [7, 2, 9, 1, 5]

nth_element(nums.begin(), nums.begin() + 2, nums.end());

Possible result:
    [2, 1, 5, 9, 7]

👉 5 is correctly placed (3rd smallest)
👉 Others are NOT sorted

------------------------------------------------------------
⚙️ HOW IT WORKS (INTUITION)

Based on Quickselect:
    1. Pick pivot
    2. Partition array
    3. Recurse only on one side

👉 Avoids full sorting

------------------------------------------------------------
⏱ Complexity:

Average: O(n)
Worst:   O(n²) (rare)

------------------------------------------------------------
🔥 WHY BETTER?

We only need median:
    → nth_element finds it in O(n)
    → avoids O(n log n) sorting

*/

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;

        // Step 1: Flatten grid
        for (auto &row : grid) {
            for (int val : row) {
                nums.push_back(val);
            }
        }

        int n = nums.size();

        // Step 2: Find median in O(n)
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int median = nums[n / 2];

        int operations = 0;

        // Step 3: Check feasibility + count operations
        for (int num : nums) {
            if (num % x != median % x) return -1;
            operations += abs(num - median) / x;
        }

        return operations;
    }
};
