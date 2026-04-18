/*
🔹 Problem: Circular Array Minimum Distance (LeetCode)
🔹 Pattern: Array + HashMap + Binary Search

────────────────────────────────────────────────────────

🧠 APPROACH 1: Brute Force

💡 Idea:
- For each query index q:
    - Traverse entire array
    - Find all indices j where nums[j] == nums[q]
    - Compute circular distance

⚠️ Important:
- Must use circular distance:
        dist = min(abs(i - j), n - abs(i - j))

⏱ Complexity:
Time: O(n * q)
Space: O(1)

--------------------------------------------------------
CODE (Brute Force)
--------------------------------------------------------
*/

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        vector<int> ans;

        for(int q : queries){
            int mini = INT_MAX;

            for(int j = 0; j < n; j++){
                if(j == q) continue;

                if(nums[j] == nums[q]){
                    int dist = abs(j - q);
                    dist = min(dist, n - dist);
                    mini = min(mini, dist);
                }
            }

            if(mini == INT_MAX) ans.push_back(-1);
            else ans.push_back(mini);
        }

        return ans;
    }
};

/*
────────────────────────────────────────────────────────

🧠 APPROACH 2: HashMap + Group Scan

💡 Idea:
- Store all indices for each value
        value → [indices]

- For each query:
    - Only check indices in that group

🔥 Improvement:
- Avoid scanning full array

⚠️ Limitation:
- Still scanning full group

⏱ Complexity:
Time: O(n + q * k)
Worst case: O(n²)

--------------------------------------------------------
CODE (HashMap + Scan)
--------------------------------------------------------
*/

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();

        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < n; i++){
            mp[nums[i]].push_back(i);
        }

        vector<int> ans;

        for(int q : queries){
            int val = nums[q];
            auto &vec = mp[val];

            if(vec.size() == 1){
                ans.push_back(-1);
                continue;
            }

            int mini = INT_MAX;

            for(int idx : vec){
                if(idx == q) continue;

                int dist = abs(idx - q);
                dist = min(dist, n - dist);

                mini = min(mini, dist);
            }

            ans.push_back(mini);
        }

        return ans;
    }
};

/*
────────────────────────────────────────────────────────

🧠 APPROACH 3: Optimal (Binary Search + Neighbors)

💡 Idea:
- Indices are sorted
- Closest element must be:
        → left neighbor
        → right neighbor

- Use binary search to find position

🔥 Key Insight:
Closest match lies among neighbors in sorted positions

⏱ Complexity:
Time: O(n + q log n)
Space: O(n)

--------------------------------------------------------
CODE (Optimal)
--------------------------------------------------------
*/

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();

        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < n; i++){
            mp[nums[i]].push_back(i);
        }

        vector<int> ans;

        for(int q : queries){
            int val = nums[q];
            auto &vec = mp[val];

            if(vec.size() == 1){
                ans.push_back(-1);
                continue;
            }

            int idx = lower_bound(vec.begin(), vec.end(), q) - vec.begin();

            int left = (idx - 1 + vec.size()) % vec.size();
            int right = (idx + 1) % vec.size();

            int dist1 = abs(q - vec[left]);
            dist1 = min(dist1, n - dist1);

            int dist2 = abs(q - vec[right]);
            dist2 = min(dist2, n - dist2);

            ans.push_back(min(dist1, dist2));
        }

        return ans;
    }
};