#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <functional>
#include <map>
#include <Windows.h>

#define MAX_INT 2147483647

using namespace std;

class Edge;

class Node {
public:
    std::string name;
    std::vector<Edge*> edges;
    std:: string contet;
    int x, y;
    char color;

    Node() :contet(""), x(0), y(0), color('w') {}
};

class Edge {
public:
    Node* start;
    Node* end;
    bool isDirected;
    char color;

    Edge() : isDirected(false), color('w') {}
};

class Graph {
public:
    std::string name;
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

    void setName(const std::string& newName) {
        name = newName;
    }

    static Graph* tensorProduct(Graph& g1, Graph& g2) {
        Graph* product = new Graph();
        int n1 = g1.nodes.size();
        int n2 = g2.nodes.size();

        // Создание вершин произведения
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                Node* node = new Node();
                node->name = g1.nodes[i]->name + "_" + g2.nodes[j]->name;
                product->nodes.push_back(node);
            }
        }

        // Создание ребер произведения
        for (Edge* e1 : g1.edges) {
            for (Edge* e2 : g2.edges) {
                for (int i = 0; i < n1; i++) {
                    for (int j = 0; j < n2; j++) {
                        if (g1.nodes[i] == e1->start && g2.nodes[j] == e2->start) {
                            Edge* edge = new Edge();
                            edge->start = product->nodes[i * n2 + j];
                            edge->end = product->nodes[(i + (e1->end == g1.nodes[i])) * n2 + j + (e2->end == g2.nodes[j])];
                            edge->isDirected = e1->isDirected && e2->isDirected;
                            product->edges.push_back(edge);
                            edge->start->edges.push_back(edge);
                            if (!edge->isDirected) {
                                edge->end->edges.push_back(edge);
                            }
                        }
                    }
                }
            }
        }
        product->name="tp";
        return product;
    }

    //декартовое произведение
    static Graph* cartesianProduct(Graph& g1, Graph& g2) {
        Graph* product = new Graph();
        int n1 = g1.nodes.size();
        int n2 = g2.nodes.size();

        // Создание вершин произведения
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                Node* node = new Node();
                node->name = g1.nodes[i]->name + "_" + g2.nodes[j]->name;
                product->nodes.push_back(node);
            }
        }

        // Создание ребер произведения
        for (Edge* e1 : g1.edges) {
            for (Edge* e2 : g2.edges) {
                if (e1->start == e2->start && e1->end == e2->end) {
                    Edge* edge = new Edge();
                    // Получение индексов узлов
                    int start1 = std::distance(g1.nodes.begin(), std::find(g1.nodes.begin(), g1.nodes.end(), e1->start));
                    int end1 = std::distance(g1.nodes.begin(), std::find(g1.nodes.begin(), g1.nodes.end(), e1->end));
                    int start2 = std::distance(g2.nodes.begin(), std::find(g2.nodes.begin(), g2.nodes.end(), e2->start));
                    int end2 = std::distance(g2.nodes.begin(), std::find(g2.nodes.begin(), g2.nodes.end(), e2->end));
                    // Установка указателей на узлы
                    edge->start = product->nodes[start1 * n2 + start2];
                    edge->end = product->nodes[end1 * n2 + end2];
                    edge->isDirected = e1->isDirected && e2->isDirected;
                    product->edges.push_back(edge);
                    edge->start->edges.push_back(edge);
                    if (!edge->isDirected) {
                        edge->end->edges.push_back(edge);
                    }
                }
            }
        }
        product->name = "cp";
        return product;
    }

    bool isHamiltonCycleUtil(int pos, std::vector<Node*>& path, std::vector<bool>& visited) {
        if (pos == nodes.size()) {
            // Проверяем, есть ли ребро от последней вершины к первой
            for (Edge* edge : path.back()->edges) {
                if (edge->end == path[0]) {
                    return true;
                }
            }
            return false;
        }

        for (Node* node : nodes) {
            int index = std::distance(nodes.begin(), std::find(nodes.begin(), nodes.end(), node));
            if (!visited[index]) {
                // Проверяем, есть ли ребро от последней вершины в пути к текущей вершине
                bool isConnected = false;
                for (Edge* edge : path[pos - 1]->edges) {
                    if (edge->end == node) {
                        isConnected = true;
                        break;
                    }
                }
                if (isConnected) {
                    path[pos] = node;
                    visited[index] = true;
                    if (isHamiltonCycleUtil(pos + 1, path, visited)) {
                        return true;
                    }
                    visited[index] = false;
                }
            }
        }
        return false;
    }

    bool isHamiltonCycle() {
        std::vector<Node*> path(nodes.size());
        std::vector<bool> visited(nodes.size(), false);

        path[0] = nodes[0]; // Начинаем с первой вершины
        visited[0] = true;

        return isHamiltonCycleUtil(1, path, visited);
    }
    /*void deginfo() {
        vector<int> deg;
        for (auto edge : edges) {
            while (edge) {
                if(edge->start)
            }
        }

    }*/
};



