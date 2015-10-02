#pragma once
#include <string>
#include <fstream>
#include <limits>
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "edgelist.h"
#include "lexer.h"
using namespace std;
Graph:: Graph(int size1){ size = size1; G = new Vertex*[size]; vnum=0; }
Graph:: Graph() { size = 0; G = NULL; vnum=0; }
void Graph:: resize()
{
	Vertex **newG = new Vertex*[size+1];
	for (int i=0; i<size; i++)
	{
		newG[i] = G[i];
	}
	delete [] G;
	G = newG;
	size++;
}
bool Graph:: addVertex(string &vName) 
{ 
	if (vnum==size) resize();
	if (vertexIsNew(vName))
	{
		G[vnum] = new Vertex(vName);
		vnum++;
		return true;
	}
	return false;
}
bool Graph:: addEdge(string &vName1, string &vName2, int weight)
{
	bool vert1IsAdd=false, vert2IsAdd=false;
	int i, num1, num2;
	for (i=0; (i<vnum && !(vert1IsAdd && vert2IsAdd)); i++)
	{
		if (G[i]->getName()==vName1)
		{
			vert1IsAdd=true;
			num1=i;
		}
		else if (G[i]->getName()==vName2)
		{
			vert2IsAdd=true;
			num2=i;
		}
	}
	if (!(vert1IsAdd && vert2IsAdd)) return false;
	i--;
	Edge E(weight,G[num1],G[num2]);
	if (G[num1]->edgeIsNew(E))
	{
		G[num1]->addEdge(E);
		return true;
	}
	return false;
}
bool Graph:: vertexIsNew(string &vName)
{
	for (int i=0; i<vnum; i++)
	{
		if (G[i]->getName()==vName) return false;
	}
	return true;
}
void Graph:: print(const std:: string &fname, int & rez)
{
	ofstream fo(fname);
	fo.close();
	for (int i=0; i<vnum; i++)
	{
		G[i]->printEdges(fname);
	}
	fo.open(fname,ios::app);
	fo<<rez<<endl;
	fo.close();
}

Graph::State Graph::loadLex(const char *fname){
    LexAn la(fname);
    if (la.eof()) return OK;
    if (la.fail()) return Error;
    LexAn::lexType lex=LexAn::None;
    string sLexem;
	int weight; string Name1,Name2;
  int state=0;  
  while (state>=0) { 
	  //0 begin // 1 name // 2 colon // 3 vertix 
	  // 4 name // 5 colon // 6 bracket1
	  // 7 name //8 comma //9 name //10 comma //11 weight //-1 EOF   //-2 lex error
	  lex=la.getLex(sLexem); 
	  switch(state){
		  case 0: if (lex==LexAn::Name)
				  {
					if (sLexem=="vertices") state=1;
					else state=-2;
				  }
				  else if (lex==LexAn::Eof) state=-1;
				  else if (lex!=LexAn::Eoln && lex!=LexAn::Whites) state=-2;
				  break;
		  case 1: if (lex==LexAn::Colon) state=2;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 2: if (lex==LexAn::Name)
				  {
					this->addVertex(sLexem);
				  }
				  else if (lex==LexAn::Eoln) state=3;
				  else if (lex==LexAn::Eof) state=-1;
				  else if (lex!=LexAn::Eoln && lex!=LexAn::Whites) state=-2;
				  break;
		  case 3: if (lex==LexAn::Name)
				  {
					if (sLexem=="edges") state=4;
					else state=-2;
				  }
				  else if (lex==LexAn::Eof) state=-1;
				  else if (lex!=LexAn::Eoln && lex!=LexAn::Whites) state=-2;
				  break;
		  case 4: if (lex==LexAn::Colon) state=5;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 5: if (lex==LexAn::Bracket1) state=6;
				  else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 6: if (lex==LexAn::Name)
				  {
					  Name1=sLexem;
					  state=7;
				  }
				  else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 7: if (lex==LexAn::Comma) state=8;
				  else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 8: if (lex==LexAn::Name)
				  {
					  Name2=sLexem;
					  state=9;
				  }
				  else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 9: if (lex==LexAn::Comma) state=10;
				  else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 10: if (lex==LexAn::Weight)
				  {
					  weight=atoi(sLexem.c_str());
					  state=11;
				  }
				  else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				  else if (lex!=LexAn::Whites) state=-2;
				  break;
		  case 11: if (lex==LexAn::Bracket2)
				   {
					   this->addEdge(Name1,Name2,weight);
					   state=5;
				   }
				   else if (lex==LexAn::Eof || lex==LexAn::Eoln) state=-1;
				   else if (lex!=LexAn::Whites) state=-2;
				   break;
				   default: state=-2;
	  }
  }
	  if (state==-1) return OK;
      else return Error;	
} 

bool Graph:: dijkstra(const string & first, const string & last, int & rez){
	int numF = -1, numL = -1, numVisited = 0, cur, addVert=0;
	int min;
 	for (int i=0; i<vnum; i++)
	{
		if (G[i]->getName()==first)
		{
			numF = i;
			G[i]->setDist(0);
			addVert++;
		}
		else
		{
			if (G[i]->getName()==last)
			{
				numL = i;
				addVert++;
			}
			G[i]->setDist(INT_MAX);
		}
	}
	if (addVert<2) return false;
	while (numVisited < vnum)
	{
		min = INT_MAX;
		for (int i=0; i<vnum; i++)
		{
			if (!G[i]->getVisit() && G[i]->getDist()<min)
			{
				min=G[i]->getDist();
				cur=i;
			}
		}
		EdgeListIterator It;
		It.setCur(It.getHead(G[cur]));
		while (It.getCur(G[cur]))
		{
			if (!It.getCur(G[cur])->e.getEnd().getVisit())
			{
				if (It.getDistBegin() + It.getWeight() < It.getDistEnd())
					It.end()->setDist(It.getDistBegin() + It.getWeight());
			}
			It.step();
		}
		G[cur]->setVisit(true);
		numVisited++;
	}
	rez=G[numL]->getDist();
	return true;
}