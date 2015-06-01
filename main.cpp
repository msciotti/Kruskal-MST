//Mason Sciotti
//CSC225 - Dr. Wilkens

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;
#include "kruskal.h"	//Header file with auxillary functions

const int INF = INT_MAX;	//Global variable for "infinity"

// Struct "edge". Stores the two vertices the edge connects, the weight of the edge, and two overloaded operators needed for sorting
struct edge {
	int vi, vj;
	int w;

	edge(int v1 = 0, int v2 = 0, int wt = 0) :w(wt){
		if (v1 < v2){ vi = v1; vj = v2; }
		else { vi = v2; vj = v1; }
	}

	bool operator<(const edge &other) const{
		return (w < other.w);
	}

	bool operator==(edge &other) const{
		return ((vi == other.vi) && (vj == other.vj)) || ((vi == other.vj) && (vj == other.vi));
	}
};

void kruskal(int n, int m, vector<edge> E, vector<edge> &F);
int printVertices(vector<edge> E);	//Prints the path for the MST
void printAdjacencyMatrix(vector < vector<int>> & g);	//Prints the matrix of weights

int main(void){
	int *n = new int[];
	bool weighted = false, directed = false;	//Boolean values for if the graph is weighted or directed
	string fname, graphType, file_end = ".dot";
	int numVertices;
	vector<string> vertexNames;
	vector<vector<int>> adjMatrix;
	ifstream ifile(fname);

	//Input graph from the file
	cout << "What is the name of your file? (no spaces, please): ";
	cin >> fname;
	ifile.open(fname);

	ifile >> graphType >> numVertices;
	if (graphType == "graph")
		directed = false;
	else if (graphType == "digraph")
		directed = true;
	string temp;

	for (int j = 0; j < numVertices; j++){
		ifile >> temp;
		vertexNames.push_back(temp);
	}

	int num;
	for (int i = 0; i < numVertices; i++){
		vector<int> rows;
		adjMatrix.push_back(rows);
	}

	for (int i = 0; i < numVertices; i++)
		for (int j = 0; j < numVertices; j++){
		ifile >> num;
		if (num == -1)
			num = INF;
		adjMatrix[i].push_back(num);
		if (num > 0 && num != 1)
			weighted = true;
		}

	printAdjacencyMatrix(adjMatrix);

	//Vectors for Kruskal, integer and edge to populate the allEdges vector
	vector<edge> MST;
	vector<edge> allEdges;
	int w;
	edge e;

	for (int i = 0; i < numVertices; i++)
		for (int j = i + 1; j < numVertices; j++){
			w = adjMatrix[i][j];
			if (w != 0 && w != INF){
				e.vi = i;
				e.vj = j;
				e.w = w;
				allEdges.push_back(e);
			}
		}

	//Calls kruskal, prints the MST, prints the total weight of the MST
	kruskal(numVertices, allEdges.size(), allEdges, MST);
	int totalweight = printVertices(MST);
	cout << "Total weight: " << totalweight << endl;

	return 0;
}

void kruskal(int n, int m, vector<edge> E, vector<edge> &F){
	vector<set<int>> allSets;
	vector<set<int>>::iterator p, q;
	int k, minw, eIndex;

	//Remember if we've considered an edge yet or not

	vector<bool> edgeConsidered(m, false);
	sort(E.begin(), E.end());
	F.clear();
	initial(allSets, n);

	//Neopolitan's Algorithm 4.2
	while (F.size() < n - 1){
		minw = INF;
		eIndex = -1;
		for (k = 0; k < m; k++)
			if (!edgeConsidered[k] && E[k].w < minw){
				minw = E[k].w;
				eIndex = k;
			}

		if (eIndex == -1)
			cout << "Error" << endl;
		else{
			edgeConsidered[eIndex] = true;
			int i = E[eIndex].vi, j = E[eIndex].vj;
			p = findSet(allSets,i);
			q = findSet(allSets,j);
			if (!equal(p, q)){
				merge(allSets, p, q);
				F.push_back(E[eIndex]);
			}
		}
	}
}

int printVertices(vector<edge> E){
	int totalweight = 0;
	cout << "\nThe path is: \n";

	//Prints the MST
	for (int i = 0; i < E.size(); i++){
		cout << "v" << E[i].vi +1 << "-->" << E[i].vj +1 << "	cost: " << E[i].w << endl;
		totalweight += E[i].w;
	}
	cout << endl;
	return totalweight;	//Returns the total weight of the MST
}

void printAdjacencyMatrix(vector < vector<int>> & g){
	int w;
	int i, j, n = g.size();
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			w = g[i][j];
			if (w != INF)
				cout << setw(4) << g[i][j];
			else
				cout << setw(4) << char(236);
		}
		cout << endl;
	}
}