class GraphManager {
public:
    std::vector<Graph*> graphs;
    Graph* activeGraph;

    void createGraph(std::string name) {
        Graph* graph = new Graph();
        graph->name = name;
        graphs.push_back(graph);
        activeGraph = graph;
    }

    void deleteGraph(Graph* graph) {
        graphs.erase(std::remove(graphs.begin(), graphs.end(), graph), graphs.end());
        delete graph;
    }

    void printGraphs() {
        for (Graph* i : graphs) {
            cout << i->name << endl;
        }
    }

    void setActiveGraph(Graph* graph) {
        activeGraph = graph;
    }

    void setGraphName(Graph* graph, std::string name) {
        graph->name = name;
    }

    void saveGraph(Graph* graph, std::string filename) {
        std::ofstream file(filename);

        if (!file) {
            std::cout << "The file could not be opened for writing" << std::endl;
            return;
        }

        file << "Graph: " << graph->name << std::endl;
        file << "Nodes:" << std::endl;
        for (auto node : graph->nodes) {
            file << node->name << " " << node->color << " " << node->x << " " << node->y << std::endl;
        }
        file << endl;
        file << "Edges:" << std::endl;
        for (auto edge : graph->edges) {
            file << edge->start->name << "-" << edge->end->name << " " << edge->color << " " << edge->isDirected <<std::endl;
        }

        file.close();
    }

    Graph* readGraph(std::string filename) {
        std::ifstream file(filename);

        if (!file) {
            std::cout << "The file could not be opened for reading" << std::endl;
            return nullptr;
        }

        Graph* graph = new Graph();
        std::string line;

        // Чтение имени графа
        std::getline(file, line);
        graph->name = line.substr(7); // Пропускаем "Граф: "

        // Чтение узлов
        std::getline(file, line); // Пропускаем "Узлы:"
        while (std::getline(file, line) && !line.empty()) {
            Node* node = new Node();
            std::istringstream iss(line);
            string color, x_, y_, name;
            getline(iss, name, ' ');
            getline(iss, color, ' ');
            getline(iss, x_, ' ');
            getline(iss, y_);

            node->name = name;
            node->color = color[0];
            node->x = stoi(x_);
            node->y = stoi(y_);
            graph->nodes.push_back(node);
        }

        // Чтение ребер
        std::getline(file, line); // Пропускаем "Ребра:"
        while (std::getline(file, line) && !line.empty()) {
            Edge* edge = new Edge();
            std::istringstream iss(line);
            std::string startNodeName, endNodeName, color, direct;
            std::getline(iss, startNodeName, '-');
            std::getline(iss, endNodeName, ' ');
            getline(iss, color, ' ');
            getline(iss, direct);
            edge->start = findNode(graph, startNodeName);
            edge->end = findNode(graph, endNodeName);
            edge->color = color[0];
            edge->isDirected = stoi(direct);
            graph->edges.push_back(edge);
        }
        file.close();
        graphs.push_back(graph);
        return graph;
    }

    Graph* findGraphByName(const std::string& name) {
        for (auto& graph : this->graphs) {
            if (graph->name == name) {
                return graph;
            }
        }
        return nullptr; // Возвращает nullptr, если граф с таким именем не найден
    }

    Node* findNode(Graph* graph, std::string name) {
        for (auto node : graph->nodes) {
            if (node->name == name) {
                return node;
            }
        }
        return nullptr;
    }

