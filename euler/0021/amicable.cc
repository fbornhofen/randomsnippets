#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

vector<int>* divisors(int n)
{
    vector<int> tmp;
    for (int i = 2; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            tmp.push_back(i);
        }
    }
    vector<int>* all_divisors = new vector<int>;
    all_divisors->push_back(1);
    for (vector<int>::iterator it = tmp.begin();
         it != tmp.end();
         ++it) {
        if (*it != 1) {
            all_divisors->push_back(*it);
            int other = n / *it;
            if (*it == other) {
                continue;
            }
            all_divisors->push_back(n / *it);
        }
    }
    return all_divisors;
}

int vec_sum(const vector<int>& vec)
{
    int sum = 0;
    for (vector<int>::const_iterator it = vec.begin();
         it != vec.end();
         ++it) {
        sum += *it;
    }
    return sum;
}

int sum_of_divisors(int n)
{
    vector<int> *d = divisors(n);
    int res = vec_sum(*d);
    delete d;
    return res;
}

vector<pair<int, int> >* amicable_numbers(int limit)
{
    vector<int> sums_of_divisors(limit);
    vector<pair<int, int> >* amicable = new vector<pair<int, int> >;
    for (int i = 0; i < limit; ++i) {
        sums_of_divisors.at(i) = 0;
    }
    for (int i = 2; i < limit; ++i) {
        sums_of_divisors.at(i) = sum_of_divisors(i);
    }
    for (int i = 2; i < limit; ++i) {
        int sum = sums_of_divisors.at(i);
        if (sum >= limit || sum <= i) {
            continue;
        }
        if (sums_of_divisors.at(sum) == i) {
            amicable->push_back(make_pair(i, sum));
        }
    }
    return amicable;
}

int sum_of_amicables(int limit)
{
    vector<pair<int, int> >* amicables = amicable_numbers(limit);
    int sum = 0;
    for (vector<pair<int, int> >::iterator it = amicables->begin();
         it != amicables->end();
         ++it) {
        sum += it->first + it->second;
    }
    delete amicables;
    return sum;
}

int main()
{
    cout << sum_of_amicables(10000) << endl;
    return 0;
}
