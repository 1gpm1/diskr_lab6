#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Graph {
private:
    int vertices;
    int edges;
    vector<vector<int>> adjacencyList;
    vector<vector<int>> incidenceMatrix;
    vector<vector<int>> adjacencyMatrix;

public:
    Graph(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Failed to open the file.");
        }

        file >> vertices >> edges;

        adjacencyList.resize(vertices);
        incidenceMatrix.resize(vertices, vector<int>(edges, 0));
        adjacencyMatrix.resize(vertices, vector<int>(vertices, 0));

        int u, v;
        for (int i = 0; i < edges; ++i) {
            file >> u >> v;
            --u;
            --v;

            adjacencyList[u].push_back(v);
            adjacencyList[v].push_back(u);

            incidenceMatrix[u][i] = 1;
            incidenceMatrix[v][i] = -1;

            adjacencyMatrix[u][v] = 1;
            adjacencyMatrix[v][u] = 1;
        }
    }

    void printAdjacencyMatrix(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Failed to open the file for writing.");
        }

        for (const auto& row : adjacencyMatrix) {
            for (int cell : row) {
                file << cell << " ";
            }
            file << "\n";
        }
    }

    void printIncidenceMatrix(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Failed to open the file for writing.");
        }

        for (const auto& row : incidenceMatrix) {
            for (int cell : row) {
                file << cell << " ";
            }
            file << "\n";
        }
    }
};

int main() {
    string graphFile, adjacencyMatrixFile, incidenceMatrixFile;
    cout << "Enter the path to the graph file: ";
    cin >> graphFile;

    try {
        Graph graph(graphFile);

        cout << "Enter the path to save the adjacency matrix: ";
        cin >> adjacencyMatrixFile;
        graph.printAdjacencyMatrix(adjacencyMatrixFile);

        cout << "Enter the path to save the incidence matrix: ";
        cin >> incidenceMatrixFile;
        graph.printIncidenceMatrix(incidenceMatrixFile);

        cout << "Adjacency and incidence matrices have been successfully saved." << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
