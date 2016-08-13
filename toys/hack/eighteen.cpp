#include <iostream>
#include <vector>

using namespace std;

class Solution {
    //Write your code here
public:
    Solution(){}
    void enqueueCharacter(char c) {
        queue.push_back(c);
    }
    char dequeueCharacter() {
        char c = queue[0];
        queue.erase(queue.begin());
        return c;
    }
    void pushCharacter(char c) {
        stack.push_back(c);
    }
    char popCharacter() {
        char c = stack.back();
        stack.pop_back();
        return c;
    }
private:
    vector<char> queue;
    vector<char> stack;
};

// palindrome

int main() {
    // read the string s.
    string s;
    getline(cin, s);
    
  	// create the Solution class object p.
    Solution obj;
    
    // push/enqueue all the characters of string s to stack.
    for (int i = 0; i < s.length(); i++) {
        obj.pushCharacter(s[i]);
        obj.enqueueCharacter(s[i]);
    }
    
    bool isPalindrome = true;
    
    // pop the top character from stack.
    // dequeue the first character from queue.
    // compare both the characters.
    for (int i = 0; i < s.length() / 2; i++) {
        if (obj.popCharacter() != obj.dequeueCharacter()) {
            isPalindrome = false;
            
            break;
        }
    }
    
    // finally print whether string s is palindrome or not.
    if (isPalindrome) {
        cout << "The word, " << s << ", is a palindrome.";
    } else {
        cout << "The word, " << s << ", is not a palindrome.";
    }
    
    cout << endl;
    return 0;
}
