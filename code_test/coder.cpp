#include "json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using json = nlohmann::json;
using namespace std;

int main(){
	int i=0;
	// read a JSON file
	ifstream file("sample_result.json");
	json code;
	file >> code;
	file.close();
	
	json variables = code["variables"];
	json functions = code["functions"];
	json main = code["main"];
	json main_variables = main["variables"];
	json main_commands = main["commands"];


	cout << "#ifndef USER_DEFINED_HPP" << endl;
	cout << "#define USER_DEFINED_HPP" << endl;

	cout << "#include \"Variables.h\"" << endl;
	cout << "#include \"Functions.h\"" << endl;
	cout << "#include \"all_functions.h\"" << endl;
	cout << "#include <GL/glut.h>" << endl;
	cout << "#include <stdlib.h>" << endl;
	cout << "#include <iostream>" << endl;
	cout << "NameSpace* heap;" << endl;
	cout << "NameSpace* global; " << endl;
	cout << "PipeLine* PipeLine::active_pipeline;" << endl;
	cout << "NameSpace* NameSpace::active_stack;" << endl;




	//function definitions

	for (json::iterator it = functions.begin(); it != functions.end(); ++it) {
		cout << "class " << it.key() << " : public Function {" << endl
		cout << "public:" << endl
		cout << it.key() << "( : public Function {" << endl
		if((*it).find("value") != (*it).end()){
			cout << "\t//" << (*it)["type"].get<string>() << " " << it.key() << "=" << (*it)["value"].get<string>() << ";" << endl;
			cout << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\"," << (*it)["value"].get<string>() << ");" << endl;
		}else{
			cout << "\t//" << (*it)["type"].get<string>() << " " << it.key() << ";" << endl;	
			cout << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\");" << endl;
		}
		cout << "\tglobal->add_Variable(" << it.key() << ");" << endl;
	}




	//start of the init
	cout << "void init(void){" << endl;
	cout << "\tglClearColor(0.3, 0.3, 0.3, 0.0);" << endl;
	cout << "\tglShadeModel(GL_FLAT);" << endl;
	cout << "\tglEnable(GL_POLYGON_STIPPLE);" << endl;
	cout << "\tNameSpace::active_stack = new NameSpace();" << endl;
	cout << "\tint depth=0;" << endl;
	cout << "\tPipeLine::active_pipeline = new PipeLine();" << endl;
	cout << "\theap = new NameSpace();" << endl;
	cout << "\tglobal = new NameSpace();" << endl;
	cout << endl << endl;

	
	//definitions maybe
	
	//global variables
	for (json::iterator it = variables.begin(); it != variables.end(); ++it) {
		if((*it).find("value") != (*it).end()){
			cout << "\t//" << (*it)["type"].get<string>() << " " << it.key() << "=" << (*it)["value"].get<string>() << ";" << endl;
			cout << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\"," << (*it)["value"].get<string>() << ");" << endl;
		}else{
			cout << "\t//" << (*it)["type"].get<string>() << " " << it.key() << ";" << endl;	
			cout << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\");" << endl;
		}
		cout << "\tglobal->add_Variable(" << it.key() << ");" << endl;
	}



	
	//function declarations but they should be to the other file
	
	//main_variables
	for (json::iterator it = main_variables.begin(); it != main_variables.end(); ++it) {
		string type = (*it)["type"].get<string>();
		if(type.compare("array")==0){
			cout << "\t//" << (*it)["value_type"].get<string>() << " " << it.key() << "[" << (*it)["size"].get<string>() << "];" << endl;
			cout << "\t" << (*it)["value_type"].get<string>() << " " << it.key() << "[" << (*it)["size"] << "];" << endl;
			cout << "\tArray<" << (*it)["value_type"].get<string>() << ">* " << it.key() << "=new Array<" << (*it)["value_type"].get<string>() << ">(\"" << it.key() << "\"," << it.key() << "," << (*it)["size"].get<string>() << ");" << endl;
			
		}else if((*it).find("value") != (*it).end()){
			cout << "\t//" << (*it)["type"].get<string>() << " " << it.key() << "=" << (*it)["value"].get<string>() << ";" << endl;
			cout << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\"," << (*it)["value"].get<string>() << ");" << endl;
		}else{
			cout << "\t//" << (*it)["type"].get<string>() << " " << it.key() << ";" << endl;	
			cout << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\");" << endl;
		}
		cout << "\tNameSpace::active_stack->add_Variable(" << it.key() << ");" << endl;
	}		
	
	//main_commands
	for (json::iterator it = main_commands.begin(); it != main_commands.end(); ++it) {
		cout << "\tPipeLine::active_pipeline->add_Command(new Command(" << (*it)["depth"].get<string>() << "," << (*it)["type"].get<string>();
		if((*it).find("function") != (*it).end()){
			cout << ",new " << (*it)["function"].get<string>() << "(";
			if((*it).find("parameters") != (*it).end()){
				int j;
				for(j=0; j < (*it)["parameters"].size()-1; ++j){
					cout << (*it)["parameters"].at(j).get<string>() << ",";
				}
				cout << (*it)["parameters"].at(j).get<string>();
			}
			cout << "))";
		}
		cout << ");" << endl;
	}
		
	
	cout << "}" << endl;

	return 0;
}