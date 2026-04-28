/*
🔹 Problem: 1391. Check if There is a Valid Path in a Grid
🔹 Source: LeetCode

============================================================
💡 PROBLEM UNDERSTANDING

We are given:
    - A grid of size m x n
    - Each cell represents a street type (1 to 6)

Each street connects specific directions:

1 → left ↔ right
2 → up ↕ down
3 → left ↔ down
4 → right ↔ down
5 → left ↔ up
6 → right ↔ up

We start at (0, 0) and need to reach (n-1, m-1).

Constraint:
    - We must follow valid street connections
    - We cannot change the grid

============================================================
🧠 KEY OBSERVATIONS

1️⃣ Movement is NOT one-way

It is NOT enough that:
    current cell → allows movement to next cell

We must also check:
    next cell → allows coming BACK to current cell

👉 This is called BIDIRECTIONAL CONNECTIVITY

------------------------------------------------------------

2️⃣ Why bidirectional check is required?

Example:
    current → RIGHT
    next cell → does NOT have LEFT

👉 Path is invalid

------------------------------------------------------------

3️⃣ Graph Interpretation

Each cell = node  
Edges exist only if:
    - current allows direction
    - neighbor allows reverse direction

👉 This becomes a graph traversal problem (DFS / BFS)

------------------------------------------------------------

4️⃣ Avoid infinite loops

We must track visited cells:
    Otherwise → cycles → infinite recursion

============================================================
🟥 APPROACH: DFS

Steps:
    1. Define direction map for each street type
    2. Start DFS from (0,0)
    3. For each direction:
        - Move to next cell
        - Check reverse connectivity
        - Continue DFS
    4. Use visited array to avoid cycles

------------------------------------------------------------
⏱ Complexity:

Time:  O(m * n)
Space: O(m * n)

============================================================
*/

class Solution {
public:
    int n, m;

    // Directions for each street type
    unordered_map<int, vector<vector<int>>> dirs;

    // Visited array
    vector<vector<bool>> vis;

    bool solve(int i, int j, vector<vector<int>> &grid) {

        // Boundary check
        if (i < 0 || i >= n || j < 0 || j >= m) return false;

        // Already visited → avoid cycle
        if (vis[i][j]) return false;

        // Destination reached
        if (i == n - 1 && j == m - 1) return true;

        vis[i][j] = true;

        // Explore all allowed directions from current cell
        for (auto &d : dirs[grid[i][j]]) {

            int nx = i + d[0];
            int ny = j + d[1];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            // 🔴 IMPORTANT: Check reverse connection
            for (auto &back : dirs[grid[nx][ny]]) {

                // If neighbor connects back to current
                if (nx + back[0] == i && ny + back[1] == j) {

                    if (solve(nx, ny, grid)) return true;
                }
            }
        }

        return false;
    }

    bool hasValidPath(vector<vector<int>>& grid) {

        n = grid.size();
        m = grid[0].size();

        // Direction mapping
        dirs = {
            {1, {{0,1},{0,-1}}},
            {2, {{1,0},{-1,0}}},
            {3, {{1,0},{0,-1}}},
            {4, {{1,0},{0,1}}},
            {5, {{-1,0},{0,-1}}},
            {6, {{-1,0},{0,1}}}
        };

        vis.assign(n, vector<bool>(m, false));

        return solve(0, 0, grid);
    }
};
