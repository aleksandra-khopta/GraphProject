#include <string>
#include "inside.h"
Graph:: Graph(int size1){ size = size1; G = new Gr[size]; vnum=0; }
Graph:: Graph() { size = 0; G = NULL; vnum=0; }
bool Graph:: addVertex(const std::string &vName) 
{ 
	if vertexIsNew(vName)
	{
		G[vnum].nameV(vName);
		vnum++;
		return true;
	}
	return false;
}
bool addEdge(const std::string &vName1, const std::string &vName2, int weight)
{
	if edgeIsNew(vName1,vName2,weight)
	{
		bool isAdd=false;
		int i;
		for (i=0; i<size && !(isAdd); i++)
		{
			if (G[i].nameV==vName1) isAdd=true;
		}
		if (isAdd) return false;
		G[i].nv.addEdge(const std::string &vName1, const std::string &vName2, int weight);
	}
	return false;
}
bool Graph:: vertexIsNew(const std::string &vName)
{
	for (int i=0; i<size; i++)
	{
		if (G[i].nameV.name==vName) return false;
	}
	return true;
}
bool Graph:: edgeIsNew(const std::string &vName1, const std::string &vName2, int weight)
{
	for (int i=0; i<size; i++)
	{
		AdjList * p = G[i].nv;
		while(p && !(p.e.weight==weight && p.e.begin.name==vName1 && p.e.end.name==vName2) )
			p = p->next;
		return (p != NULL);
	}
}

Vertex:: Vertex(std:: string n=""){ name=n; }
std:: string Vertex:: getName() { return name; }
bool Vertex:: isVertex() { return name!=""; }
bool Vertex:: operator==(const Vertex& other){ return other.getName()==name; }
void Vertex:: operator=(const Vertex& other){ name=other.getName(); }

Edge:: Edge() { weight=0; }
Edge:: Edge(double w, std::string &vName1, std::string &vName2) : begin(vName1), end(vName2) { weight=w; } 

AdjList:: AdjList() { head = NULL; }
bool AdjList:: addEdge(const std::string &vName1, const std::string &vName2, int weight)
{
	Edge newEdge(vName1,vName2,weight);
	ListElem * pElem = new ListElem;
	if (pElem==NULL) return false;
	pElem.e=newEdge; pElem->next=head;
	head=pElem;
	return true;
}


