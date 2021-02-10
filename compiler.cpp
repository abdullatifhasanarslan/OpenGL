#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

#define INT 0
#define FLOAT 1
#define CHAR 2
#define FUNCTION_CALL 3
#define VARIABLE 4

int STATE = 0;
string function_type="";
string function_name="";
vector<bool> is_loop;
json code_result = R"({
	"definitions": [],
	"variables": {},
	"functions": {},
	"main": {}
})"_json;


int find_type(string variable){
	int result;
	if(regex_match(variable, regex("\\d*") )){
		result=INT;
	}else if(regex_match(variable, regex("\\d*\\.\\d*") )){
		result=FLOAT;
	}else if (regex_match(variable, regex("'.'") )){
		result=CHAR;
	}else if(regex_match(variable, regex(".*\\(.*\\)") )){
		result=FUNCTION_CALL;
	}else{
		result=VARIABLE;
	}
	return result;
}
string inverse_find_type(int type_id){
	switch(type_id){
		case INT:
			return "int";
		case FLOAT:
			return "flaot";
		case CHAR:
			return "char";
		case FUNCTION_CALL:
			return "function_call";
		case VARIABLE:
			return "variable";
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
}

string translate_parameter(string value){
	switch(find_type(value)){
		case INT:
		case CHAR:
		case FLOAT:
			value="new Variable<"+inverse_find_type(find_type(value))+">(\"\","+value+")";
			break;
		case FUNCTION_CALL:
			// // recursion
			break;
		case VARIABLE:
			break;
		default:
			cout << "WRONG TYPE" << endl;
	}
	return value;
}

string find_real_type(string value){
	string type;
	json variable;
	if(find_type(value)==VARIABLE){

		if(function_name=="main"){
			if(code_result["main"]["variables"].find(value) != code_result["main"]["variables"].end()){
				variable= code_result["main"]["variables"][value];
			}else{
				variable= code_result["variables"][value];
			}
		}else{
			if(code_result["functions"][function_name]["variables"].find(value) != code_result["functions"][function_name]["variables"].end()){	
				variable= code_result["functions"][function_name]["variables"][value];
			}else if(code_result["functions"][function_name]["parameters"].size()!=0){	
				int i;
				for(i=0;i<code_result["functions"][function_name]["parameters"].size();i++){
					if(value==code_result["functions"][function_name]["parameters"].at(i)["name"].get<string>()){
						variable= code_result["functions"][function_name]["parameters"].at(i);
						break;
					}
				}
			}else{
				variable= code_result["variables"][value];
			}
		}
		type = variable["type"].get<string>();
		if(type=="array"){
			type=variable["value_type"].get<string>();
		}
		return type;
	}
	else{
		return inverse_find_type(find_type(value));
	}
}

json create_command(string line, int depth){
	json command = {};
	command["text"]=line;
	if(line=="{"){
		command["depth"]=to_string(depth);
		command["type"]="OPEN_SCOPE";
		command["text"]="{";
	}else if(line=="}"){
		command["depth"]=to_string(depth);
		command["text"]="}";
		if(is_loop.back()){
			command["type"]="CLOSE_LOOP_SCOPE";
		}else{
			command["type"]="CLOSE_SCOPE";
		}
		is_loop.pop_back();
	} else{
		command["depth"]=to_string(depth);
		string substr=line;
		if (regex_match(substr, regex("while .*") )){
			substr=line.substr(8,line.length()-10);
			command["type"]="WHILE";
			is_loop.push_back(true);
		} else if (regex_match(substr, regex("if .*") )){
			substr=line.substr(5,line.length()-7);
			command["type"]="IF";
			is_loop.push_back(false);
		} else if (regex_match(substr, regex("else if .*") )){
			substr=line.substr(10,line.length()-12);
			command["type"]="ELSE_IF";
			is_loop.push_back(false);
		} else if (regex_match(substr, regex("else") )){
			command["type"]="ELSE";
			is_loop.push_back(false);
			return command;
		} else{
			substr=line.substr(0,line.length()-2);
			command["type"]="NORMAL";
		}		
		string type_name = "(int|char|double|float)";
		string variable_name = "[a-zA-Z_][a-zA-Z_0-9]*";
		string parameter = "("+variable_name+"|'.'|\\d*|\\d*\\.\\d*)";
		json::iterator it;
		string function_call;
		if(code_result["functions"].size()!=0){
			it=code_result["functions"].begin();
			function_call = "("+it.key();
			for (++it; it != code_result["functions"].end();++it) {
				function_call += "|"+it.key();
			}
			function_call+=")";
		}
 		if (regex_match(substr, regex(type_name+" "+variable_name+" = "+".*") )){
			string type = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+1,substr.length()-type.length()-1);
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-type.length()-3);
			string value = substr;
			if(function_name=="main"){
				code_result["main"]["variables"][name]={};
				code_result["main"]["variables"][name]["type"]=type;
				code_result["main"]["variables"][name]["value"]=value;
			}else{
				code_result["functions"][function_name]["variables"][name]={};
				code_result["functions"][function_name]["variables"][name]["type"]=type;
				code_result["functions"][function_name]["variables"][name]["value"]=value;
			}
			return NULL;
		} else if (regex_match(substr, regex(type_name+" "+variable_name) )){
			string type = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+1,substr.length()-type.length()-1);
			string name = substr.substr(0,substr.find(" "));
			if(function_name=="main"){
				code_result["main"]["variables"][name]={};
				code_result["main"]["variables"][name]["type"]=type;
			}else{
				code_result["functions"][function_name]["variables"][name]={};
				code_result["functions"][function_name]["variables"][name]["type"]=type;
			}
			return NULL;
		} else if (regex_match(substr, regex(type_name+" "+variable_name+" \\[ \\d* \\]") )){
			string value_type = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+1,substr.length()-value_type.length()-1);
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-value_type.length()-3);
			string value = substr.substr(0,substr.find(" "));
			if(function_name=="main"){
				code_result["main"]["variables"][name]={};
				code_result["main"]["variables"][name]["type"]="array";
				code_result["main"]["variables"][name]["value_type"]=value_type;
				code_result["main"]["variables"][name]["size"]=value;
			}else{
				code_result["functions"][function_name]["variables"][name]={};
				code_result["functions"][function_name]["variables"][name]["type"]="array";
				code_result["functions"][function_name]["variables"][name]["value_type"]=value_type;
				code_result["functions"][function_name]["variables"][name]["size"]=value;
			}
			return NULL;
		} else if (regex_match(substr, regex(variable_name+" = "+function_call+" \\( .* \\)") )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string function = substr.substr(0,substr.find(" "));
			command["function"]=function;
			command["parameters"]={};
			command["parameters"].push_back(translate_parameter(name));
			substr = substr.substr(substr.find(" ")+3,substr.length()-function.length()-3);
			while(regex_match(substr, regex(parameter+" , .*")) ){
				string value = substr.substr(0,substr.find(" "));
				command["parameters"].push_back(translate_parameter(value));
				substr = substr.substr(substr.find(" ")+3,substr.length()-value.length()-3);
			}
			if(regex_match(substr, regex(parameter+" \\)")) ){
				string value = substr.substr(0,substr.find(" "));
				command["parameters"].push_back(translate_parameter(value));
			}
		} else if (regex_match(substr, regex(function_call+" \\(.* \\)") )){
			string function = substr.substr(0,substr.find(" "));
			command["function"]=function;
			command["parameters"]={};
			command["parameters"].push_back(translate_parameter("NULL"));
			substr = substr.substr(substr.find(" ")+3,substr.length()-function.length()-3);
			while(regex_match(substr, regex(parameter+" , .*")) ){
				string value = substr.substr(0,substr.find(" "));
				command["parameters"].push_back(translate_parameter(value));
				substr = substr.substr(substr.find(" ")+3,substr.length()-value.length()-3);
			}
			if(regex_match(substr, regex(parameter+" \\)")) ){
				string value = substr.substr(0,substr.find(" "));
				command["parameters"].push_back(translate_parameter(value));
			}
		} else if (regex_match(substr, regex(variable_name+" \\[ .* \\] = "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string index= substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+5,substr.length()-index.length()-5);
			string value =substr;

			
			command["function"]="array_assignment<"+find_real_type(name)+">";	
			command["parameters"]={};
			command["parameters"].push_back(name);
			command["parameters"].push_back(translate_parameter(index));
			command["parameters"].push_back(translate_parameter(value));
		} else if (regex_match(substr, regex(variable_name+" \\*= "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+4,substr.length()-name.length()-4);
			string value = substr;

	
			command["function"]="multiply_and_assign<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(name);
			command["parameters"].push_back(translate_parameter(value));
		} else if (regex_match(substr, regex(variable_name+" = "+parameter+" / "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name2.length()-3);

			command["function"]="division<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(name);
			command["parameters"].push_back(translate_parameter(name2));
			command["parameters"].push_back(translate_parameter(substr));
		} else if (regex_match(substr, regex(variable_name+" = "+parameter+" \\* "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name2.length()-3);

			command["function"]="multiplication<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(name);
			command["parameters"].push_back(translate_parameter(name2));
			command["parameters"].push_back(translate_parameter(substr));
		} else if (regex_match(substr, regex(variable_name+" = "+parameter+" - "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name2.length()-3);

			command["function"]="subtraction<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(name);
			command["parameters"].push_back(translate_parameter(name2));
			command["parameters"].push_back(translate_parameter(substr));
		} else if (regex_match(substr, regex(variable_name+" = "+parameter+" \\+ "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name2.length()-3);

			command["function"]="addition<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(name);
			command["parameters"].push_back(translate_parameter(name2));
			command["parameters"].push_back(translate_parameter(substr));
		} else if (regex_match(substr, regex(variable_name+" --") )){
			string name = substr.substr(0,substr.find(" "));
			command["function"]="post_decrement";
			command["parameters"]={};
			command["parameters"].push_back(name);
		} else if (regex_match(substr, regex(variable_name+" \\+\\+") )){
			string name = substr.substr(0,substr.find(" "));
			command["function"]="post_increment";
			command["parameters"]={};
			command["parameters"].push_back(name);
		} else if (regex_match(substr, regex(parameter+" > "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr;
			
			command["function"]="greaterthan<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(translate_parameter(name));
			command["parameters"].push_back(translate_parameter(name2));
		} else if (regex_match(substr, regex(parameter+" < "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr;

			command["function"]="lessthan<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(translate_parameter(name));
			command["parameters"].push_back(translate_parameter(name2));
		} else if (regex_match(substr, regex(parameter+" % "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr;

			command["function"]="modulo";
			command["parameters"]={};
			command["parameters"].push_back(translate_parameter(name));
			command["parameters"].push_back(translate_parameter(name2));
		} else if (regex_match(substr, regex(parameter+" = "+parameter) )){
			string name = substr.substr(0,substr.find(" "));
			substr = substr.substr(substr.find(" ")+3,substr.length()-name.length()-3);
			string name2 = substr;

			command["function"]="assignment<Variable<"+find_real_type(name)+">>";
			command["parameters"]={};
			command["parameters"].push_back(translate_parameter(name));
			command["parameters"].push_back(translate_parameter(name2));
		} else if (regex_match(substr, regex("return "+parameter) )){
			string return_string = substr.substr(substr.find(" ")+1,substr.length()-7);
			substr = substr.substr(substr.find(" ")+1,substr.length()-return_string.length()-1);
			string result = substr;

			if(function_name!="main"){
				command["function"]="returner<Variable<"+find_real_type(result)+">>";
				command["parameters"]={};
				command["parameters"].push_back("this->left");
				command["parameters"].push_back(translate_parameter(result));
			} else{
				command["function"]="returner<Variable<"+find_real_type(result)+">>";
				command["parameters"]={};
				command["parameters"].push_back("NULL");
				command["parameters"].push_back(translate_parameter(result));
			}
		}
	}
	return command;

}
		
int main(){
	fstream code;
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
		//macros
		if(STATE==0){
			if(line.rfind("#", 0)==0){
				code_result["definitions"]+=line;
			}else{
				STATE++;
			}
		}
		//variable declarations
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
						++i;
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
		//function name
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
						is_loop.push_back(false);
						if(function_name=="main"){
							code_result[function_name]={};
							code_result[function_name]["parameters"]={};
							code_result[function_name]["variables"]={};
							code_result[function_name]["commands"]={};
							code_result[function_name]["display"]={};
						}else{
							code_result["functions"][function_name]={};
							code_result["functions"][function_name]["variables"]={};
							code_result["functions"][function_name]["parameters"]={};
							if(function_type!="void"){
								code_result["functions"][function_name]["parameters"].push_back({});
								code_result["functions"][function_name]["parameters"][parameter_count]["nostack"]="";
								code_result["functions"][function_name]["parameters"][parameter_count]["name"]="left";
								code_result["functions"][function_name]["parameters"][parameter_count]["type"]=function_type;
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
						parameter_count++;
					}				

					//,
					if(state==5 && character==','){
						state=3;
						character=line[++i];
						parameter_name="";
						parameter_type="";
					}
				}
			} else{
				STATE++;
			}
		}
		//commands
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
				json command = create_command(line, depth);
				if(command!=NULL){	
					if(function_name!="main"){
						code_result["functions"][function_name]["commands"] += command;
					}else{
						code_result[function_name]["commands"] += command;
					}
				}
			}

		}
	}
	code.close();

	ofstream output("sample_result.json");
	output << code_result << endl;
	output.close();

	return 0;
}
