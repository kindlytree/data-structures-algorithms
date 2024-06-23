#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<limits>
#include<iostream>

using namespace std;

class Solution {
public:

    int isZeroOneMoreCharDistance(string& gene1, string& gene2)
    {
        int diff_count = 0;
        for(int i = 0; i < 8; i++)
        {
            if(gene1[i] != gene2[i]){
                diff_count++;
                if(diff_count >= 2){
                    return 2;
                }
            }
        }
        return diff_count;
    }
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        //首先根据bank构建一个无向图，图中每个节点对应着一个基因序列，相邻的节点为一个字符发生了变化
        //怎么去快速的构建这个图？
        int size = bank.size();
        if(size == 1)
        {
            if(isZeroOneMoreCharDistance(startGene, endGene) == 1){
                return 1;
            }else{
                return -1;
            }
        }
        //std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, initial_value));
        vector<vector<int>>geneGraph(size, vector<int>(size, -1));
        //就两两距离复杂度为n的平方，其实只求距离为1的即可，大于1的直接不往后续的去进行比较
        int goal_gene_index = -1;
        vector<int>candidateStartSearchNodes;
        int start_gene_index = -1;
        for(int i = 0; i < size; i++)
        {
            int end_diff_count = isZeroOneMoreCharDistance(bank[i], endGene);
            int start_diff_count = isZeroOneMoreCharDistance(bank[i], startGene);
            if(end_diff_count == 0)
            {
                goal_gene_index = i;
            }
            if(start_diff_count == 1)
            {
                candidateStartSearchNodes.push_back(i);
            }else if(start_diff_count ==0)
            {
                start_gene_index = i;
            }
            for(int j = i+1; j < size; j++)
            {
                int diff_count = isZeroOneMoreCharDistance(bank[i], bank[j]);
                if(diff_count == 1){
                    geneGraph[i][j] = 1;
                    geneGraph[j][i] = 1;
                }
            }
        }
        //找到
        //然后从candidatestartnodes分别求达到目的地的最短路径
        int candidate_size = candidateStartSearchNodes.size();
        if(candidate_size == 0)return -1;
        if(start_gene_index != -1)
        {
            candidateStartSearchNodes.clear();
            candidateStartSearchNodes.push_back(start_gene_index);
            candidate_size = 1;
        }
        
        int minSteps =  9;
        bool curr_found = false;
        for(int i = 0; i < candidate_size; i++)
        {
            int startNode = candidateStartSearchNodes[i];
            int steps = 1;
            if(start_gene_index != -1)
            {
                steps = 0;
            }
            queue<pair<int,int>> bfsQueue;//node index, step pair;
            bfsQueue.push(pair<int,int>(startNode,steps));
            vector<bool>visited(size, false);
            visited[startNode] = true;
            curr_found = false;
            if(goal_gene_index == startNode){
                minSteps = 1;
                return minSteps;
            }
            while(!bfsQueue.empty() && !curr_found)
            {
                pair<int,int>node = bfsQueue.front();
                bfsQueue.pop();
                int search_index = node.first;
                int steps = node.second;
                //从对角线上的(search_index,search_index)位置横向向右，纵向向上的矩阵单元进行搜索，找到值为1的候选
                //向右
                for(int col = search_index+1; col < size; col++)
                {
                   if(visited[col] == false && geneGraph[search_index][col] == 1){
                        if(goal_gene_index == col){
                            if(minSteps > steps + 1)
                            {
                                minSteps = steps+1;//在以当前的i节点作为起始节点已经找到了目标
                                curr_found = true;
                                break;
                            }
                        }else{
                            visited[col] = true;
                            bfsQueue.push(pair<int,int>(col, steps+1));
                        }
                    }
                }
                if(curr_found) break;
                //向左
                for(int row = search_index-1; row >=0 ; row--)
                {
                   if(visited[row] == false && geneGraph[row][search_index] == 1){
                        if(row == goal_gene_index){
                            if(minSteps > steps + 1)
                            {
                                minSteps = steps+1;//在以当前的i节点作为起始节点已经找到了目标
                                curr_found = true;
                                break;
                            }
                        }else{
                            visited[row] = true;
                            bfsQueue.push(pair<int,int>(row, steps+1));
                        }
                    }
                }
            }
        }
        if(curr_found)
        {
            return minSteps;
        }else{
            return -1;
        }
        
    }
};

int main()
{
    //string start_gene = "AAAAACCC";
    //string end_gene = "AACCCCCC";
    //vector<string> bank={"AAAACCCC","AAACCCCC","AACCCCCC"};

    // string start_gene = "AACCGGTT";
    // string   end_gene = "AACCGGTA";
    // vector<string> bank={"AACCGGTA","AACCGCTA","AAACGGTA"};

    // string start_gene = "AACCTTGG";
    // string   end_gene = "AATTCCGG";
    // vector<string> bank={"AATTCCGG","AACCTGGG","AACCCCGG", "AACCTACC"};    

    string start_gene = "AAAAAAAA";
    string   end_gene = "CCCCCCCC";
    vector<string> bank={"AAAAAAAA","AAAAAAAC","AAAAAACC","AAAAACCC","AAAACCCC","AACACCCC","ACCACCCC","ACCCCCCC","CCCCCCCA","CCCCCCCC"};
    Solution sln;
    int mini_gene = sln.minMutation(start_gene, end_gene, bank);
    cout << mini_gene << endl;

}