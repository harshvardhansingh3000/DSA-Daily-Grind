/*
🔹 Problem: Robot Simulation (LeetCode)
🔹 Pattern: Simulation + Hashing

────────────────────────────────────────────────────────

APPROACH 1: Brute Force (Naive Obstacle Check)

Idea:
- Simulate robot movement step-by-step
- For each move:
    - Check ALL obstacles to see if next position is blocked

Problem:
- For every step → scanning obstacles → O(n)
- Total becomes:
        O(commands * steps * obstacles) → very slow

Insight:
We are repeatedly checking:
    "Does (x, y) exist in obstacles?"

This is a lookup problem → should be O(1), not O(n)

⏱ Complexity:
Time: O(m * k * n)
Space: O(1)

--------------------------------------------------------
CODE (Brute Force)
--------------------------------------------------------
*/

class SolutionBrute {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int x = 0, y = 0;
        int d = 0; // 0=N,1=E,2=S,3=W

        int dx[4] = {0,1,0,-1};
        int dy[4] = {1,0,-1,0};

        int maxDist = 0;

        for(int cmd : commands){
            if(cmd == -1){
                d = (d + 1) % 4;
            }
            else if(cmd == -2){
                d = (d + 3) % 4;
            }
            else{
                for(int step = 0; step < cmd; step++){
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    // check all obstacles
                    bool blocked = false;
                    for(auto &o : obstacles){
                        if(o[0] == nx && o[1] == ny){
                            blocked = true;
                            break;
                        }
                    }

                    if(blocked) break;

                    x = nx;
                    y = ny;

                    maxDist = max(maxDist, x*x + y*y);
                }
            }
        }

        return maxDist;
    }
};

/*
────────────────────────────────────────────────────────

APPROACH 2: Hashing with String (Better)

Idea:
- Store obstacles in hash set
- Instead of scanning → O(1) lookup

Insight:
Repeated search → use hashing

Implementation:
- Convert (x,y) → "x,y" string

Limitation:
- String creation is slow
- Extra memory overhead

⏱ Complexity:
Time: O(m)
Space: O(n)

--------------------------------------------------------
CODE (Hashing using string)
--------------------------------------------------------
*/

class SolutionBetter {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<string> st;

        for(auto &o : obstacles){
            st.insert(to_string(o[0]) + "," + to_string(o[1]));
        }

        int dx[4] = {0,1,0,-1};
        int dy[4] = {1,0,-1,0};

        int x = 0, y = 0, d = 0;
        int maxDist = 0;

        for(int cmd : commands){
            if(cmd == -1){
                d = (d + 1) % 4;
            }
            else if(cmd == -2){
                d = (d + 3) % 4;
            }
            else{
                for(int step = 0; step < cmd; step++){
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    string key = to_string(nx) + "," + to_string(ny);

                    if(st.count(key)) break;

                    x = nx;
                    y = ny;

                    maxDist = max(maxDist, x*x + y*y);
                }
            }
        }

        return maxDist;
    }
};

/*
────────────────────────────────────────────────────────

APPROACH 3: Optimal (Integer Hashing)

Idea:
- Instead of string → encode (x,y) into single integer

hash(x,y) = x + MULTIPLIER * y

Why this works:
- Unique mapping for coordinates
- Faster than string hashing
- Less memory overhead

MULTIPLIER:
- Slightly larger than coordinate range
- Here: 60013 (prime > 60000)

⏱ Complexity:
Time: O(m + n)
Space: O(n)

--------------------------------------------------------
CODE (Optimal)
--------------------------------------------------------
*/

class Solution {
public:
    static const long long MULT = 60013;

    long long hashCoord(int x, int y){
        return (long long)x + MULT * y;
    }

    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<long long> st;

        for(auto &o : obstacles){
            st.insert(hashCoord(o[0], o[1]));
        }

        int dx[4] = {0,1,0,-1};
        int dy[4] = {1,0,-1,0};

        int x = 0, y = 0, d = 0;
        int maxDist = 0;

        for(int cmd : commands){
            if(cmd == -1){
                d = (d + 1) % 4;
            }
            else if(cmd == -2){
                d = (d + 3) % 4;
            }
            else{
                for(int step = 0; step < cmd; step++){
                    int nx = x + dx[d];
                    int ny = y + dy[d];

                    if(st.count(hashCoord(nx, ny))) break;

                    x = nx;
                    y = ny;

                    maxDist = max(maxDist, x*x + y*y);
                }
            }
        }

        return maxDist;
    }
};