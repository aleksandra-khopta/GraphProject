#pragma once
#include <string>
#include <fstream>
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "edgelist.h"
using namespace std;
EdgeList:: EdgeList() { head = NULL; }
bool EdgeList:: addEdge(const Edge&E)
{
	ListElem * pElem = new ListElem;
	if (pElem==NULL) return false;
	pElem->e=E;
	pElem->next=head;
	head=pElem;
	return true;
}
void EdgeList:: print(const std:: string &fname)
{
	ofstream fo(fname,ios::app);
	ListElem * p = head;
	while(p!=NULL)
	{
		fo<<p->e.getBegin().getName()<<' '<<p->e.getEnd().getName()<<' '<<p->e.getWeight()<<' ';
		p = p->next;
	}
	fo.close();
}
bool EdgeList:: edgeIsOld(const Edge&E)
{
		ListElem * p = head;
		while(p && !(p->e==E))
			p = p->next;
		return (p != NULL);
}
void EdgeList:: setMaster(const Vertex& other) { master.setV(other.getName()); }
Vertex EdgeList:: getMaster() const { return master; } 

EdgeListIterator :: EdgeListIterator() {}
EdgeList:: ListElem* EdgeListIterator:: getHead(Vertex *v)
{
	if (v->edges!=NULL)
		return v->edges->head;
	else return NULL;
}
void EdgeListIterator :: setCur(EdgeList:: ListElem *p) { cur = p; }
EdgeList:: ListElem* EdgeListIterator :: getCur(Vertex *v)
{
	if (v->edges!=NULL)
		return cur;
	else return NULL;
}
bool EdgeListIterator :: step()
{
	if (!cur) return false;
	cur = cur->next;
	return true;
}
int EdgeListIterator :: getDistBegin() const { return cur->e.begin->distance; }
int EdgeListIterator :: getWeight() const { return cur->e.weight; }
int EdgeListIterator :: getDistEnd() const { return cur->e.end->distance; }
Vertex* EdgeListIterator :: end() { return cur->e.end; }