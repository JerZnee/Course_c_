#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Для простых типов
template<typename T>
T Sqr(T value);

// Для пары
template<typename K, typename V>
pair<K, V> Sqr(const pair<K, V>& value);

// Для мапа
template<typename K, typename V>
map<K, V> Sqr(const map<K, V>& value);

// Для вектора
template<typename T>
vector<T> Sqr(const vector<T>& value);

// Функция умножения
template<typename T>
T Sqr(T value){
    return value * value;
}

template<typename T>
vector<T> Sqr(const vector<T>& value) {
    vector<T> result;
    for (const T& i: value) {
        result.push_back(Sqr(i));
    }
    return result;
}

template<typename K, typename Second>
pair<K, Second> Sqr(const pair<K, Second>& value) {
    return {Sqr(value.first), Sqr(value.second)};
}

template<typename Key, typename V>
map<Key, V> Sqr(const map<Key, V>& value) {
    map<Key, V> result;
    for(const auto& element: value){
        result[element.first] = Sqr(element.second);
    }
    return result;
}



int main() {
// Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}
