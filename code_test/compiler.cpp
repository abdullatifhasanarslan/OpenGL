#include <iostream>
#include <string>
#include <fstream>
#include <regex>

using namespace std;

enum STATE{
	START,		//define, include, variable and function declarations
	START2,		//variable and function declarations
	INCLUDE,	//include
	DEFINE,		//define
	VARIABLE,
	FUNCTION_DECLARATION,
	FUNCTION_DEFINITION,
	SPACE,
	LIBRARY,
	NAME,
	VALUE,
	TYPE,
	PARAMETER,
	CONTENT,
	COMMAND,
	LOOP,
	VARIABLE_DECLARATION,
	VARIABLE_DEFINITION,
	FUNCTION_CALL,
	CONDITIONAL,
	FOR_LOOP,
	WHILE_LOOP,
	DO_WHILE_LOOP
};

fstream file;

bool parser(string code);
string read();
int string_until(string code, int start_index, char end_char);

int main(){
	//open_file--------------------------
	char file_name[]="code.c";
	file.open(file_name,ios::in);

	//read_file------------------------------
	string code;
	int i=0;
	while(!file.eof()){
		code+=read();
		code+='\n';
	}
	cout << code << endl;

	//parse file-----------------------------
	// if(parser()){
	// 	cout << "Parser complete" << endl;
	// }
	
	return 0;
}

//regex_match(string, regex(regex_string));
bool parser(string code){
	STATE state=START;	
	for(string::iterator i=code.begin();i!=code.end();){
		switch(state){
			case START:
				if(*i=='#'){
					i++;
					if(*i=='i'){
						state=INCLUDE;
					}else if(*i=='d'){
						state=DEFINE;
					}
				}else{
					state=START2;
				}
				break;
			case INCLUDE:
				// string
				break;
			case DEFINE:
				break;
			case START2:
				break;
			// case :
			// 	break;
			// case :
			// 	break;
			// case :
			// 	break;
			// case :
			// 	break;
			// case :
			// 	break;
			// case :
			// 	break;
			// case :
			// 	break;
			default:
				break;
		}
	}
}

string read(){
	//ignore new lines
	string temp;
	getline(file,temp);
	return temp;
}

int string_until(string code, int start_index, char end_char){
	int index=0;
	while(code[index++]!=end_char){
		//just iterate
	}
	start_index--;
	return start_index;
}