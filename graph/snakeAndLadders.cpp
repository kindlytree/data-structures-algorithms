//问题记录：
// https://leetcode.cn/problems/snakes-and-ladders/solutions/846328/she-ti-qi-by-leetcode-solution-w0vl/

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits> // Include this header

using namespace std;
class Solution {

public:
    int getPosValue(vector<vector<int>>& board, int pos)
    {
        int row_index = (pos-1) / rows; //从下往上数
        int direction = row_index % 2;
        int col_index = (cols-1)*direction + (1-2*direction)*(pos-1) % cols; //
        int dest = board[rows-1-row_index][col_index];
        return dest;    
    }

    //pos为位置，从1到n的平方，val为值；
    void candidatePath(vector<vector<int>>& board, std::vector<bool>&visited, int pos, int val, int depth, int& minSteps, std::vector<string>path, std::vector<std::vector<string>>&allPossiblePaths){
        visited[pos] = true;
        path.push_back(std::to_string(pos));
        path.push_back("->");
        // if(depth >= minSteps){//如果depth比当前最小的深度要大，就进行剪枝不再需要继续遍历了。
        //     path.pop_back();
        //     path.pop_back();
        //     visited[pos] = false;
        //     return;
        // }
        
        if(val == -1)//可以往后走六步看看
        {
            //如果直接在目的地位置
            if(pos == goal){//直接跳到了目的地
                minSteps = depth;
                visited[pos] = false;
                //minPath = path;
                path.pop_back();
                path.push_back("\n");
                allPossiblePaths.push_back(path);
                path.pop_back();
                path.pop_back();                
                return;
            }//否则如果在一步抵达目标以内
            else if(pos+6 >= goal)
            {
                depth += 1;
                if(minSteps > depth)
                {
                    minSteps = depth;
                }
                visited[pos] = false;
                visited[goal] = false;
                path.push_back(std::to_string(goal));
                path.push_back("\n");
                allPossiblePaths.push_back(path);
                path.pop_back();
                path.pop_back();                  
                return;   
            }
            else  
            {
                for(int i = pos+1; i <= pos+6; i++)
                {
                    int new_val = getPosValue(board, i);//获取后面每一个candidate格子的值
                    //[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]这个示例中visited[13]在第二次遍历时更有
                    //所以要考虑回溯状态的恢复情况；
                    //如果出现的位置的值和位置一样，则跳不动需要过滤掉
                    //[[-1,4,-1],[6,2,6],[-1,3,-1]]
                    if(new_val == -1 && visited[i] == false){//如果值==-1，则可以考虑走一步再继续遍历,或者大于1，则跳到对应的位置,等于1没有意义不允许 不会走过去已经遍历过的
                        candidatePath(board, visited, i, new_val, depth+1, minSteps, path, allPossiblePaths);
                        //visited[i] = false;
                    }else if(new_val > 1 && new_val != i && visited[new_val] == false && visited[i] == false)
                    {
                        //int snake_end = getPosValue(board,new_val);
                        //visited[i] = true;
                        candidatePath(board, visited, i, new_val, depth+1, minSteps, path, allPossiblePaths);
                        //visited[i] = false;
                    }
                }
            }    

        }
        //val不会出现为1的情况，因为起始点为1的已经处理了，其他的为1的也滤除了。
        else if(val > 1)
        {
            if(val == goal){//直接跳到了目的地
                minSteps = depth;
                visited[pos] = false;
                path.push_back("->");
                path.push_back(std::to_string(goal));
                path.push_back("\n");
                allPossiblePaths.push_back(path);
                path.pop_back();
                path.pop_back();
                path.pop_back();
                return;
            }

            if(val > goal){
                visited[pos] = true;
                path.pop_back();
                path.pop_back();
                return;
            }
            
            int new_val = getPosValue(board, val);//考虑有循环的情况，如2的位置为-1，3的位置为2，这样就可能造成循环，
            //对于往回走的情况可以允许，但一定是没有遍历过的
            //[[-1,4,-1],[6,2,6],[-1,3,-1]] 边界条件
            if(new_val > 0 && new_val != val && visited[new_val] == false){//需要考虑有循环的情况,new_val如果为-1，继续深度优先遍历在new_val位置开始进行遍历，
                candidatePath(board, visited, val, new_val, depth, minSteps, path, allPossiblePaths);//
                //visited[val] = false;
            }else if(new_val == -1){
                candidatePath(board, visited, val, new_val, depth, minSteps, path, allPossiblePaths);//
                //visited[val] = false;
            }else if(new_val == 1){
                visited[pos] = true;
                path.pop_back();
                path.pop_back();
                return;
            }   
        }
        visited[pos] = false;
        path.pop_back();
        path.pop_back();
    }


