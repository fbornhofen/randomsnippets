#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

class Position
{
public:

    int x, y;

    Position(int a, int b) : x(a), y(b) {
    }

    Position() : x(-1), y(-1) {
    }

    bool IsValid() const {
        return x >= 0 && y >= 0;
    }

    bool Reaches(const Position& p) const {
        return IsValid() && p.IsValid() &&
            (x == p.x ||
             y == p.y ||
             abs(y - p.y) == abs(x - p.x));
    }

    void Print() const {
        std::cout << "Position(" << x << "," << y << ")" << std::endl;
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

void NQueens(int size, Stack<Position>* ps) {
    // FIXME filter permutations
    if (ps->Size() == size) {
        for (int i = 0; i < size; ++i) {
            ps->Elements()[i].Print();
        }
        cout << "---" << endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Position p(i, j);
            if (!ReachesAny(p, *ps)) {
                ps->Push(p);
                NQueens(size, ps);
                ps->Pop();
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
    NQueens(size, &s);
}
