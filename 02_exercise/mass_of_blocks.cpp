#include <iostream>
#include <vector>

using namespace std;

int main() {
    long long n, density;
    cin >> n >> density;
    vector<unsigned long long> sizes;
    for (int i = 0; i < n; ++i) {
        unsigned long long mul = 1;
        for (int j = 0; j < 3; ++j) {
            int k;
            cin >> k;
            mul *= k;
        }
        sizes.push_back(mul);
    }
    unsigned long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += sizes[i];
    }
    unsigned long long v = sum * density;
    cout << v;
    return 0;
}