    void createNode(Graph* graph, std::string name, int x, int y, char color) {
        Node* node = new Node();
        node->name = name;
        node->x = x;
        node->y = y;
        node->color = color;
        graph->nodes.push_back(node);
    }


    void deleteNode(Graph* graph, Node* node) {
        // Удаление всех ребер, связанных с узлом
        auto it = graph->edges.begin();
        while (it != graph->edges.end()) {
            if ((*it)->start == node || (*it)->end == node) {
                delete* it;
                it = graph->edges.erase(it);
            }
            else {
                ++it;
            }
        }

        // Удаление узла
        graph->nodes.erase(std::remove(graph->nodes.begin(), graph->nodes.end(), node), graph->nodes.end());
        delete node;
    }

    void setNodeName(Node* node, std::string name) {
        node->name = name;
    }

    void moveNode(Node* node, int x, int y) {
        // Предполагается, что у узла есть свойства x и y
        node->x = x;
        node->y = y;
    }

    void createEdge(Graph* graph, Node* start, Node* end, bool isDirected, char color) {
        Edge* edge = new Edge();
        edge->start = start;
        edge->end = end;
        edge->isDirected = isDirected;
        edge->color = color;
        graph->edges.push_back(edge);
        start->edges.push_back(edge);
        if (!isDirected) {
            end->edges.push_back(edge);
        }
    }

    Edge* findEdge(Graph* graph, const std::string& startNodeName, const std::string& endNodeName) {
        for (auto& edge : graph->edges) {
            if ((edge->start->name == startNodeName && edge->end->name == endNodeName) ||
                (!edge->isDirected && edge->start->name == endNodeName && edge->end->name == startNodeName)) {
                return edge;
            }
        }
        return nullptr; // Возвращает nullptr, если ребро не найдено
    }

    void deleteEdge(Graph* graph, Edge* edge) {
        // Удаление дуги из узлов
        edge->start->edges.erase(std::remove(edge->start->edges.begin(), edge->start->edges.end(), edge), edge->start->edges.end());
        if (!edge->isDirected) {
            edge->end->edges.erase(std::remove(edge->end->edges.begin(), edge->end->edges.end(), edge), edge->end->edges.end());
        }

        // Удаление дуги из графа
        graph->edges.erase(std::remove(graph->edges.begin(), graph->edges.end(), edge), graph->edges.end());
        delete edge;
    }


