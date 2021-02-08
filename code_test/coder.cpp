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

	ofstream output("../user_defined.hpp");
	
	json variables = code["variables"];
	json functions = code["functions"];
	json main = code["main"];
	json main_variables = main["variables"];
	json main_commands = main["commands"];


	output << "#ifndef USER_DEFINED_HPP" << endl;
	output << "#define USER_DEFINED_HPP" << endl;

	output << "#include \"Variables.h\"" << endl;
	output << "#include \"Functions.h\"" << endl;
	output << "#include \"all_functions.h\"" << endl;
	output << "#include <GL/glut.h>" << endl;
	output << "#include <stdlib.h>" << endl;
	output << "#include <iostream>" << endl;

	output << "NameSpace* heap;" << endl;
	output << "NameSpace* global; " << endl;
	output << "PipeLine* PipeLine::active_pipeline;" << endl;
	output << "NameSpace* NameSpace::active_stack;" << endl;


	//global variables
	for (json::iterator it = variables.begin(); it != variables.end(); ++it) {
		output << "Variable<" << (*it)["type"].get<string>() << ">* " << it.key() << ";" << endl;
	}

	//function definitions

	for (json::iterator it = functions.begin(); it != functions.end(); ++it) {
		json function_variables = (*it)["variables"];
		json function_parameters = (*it)["parameters"];
		json function_commands = (*it)["commands"];

		output << "class " << it.key() << " : public Function {" << endl;
		output << "\tpublic:" << endl;

		//variables
		//parameter
		for (int j = 0; j < function_parameters.size();++j) {
			json parameter = function_parameters.at(j);
			output << "\t\tVariable<" << parameter["type"].get<string>() << ">* " << parameter["name"].get<string>() << ";" << endl;
		}
		//others
		for (json::iterator it2 = function_variables.begin(); it2 != function_variables.end();++it2) {
			output << "\t\tVariable<" << (*it2)["type"].get<string>() << ">* " << it2.key() << ";" << endl;
		}

		//constructor----------------------
		//parameters
		output << "\t\t" << it.key() << "(";
		int j;
		for (j = 0; j < function_parameters.size()-1;++j) {
			json parameter = function_parameters.at(j);
			output << "Variable<" << parameter["type"].get<string>() << ">* ";
			output << parameter["name"].get<string>();
		}
		output << "Variable<" << function_parameters.at(j)["type"].get<string>() << ">* ";
		output << function_parameters.at(j)["name"].get<string>();
		output << "){" << endl;
		//assignment
		for (j = 0; j < function_parameters.size();++j) {
			json parameter = function_parameters.at(j);
			output << "\t\t\tthis->" << parameter["name"].get<string>() << "=" << parameter["name"].get<string>() << ";" << endl;
		}
		output << "\t\t}" << endl;
		
		//display---------------------------
		output << "\t\tvoid display(int x, int y){" << endl;
		for (j = 0; j < (*it)["display"].size();++j) {
			output << "\t\t\t//nothing for now" << endl;
		}
		output << "\t\t}" << endl;

		// implement-----------------------
		output << "\t\tvoid implement(){" << endl;
		output << "\t\t\tNameSpace::active_stack=new NameSpace(NameSpace::active_stack);" << endl;
		//variables
		for (j = 0; j < function_parameters.size();++j) {
			json parameter = function_parameters.at(j);
			if(parameter.find("nostack") == parameter.end()){
				output << "\t\t\tVariable<" << parameter["type"].get<string>() << ">* " << parameter["name"].get<string>() << "= new Variable<" << parameter["type"].get<string>() << ">(\"" << parameter["name"].get<string>() << "\",this->" << parameter["name"].get<string>() << "->value);" << endl;
			}
		}
		for (json::iterator it2 = function_variables.begin(); it2 != function_variables.end();++it2) {
			output << "\t\t\tVariable<" << (*it2)["type"].get<string>() << ">* " << it2.key() << "= new Variable<" << (*it2)["type"].get<string>() << ">(\"" << it2.key() << "\"";
			if((*it2).find("value") != (*it2).end()){
				output << "," << (*it2)["value"].get<string>();
			}
			output << ");" << endl;
		}
		output << "\t\t\tint depth=0;" << endl;
		output << "\t\t\tPipeLine::active_pipeline = new PipeLine(PipeLine::active_pipeline);" << endl;
		


		//commands
		for (j = 0; j < function_commands.size();++j) {
			output << "\t\t\t//" << function_commands.at(j)["text"].get<string>() << endl;
			output << "\t\t\tPipeLine::active_pipeline->add_Command( new Command(" << function_commands.at(j)["depth"].get<string>() << "," << function_commands.at(j)["type"].get<string>() << "," << function_commands.at(j)["text"];
			
			json command_function = function_commands.at(j);
			if(command_function.find("function")!=command_function.end()){
				output << ",new " << command_function["function"].get<string>() << "(";
				if(command_function.find("parameters") != command_function.end()){
					json command_parameters=command_function["parameters"];
					int k;
					for(k=0; k < command_function["parameters"].size()-1; ++k){
						output << command_function["parameters"].at(k).get<string>() << ",";
					}
					output << command_function["parameters"].at(k).get<string>();
				}
				output << ")";
			}
			output << "));" << endl;
		}

		output << "\t\t}" << endl << "};" << endl;
	}


	//start of the init----------------------------------------
	output << "void init(void){" << endl;
	output << "\tglClearColor(0.3, 0.3, 0.3, 0.0);" << endl;
	output << "\tglShadeModel(GL_FLAT);" << endl;
	output << "\tglEnable(GL_POLYGON_STIPPLE);" << endl;

	output << "\theap = new NameSpace();" << endl;

	output << "\tglobal = new NameSpace();" << endl;
	//global variables
	for (json::iterator it = variables.begin(); it != variables.end(); ++it) {
		output << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\"";
		if((*it).find("value")!=(*it).end()){
			output << "," << (*it)["value"].get<string>();
		}
		output << ");" << endl;
		output << "global->add_Variable(" << it.key() << ");" << endl;
	}

	output << "\tNameSpace::active_stack = new NameSpace();" << endl;

	output << "\tPipeLine::active_pipeline = new PipeLine();" << endl;
	output << "\tint depth=0;" << endl;
	
	
	//main_variables
	for (json::iterator it = main_variables.begin(); it != main_variables.end(); ++it) {
		string type = (*it)["type"].get<string>();
		if(type.compare("array")==0){
			output << "\t//" << (*it)["value_type"].get<string>() << " " << it.key() << "[" << (*it)["size"].get<string>() << "];" << endl;
			output << "\t" << (*it)["value_type"].get<string>() << " " << it.key() << "[" << (*it)["size"] << "];" << endl;
			output << "\tArray<" << (*it)["value_type"].get<string>() << ">* " << it.key() << "=new Array<" << (*it)["value_type"].get<string>() << ">(\"" << it.key() << "\"," << it.key() << "," << (*it)["size"].get<string>() << ");" << endl;
		}else if((*it).find("value") != (*it).end()){
			output << "\t//" << (*it)["type"].get<string>() << " " << it.key() << "=" << (*it)["value"].get<string>() << ";" << endl;
			output << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\"," << (*it)["value"].get<string>() << ");" << endl;
		}else{
			output << "\t//" << (*it)["type"].get<string>() << " " << it.key() << ";" << endl;	
			output << "\tVariable<" << (*it)["type"].get<string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<string>() << ">(\"" << it.key() << "\");" << endl;
		}
		output << "\tNameSpace::active_stack->add_Variable(" << it.key() << ");" << endl;
	}		
	
	//main_commands
	for (json::iterator it = main_commands.begin(); it != main_commands.end(); ++it) {
		output << "\tPipeLine::active_pipeline->add_Command(new Command(" << (*it)["depth"].get<string>() << "," << (*it)["type"].get<string>() << "," << (*it)["text"];
		if((*it).find("function") != (*it).end()){
			output << ",new " << (*it)["function"].get<string>() << "(";
			if((*it).find("parameters") != (*it).end()){
				int j;
				for(j=0; j < (*it)["parameters"].size()-1; ++j){
					output << (*it)["parameters"].at(j).get<string>() << ",";
				}
				output << (*it)["parameters"].at(j).get<string>();
			}
			output << ")";
		}
		output << "));" << endl;
	}
		
	
	output << "}" << endl;
	
	output.close();
	return 0;
}