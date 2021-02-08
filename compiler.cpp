#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int STATE = 0;
string function_type="";
string function_name="";
vector<bool> is_loop;

int find_type(string variable){
	// char 2
	// double 1
	// int	0s
	regex new_variable ("[a-zA-Z_]* [a-zA-Z_]*");
	regex defined_variable ("[a-zA-Z_]*");
	// cout << variable << ":" << regex_match(variable,defined_variable) << endl;
	if(variable.find("'")>9){
	}
	if(variable.find("'")>9){
	}
	if(variable.find("'")>9){
		return 2;
	}else if(variable.find(".")>9){
		return 1;
	}else{
		return 0;
	}
}

void clean(std::string& line) {
	//delete all \ts
    int i = line.find("\t");
	while(i!=std::string::npos){
	    line.erase(i, i+1);
		i=line.find("\t");
	}
    //delete all double spalces
	i = line.find("  ");
	while(i!=std::string::npos){
	    line.erase(i, i+1);
		i=line.find("  ");
	}

	//delete space in start
	if(line.front()==' '){
	    line.erase(0, 1);
	}
	//delete space in end
    if(line.back()==' '){
		line.erase(line.size()-1,line.size());
	}
	// cout << line << endl;
}

json create_command(string line, int depth){
	json command = {};
	if(line=="{"){
		command["depth"]=to_string(depth);
		command["type"]="OPEN_SCOPE";
		command["text"]="{";
	}else if(line=="}"){
		command["depth"]=to_string(depth);
		//----------------------------------------------------
		//----------------------------------------------------
		//----------------------------------------------------
		command["type"]="CLOSE_SCOPE";
		command["type"]="CLOSE_LOOP_SCOPE";
		//----------------------------------------------------
		//----------------------------------------------------
		//----------------------------------------------------
		command["text"]="}";
	} else{
		command["depth"]=to_string(depth);
		string substr=line;
		if(line.rfind("while", 0)==0){
			substr=line.substr(8,line.length()-10);
			command["type"]="WHILE";
		} else if(line.rfind("if", 0)==0){
			substr=line.substr(5,line.length()-7);
			command["type"]="IF";
		} else if(line.rfind("else if", 0)==0){
			substr=line.substr(10,line.length()-12);
			command["type"]="WHILE";
		} else if(line.rfind("else", 0)==0){
			command["type"]="ELSE";
		}

		if(substr.find(" = ") != std::string::npos){
			command["function"]="assignment";
			// cout << "----" << substr.substr(0,substr.find(" = ")) << "----" << endl;
			find_type(substr.substr(0,substr.find(" = ")));
			// if(find_type(substr.substr(0,substr.find("="))
		}else{
			// cout << substr << endl;
		}
	}
	command["text"]=line;
	
	return command;
}

		
int main(){
	// string deneme = "";
	// cout << deneme.find(" = ") << endl;
	fstream code;
	json code_result = R"({
		"definitions": [],
		"variables": {},
		"functions": {},
		"main": {}
	})"_json;
	//open_file--------------------------
	char file_name[]="code.c";
	code.open(file_name,ios::in);
	if(!code.good()){
		return -1;
	}
	//read_line_by_line------------------------------
  	string line;
	int depth=-1;
	while (getline( code, line )){
		clean(line);
		if(line==""){
			continue;
		}
		if(STATE==0){
			if(line.rfind("#", 0)==0){
				code_result["definitions"]+=line;
			}else{
				STATE++;
			}
		}
		if(STATE==1){
		    int i;
			
			if(line.back()==';'){
				char character;
				string name="";
				string type="";
				string value="";
				int state=0;
				for(i=0;i<line.size();i++){
					character=line[i];
					//type
					if(state==0 && character!=' '){
						type+=character;
					}else if(state==0){
						state++;
						character=line[++i];
					}

					//name
					if(state==1 && character!=' '){
						name+=character;
					}else if(state==1){
						state++;
						code_result["variables"][name]={};
						code_result["variables"][name]["type"]=type;
						character=line[++i];
					}

					//= or ;
					if(state==2 && character==';'){
						break;
					}else if(state==2 && character!='='){
						//nothing
					}else if(state==2){
						character=line[++i];
						state++;
					}
						//value
					if(state==3 && character==';'){
						break;
					}if(state==3 && character!=' '){
						value+=character;
					}else if(state==3){
						code_result["variables"][name]["value"]=value;
						code_result["variables"][name]["type"]=type;
						character=line[++i];
					}
				}
			} else{
				STATE++;
			}
		}
		if(STATE==2){
		    int i;
			
			if(line.back()==')'){
				char character;
				string parameter_type="";
				string parameter_name="";
				json parameter_json = {};
				int parameter_count=0;
				string parameter="";
				int state=0;
				for(i=0;i<line.size();i++){
					character=line[i];
					//type
					if(state==0 && character!=' '){
						function_type+=character;
					}else if(state==0){
						state++;
						character=line[++i];
					}

					//name
					if(state==1 && character!=' '){
						function_name+=character;
					}else if(state==1){
						state++;
						if(function_name=="main"){
							code_result[function_name]={};
							code_result[function_name]["parameters"]={};
							code_result[function_name]["variables"]={};
							code_result[function_name]["commands"]={};
							code_result[function_name]["display"]={};
						}else{
							code_result["functions"][function_name]={};
							code_result["functions"][function_name]["parameters"]={};
							if(function_type!="void"){
								code_result["functions"][function_name]["parameters"].push_back({});
								code_result["functions"][function_name]["parameters"][parameter_count]["nostack"]="";
								code_result["functions"][function_name]["parameters"][parameter_count]["name"]="left";
								code_result["functions"][function_name]["parameters"][parameter_count]["type"]=parameter_type;
								parameter_count++;
							}
							code_result["functions"][function_name]["display"]={};
							code_result["functions"][function_name]["commands"]={};
							character=line[++i];
						}
					}
					
					//(
					if(state==2 && character=='('){
						state++;
						i++;
						character=line[++i];
					}

					//parameter_type
					if(state==3 && character==')'){
						break;
					}else if(state==3 && character!=' '){
						parameter_type+=character;
					}else if(state==3){
						state++;
						character=line[++i];
					}

					//parameter_name
					if(state==4 && character!=' '){
						parameter_name+=character;
					}else if(state==4){
						code_result["functions"][function_name]["parameters"].push_back({});
						code_result["functions"][function_name]["parameters"][parameter_count]["name"]=parameter_name;
						code_result["functions"][function_name]["parameters"][parameter_count]["type"]=parameter_type;
						character=line[++i];
						state++;
					}				

					//,
					if(state==5 && character==','){
						state=3;
						i++;
						character=line[++i];
					}
				}
			} else{
				cout << function_name << endl;
				STATE++;
			}
		}
		if(STATE==3){
			if(line.back()=='{'){
				++depth;
				if(function_name!="main"){
					code_result["functions"][function_name]["commands"] += create_command(line, depth);
				}else{
					code_result[function_name]["commands"] += create_command(line, depth);
				}
				
				continue;
			} else if(line.back()=='}'){
				if(function_name!="main"){
					code_result["functions"][function_name]["commands"] += create_command(line, depth);
				}else{
					code_result[function_name]["commands"] += create_command(line, depth);
				}
				depth--;
				if(depth==-1){
					function_name="";
					function_type="";
					STATE=2;
				}
				continue;
			} else{
				if(function_name!="main"){
					code_result["functions"][function_name]["commands"] += create_command(line, depth);
				}else{
					code_result[function_name]["commands"] += create_command(line, depth);
				}
			}

		}
	}
	code.close();

	cout << code_result << endl;

	return 0;
}
