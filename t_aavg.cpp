#include <iostream>
#include <vector>

using namespace std;

long long t_avg(int x, const vector<int> &t) {
    long long agv = 0;
    for (int i = 0; i < x; ++i) {
        agv += t[i];
    }
    agv /= x;
    return agv;
};

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    int count = 0;
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    long long m = t_avg(n, t);
    for (int i = 0; i < n; ++i) {
        if (t[i] > m) {
            ++count;
        }
    }
    cout << count << endl;
    for (int i = 0; i < n; ++i) {
        if (t[i] > m) {
            cout << i << " ";
        }
    }
}
