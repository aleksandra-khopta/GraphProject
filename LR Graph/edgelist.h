class Vertex;
class Edge;
class EdgeList{
	friend class EdgeListIterator;
	Vertex master;
	struct ListElem{
		Edge e;
		ListElem* next;
	};
	ListElem* head;
public: EdgeList();
		void setMaster(const Vertex&);
		Vertex getMaster() const;
		bool edgeIsOld(const Edge&);
		bool addEdge(const Edge&);
		void print(const std:: string &fname);
};

class EdgeListIterator {
	EdgeList:: ListElem* cur;
public:
	EdgeListIterator();
	EdgeList:: ListElem* getHead(Vertex *v);
	EdgeList:: ListElem* getCur(Vertex *v);
	int getDistBegin() const;
	int getWeight() const;
	int getDistEnd() const;
	void setCur(EdgeList:: ListElem *p);
	void setEndDist(int);
	bool step();
	Vertex* end();
};