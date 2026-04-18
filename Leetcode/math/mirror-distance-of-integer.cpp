/*
🔹 Problem: Mirror Distance of an Integer
🔹 Source: LeetCode

💡 Approach:
- Reverse the number
- Return abs(n - reverse(n))

🔥 Key Insight:
Simple digit reversal logic.

⏱ Complexity:
Time: O(digits)
Space: O(1)
*/

class Solution {
public:
    int rev(int num){
        int ans = 0;
        while(num > 0){
            ans = ans * 10 + num % 10;
            num /= 10;
        }
        return ans;
    }

    int mirrorDistance(int n) {
        return abs(n - rev(n));
    }
};