#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Trie {
public:
    Trie() {

    }
    void insert(string word) {
        Trie* node = this;
        for(auto c: word)
        {
            if(node->children[c-'a'] == nullptr){
                node->children[c- 'a'] = new Trie();
                
            }
            node = node->children[c-'a'];
        }
        node->is_word = true;
    }
    
    Trie* traverseByChar(char current_char, string& prefix, bool& is_word)
    {
        Trie* node = this;
        if(node->children[current_char-'a'] == nullptr){
            is_word = false;
            return nullptr;
        }else{
            node = node->children[current_char-'a'];
            prefix += current_char;
            if(node->is_word){
                is_word = true;
                return node;
            }else{
                is_word = false;
                return node;
            }
        }
    }

private:
    //char val;//根节点为dummy节点
    Trie* children[26]={nullptr};
    bool is_word = false;
};

class Solution {

    //建立一个前缀树
    Trie* words_tree = new Trie();
    void searchBoard(vector<vector<char>>& board, vector<vector<bool>>&visited, int row_index, int col_index, vector<string>&exist_words, Trie* currentTraverseNode, string& prefix, bool& is_word)
    {
        char c = board[row_index][col_index];
        visited[row_index][col_index] = true;
        string prefix_cache;
        Trie* nextTraverseNode = currentTraverseNode->traverseByChar(c, prefix, is_word);
        prefix_cache.assign(prefix);
        if(nextTraverseNode == nullptr){
            return;
        }
        if(is_word == true){
            auto it = std::find(exist_words.begin(), exist_words.end(), prefix);
            // 找到了重复的值
            if (it != exist_words.end()) {

            }else
            {
                exist_words.push_back(prefix);
            }
            is_word = false;
        }
        Trie* ret_node = nullptr;
        //move to left
        if(col_index >= 1 && visited[row_index][col_index-1] == false)
        {
            col_index -= 1;
            searchBoard(board, visited, row_index, col_index, exist_words, nextTraverseNode, prefix, is_word);
            visited[row_index][col_index] = false;
            prefix.assign(prefix_cache);
            col_index += 1;
        }
        //move to the right
        if(col_index < cols-1 && visited[row_index][col_index+1] == false)
        {
            col_index += 1;
            searchBoard(board, visited, row_index, col_index, exist_words, nextTraverseNode, prefix, is_word);
            visited[row_index][col_index] = false;
            prefix.assign(prefix_cache);
            col_index -= 1;
        }

        //move to up
        if(row_index >= 1 && visited[row_index-1][col_index] == false)
        {
            row_index -= 1;
            searchBoard(board, visited, row_index, col_index, exist_words, nextTraverseNode, prefix, is_word);
            visited[row_index][col_index] = false;
            prefix.assign(prefix_cache);
            row_index += 1;
        }
        //move to down
        if(row_index < rows-1 && visited[row_index+1][col_index] == false)
        {
            row_index += 1;
            searchBoard(board, visited, row_index, col_index, exist_words, nextTraverseNode, prefix, is_word);
            visited[row_index][col_index] = false;
            prefix.assign(prefix_cache);
            row_index -= 1;
        }
    }

public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        for(int i = 0; i < words.size(); i++){
            words_tree->insert(words[i]);
        }
        rows = board.size();
        cols = board[0].size();

        vector<string>exist_words;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
                string candidate="";
                bool is_word = false;
                searchBoard(board, visited, i, j, exist_words, words_tree, candidate, is_word);
            }
        }
        return exist_words;
    }

private:
    int rows = -1;
    int cols = -1;
};