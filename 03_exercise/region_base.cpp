//The "Base of Regions" task.
// The FindMaxRepetitionCount function, which accepts a region base and determines what maximum number
// of repetitions (number of occurrences of the same element) it contains.
// Two records (objects of Region type) are considered different if they differ by at least one field.

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class Lang {
    DE, FR, IT
};

struct Region {
    string std_name;
    string parent_std_name;
    map<Lang, string> names;
    int64_t population;
};

int FindMaxRepetitionCount(const vector<Region>& regions){
    if(regions.empty()) { return 0; }
    map<tuple<string, string, map<Lang, string>, int64_t>, int> y;
    for(auto &reg: regions) {
        y[tie(reg.std_name, reg.parent_std_name, reg.names, reg.population)] ++;
    }
    int count = 1;
    for(const auto &item: y){
        count = max(count, item.second);
    }
    return count;
}

int main() {
    cout << FindMaxRepetitionCount({
                                           {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Russia",
                                                   "Eurasia",
                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Russia",
                                                   "Eurasia",
                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                                                   89
                                           },
                                   }) << endl;

    cout << FindMaxRepetitionCount({
                                           {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Russia",
                                                   "Eurasia",
                                                   {{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Toulouse",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   89
                                           }, {
                                                   "Moscow",
                                                   "Russia",
                                                   {{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
                                                   31
                                           },
                                   }) << endl;

    return 0;
}
