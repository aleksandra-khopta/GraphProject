#pragma once
#include <istream>
#include <string>
//for text in format
//vertices:{<vertix>}<EOLN>
//edges:{(vertix,vertix,weight)}
class LexAn{
private:
	enum CT {ctWhite, ctLatin, ctColon, ctDigit, ctOther, ctBracket1, ctBracket2, ctComma, ctEoln, ctEof=254, ctFail=255,ctNone=-1};
	char c;     //last read char, if exists
	CT ct;   //last char type
	CT readChar(); //pre: stream is OK; read char into c and set it's type

	std::istream *f; //input stream
	bool isNew; // true if f was created by new operation

	//int maxLexLength; //lexem size limit; needed for more than 1 symbol lookahead mode
public:	enum lexType {Error=0, Whites, Name, Weight, Bracket1, Bracket2, Comma, Colon, Eof, Eoln, None};
		// Error means input or lex error
private:    lexType state2lexeme(int state) const; // 
			int step(int state) const;//one step from state
			LexAn(const LexAn &);
			LexAn& operator =(const LexAn &);
			
public:		LexAn(std::string fname);
			~LexAn();
			lexType getLex(std::string &sLexem); //get next lexem, if exist;
	        bool fail() const;
	        bool eof() const;
};