#include <bits/stdc++.h>
using namespace std;

int main(){
    // ZADANIE 1
    vector<string> vec = { "aaaa", "aa", "baa", "aba", "abababaabab" };
    regex regex1("(a){2}");
    cout << "First search - double a with regex_search:\n";
    for (auto it : vec){
        if(regex_search(it, regex1)){
            cout << "Found in string: " << it << endl;
        }
    }
    regex regex2(".*(a){2}.*");
    cout << "Second search - double a with regex_match:\n";
    for (auto it : vec){
        if(regex_match(it, regex2)){
            cout << "Found in string: " << it << endl;
        }
    }
    // ZADANIE 2
    regex hourMatch("^(0{2}|[1-9]|1[0-9]|2[0-3]):([0-5][0-9])$");
    string temp;
    cout << "HOUR: ";
    while(cin >> temp){
        if(regex_match(temp, hourMatch)){
            cout << "Success!\n";
            break;
        }
        else{
            cout << "HOUR: ";
        }
    }
    // ZADANIE 3
    regex emailMatch("([_a-z0-9-]+(\.[_a-z0-9-]+)*@([a-z0-9-\.]+)*(\.[a-z]{2,4}))");
    smatch emailParted;
    string emailTemp;
    cout << "EMAIL: ";
    while(cin >> emailTemp){
        if(regex_match(emailTemp, emailParted, emailMatch)){
            cout << "EMAIL correct! Domain is: " << emailParted.str(emailParted.size()-2) << emailParted[emailParted.size()-1] << endl;
            break;
        }
        else{
            cout << "EMAIL: ";
        }
    }
    // ZADANIE 4
    string phoneNumbers = "023 456 789, 223-111-555, 666 666 666, 999-999-999";
    regex numberMatch("[1-9]{3}[-|\\s)]\\d{3}[-|\\s]\\d{3}");
    string result = regex_replace(phoneNumbers, numberMatch, "nr_telefonu");
    cout << result << endl;
    // ZADANIE 5
    string words = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed et tincidunt mauris, sed mattis lorem. Donec diam risus, hendrerit ut nisi id, pharetra luctus lorem. Maecenas quis ipsum non sapien tempus scelerisque id eget purus. Fusce cursus, erat et eleifend semper, risus leo faucibus sem, et lobortis ante mi eu augue.";
    regex wordsMatch("[\\w^aoueiy]*([aoueiy][\\w^aoueiy]*){2}[\\w]*", std::regex_constants::icase);
    auto wordsBegin = sregex_iterator(words.begin(), words.end(), wordsMatch);
    auto wordsEnd = sregex_iterator();

    cout << "Found: " << distance(wordsBegin, wordsEnd) << " occurances in text.\n";
}
