// https://leetcode.cn/problems/design-add-and-search-words-data-structure/description/?envType=study-plan-v2&envId=top-interview-150

#include <string>

using namespace std;
class WordDictionary {
public:
    WordDictionary() {

    }
    
    void addWord(string word) {
        WordDictionary* node = this;
        for(auto c:word){
            if(node->children[c-'a'] == nullptr){
                node->children[c-'a'] = new WordDictionary();
                node = node->children[c-'a'];
            }else{
                node = node->children[c-'a'];
            }
        }
        node->is_word = true;
    }
    
    bool search(string word) {
        WordDictionary* node = this;
        for(int i = 0; i < word.size(); i++){
            WordDictionary* child_node;
            if(word[i] == '.'){
                if(i == word.size()-1){
                    for(int j = 0; j < 26; j++)
                    {
                        child_node = node->children[j];
                        if(child_node != nullptr && child_node->is_word == true){
                            return true;
                        }
                    }
                    return false;
                }
                for(int j = 0; j < 26; j++)
                {
                    child_node = node->children[j];
                    if(child_node != nullptr){
                        if(child_node->search(word.substr(i+1))){
                            return true;
                        }
                    }
                }
                return false;
            }else if(node->children[word[i] - 'a'] == nullptr){
                return false;
            }else{
                if(i == word.size()-1 && node->children[word[i] - 'a']->is_word == true){
                    return true;
                }
            }
            if(word[i] != '.'){
                node = node->children[word[i] - 'a'];
            }
        }
        return false;
    }

private:
    WordDictionary* children[26]={nullptr};
    bool is_word = false;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */