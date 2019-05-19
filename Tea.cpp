#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using std::vector;
using std::cin;
using std::pair;
using std::make_pair;

class Edge {
public:
    pair<size_t, size_t> getEdge () const {
        return make_pair(from, to);
    }
    size_t getCapacity () const {
        return capacity;
    }
    void setCapacity (size_t capacity) {
        this->capacity = capacity;
    }
    long long getFlow () const {
        return flow;
    }
    void setFlow (long long flow) {
        this->flow = flow;
    }
    long long getResidualCapacity () const {
        return static_cast<long long>(capacity) - flow;
    }
    Edge(size_t from, size_t to, size_t capacity) :
            from(from),
            to(to),
            capacity(capacity),
            flow(static_cast<long long>(0)) {}
private:
    size_t from, to;
    size_t capacity;
    long long flow;
};

class Net {
public:
    typedef pair<Edge*, Edge*> Arc;
    Net(size_t verticesCount, size_t source, size_t sink) :
            verticesCount(verticesCount),
            source(source),
            sink(sink) {
        edges.resize(verticesCount);
    }
    void addEdge(const Edge& edge) {
        Edge* straightEdge = new Edge(edge.getEdge().first, edge.getEdge().second, edge.getCapacity());
        Edge* reverseEdge = new Edge(edge.getEdge().second, edge.getEdge().first, 0);
        Arc straightArc = make_pair(straightEdge, reverseEdge);
        Arc reverseArc = make_pair(reverseEdge, straightEdge);
        edges[edge.getEdge().first].push_back(straightArc);
        edges[edge.getEdge().second].push_back(reverseArc);
    }
    const vector<Arc>& getOuterEdges(size_t from) const {
        return edges[from];
    }
    size_t getVerticesCount() const {
        return verticesCount;
    }
    size_t getSource() const {
        return source;
    }
    size_t getSink() const {
        return sink;
    }
private:
    size_t verticesCount;
    size_t source;
    size_t sink;
    vector<vector<Arc>> edges;
};

long long DFS(const Net& net, const vector<size_t>& layers, size_t vertex, vector<size_t>& edgeIterators,
              long long pushingFlow = std::numeric_limits<long long>::max()) {
    if (vertex == net.getSink() || pushingFlow == 0) {
        return pushingFlow;
    }
    const vector<Net::Arc>& arcs = net.getOuterEdges(vertex);
    for (size_t i = edgeIterators[vertex]; i < arcs.size(); ++i) {
        const Edge edge = *arcs[i].first;
        if (layers[edge.getEdge().first] + 1 != layers[edge.getEdge().second] || edge.getResidualCapacity() <= 0) {
            continue;
        }
        const long long newPushingFlow = std::min<long long>(pushingFlow, edge.getResidualCapacity());
        const long long pushedFlow = DFS(net, layers, edge.getEdge().second, edgeIterators, newPushingFlow);
        if (pushedFlow != 0) {
            arcs[i].first->setFlow(arcs[i].first->getFlow() + pushedFlow);
            arcs[i].second->setFlow(arcs[i].second->getFlow() - pushedFlow);
            return pushedFlow;
        }
    }
    if (edgeIterators[vertex] != arcs.size()) {
        ++edgeIterators[vertex];
    }
    return 0;
}

vector<size_t> buildLayeredNetwork (const Net& net) {
    std::queue<size_t> que;
    vector<size_t> layers(net.getVerticesCount(), static_cast<size_t>(-1));
    layers[net.getSource()] = 0;
    vector<bool> used(net.getVerticesCount(), false);
    que.push(net.getSource());
    while (!que.empty()) {
        const size_t vertex = que.front();
        que.pop();
        if (used[vertex]) {
            continue;
        }
        else {
            for (const Net::Arc& arc: net.getOuterEdges(vertex)) {
                if (arc.first->getResidualCapacity() <= 0) {
                    continue;
                }
                const size_t nextVertex = arc.first->getEdge().second;
                if (layers[nextVertex] == static_cast<size_t>(-1)) {
                    layers[nextVertex] = layers[vertex] + 1;
                    que.push(nextVertex);
                }
            }
        }
        used[vertex] = true;
    }
    return layers;
}

long long setMaxFlow (const Net& net) {
    long long maxFlow = 0;
    while (true) {
        vector<size_t> layers = buildLayeredNetwork(net);
        if (layers[net.getSink()] == static_cast<size_t>(-1)) {
            break;
        }
        long long augmentation = 0;
        vector<size_t> edgeIterators(net.getVerticesCount(), 0);
        do {
            augmentation = DFS(net, layers, net.getSource(), edgeIterators);
            maxFlow += augmentation;
        }
        while (augmentation > 0);
    }
    return maxFlow;
}

void clearFlow (Net& net) {
    for (size_t i = 0; i < net.getVerticesCount(); ++i) {
        for (const Net::Arc& arc: net.getOuterEdges(i)) {
            arc.first->setFlow(0);
        }
    }
}

bool canDrink (Net& net, size_t employeesCount, size_t days) {
    for (const Net::Arc& arc: net.getOuterEdges(net.getSource())) {
        arc.first->setCapacity(days);
    }
    long long maxFlow = setMaxFlow(net);
    bool out = (maxFlow == employeesCount * days);
    clearFlow(net);
    return out;
}

int main() {
    size_t employeesCount, teaTypesCount;
    cin >> employeesCount >> teaTypesCount;
    const size_t verticesCount = 2 + employeesCount + teaTypesCount;
    const size_t source = 0;
    const size_t sink = verticesCount - 1;
    Net net(verticesCount, source, sink);
    for (size_t i = 0; i < employeesCount; ++i) {
        const size_t capacity = 100000000000;
        Edge edge(source, 1 + i, capacity);
        net.addEdge(edge);
    }
    for (size_t i = 0; i < teaTypesCount; ++i) {
        size_t capacity;
        cin >> capacity;
        Edge edge(1 + employeesCount + i, sink, capacity);
        net.addEdge(edge);
    }

    for (size_t i = 0; i < employeesCount; ++i) {
        size_t favouriteTeaTypesCount;
        cin >> favouriteTeaTypesCount;
        for (size_t j = 0; j < favouriteTeaTypesCount; ++j) {
            size_t favouriteTeaTypeId;
            cin >> favouriteTeaTypeId;
            --favouriteTeaTypeId;
            const size_t capacity = 100000000000;
            Edge edge(1 + i, 1 + employeesCount + favouriteTeaTypeId, capacity);
            net.addEdge(edge);
        }
    }
    size_t left = 0;
    size_t right = 100000000000;
    while (right - left > 1) {
        const size_t middle = (left + right) / 2;
        (canDrink(net, employeesCount, middle) ? left : right) = middle;
    }
    std::cout << left << std::endl;
    return 0;
}
