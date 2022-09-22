#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<stack>
using namespace std;
# define INF 0x3f3f3f3f
class WeightedGraph {
private:
	int num_of_vertices;
	vector<pair<int, int>>* graph;
public:
	WeightedGraph() {
		num_of_vertices = 0;
	}
	WeightedGraph(int num):num_of_vertices(num) {
		graph = new vector<pair<int, int>>[num];
	}
    ~WeightedGraph() {
        if (num_of_vertices != 0) {
            delete[] graph;
        }
    }
	void add_new_edge(int initial, int weight, int terminal) {
        graph[initial].push_back({ terminal, weight });
	}
	friend istream& operator>>(istream& is, WeightedGraph& x) {
		if (x.num_of_vertices != 0) {
			delete[] x.graph;
		}
		is >> x.num_of_vertices;
		x.graph = new vector<pair<int, int>>[x.num_of_vertices];
		int vertice;
		int its_weight;
		int num_of_terminal;
		for (int i = 0; i < x.num_of_vertices; i++) {
			is >> num_of_terminal;
			for (int j = 0; j < num_of_terminal; j++) {
				is >> vertice;
				is >> its_weight;
				x.add_new_edge(i, its_weight, vertice);
			}
		}
        return is;
	}
    friend ostream& operator<<(ostream& os, WeightedGraph& x) {
        os << x.num_of_vertices<<"\n";
        for (int i = 0; i < x.num_of_vertices; i++) {
            os << "vertex " << i << " : " << "\n";
            for (auto m : x.graph[i]) {
               os <<m.first << " weight: " << m.second << "\n";
            }
        }
        os << "\n";
        return os;
    }
	int dijsktra(int from, int to) {
        priority_queue< pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > frontier;
        vector<int> dist(num_of_vertices, INF);
        vector<int> parents(num_of_vertices, -1);
        vector<bool> processed(num_of_vertices, false);
        frontier.push(make_pair(0, from));
        dist[from] = 0;
        while (!frontier.empty())
        {
            //searching for current vertex
            //(minimum known weight from our from)
            //priority_queue is always sorted, so one with minimum weight is on the top
            int u = frontier.top().second;

            //if it`s already processed, we don`t check it`s edges and simply go on
            if (processed[u] == true) {
                frontier.pop();
                continue;
            }

            frontier.pop();
            processed[u] = true;
            // 'i' is used to get all adjacent vertices of a vertex
            vector< pair<int, int> >::iterator i;
            for (i = graph[u].begin(); i != graph[u].end(); ++i)
            {
                    int v = (*i).first;
                    int weight = (*i).second;

                    //  If there is shorted path to v through u
                    if (dist[v] > dist[u] + weight)
                    {
                        // Updating distance of v
                        dist[v] = dist[u] + weight;
                        parents[v] = u;
                        frontier.push(make_pair(dist[v], v));
                    }
            }
        }
       

        cout << "shortest path from " << from << " to " << to << endl;
        int temp_par = parents[to];
        stack<int> shortest_path;
        shortest_path.push(to);
        while (temp_par != -1) {
            shortest_path.push(temp_par);
            temp_par = parents[temp_par];
        }
        while (!shortest_path.empty()) {
            cout << shortest_path.top() << endl;
            shortest_path.pop();
        }
        cout << "with weight: " << dist[to] << endl;

        cout << "All shortest distances from "<<from<<"\n";
        cout<<"Vertex  Distance from "<<from<<"\n";
        for (int i = 0; i < num_of_vertices; ++i)
            cout << i << "\t" << dist[i] << "\n";
        return dist[to];
	}
};


int main() {
    WeightedGraph x(8);
    x.add_new_edge(0, 4, 1);
    x.add_new_edge(0, 3, 4);

    x.add_new_edge(1, 5, 2);
    x.add_new_edge(1, 2, 4);
    x.add_new_edge(1, 4, 0);

    x.add_new_edge(2, 5, 1);
    x.add_new_edge(2, 1, 5);
    x.add_new_edge(2, 3, 4);
    x.add_new_edge(2, 5, 3);

    x.add_new_edge(3, 7, 7);
    x.add_new_edge(3, 5, 2);
    x.add_new_edge(3, 2, 6);

    x.add_new_edge(4, 3, 0);
    x.add_new_edge(4, 2, 1);
    x.add_new_edge(4, 6, 5);
    x.add_new_edge(4, 3, 2);

    x.add_new_edge(5, 5, 5);
    x.add_new_edge(5, 2, 3);
    x.add_new_edge(5, 4, 7);

    x.add_new_edge(6, 7, 3);
    x.add_new_edge(6, 4, 6);
    x.dijsktra(0, 7);
  


    //ifstream fin("graph.txt");//читання з файлу
    //WeightedGraph x;
    //fin >> x;
    //cout << x;
    //cout << x.dijsktra(0, 7) << endl;
    //fin.close();
}