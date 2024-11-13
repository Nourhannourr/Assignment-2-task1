#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <map>
using namespace std;

class Words {
private:
    map<string, int> words;
public:
    void read_file(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Cannot open the file\n";
            return;
        }
        string word;
        while (file >> word) {
            word = check(word);  // returns the word with no punctuation at the (beginning || end ) & (in a lower case)
            if (!word.empty()) { //(condition)if the word ends it goes to the next one
                words[word]++;  // increment the count of each word
            }
        }
        file.close();
    }
    string check(string word) { //remove punctuation from both ( beginning & end )
        auto start = find_if(word.begin(), word.end(), [](char ch) { return !ispunct(ch); });
        //.base() return the last char which is not punctuation.
        auto end = find_if(word.rbegin(), word.rend(), [](char ch) { return !ispunct(ch); }).base();

        if (start < end) { //(condition) if there is no punctuation in the word
            word = string(start, end);//sub string to insert the whole word

        }
        else {
            word.clear(); // In case the word is all punctuation
        }
        //convert the whole word to lower case
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        return word;
    }
    void print() {
        for (auto it : words) { //loop on each element in map
            cout << "The word: (" << it.first << ") & Times a word exists = " << it.second << "\n";
        }
    }
};
int main() {
    Words w;
    string file;
    cout << "Please Enter your File Name:\n";
    cin >> file;
    w.read_file(file);
    cout << "The modified file is:\n\n";
    w.print();
    return 0;
}
