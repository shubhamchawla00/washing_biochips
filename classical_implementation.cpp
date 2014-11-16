#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <ctime>
#include <algorithm>
#define SIZE 200
using namespace std;

class graph {
public:
    vector<int> adj[SIZE], adj_c[SIZE];
    int numOfVertices, numOfEdges, label_source[SIZE], label_sink[SIZE], source, sink;
    set<int> unvisited_vertices;
	bool baseline;

    graph() {
        numOfVertices = 0;
        memset(label_source, 0, sizeof (int) *SIZE);
        memset(label_sink, 0, sizeof (int) *SIZE);
        memset(adj, 0, sizeof (int) *SIZE);
        source = 0;
        sink = 0;
		baseline = false;
		srand(time(0));
	}

    void read_input() {
        int i, j, m, n;
        cin >> source >> sink;
        cin >> numOfVertices >> numOfEdges;
        for (i = 0; i < numOfEdges; i++) {
            cin >> m >> n;
            adj[m].push_back(n);
            adj[n].push_back(m);
            adj_c[m].push_back(n);
            adj_c[n].push_back(m);
        }
        for (i = 0; i < numOfVertices; i++) unvisited_vertices.insert(i);
        /*for(i=0; i<numOfVertices; i++) {
                        for(j=0; j<adj[i].size(); j++) cout<<adj[i][j]<<" ";
                        cout<<endl;
                }*/
    }

    void bfs(int start, char type) {
        queue<int> q;
        bool isvisited[SIZE] = {false};
        q.push(start);
        (type == 's' ? label_source[start] : label_sink[start]) = 0;
        while (!q.empty()) {
            int u, v;
            u = q.front();
            isvisited[u] = true;
            q.pop();
            for (v = 0; v < adj[u].size(); v++) {
                if (!isvisited[adj[u][v]]) {
                    if (type == 's') label_source[adj[u][v]] = label_source[u] + 1;
                    else label_sink[adj[u][v]] = label_sink[u] + 1;
                    q.push(adj[u][v]);
                }
            }
        }
        //for(int i=0; i<numOfVertices; i++) cout<<label_sink[i]<<" ";
        //cout<<endl;
    }

    void make_unvisited_vertex_set() {
        for (int i = 0; i < numOfVertices; i++) {
            if (adj_c[i].size()==0) unvisited_vertices.erase(i);
        }
    }

    int find_random_vertex() {
        make_unvisited_vertex_set();
        int random = rand() % unvisited_vertices.size();
        std::set<int>::iterator it = unvisited_vertices.begin();
        for (int i = 0; i < random; i++) it++;
        return (*it);
    }

    int find_critical_vertex() {
        int i, cr_v;
        while (!adj_c[cr_v].size()) cr_v++;
        for (i = 0; i < numOfVertices; i++) {
            if (adj_c[i].size() && (label_sink[i] + label_source[i] > label_sink[cr_v] + label_source[cr_v])) cr_v = i;
        }
        return cr_v;
    }

    void find_paths() {
        int total_path_length = 0, i, j, count = numOfEdges, numberOfPaths = 0, longest_path_length=0;
        stack<int> s;
        bfs(source, 's');
        bfs(sink, 'd');

		while (count > 0) {
            int cr_v, buff, buff_t, numOfNeighb;
            bool flag = true;

			cr_v = buff = ( baseline ? find_random_vertex() : find_critical_vertex() );

			if( longest_path_length < label_source[cr_v] + label_sink[cr_v] + 1) longest_path_length = label_source[cr_v] + label_sink[cr_v] + 1;
			while (buff != source) {
                s.push(buff);
                flag = 1;
                numOfNeighb = adj_c[buff].size();
                for (i = 0; i < adj_c[buff].size(); i++) {
                    if (label_source[buff] == label_source[adj_c[buff][i]] + 1) {
                        buff_t = adj_c[buff][i];

                        count--;

                        //delete the edge
                        for (j = 0; j < adj_c[buff_t].size(); j++) {
                            if (adj_c[buff_t][j] == buff) {
                                adj_c[buff_t].erase(adj_c[buff_t].begin() + j);
                                break;
                            }
                        }
                        adj_c[buff].erase(adj_c[buff].begin() + i);

                        buff = buff_t;
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    for (i = 0; i < adj[buff].size(); i++) {
                        if (label_source[buff] == label_source[adj[buff][i]] + 1) {
                            buff = adj[buff][i];
                            break;
                        }
                    }
                }
            }
            s.push(source);
			int path_length = s.size();
            while (!s.empty()) {
                cout << s.top() << "->";
                s.pop();
            }
            buff = cr_v;
            while (buff != sink) {
				path_length++;
                flag = 1;
                numOfNeighb = adj_c[buff].size();
                for (i = 0; i < adj_c[buff].size(); i++) {
                    if (label_sink[buff] == label_sink[adj_c[buff][i]] + 1) {
                        buff_t = adj_c[buff][i];

                        count--;

                        //delete the edge
                        for (j = 0; j < adj_c[buff_t].size(); j++) {
                            if (adj_c[buff_t][j] == buff) {
                                //cout<<"Deleted Foredge "<<buff<<endl;
                                adj_c[buff_t].erase(adj_c[buff_t].begin() + j);
                                break;
                            }
                        }
                        //cout<<"Deleted Backedge "<<buff_t<<endl;
                        adj_c[buff].erase(adj_c[buff].begin() + i);

                        buff = buff_t;
                        flag = 0;
                        break;
                    }
                }
                if (flag) {
                    for (i = 0; i < adj[buff].size(); i++) {
                        if (label_sink[buff] == label_sink[adj[buff][i]] + 1) {
                            buff = adj[buff][i];
                            break;
                        }
                    }
                }
                cout << buff << "->";
            }
            total_path_length += path_length;
			cout<<"(Path Length : "<<path_length<<")";
			cout << endl;
            numberOfPaths++;
            cout << "";
        }
        cout << "Number Of paths: " << numberOfPaths << endl;
        cout << "Length of the longest path: " << longest_path_length << endl;
        cout << "Total path length: " << total_path_length << endl;
    }
};

int main(int argc, char* argv[]) {
    graph g;
	g.baseline = (argc == 2 && argv[1][0] == 'r' ? true : false);
    g.read_input();
    g.find_paths();
    return 0;
}