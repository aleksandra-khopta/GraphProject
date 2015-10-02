#include <string>

class Vertex{
	friend class EdgeListIterator;
	std:: string name;
	EdgeList *edges;
	bool isVisited;
	int distance;
public: Vertex(std:: string);
		Vertex();
		void setV(std:: string);
		void setDist(int);
		int getDist();
		bool getVisit();
		void setVisit(bool);
		std:: string getName() const;
		bool isVertex();
		bool addEdge(const Edge&);
		void printEdges(const std::string &fname);
		bool edgeIsNew(const Edge&);
		bool operator==(const Vertex&) const;
};
