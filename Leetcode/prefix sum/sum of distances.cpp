/*
🔹 Problem: 2615. Sum of Distances
🔹 Source: LeetCode

============================================================
💡 PROBLEM UNDERSTANDING

For each index i, we need:
    sum of |i - j| for all j such that nums[i] == nums[j]

👉 Important:
We are NOT comparing values — we are computing DISTANCES BETWEEN INDICES.

============================================================
🟥 1. BRUTE FORCE (O(n²))

Idea:
For each index i:
    - Compare with every index j
    - If nums[i] == nums[j], add |i - j|

Why it works:
It directly follows the problem definition.

Why it's slow:
Two nested loops → O(n²)
For n = 1e5 → impossible to run in time.

------------------------------------------------------------
*/

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> ans(n, 0);

        for(int i = 0; i < n; i++){
            long long res = 0;

            for(int j = 0; j < n; j++){
                if(i != j && nums[i] == nums[j]){
                    res += abs(i - j);
                }
            }

            ans[i] = res;
        }

        return ans;
    }
};


/*
============================================================
🟧 2. GROUPING USING HASHMAP

Key Observation:
We ONLY care about indices where values are equal.

So instead of:
    comparing every i with every j

We group indices by value.

Example:
nums = [1,3,1,1,2]

Groups:
1 → [0,2,3]
3 → [1]
2 → [4]

Now:
👉 We only compute distances WITHIN each group

------------------------------------------------------------
🟨 2A. GROUPING + BRUTE INSIDE GROUP

For each group:
    For each index in group:
        loop over all other indices in same group

Why it's better:
Avoids unnecessary comparisons across different values.

Why still bad:
Worst case:
    nums = [1,1,1,1,...]
    → one group of size n
    → still O(n²)

------------------------------------------------------------
*/

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;

        // Step 1: group indices
        for(int i = 0; i < nums.size(); i++){
            mp[nums[i]].push_back(i);
        }

        vector<long long> ans(nums.size(), 0);

        // Step 2: brute inside each group
        for(auto &p : mp){
            vector<int>& v = p.second;

            for(int i = 0; i < v.size(); i++){
                long long res = 0;

                for(int j = 0; j < v.size(); j++){
                    if(i != j){
                        res += abs(v[i] - v[j]);
                    }
                }

                ans[v[i]] = res;
            }
        }

        return ans;
    }
};


/*
============================================================
🟩 3. OPTIMAL: PREFIX SUM + MATH (O(n))

Now we eliminate the inner loop completely.

------------------------------------------------------------
💡 CORE IDEA

Instead of computing:
    for each i → loop over all j

We compute contribution using:
    - how many elements are on LEFT
    - how many elements are on RIGHT
    - what is their SUM

------------------------------------------------------------
📌 For a group:

v = [a0, a1, a2, ..., am-1]   (sorted indices)

We process each position i:

We want:
    sum of |a[i] - a[j]|

------------------------------------------------------------
🔵 Split into TWO PARTS

1️⃣ LEFT SIDE (j < i)

All elements before i:
    a[0], a[1], ..., a[i-1]

Distance:
    (a[i] - a[0]) + (a[i] - a[1]) + ...

Rewrite:
    = i * a[i] - (sum of left elements)

We maintain:
    prefix = sum of elements before i

So:
    LEFT = i * a[i] - prefix

------------------------------------------------------------
2️⃣ RIGHT SIDE (j > i)

All elements after i:
    a[i+1], a[i+2], ...

Distance:
    (a[j] - a[i])

Rewrite:
    = (sum of right elements) - (count * a[i])

We know:
    total_sum = S
    sum of right = S - prefix - a[i]
    count = m - i - 1

So:
    RIGHT = (S - prefix - a[i]) - (m - i - 1) * a[i]

------------------------------------------------------------
🔥 FINAL RESULT

res = LEFT + RIGHT

------------------------------------------------------------
💡 WHY THIS IS FAST

Instead of recomputing distances repeatedly:
    - We reuse prefix sums
    - Each element is processed once

Total work across all groups = n

------------------------------------------------------------
⏱ Complexity:
Time: O(n)
Space: O(n)
============================================================
*/

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        unordered_map<int, vector<int>> mp;

        // Step 1: group indices
        for (int i = 0; i < nums.size(); i++) {
            mp[nums[i]].push_back(i);
        }

        vector<long long> ans(nums.size(), 0);

        // Step 2: process each group
        for (auto &p : mp) {
            vector<int>& v = p.second;
            int m = v.size();

            if (m == 1) continue;

            // total sum of indices
            long long S = 0;
            for (int x : v) S += x;

            long long prefix = 0;

            for (int i = 0; i < m; i++) {
                long long idx = v[i];

                long long left  = (long long)i * idx - prefix;
                long long right = (S - prefix - idx) - (long long)(m - i - 1) * idx;

                ans[idx] = left + right;

                prefix += idx;
            }
        }

        return ans;
    }
};