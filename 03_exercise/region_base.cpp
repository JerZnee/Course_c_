#include <vector>
#include <algorithm>
#include <set>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <deque>
#include <stack>
#include <list>

using namespace std;

void solve() {
    int n;
    deque<pair<int, bool>> a;
    cin >> n;
    a.resize(n);
    for(auto&el: a){
        char t;
        cin >> t;
        cin >> el.first;
        el.second = t == 'y';
    }

    while(!a.empty() && !a.front().second) a.pop_front();
    while(!a.empty() && !a.back().second) a.pop_back();

    if(a.empty()){
        cout << 0 << endl;
        return;
    }

    int ans = 1;
    int y_min=numeric_limits<int>::max(), n_max = -1;

    bool skip = false;

    for(auto &[sze, to_del]: a){
        if(to_del){
            skip = false;
            y_min = min(y_min, sze);
        } else{
            if(skip) continue;
            n_max = max(n_max, sze);
        }
        if(n_max >= y_min){
            ans++;
            n_max = -1;
            y_min = numeric_limits<int>::max();
            skip = true;
        } else{
            skip = false;
        }
    }

    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}
