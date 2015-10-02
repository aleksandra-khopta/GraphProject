#pragma once
#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "edgelist.h"
Edge:: Edge() { weight=0; }
Edge:: Edge(int&w, Vertex *b, Vertex *e) { weight=w; begin=b; end=e; } 
bool Edge:: operator==(const Edge& other) const { return (weight==other.getWeight() &&
	*begin==other.getBegin() && *end==other.getEnd()); }
int Edge:: getWeight() const{ return weight; }
Vertex Edge:: getBegin() const{ return *begin; }
Vertex Edge:: getEnd() const { return *end; }
