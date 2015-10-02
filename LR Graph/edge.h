class Vertex;
class EdgeList;
class Edge{
	friend class EdgeListIterator;
	int weight;
	Vertex *begin;
	Vertex *end;
public: Edge();
		Edge(int&, Vertex*, Vertex*);
		int getWeight() const;
		Vertex getBegin() const;
		Vertex getEnd() const;
		bool operator==(const Edge&) const;
};
