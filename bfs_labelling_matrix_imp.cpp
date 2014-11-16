#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <stack>
#include <queue>
#include <utility>
#define size 19
using namespace std;
class graph {
public:
	bool input[size][size], adj[size][size][4], adj_c[size][size][4];
	int label_source[size][size], label_sink[size][size], source_p, sink_p;
	graph() {
		memset(label_source, 0, sizeof(int)*size*size);
		memset(label_sink, 0, sizeof(int)*size*size);
		memset(adj, 0, sizeof(int)*size*size*4);
		source_p = 0;
		sink_p = 17;
	}
	
	void read_input() {
		int i, j;
		for(i=0; i<size; i++) {
			for(j=0; j<size; j++) cin>>input[i][j];
		}
	}
	
	void make_adj() {
		int i, j;
		for(i=0; i<size; i++) {
			adj[i][0][0] = 0;
			adj[0][i][1] = 0;
			adj[i][size-1][2] = 0;
			adj[size-1][i][3] = 0;
		}
		for(i=0; i<size; i++) {
			for(j=1; j<size; j++) {
				if(input[i][j]) adj[i][j][0] = input[i][j-1];
			}
		}
		for(i=1; i<size; i++) {
			for(j=0; j<size; j++) {
				if(input[i][j]) adj[i][j][1] = input[i-1][j];
			}
		}
		for(i=0; i<size; i++) {
			for(j=0; j<size-1; j++) {
				if(input[i][j]) adj[i][j][2] = input[i][j+1];
			}
		}
		for(i=0; i<size-1; i++) {
			for(j=0; j<size; j++) {
				if(input[i][j]) adj[i][j][3] = input[i+1][j];
			}
		}
		memcpy(adj_c, adj, sizeof(bool)*size*size*4);
	}
	
	void assign_label() {
		int i, j;
		for(i=0; i<size; i++) {
			for(j=0; j<size; j++) {
				if(input[i][j]) {
					label_source[i][j] = i+j;
					label_sink[i][j] = j+abs(i-sink_p);
				}
			}
		}
		/*for(i=0; i<size; i++) {
		 *		for(j=0; j<size; j++) cout<<"("<<label_source[i][j]<<", "<<label_sink[i][j]<<") ";
		 *		cout<<endl;
	}*/
	}
	
	int cr_b_i, cr_b_j, cr_e_i, cr_e_j, i, j;
	int find_critical_edge() {
		int i, j;
		/*for(i=0; i<size; i++) {
		 *		for(j=0; j<size; j++) {
		 *			for(int k=0; k<4; k++) cout<<adj_c[i][j][k]<<" ";
		 *			cout<<"   ";
		 }
		 cout<<endl;
		 }*/
		for(j=size-1; j>=0; j--)
		{
			for(i=0; i<size; i++)
			{
				//cout<<i<<" "<<j<<endl;
				if(adj_c[i][j][1])
				{
					cr_b_i=i-1;
					cr_b_j=j;
					cr_e_i=i;
					cr_e_j=j;
					adj_c[i][j][1] = 0;
					adj_c[i][j][3] = 0;
					return 0;
				}
				else if(adj_c[i][j][0])
				{
					cr_b_i=i;
					cr_b_j=j-1;
					cr_e_i=i;
					cr_e_j=j;
					adj_c[i][j][0] = 0;
					adj_c[i][j-1][2] = 0;
					return 0;
				}
			}
		}
		/* all edges got covered */
		if( i==size && j==-1) cr_b_i = -1;//finish
		/*find path from source*/
		 }
		 void find_paths() {
			 int total_path_length = 0, count = 0;
			 make_adj();
			 assign_label();
			 while(1) {
				 
				 find_critical_edge();
				 if(cr_b_i == -1) break;
				 
				 count++;
				 
				 int max_path_length = 0, path_length = 1;
				 i = cr_b_i;
				 j = cr_b_j;
				 
				 path_length = label_source[cr_b_i][cr_b_j] + label_sink[cr_e_i][cr_e_j] + 1;
				 
				 if(!max_path_length) max_path_length = path_length;
				 
				 total_path_length += path_length;
				 stack< pair<int, int> > source;
				 queue< pair<int, int> > sink;
				 //source.push(make_pair(cr_e_i, cr_e_j));
				 while(i>source_p || j>0) {
					 source.push(make_pair(i, j));
					 if(adj_c[i][j][1] && (label_source[i][j] == label_source[i-1][j]+1)) {
						 adj_c[i][j][1] = 0;
						 adj_c[i-1][j][3] = 0;
						 i--;
					 }
					 else if(adj_c[i][j][0] && (label_source[i][j] == label_source[i][j-1]+1)) {
						 adj_c[i][j][0] = 0;
						 adj_c[i][j-1][2] = 0;
						 j--;
					 }
					 else adj[i][j][0] ? j-- : i--;
				 }
				 
				 source.push(make_pair(source_p, 0));
				 i = cr_e_i;
				 j = cr_e_j;
				 
				 while(i!=sink_p || j>0) {
					 //cout<<i<<","<<j<<" ";
					 sink.push(make_pair(i, j));
					 if(adj_c[i][j][0] && (label_sink[i][j] == label_sink[i][j-1]+1)) {
						 adj_c[i][j][0] = 0;
						 adj_c[i][j-1][2] = 0;
						 /*if(max_path_length >= path_length+2) {
						  *					int k = i, l = j, slag;
						  *					while(k>=0 && adj_c[k][l][1] && slag) {k--;}
						 }*/
						 j--;
						 }
						 else if(adj_c[i][j][3] && (label_sink[i][j] == label_sink[i+1][j]+1)) {
							 adj_c[i][j][3] = 0;
							 adj_c[i+1][j][1] = 0;
							 i++;
						 }
						 else if(adj_c[i][j][1] && (label_sink[i][j] == label_sink[i-1][j]+1) && i > sink_p) {
							 adj_c[i][j][1] = 0;
							 adj_c[i-1][j][3] = 0;
							 i--;
						 }
						 else if(adj[i][j][0]) j--;
						 else if(adj[i][j][3]) i++;
						 else i--;
						 if(!max_path_length) max_path_length = path_length;
					 }
					 //getchar();
					 sink.push(make_pair(sink_p, 0));
					 cout<<"Path "<<count<<" : ";
					 
					 while(!source.empty()) {
						 cout<<"("<<source.top().first<<","<<source.top().second<<") -> ";
						 source.pop();
					 }
					 while(!sink.empty()) {
						 cout<<"("<<sink.front().first<<","<<sink.front().second<<") -> ";
						 sink.pop();
					 }
					 cout<<"(length = "<<path_length<<")"<<endl;
					 
				 }
				 
				 cout<<"Number of paths : "<<count<<endl;
				 cout<<"Total path length : "<<total_path_length;
				 
			 }
		 };
		 int main() {
			 graph g;
			 g.read_input();
			 g.find_paths();
			 return 0;
		 }