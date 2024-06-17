#include <string>

using namespace std;

class Trie {
public:
    Trie() {

    }
    
    void insert(string word) {
        char c = word[0];
        if(word.length()  > 1){
            string substr = word.substr(1);
            if(children[c-97] != nullptr){
                children[c-97]->insert(substr);
            }else{
                children[c-97] = new Trie();
                children[c-97]->val = c;
                children[c-97]->is_word = false;
                children[c-97]->insert(substr);
            }
        }else{
            if(children[c-97] != nullptr){
                //children[c-97]->insert(substr);
                children[c-97]->is_word = true;
            }else{
                children[c-97] = new Trie();
                children[c-97]->val = c;
                children[c-97]->is_word = true;
            }
        }
    }
    
    bool search(string word) {
        if(word.length()  > 1){
            char c = word[0];
            string substr = word.substr(1);
            if(children[c-97] != nullptr){
                return children[c-97]->search(substr);
            }else{
                return false;
            }
        }else{
            char c = word[0];
            if(children[c-97] != nullptr){
                if(children[c-97]->is_word){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }            
        }
    }
    
    bool startsWith(string prefix) {
        if(prefix.length()  > 1){
            char c = prefix[0];
            string substr = prefix.substr(1);
            if(children[c-97] != nullptr){
                return children[c-97]->startsWith(substr);
            }else{
                return false;
            }
        }else{
            char c = prefix[0];
            if(children[c-97] != nullptr){
                return true;
            }else{
                return false;
            }            
        }
    }

private:
    char val;//根节点为dummy节点
    Trie* children[26]={nullptr};
    bool is_word = false;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */