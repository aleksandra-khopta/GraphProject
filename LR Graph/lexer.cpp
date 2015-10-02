#include <iostream>
#include <fstream>
#include "lexer.h"
using namespace std;
LexAn::LexAn(string fname){
	f=NULL; ct=ctNone; isNew=false; 
	if (fname.empty()) {f=&cin; cout<<"Enter a graph in format vertices:{<vertix>}<EOLN> edges:{(vertix,vertix,weight)} \n";}
	else { f=new ifstream(fname.c_str(),ios_base::binary);
           if (f==NULL) return;
		   if (f->fail()) {delete f; f=NULL; return;} 
	}
	readChar();
	return;
}
LexAn::~LexAn(){
	if (f!=NULL && isNew) {((ifstream*)f)->close(); delete f;}
	isNew=false; f=NULL; 
}
bool LexAn::fail() const {return ct==ctEof || ct==ctFail;}
bool LexAn::eof() const {return ct==ctEof;}

LexAn::CT LexAn::readChar(){
 (*f).get(c);
  if (f->fail()) {
	if (f->eof()) ct=ctEof;
	else ct=ctFail;
  } else {
	if (c==':') ct=ctColon; 
	else if ('0'<=c && c<='9') ct=ctDigit;
	else if (c==10) ct=ctEoln;
	else if (c<=' ') ct=ctWhite;
	else if ('A'<=c && c<='Z' ||'a'<=c && c<='z') ct=ctLatin;
	else if (c=='(') ct=ctBracket1;
	else if (c==')') ct=ctBracket2;
	else if (c==',') ct=ctComma;
	else ct=ctOther;
  }
  return ct;
}

LexAn::lexType LexAn::state2lexeme(int state)const {
	switch(state){
		case 0: return Error;
		case 1: return Whites;
		case 2: return Name;
		case 3: return Weight;
		case 4: return Bracket1;
		case 5: return Bracket2;
		case 6: return Comma;
		case 7: return Colon;
		case 8: return Eof;
		case 9: return Eoln;
		default: return Error;
	}
}

int LexAn::step(int state)const {
	//0   initial
	//1   read whites
	//2   read latins
	//3   read digits
	//4   bracket1
	//5   bracket2
	//6	  comma
	//7   colon
	//8   eoln
	//9   eof
	//-1   error
	switch (state) {
		case 0: switch (ct){
		        case ctColon: state=7;break;
				case ctLatin: state=2; break;
				case ctComma: state=6; break;
				case ctBracket1: state=4; break;
				case ctBracket2: state= 5; break;
				case ctWhite: state=1; break;
				case ctDigit: state=3; break;
				case ctEoln: state=9; break;
				case ctEof: state=8; break;
				default:  state=-1; break;
				}
				break;
		case 1: if (ct!=ctWhite) state=-1; break;
		case 2: if (ct!=ctLatin) state=-1; break;
		case 3: if (ct!=ctDigit) state=-1; break;
		default: state=-1;
	}
	return state;
}
LexAn::lexType LexAn::getLex(string &sLexem){
  sLexem.clear(); 
  int state=0;
  int prevState=state;
  state=step(state); 
  while (state>=0){
	if (ct!=ctEof || ct!=ctFail || ct!=ctWhite || ct!=ctEoln) sLexem+=c; 
	readChar(); prevState=state; state=step(state);
  } 
  return state2lexeme(prevState);
}