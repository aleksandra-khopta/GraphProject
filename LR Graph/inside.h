#pragma once
class Vertex;
class AdjList;
class Edge;
class AdjListIterator;
class Graph{
	Graph(const Graph&);
	Graph& operator= (const Graph&);
	Gr *G;
	struct Gr{
		Vertex nameV;
		AdjList nV;
	};
	int size;
	int vnum;
public:
	Graph(int);
	Graph();
	~Graph();

	bool addVertex(const std::string &vName);
	bool addEdge(const std::string &vName1, const std::string &vName2, int weight);
	bool vertexIsNew(const std::string &vName);
	bool edgeIsNew(const std::string &vName1, const std::string &vName2, int weight);

	enum State {OK=0, Error=255}; // maybe smth else
	//for text in format vertices:{<vertix>}<EOLN> edges:{(vertix,vertix,weight)}
	State loadLex(const char *fname=NULL);//// 0 if OK, 1 wrong data
};
class Vertex{
	std:: string name;
	AdjList edjes;
public: Vertex(std:: string);
		~Vertex();
		std:: string getName();
		bool isVertex();
		AdjListIterator first() const; //
		bool operator==(const Vertex&);
		bool operator=(const Vertex&);
};

class Edge{
	double weight;
	Vertex begin;
	Vertex end;
	Edge *reverse;
public: Edge();
		Edge(double,std::string &vName1, std::string &vName2);
		bool belongToVertex(const Vertex &vname);
		void print();
};

class AdjList{
	struct ListElem{
		Edge e;
		ListElem *next;
	};
	ListElem *head;
public: AdjList();
		~AdjList();
		bool isEdge(Vertex);
		bool addEdge(const std::string &vName1, const std::string &vName2, int weight);
		void print();
		AdjListIterator first();
};

class AdjListIterator{
public:
	AdjListIterator();
};