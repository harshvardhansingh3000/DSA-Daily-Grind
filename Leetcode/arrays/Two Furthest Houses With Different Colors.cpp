/*
🔹 Problem: Maximum Distance Between Different Colored Houses (LeetCode)
🔹 Pattern: Array + Observation

────────────────────────────────────────────────────────

APPROACH 1: Brute Force

Idea:
- Check all pairs (i, j)
- If colors[i] != colors[j], update distance

Insight:
- We try every possible pair → guarantees correctness

⏱ Complexity:
Time: O(n^2)
Space: O(1)

--------------------------------------------------------
CODE (Brute Force)
--------------------------------------------------------
*/

class SolutionBrute {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int ans = 0;

        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(colors[i] != colors[j]){
                    ans = max(ans, j - i);
                }
            }
        }

        return ans;
    }
};

/*
────────────────────────────────────────────────────────

APPROACH 2: Optimal (Edge-Based Observation)

Idea:
- Maximum distance will always involve:
        → first house (index 0)
        → or last house (index n-1)

Why?
- To maximize |i - j|, we want i and j as far apart as possible
- So one index must be at an edge

Steps:
1. From right → find farthest index where colors[i] != colors[0]
2. From left → find farthest index where colors[i] != colors[n-1]

Take maximum of both

⏱ Complexity:
Time: O(n)
Space: O(1)

--------------------------------------------------------
CODE (Optimal)
--------------------------------------------------------
*/

class Solution {
public:
    int maxDistance(vector<int>& colors) {
        int n = colors.size();
        int ans = 0;

        // compare with first element
        for(int i = n - 1; i >= 0; i--){
            if(colors[i] != colors[0]){
                ans = max(ans, i);
                break;
            }
        }

        // compare with last element
        for(int i = 0; i < n; i++){
            if(colors[i] != colors[n - 1]){
                ans = max(ans, n - 1 - i);
                break;
            }
        }

        return ans;
    }
};