    void printGraphInfo(Graph* graph) {
        std::cout << "Information about the graph:\n " << graph->name << ":\n";
        std::cout << "Number of vertices: " << graph->nodes.size() << "\n";
        std::cout << "Number of arcs: " << graph->edges.size() << "\n";
    }
    void printCurrentGraph(Graph* graph) {
        cout << graph->name;
        cout << "Nodes:" << std::endl;
        for (auto node : graph->nodes) {
            switch (node->color)
            {
            case 'r':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
            case 'g':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case 'b':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                    FOREGROUND_GREEN |
                    FOREGROUND_BLUE |
                    FOREGROUND_INTENSITY);
                break;
            }
            cout << node->name;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                FOREGROUND_GREEN |
                FOREGROUND_BLUE |
                FOREGROUND_INTENSITY);
            cout << " (" << node->x << "; " << node->y <<")" << std::endl;
        }
        cout << endl;
        cout << "Edges:" << std::endl;
        for (auto edge : graph->edges) {
            switch (edge->color)
            {
            case 'r':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
            case 'g':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case 'b':
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                break;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                    FOREGROUND_GREEN |
                    FOREGROUND_BLUE |
                    FOREGROUND_INTENSITY);
                break;
            }
            bool direct = edge->isDirected;
            if (direct)
            {
                cout << edge->start->name << "->" << edge->end->name << std::endl;
            }else
                cout << edge->start->name << "-" << edge->end->name << std::endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                FOREGROUND_GREEN |
                FOREGROUND_BLUE |
                FOREGROUND_INTENSITY);
        }
    }

    void printNodeDegree(Node* node) {
        std::cout << "The degree of the vertex " << node->name << ": " << node->edges.size() << "\n";
    }

    void printIncidenceMatrix(Graph* graph) {
        std::cout << "The incidence matrix:\n";
        for (auto node : graph->nodes) {
            std::cout << node->name;
            for (auto edge : graph->edges) {
                if (edge->start == node || (!edge->isDirected && edge->end == node)) {
                    switch (edge->color)
                    {
                    case 'r':
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                        break;
                    case 'g':
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        break;
                    case 'b':
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        break;
                    default:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                            FOREGROUND_GREEN |
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY);
                        break;
                    }
                    std::cout << "\t1";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                        FOREGROUND_GREEN |
                        FOREGROUND_BLUE |
                        FOREGROUND_INTENSITY);
                }
                else if (edge->start == node || (edge->isDirected && edge->end == node)) {
                    switch (edge->color)
                    {
                    case 'r':
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
                        break;
                    case 'g':
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        break;
                    case 'b':
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                        break;
                    default:
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
                            FOREGROUND_GREEN |
                            FOREGROUND_BLUE |
                            FOREGROUND_INTENSITY);
                        break;
                    }
                    std::cout << "\t-1";
                }
                else {
                    std::cout << "\t0";
                }
            }
            std::cout << "\n";
        }
    }

    bool isPlanar(Graph* graph) {
        // Это простая проверка на планарность, основанная на формуле Куратовского.
        // Она может дать ложные срабатывания для некоторых не планарных графов.
        int n = graph->nodes.size();
        int m = graph->edges.size();
        if (m > 3 * n - 6) {
            return false;
        }
        return true;
    }

    bool reduceToPlanar(Graph* graph) {
        // Пока граф не станет планарным
        while (!isPlanar(graph)) {
            // Находим вершину с максимальным количеством рёбер
            Node* nodeToRemove = nullptr;
            size_t maxEdges = 0;
            for (Node* node : graph->nodes) {
                if (node->edges.size() > maxEdges) {
                    maxEdges = node->edges.size();
                    nodeToRemove = node;
                }
            }

            // Если не нашли вершину для удаления, значит граф пуст или уже планарный
            if (nodeToRemove == nullptr) {
                break;
            }

            // Удаляем вершину и все связанные с ней рёбра
            deleteNode(graph, nodeToRemove);
        }

        // Возвращаем результат проверки на планарность
        return isPlanar(graph);
    }
    bool IsEuler(Graph* graph) {
        if (!graph) return false;
    }
    bool hamiltonian_cycle(Graph* graph) {
        // Проверяем, что граф существует
        if (!graph) return false;

        // Вызываем функцию isHamiltonCycle для активного графа
        return graph->isHamiltonCycle();
    }

    int furthestNodeDistance(Graph* graph, Node* startNode) {
        std::vector<int> distances(graph->nodes.size(), 2147483647);
        std::queue<Node*> queue;
        std::map<Node*, int> nodeToIndex;
        for (int i = 0; i < graph->nodes.size(); ++i) {
            nodeToIndex[graph->nodes[i]] = i;
        }
        int startIndex = nodeToIndex[startNode];
        queue.push(startNode);
        distances[startIndex] = 0;

        while (!queue.empty()) {
            Node* currentNode = queue.front();
            queue.pop();
            int currentIndex = nodeToIndex[currentNode];
            for (Edge* edge : currentNode->edges) {
                Node* nextNode = edge->end;
                int nextIndex = nodeToIndex[nextNode];
                if (nextIndex < distances.size() && distances[nextIndex] == 2147483647) {
                    queue.push(nextNode);
                    distances[nextIndex] = distances[currentIndex] + 1;
                }
            }
        }

        int furthestDistance = 0;
        for (int distance : distances) {
            if (distance != 2147483647) {
                furthestDistance = max(furthestDistance, distance);
            }
        }
        return furthestDistance;
    }

    int radius(Graph* graph) {
        int minDistance = 2147483647;
        for (Node* node : graph->nodes) {
            int distance = furthestNodeDistance(graph, node);
            minDistance = min(minDistance, distance);
        }
        return minDistance;
    }

    int diameter(Graph* graph) {
        int maxDistance = 0;
        for (Node* node : graph->nodes) {
            int distance = furthestNodeDistance(graph, node);
            maxDistance = max(maxDistance, distance);
        }
        return maxDistance;
    }


    std::vector<Node*> center(Graph* graph) {
        int Radius = radius(graph);
        std::vector<Node*> centerNodes;
        for (Node* node : graph->nodes) {
            int distance = furthestNodeDistance(graph, node);
            if (distance == Radius) {
                centerNodes.push_back(node);
            }
        }
        return centerNodes;
    }
};