    //pos为位置，从1到n的平方，val为值；
    void shortestPath(vector<vector<int>>& board, std::vector<bool>&visited, int pos, int val, int depth, int& minSteps, std::vector<string>path, std::vector<string>&minPath){
        visited[pos] = true;
        path.push_back(std::to_string(pos));
        path.push_back("->");
        if(depth >= minSteps){//如果depth比当前最小的深度要大，就进行剪枝不再需要继续遍历了。
            path.pop_back();
            path.pop_back();
            visited[pos] = false;
            return;
        }
        
        if(val == -1)//可以往后走六步看看
        {
            //如果直接在目的地位置
            if(pos == goal){//直接跳到了目的地
                minSteps = depth;
                visited[pos] = false;
                minPath = path;
                path.pop_back();
                path.pop_back();                
                return;
            }//否则如果在一步抵达目标以内
            else if(pos+6 >= goal)
            {
                depth += 1;
                if(minSteps > depth)
                {
                    minSteps = depth;
                }
                visited[pos] = false;
                visited[goal] = false;
                path.push_back(std::to_string(goal));
                minPath = path;
                path.pop_back();
                path.pop_back();                  
                return;   
            }
            else  
            {
                for(int i = pos+1; i <= pos+6; i++)
                {
                    int new_val = getPosValue(board, i);//获取后面每一个candidate格子的值
                    //[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]这个示例中visited[13]在第二次遍历时更有
                    //所以要考虑回溯状态的恢复情况；
                    //如果出现的位置的值和位置一样，则跳不动需要过滤掉
                    //[[-1,4,-1],[6,2,6],[-1,3,-1]]
                    if(new_val == -1 && visited[i] == false){//如果值==-1，则可以考虑走一步再继续遍历,或者大于1，则跳到对应的位置,等于1没有意义不允许 不会走过去已经遍历过的
                        shortestPath(board, visited, i, new_val, depth+1, minSteps, path, minPath);
                        //visited[i] = false;
                    }else if(new_val > 1 && new_val != i && visited[new_val] == false && visited[i] == false)
                    {
                        //int snake_end = getPosValue(board,new_val);
                        //visited[i] = true;
                        shortestPath(board, visited, i, new_val, depth, minSteps, path, minPath);
                        //visited[i] = false;
                    }
                }
            }    

        }
        //val不会出现为1的情况，因为起始点为1的已经处理了，其他的为1的也滤除了。
        else if(val > 1)
        {
            if(val == goal){//直接跳到了目的地
                minSteps = depth;
                visited[pos] = false;
                minPath = path;
                path.pop_back();
                path.pop_back();
                return;
            }
            if(val > goal){
                visited[pos] = true;
                path.pop_back();
                path.pop_back();
                return;
            }
            
            int new_val = getPosValue(board, val);//考虑有循环的情况，如2的位置为-1，3的位置为2，这样就可能造成循环，
            //对于往回走的情况可以允许，但一定是没有遍历过的
            //[[-1,4,-1],[6,2,6],[-1,3,-1]] 边界条件
            if(new_val > 0 && new_val != val && visited[new_val] == false){//需要考虑有循环的情况,new_val如果为-1，继续深度优先遍历在new_val位置开始进行遍历，
                //shortestPath(board, visited, val, new_val, depth, minSteps, path, minPath);//
                //不允许连续跳
                for(int i = new_val+1; i <= new_val+6; i++)
                {
                    //int new_val = getPosValue(board, i);//获取后面每一个candidate格子的值
                    shortestPath(board, visited, val, -1, depth+1, minSteps, path, minPath);//
                }
                //visited[val] = false;
            }else if(new_val == -1){
                shortestPath(board, visited, val, new_val, depth, minSteps, path, minPath);//
                //visited[val] = false;
            }else if(new_val == 1){
                visited[pos] = true;
                path.pop_back();
                path.pop_back();
                return;
            }   
        }
        visited[pos] = false;
        path.pop_back();
        path.pop_back();
    }

