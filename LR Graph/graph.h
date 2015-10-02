#include <string>
class Vertex;
class Edge;
class EdgeList;
class Graph{
	Vertex **G;
	int size;
	int vnum;
	void resize();
public:
	Graph();
	Graph(int);

	bool addVertex(std:: string &vName);
	bool addEdge(std:: string &vName1, std:: string &vName2, int weight);
	bool vertexIsNew(std:: string &vName);

	enum State {OK=0, Error=255};
	//for text in format vertices:{<vertix>}<EOLN> edges:{(vertix,vertix,weight)}
	State loadLex(const char *fname=NULL);// 0 if OK, 1 wrong data
	void print(const std:: string &, int &);

	bool dijkstra(const std:: string &, const std:: string &, int & rez);
};