#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <locale>
#include <fstream>

using namespace std;

class Name {
    string name_;

public:

    Name() {};
    Name(string s) : name_(s) {};

    virtual ~Name() {};

    void read_from(istream& s) {
        char c = 0;
        while (!isalnum(c) && !s.eof()) {
            c = s.get();
        }
        while (isalnum(c)) {
            name_ += c;
            c = s.get();
        }
    }

    string to_string() const {
        return name_;
    }

    int score() const {
        int res = 0;
        for (string::const_iterator it = name_.begin(); it != name_.end(); ++it) {
            res += (*it) - 'A' + 1;
        }
        return res;
    }

    bool operator<(const Name& other) const {
        return to_string() < other.to_string();
    }
};

class NamesCollection {
    vector<Name> names_;

public:
    NamesCollection() {};
    virtual ~NamesCollection() {};
    
    void read_from(istream& in) {
        string s;
        for (;;) {
            Name n;
            n.read_from(in);
            if (n.to_string().length() == 0) {
                break;
            }
            names_.push_back(n);
        }
    }

    void sort() {
        std::sort(names_.begin(), names_.end());
    }

    int total_score() {
        int res = 0;
        sort();
        for (int i = 0; i < names_.size(); ++i) {
            res += (i+1) * names_[i].score();
        }
        return res;
    }

};

int main() {
    ifstream in("names.txt");
    NamesCollection nc;
    nc.read_from(in);
    cout << nc.total_score() << endl;
    return 0;
}

