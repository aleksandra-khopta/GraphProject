#pragma once
#include <fstream>
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "edgelist.h"
using namespace std;
Vertex:: Vertex(string n){ name=n; isVisited=false; edges=NULL; distance=0; }
Vertex:: Vertex(){ name=""; isVisited=false; edges=NULL; distance=0; }
string Vertex:: getName() const{ return name; }
void Vertex:: setV(string n) { name=n; }
void Vertex:: setDist(int d) { distance=d; }
int Vertex:: getDist() { return distance; }
bool Vertex:: getVisit() { return isVisited; }
bool Vertex:: isVertex() { return name!=""; }
bool Vertex:: operator==(const Vertex& other) const { return (name==other.getName()); }
bool Vertex:: addEdge(const Edge&E)
{
	if (edges==NULL)
		edges = new EdgeList();
	return (edges->addEdge(E));
}
void Vertex:: printEdges(const std:: string &fname) { 

	ofstream fo(fname,ios::app); 
	fo<<name<<' '<<distance<<' ';
	fo.close();
	if (edges!=NULL) 
		(*edges).print(fname);
	fo.open(fname,ios::app);
	fo<<endl;
	fo.close();
}
bool Vertex:: edgeIsNew(const Edge&E)
{
	if (edges==NULL) return true; 
	return (!(*edges).edgeIsOld(E));
}
void Vertex:: setVisit(bool v) { isVisited=v; }