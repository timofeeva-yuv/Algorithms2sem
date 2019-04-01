#include <vector>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <queue>
#include <cstdio>
using namespace std;

class State {
public:
    State(int);
    State(const State*);
    State(int, const vector<int>);
    vector<int> getField() const { return field; }
    string getPath() const { return path; }
    bool tryMoveLeft();
    bool tryMoveRight();
    bool tryMoveUp();
    bool tryMoveDown();
    int getDim() const { return dim; }
    double getApproxDist() const;
    int getCmpFunc() const { return path.size() + getApproxDist(); }
    long long getHash() const;
private:
    vector<int> field;
    string path;
    int dim;
    int nullPos;
};

State::State(int num = 4) {dim = num;}

State::State(const State* other) {
    dim = other->getDim();
    std::copy(other->getField().begin(), other->getField().end(), std::back_inserter(field));
    path = other->getPath();
    nullPos = other->nullPos;
}

State::State(int _dim, const vector<int> _field) {
    dim = _dim;
    std::copy(_field.begin(), _field.end(), std::back_inserter(field));
    for (int i = 0; i < dim * dim; ++i) {
        if (_field[i] == 0) {
            nullPos = i;
        }
    }
}

bool State::tryMoveLeft() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == i * dim)
            return false;
    }
    std::swap(field[nullPos], field[nullPos - 1]);
    nullPos--;
    path.push_back('R');
    return true;
}

bool State::tryMoveRight() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == i * dim + dim - 1)
            return false;
    }
    std::swap(field[nullPos], field[nullPos + 1]);
    nullPos++;
    path.push_back('L');
    return true;
}

bool State::tryMoveUp() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == i)
            return false;
    }
    std::swap(field[nullPos], field[nullPos - 4]);
    nullPos -= 4;
    path.push_back('D');
    return true;
}

bool State::tryMoveDown() {
    for (int i = 0; i < dim; ++i) {
        if (nullPos == dim * dim - dim + i)
            return false;
    }
    std::swap(field[nullPos], field[nullPos + 4]);
    nullPos += 4;
    path.push_back('U');
    return true;
}

double State::getApproxDist() const {
    int answer = 0;
    for (int i = 0; i < dim; ++i)
        for (int j = 0; j < dim; ++j) {
            int num = field[i * dim + j];
            if (num == 0) num = dim * dim;
            int xdest = (num - 1) / dim;
            int ydest = (num - 1) % dim;
            answer += abs((i - xdest)) + abs((j - ydest));
        }
    return answer * 10;
}

long long State::getHash() const {
    long long ans = 0;
    long long pow10 = 1;
    for (int i = 0; i < dim * dim; ++i) {
        ans += field[i] * pow10;
        pow10 *= 10;
    }
    return ans;
}

struct Comparison {
    bool operator() (State& A, State& B) { return A.getCmpFunc() > B.getCmpFunc(); }
};

class Solver {
public:
    Solver(int, State);
    bool solve(string&);
private:
    std::priority_queue < State, std::deque<State>, Comparison> q;
    std::unordered_set<long long> used;
    int dim;
    State startState;
};

Solver::Solver(int _dim, State start) : dim(_dim), startState(start) {}

bool Solver::solve(string &answer) {
    q.push(startState);
    while (!q.empty()) {
        State curState = q.top();
        q.pop();
        if (used.find(curState.getHash()) != used.end()) {
            continue;
        }
        if (curState.getApproxDist() == 0) {
            answer = curState.getPath();
            return true;
        }
        else {
            used.insert(curState.getHash());
        }
        State left, right, up, down;
        left = right = up = down = curState;
        if (left.tryMoveLeft()) {
            if (used.find(left.getHash()) == used.end())
                q.push(left);
        }
        if (right.tryMoveRight()) {
            if (used.find(right.getHash()) == used.end())
                q.push(right);
        }
        if (up.tryMoveUp()) {
            if (used.find(up.getHash()) == used.end())
                q.push(up);
        }
        if (down.tryMoveDown()) {
            if (used.find(down.getHash()) == used.end())
                q.push(down);
        }
    }
    return false;
}

int inversionCount(vector<int> &field) {
    int inversion = 0;
    for (int i = 0; i < 16; i++) {
        if (field[i] != 0) {
            for (int j = i + 1; j < 16; ++j) {
                if (field[i] > field[j] && field[j] != 0) {
                    ++inversion;
                }
            }
        }
    }
    return inversion;
}

int main() {;
    int nullPos = 0;
    vector<int> field(16);
    for (int i = 0; i < 16; ++i) {
        int x;
        cin >> x;
        if (x == 0) {
            nullPos = i;
        }
        field[i] = x;
    }
    if ((inversionCount(field) + ((nullPos/4) + 1)) % 2 == 1) {
        cout << -1;
    }
    else {
        State A = State(4, field);
        Solver S(4, A);
        string ans = "";
        S.solve(ans);
        cout << ans.size() << "\n" << ans.c_str();
    }
    return 0;
}
