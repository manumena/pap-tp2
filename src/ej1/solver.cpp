#include "./ej1.h"
#include <queue>

/*
**  Exercise 1
**  Problem solver
*/

#define SOURCE  0
#define SINK    1

list<int> formPath(vector<int> previous, int initialNode, int finalNode) {
	list<int> path;

	int actual = finalNode;
	while(actual != initialNode) {
		path.push_front(actual);
		actual = previous[actual];
	}
	path.push_front(initialNode);

	return path;
}

list<int> bfs(vector<list<int>> &graph, int initialNode, int finalNode) {
	int n = graph.size();
	vector<int> previous(n);
	bool valid = false;

	vector<bool> visited(n, false);
	visited[initialNode] = true;

	queue<int> pending;
	pending.push(initialNode);

	int actual;
	while(!pending.empty()){

		actual = pending.front();
		pending.pop();

		if(actual == finalNode)
			valid = true;

		for(list<int>::iterator it = graph[actual].begin(); it != graph[actual].end(); it++){
			if(!visited[*it]){
				visited[*it] = true;
				pending.push(*it);
				previous[*it] = actual;
			}
		}
	}


	if(valid)
		return formPath(previous, initialNode, finalNode);
	else
		return list<int>();
}

void augmentPath(vector<list<int>> &network, list<int> path) {
	list<int>::iterator itActual = path.begin();
	list<int>::iterator itNext = path.begin();
	itNext++;
	while(itNext != path.end()) {
		int from = *itActual;
		int to = *itNext;

		// This can be done only because all capacities are 1
		network[from].remove(to);
		network[to].push_back(from);

		itActual++;
		itNext++;
	}
}

int maxFlow(vector<list<int>> network) {
	list<int> path = bfs(network, SOURCE, SINK);
	int flow = 0;
	while(!path.empty()) {
		augmentPath(network, path);
		path = bfs(network, SOURCE, SINK);
		flow++;
	}
	return flow;
}

void run_solver() {
	int n, m;
	cin >> n >> m;

	vector<list<int>> network(2 * n + 2);

	for(int corner = 1; corner <= n; corner++) {
		int in = 2 * corner;
		int out = in + 1;

		char type;
		cin >> type;

		switch(type) {
			case 'A':
				network[SOURCE].push_back(in);
				break;
			case 'E':
				network[out].push_back(SINK);
				break;
		}

		network[in].push_back(out);
	}

	for(int edges = 0; edges < m; edges++) {
		// The edges are indexed from 1
		int corner1, corner2;
		cin >> corner1 >> corner2;

		int in1 = 2 * corner1;
		int in2 = 2 * corner2;
		int out1 = in1 + 1;
		int out2 = in2 + 1;

		network[out1].push_back(in2);
		network[out2].push_back(in1);
	}

	cout << maxFlow(network) << endl;
}