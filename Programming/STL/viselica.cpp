#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

void upper_letters(string &word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = toupper(word[i]);
    }
}

void print_word(const string &word, const vector<bool> &ugadano) {
    for (int i = 0; i < word.length(); i++) {
        if (ugadano[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void print_alf(const vector<bool> &used) {
    string alf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "Dostupnye letters: ";
    for (int i = 0; i < alf.length(); ++i) {
        int index = alf[i] - 'A';
        if (!used[index]) {
            cout << alf[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    
    vector<string> list_of_words;
    list_of_words.push_back("PROGRAMMER");
    list_of_words.push_back("COMPILER");
    list_of_words.push_back("ALGORITHM");
    list_of_words.push_back("VARIABLE");
    list_of_words.push_back("FUNCTION");
    list_of_words.push_back("DATABASE");
    list_of_words.push_back("SOFTWARE");
    list_of_words.push_back("HARDWARE");
    list_of_words.push_back("OPERATING");
    list_of_words.push_back("DEVELOPER");
    
    srand(time(NULL)); // инициализируем генератор случайных чисел

    int random_index = rand() % list_of_words.size();
    string zagadannoe_word = list_of_words[random_index];
    upper_letters(zagadannoe_word);

    vector<bool> ugadano_letters(zagadannoe_word.length(), false);
    vector<bool> ispolzovano_letters(26, false);
    
    int mistake = 0;
    int max_mistake = 7;
    bool game_end = false;
    bool word_ugadano = false;
    
    cout << "<--- GAME VISILITSA --->" << endl;
    cout << "Zagadannoe word sostoit iz " << zagadannoe_word.length() << " letters." << endl;
    cout << "You have " << max_mistake << " tries." << endl;
    cout << endl;
    
    while (!game_end) {
        cout << "Remaning tries: " << (max_mistake - mistake) << endl;
        cout << "Word: ";
        print_word(zagadannoe_word, ugadano_letters);
        print_alf(ispolzovano_letters);
        
        bool all_ugadano = true;
        for (int i = 0; i < ugadano_letters.size(); i++) {
            if (!ugadano_letters[i]) {
                all_ugadano = false;
                break;
            }
        }
        
        if (all_ugadano) {
            word_ugadano = true;
            game_end = true;
            break;
        }
        
        cout << "Enter letter or all word: ";
        string in; cin >> in;
        upper_letters(in);
        
        if (in.length() == 1) {    // если буква
            char letter = in[0];
            int index_letter = letter - 'A';
            if (index_letter < 0 || index_letter >= 26) {
                cout << "Mistake: enter english letter" << endl;
                continue;
            }
            
            if (ispolzovano_letters[index_letter]) {
                cout << "This letter actually used" << endl;
                continue;
            }
        
            bool need_letter = false;
            for (int i = 0; i < zagadannoe_word.length(); i++) {
                if (zagadannoe_word[i] == letter) {
                    ugadano_letters[i] = true;
                    need_letter = true;
                }
            }
            ispolzovano_letters[index_letter] = true;
            
            if (need_letter) {
                cout << "Right! Letter " << letter << " in word." << endl;
            } 
            else {
                cout << "Sad! Letter " << letter << " not in word." << endl;
                mistake++;
                
                if (mistake >= max_mistake) {
                    game_end = true;
                }
            }
            cout << endl;
        } 
        else {
            if (in == zagadannoe_word) {
                word_ugadano = true;
                game_end = true;
            } 
            else {
                cout << "Sad! Word ne ugadano." << endl;
                game_end = true;
            }
        }
    }

    cout << "\n<--- GAME ENDED --->" << endl;
    if (word_ugadano) {
        cout << "Yeeees! You win!" << endl;
        cout << "Zagadannoe word was: " << zagadannoe_word << endl;
    } 
    else {
        cout << "You lose!" << endl;
        cout << "Zagadannoe word was: " << zagadannoe_word << endl;
    }
    
    return 0;
}