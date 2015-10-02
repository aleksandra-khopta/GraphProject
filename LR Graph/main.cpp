#include <iostream>
#include "graph.h"
#include "lexer.h"
using namespace std;

void test() {
	int rez;
	Graph gr(100); 
	gr.loadLex("input.txt");
	gr.dijkstra("Vinnica","Paris",rez);
	gr.print("output.txt",rez);
}

int main() {
	test();
	//system("pause");
	return 0;
}