#include <iostream>
#include <vector>
#include <string>
using namespace std;

void backtranqui (vector <string> &ans, string s, vector <int> v, int ind) {
    if (ind == v.size()) {ans.push_back (s); return;}
 
    s += to_string (v[ind]);
    backtranqui (ans, s, v, ind + 1);
    
    s.pop_back();
    s += " ";
    s += to_string (v[ind]);
    backtranqui (ans, s, v, ind + 1);

    s.pop_back();
    s.pop_back();
}

void problema_2 () {
    vector <int> v = {4, 5, 9, 2};
    string s = to_string (v[0]);
    vector <string> ans;
    backtranqui (ans, s, v, 1);
    for (auto it : ans) cout << it << endl;
}

int main () {
    problema_2 ();
    return 0;
}