    int snakesAndLadders(vector<vector<int>>& board) {
        //首先从左下角的顶点开始
        rows = board.size();
        cols = board[0].size();
        goal = rows*cols;
        visited = std::vector<bool>(goal+1, false);
        std::vector<string>path;
        std::vector<string>minPath;
        int depth = 0;
        int pos = 1;
        int minSteps = std::numeric_limits<signed int>::max();
        if(rows % 2 == 1)
        {
            if(board[0][cols-1] != -1){return -1;}
        }else{
            if(board[0][0] != -1){return -1;}
        }
        if(board[rows-1][0] == 1){return -1;}
        std::vector<std::vector<string>>allPossiblePaths;
        shortestPath(board, visited, pos, board[rows-1][0], depth, minSteps, path, minPath);
        candidatePath(board, visited, pos, board[rows-1][0], depth, minSteps, path, allPossiblePaths);
        std::ofstream out_file("output.txt");
        if(minSteps ==  std::numeric_limits<signed int>::max()){
            minSteps = -1;
        }
        for(string elem : minPath){
            cout << elem;
        }
        for(auto path: allPossiblePaths){
            std::string path_;
            for(auto elem: path)
            {
                path_ += elem;
            }
            out_file <<  path_;
        }
        out_file.close();
        cout << std::endl;
        return minSteps;
    }

private:
    int rows;
    int cols;
    int goal;
    std::vector<bool> visited;
};


#include<queue>

class Solution2 {
    pair<int, int> id2rc(int id, int n) {
        int r = (id - 1) / n, c = (id - 1) % n;
        if (r % 2 == 1) {
            c = n - 1 - c;
        }
        return {n - 1 - r, c};
    }

public:
    int snakesAndLadders(vector<vector<int>> &board) {
        int n = board.size();
        vector<int> vis(n * n + 1);
        queue<pair<int, int>> q;
        q.emplace(1, 0);
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            //cout << "(" << p.first  << ","  << p.second << ")" << std::endl;
            for (int i = 1; i <= 6; ++i) {
                int nxt = p.first + i;
                //cout << "nxt=(" << nxt << ", " << p.first  << ","  << p.second << ")" << std::endl;
                if (nxt > n * n) { // 超出边界
                    break;
                }
                auto rc = id2rc(nxt, n); // 得到下一步的行列
                if (board[rc.first][rc.second] > 0) { // 存在蛇或梯子
                    nxt = board[rc.first][rc.second];
                    //cout << "nxt=(" << nxt << ", " << rc.first  << ","  << rc.second << ")" << std::endl;
                }
                //cout << "(" << p.first  << ","  << p.second+1 << ")" << std::endl;
                if (nxt == n * n) { // 到达终点
                    //cout << "success: nxt=(" << nxt  << ","  << n * n << ")" << std::endl;
                    return p.second + 1;
                }
                if (!vis[nxt]) {
                    vis[nxt] = true;
                    q.emplace(nxt, p.second + 1); // 扩展新状态
                }
            }
        }
        return -1;
    }
};


int main()
{
    vector<vector<int>> board = {{-1,-1,30,14,15,-1},{23,9,-1,-1,-1,9},{12,5,7,24,-1,30},{10,-1,-1,-1,25,17},{32,-1,28,-1,-1,32},{-1,-1,23,-1,13,19}};
    Solution sln;
    int steps = sln.snakesAndLadders(board);
    cout << steps << std::endl;
    // Solution2 sln2;
    // int steps2 = sln2.snakesAndLadders(board);
    // cout << steps2 << std::endl;
}