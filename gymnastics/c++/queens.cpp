#include <iostream>
#include <set>
#include <utility>
#include <cstdlib>

using namespace std;

class Position : public pair<int, int>
{
public:

    Position(int x, int y) : pair<int, int>(x, y) {
    }

    Position() : pair<int, int>(-1, -1) {
    }

    bool IsValid() const {
        return first >= 0 && second >= 0;
    }

    bool Reaches(const Position& p) const {
        return IsValid() && p.IsValid() &&
            (first == p.first ||
             second == p.second ||
             abs(second - p.second) == abs(first - p.first));
    }

    void Print() const {
        std::cout << "Position(" << first << "," << second << ")" << std::endl;
    }
};

template <class T>
class Stack
{
    T* xs_;
    int capacity_;
    int size_;

public:

    Stack(int c) : capacity_(c), size_(0) {
        xs_ = new T[c];
    }

    virtual ~Stack() {
        delete [] xs_;
    }

    void Push(const T& x) {
        xs_[size_++] = x;
    }

    const T& Pop() {
        return xs_[--size_];
    }

    const T* Elements() const {
        return xs_;
    }

    const int Size() const {
        return size_;
    }
};

bool ReachesAny(const Position& p, const Stack<Position>& s) {
    const Position* elems = s.Elements();
    for (int i = 0; i < s.Size(); ++i) {
        if (p.Reaches(elems[i])) {
            return true;
        }
    }
    return false;
}

void NQueens(int size, int start_x, int start_y, Stack<Position>& ps, set<set<Position> >& solutions) {
    if (ps.Size() == size) {
        set<Position> solution;
        for (int i = 0; i < size; ++i) {
            solution.insert(ps.Elements()[i]);
        }
        solutions.insert(solution);
        return;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Position p(i, j);
            if (!ReachesAny(p, ps)) {
                int next_x = start_x + 1;
                int next_y = start_y;
                if (next_x == size) {
                    next_x = 0;
                    next_y++;
                }
                ps.Push(p);
                NQueens(size, next_x, next_y, ps, solutions);
                ps.Pop();
            }
        }
    }
}

int main(int argc, char** argv)
{
    int size = 8;
    if (argc > 1) {
        size = atoi(argv[1]);
    }
    Stack<Position> s(size);
    set<set<Position> > solutions;
    NQueens(size, 0, 0, s, solutions);
    for (set<set<Position> >::iterator it = solutions.begin();
         it != solutions.end();
         ++it) {
        for (set<Position>::iterator pos = it->begin();
             pos != it->end();
             ++pos) {
            pos->Print();
        }
        cout << " ----- " << endl;
    }
}
