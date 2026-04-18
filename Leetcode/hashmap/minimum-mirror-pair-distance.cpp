/*
🔹 Problem: Minimum Mirror Pair Distance
🔹 Source: LeetCode

💡 Approach:
- Store reversed values in hashmap
- For each number:
    - Check if current number exists in map
    - If yes → mirror pair found
    - Update minimum distance

🔥 Key Insight:
Store reverse(num) instead of num to match condition directly.

⏱ Complexity:
Time: O(n)
Space: O(n)
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

    int minMirrorPairDistance(vector<int>& nums) {
        int ans = INT_MAX;
        unordered_map<int,int> mp;

        for(int i = 0; i < nums.size(); i++){
            int num = nums[i];
            int revNum = rev(num);

            if(mp.find(num) != mp.end()){
                ans = min(ans, i - mp[num]);
            }

            mp[revNum] = i;
        }

        return ans == INT_MAX ? -1 : ans;
    }
};