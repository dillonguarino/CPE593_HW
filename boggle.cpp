#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Trie {
private:
    class Node {
    public:
        Node* child[26];
        bool isWord;
    };
    Node* root;
public:
    Trie() {
        root = new Node();
    }
    void add(string word) {
        Node* temp = root;
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        for (unsigned int i = 0; i < word.length(); i++) {
            if(temp->child[word[i]-'a'] == nullptr)
                temp->child[word[i]-'a'] = new Node();
            temp = temp->child[word[i]-'a'];
        }
        temp->isWord = true;
    }
    bool contains(string word) {
        Node *p = root;
        for(unsigned int i = 0; i < word.length(); i++) {
            p = p->child[word[i]-'a'];
            if(p == nullptr)
                return false;
        }
        return p->isWord;
    }
    bool containsPrefix(string s) {
        Node *p = root;
        for(unsigned int i=0; i < s.length(); i++) {
            p = p->child[s[i]-'a'];
            if(p==nullptr)
                return false;
        }
        return true;
    }
};


Trie dict;
int n = 1;
vector<vector<char>> board;

void boggle(string word, int row, int col, vector<vector <bool>> used) {
    if(row < 0 || row > n || col < 0 || col > n)
        return;
    if(used[row][col])
        return;
    used[row][col] = true;
    cout << "Word: " << word << "  row: " << row << "  col: " << col << endl;

    word+=board[row][col];
    cout << board[row][col] << endl;
    cout << word << endl;

    if(!dict.containsPrefix(word))
        return;
    if(dict.contains(word) && word.length() >= 3)
        cout << word << endl;
    boggle(word, row-1, col-1, used);
    boggle(word, row-1, col, used);
    boggle(word, row-1, col+1, used);
    boggle(word, row, col-1, used);
    boggle(word, row, col, used);
    boggle(word, row, col+1, used);
    boggle(word, row+1, col-1, used);
    boggle(word, row+1, col, used);
    boggle(word, row+1, col+1, used);
}

int main() {
    string word = "";

    // READ IN DICTIONARY
    ifstream dictFile;
    dictFile.open("dictionary.txt");
    string data;
    if(dictFile.is_open()) {
        while(!dictFile.eof()) {
            dictFile>>data;
            dict.add(data);
        }
    }
    else {
        dictFile.close();
        cout << "COULD NOT OPEN DICTIONARY FILE" << endl;
        return 0;
    }
    dictFile.close();

    cout << "DONE READING DICTIONARY" << endl;
    // READ IN DATA FILE
    ifstream dataFile;
    dataFile.open("boggle.dat");

    if(dataFile.is_open()) {
        dataFile >> n;
        vector<vector<bool>> used;
        board.resize(n);
        used.resize(n);
        for(int i = 0; i < n; i++) {
            board[i].resize(n);
            used[i].resize(n);
            for(int j = 0; j<n; j++) {
                dataFile >> board[i][j];
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        for(int i = 0; i < n; i++)
            for(int j = 0; j<n; j++)
                used[i][j] = false;
        boggle(word, 0, 2, used);
    }
    else {
        dataFile.close();
        cout << "COULD NOT OPEN DATA FILE" << endl;
        return 0;
    }
    dataFile.close();

    return 0;
}