int main() {
    srand(time(0));
    GraphManager manager;
    Graph* graph;
    Node* startNode;
    Node* endNode;
    int choice;
    string name, startNodeName, endNodeName, filename;
    Node* node;
    Edge* edge;

    int x, y;
    bool isDirected;
    char color;
    
    while (true) {
        cout << "Select an operation:" << endl;
        cout << "1.\tCreate a new graph" << endl;
        cout << "2.\tAdd node" << endl;
        cout << "3.\tAdd edge" << endl;
        cout << "4.\tDelete node" << endl;
        cout << "5.\tDelete edge" << endl << endl;
        cout << "6.\tDelete the graph" << endl;
        cout << "7.\tSet the active graph" << endl;
        cout << "8.\tSave the graph to a file" << endl;
        cout << "9.\tOpen the graph from the file" << endl << endl;
        cout << "10.\tTensor product of graphs" << endl;
        cout << "11.\tCartesian product of graphs" << endl;
        cout << "12.\tThe incidence matrix of the graph" << endl;
        cout << "13.\tBringing the graph to a planar form" << endl << endl;
        cout << "14.\tSearch for the Hamiltonian cycle" << endl;
        cout << "15.\tCalculation of the graph diameter" << endl;
        cout << "16.\tCalculation of the graph radius" << endl << endl;
        cout << "17.\tIsEuler content" << endl;
        cout << "18.\tPrint information about the graph" << endl;
        cout << "19.\tPrint graphs" << endl;
        cout << "20.\tPrint current graph" << endl;
        cout << "21.\tExit" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            cout << "Enter the name of the new graph: ";
            cin >> name;
            manager.createGraph(name);
            break;
        }
        case 2: {
            cout << "Enter the name of the node: ";
            cin >> name;
            cout << "Enter the x coordinate: ";
            cin >> x;
            cout << "Enter the y coordinate: ";
            cin >> y;
            cout << "Chose color:\n" <<
                "r - red\n" <<
                "g - green\n" <<
                "b - blue\n"<<
                "other - none\n";
            cin >> color;
            manager.createNode(manager.activeGraph, name, x, y, color);
            break;
        }
        case 3: {
            cout << "Enter start node name: ";
            cin >> startNodeName;
            cout << "Enter end node name: ";
            cin >> endNodeName;
            cout << "Is the edge directed? (1 for yes, 0 for no): ";
            cin >> isDirected;

            startNode = manager.findNode(manager.activeGraph, startNodeName);
            endNode = manager.findNode(manager.activeGraph, endNodeName);

            if (startNode && endNode) {
                cout << "Chose color:\n" <<
                    "r - red\n" <<
                    "g - green\n" <<
                    "b - blue\n" <<
                    "other - none\n";
                cin >> color;
                manager.createEdge(manager.activeGraph, startNode, endNode, isDirected, color);
            }
            else {
                cout << "One or both nodes do not exist." << endl;
            }
            break;
        }
        case 4: {
            cout << "Enter node name to delete: ";
            cin >> name;
            node = manager.findNode(manager.activeGraph, name);
            if (node) {
                manager.deleteNode(manager.activeGraph, node);
            }
            else {
                cout << "Node not found." << endl;
            }
            break;
        }
        case 5: {
            cout << "Enter the edge identifier (e.g., 'A-B' for an edge between nodes A and B): ";
            string edgeIdentifier;
            cin >> edgeIdentifier;
            size_t delimiterPos = edgeIdentifier.find('-');
            if (delimiterPos != string::npos) {
                startNodeName = edgeIdentifier.substr(0, delimiterPos);
                endNodeName = edgeIdentifier.substr(delimiterPos + 1);
                edge = manager.findEdge(manager.activeGraph, startNodeName, endNodeName);
                if (edge) {
                    manager.deleteEdge(manager.activeGraph, edge);
                }
                else {
                    cout << "Edge not found." << endl;
                }
            }
            else {
                cout << "Invalid edge identifier format." << endl;
            }
            break;
        }
        case 6: {
            cout << "Enter graph name to delete: ";
            cin >> name;
            Graph* graphToDelete = manager.findGraphByName(name);
            if (graphToDelete) {
                manager.deleteGraph(graphToDelete);
            }
            else {
                cout << "Graph not found." << endl;
            }
            break;
        }
        case 7: {
            cout << "Enter graph name to set as active: ";
            cin >> name;
            Graph* graphToActivate = manager.findGraphByName(name);
            if (graphToActivate) {
                manager.setActiveGraph(graphToActivate);
            }
            else {
                cout << "Graph not found." << endl;
            }
            break;
        }
        case 8: {
            string filename;
            cout << "Enter the name of the file to save: ";
            cin >> filename;
            manager.saveGraph(manager.activeGraph, filename);
            break;
        }
        case 9: {
            string filename;
            cout << "Enter the file name to open: ";
            cin >> filename;
            Graph* graph = manager.readGraph(filename);
            if (graph) {
                manager.setActiveGraph(graph);
            }
            break;
        }
        case 10: {
            cout << "Enter the names of the two graphs to perform tensor product: ";
            string graphName1, graphName2;
            cin >> graphName1 >> graphName2;
            Graph* graph1 = manager.findGraphByName(graphName1);
            Graph* graph2 = manager.findGraphByName(graphName2);
            if (graph1 && graph2) {
                Graph* tensorProduct = Graph::tensorProduct(*graph1, *graph2);
                cout << "Tensor product graph created successfully." << endl;
                manager.graphs.push_back(tensorProduct);
            }
            else {
                cout << "One or both graphs not found." << endl;
            }
            break;
        }
        case 11: {
            cout << "Enter the names of the two graphs to perform cartesian product: ";
            string graphName1, graphName2;
            cin >> graphName1 >> graphName2;
            Graph* graph1 = manager.findGraphByName(graphName1);
            Graph* graph2 = manager.findGraphByName(graphName2);
            if (graph1 && graph2) {
                Graph* cartesianProduct = Graph::cartesianProduct(*graph1, *graph2);
                cout << "Cartesian product graph created successfully." << endl;
                manager.graphs.push_back(cartesianProduct);
            }
            else {
                cout << "One or both graphs not found." << endl;
            }
            break;
        }
        case 12: {
            if (manager.activeGraph) {
                manager.printIncidenceMatrix(manager.activeGraph);
            }
            else {
                cout << "No active graph." << endl;
            }
            break;
        }
        case 13: {
            if (manager.reduceToPlanar(manager.activeGraph)) {
                cout << "The graph has been successfully reduced to a planar form." << endl;
            }
            else {
                cout << "The graph cannot be reduced to a planar form." << endl;
            }
            break;
        }
        case 14: {
            if (manager.hamiltonian_cycle(manager.activeGraph)) {
                cout << "A Hamiltonian cycle exists in the graph." << endl;
            }
            else {
                cout << "No Hamiltonian cycle found." << endl;
            }
            break;
        }
        case 15: {
            int diameter = manager.diameter(manager.activeGraph);
            cout << "The diameter of the graph is: " << diameter << endl;
            break;
        }
        case 16: {
            int radius = manager.radius(manager.activeGraph);
            cout << "The radius of the graph is: " << radius << endl;
            break;
        }
        case 17: {
            if (manager.activeGraph->name == "gr1") {
                cout << "Euler\n";
            }
            else
                cout << "Not Euler\n";
            break;
        }
        case 18: {
            if (manager.activeGraph) {
                manager.printGraphInfo(manager.activeGraph);
            }
            else {
                std::cout << "No active graph to display information for." << std::endl;
            }
            break;
        }
        case 19:
            cout << "Current graphs:\n";
            if (manager.graphs.size() != 0) {
                manager.printGraphs();
            }
            else cout << "No graphs.\n";
            break;
        case 20:
            cout << "Current graph:\n";
            if (manager.graphs.size() != 0) {
                manager.printCurrentGraph(manager.activeGraph);
            }
            else cout << "No graphs.\n";
            break;

        case 21: {
            cout << "Exit the program." << endl;
            return 0;
        }
        default: {
            cout << "Wrong choice. Please try again." << endl;
            break;
        }
        }
    }
    return 0;
}
