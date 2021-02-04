#include "json.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using json = nlohmann::json;

int main(){
	int i=0;
	// read a JSON file
	std::ifstream file("sample_result.json");
	json code;
	file >> code;
	file.close();
	
	json variables = code["variables"];
	json functions = code["functions"];
	json main = code["main"];
	json main_variables = main["variables"];
	json main_commands = main["commands"];

	//start of the init

	
	std::cout << "void init(void){" << std::endl;
	std::cout << "\tglClearColor(0.3, 0.3, 0.3, 0.0);" << std::endl;
	std::cout << "\tglShadeModel(GL_FLAT);" << std::endl;
	std::cout << "\tglEnable(GL_POLYGON_STIPPLE);" << std::endl;
	std::cout << "\tNameSpace::active_stack = new NameSpace();" << std::endl;
	std::cout << "\tint depth=0;" << std::endl;
	std::cout << "\tPipeLine::active_pipeline = new PipeLine();" << std::endl;
	std::cout << "\theap = new NameSpace();" << std::endl;
	std::cout << "\tglobal = new NameSpace();" << std::endl;
	std::cout << std::endl << std::endl;

	
	//definitions maybe
	
	//global variables
	for (json::iterator it = variables.begin(); it != variables.end(); ++it) {
		if((*it).find("value") != (*it).end()){
			std::cout << "\t//" << (*it)["type"].get<std::string>() << " " << it.key() << "=" << (*it)["value"].get<std::string>() << ";" << std::endl;
			std::cout << "\tVariable<" << (*it)["type"].get<std::string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<std::string>() << ">(\"" << it.key() << "\"," << (*it)["value"].get<std::string>() << ");" << std::endl;
		}else{
			std::cout << "\t//" << (*it)["type"].get<std::string>() << " " << it.key() << ";" << std::endl;	
			std::cout << "\tVariable<" << (*it)["type"].get<std::string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<std::string>() << ">(\"" << it.key() << "\");" << std::endl;
		}
		std::cout << "\tglobal->add_Variable(" << it.key() << ");" << std::endl;
	}



	
	//function declarations but they should be to the other file
	
	//main_variables
	for (json::iterator it = main_variables.begin(); it != main_variables.end(); ++it) {
		std::string type = (*it)["type"].get<std::string>();
		if(type.compare("array")==0){
			std::cout << "\t//" << (*it)["value_type"].get<std::string>() << " " << it.key() << "[" << (*it)["size"].get<std::string>() << "];" << std::endl;
			std::cout << "\t" << (*it)["value_type"].get<std::string>() << " " << it.key() << "[" << (*it)["size"] << "];" << std::endl;
			std::cout << "\tArray<" << (*it)["value_type"].get<std::string>() << ">* " << it.key() << "=new Array<" << (*it)["value_type"].get<std::string>() << ">(\"" << it.key() << "\"," << it.key() << "," << (*it)["size"].get<std::string>() << ");" << std::endl;
			
		}else if((*it).find("value") != (*it).end()){
			std::cout << "\t//" << (*it)["type"].get<std::string>() << " " << it.key() << "=" << (*it)["value"].get<std::string>() << ";" << std::endl;
			std::cout << "\tVariable<" << (*it)["type"].get<std::string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<std::string>() << ">(\"" << it.key() << "\"," << (*it)["value"].get<std::string>() << ");" << std::endl;
		}else{
			std::cout << "\t//" << (*it)["type"].get<std::string>() << " " << it.key() << ";" << std::endl;	
			std::cout << "\tVariable<" << (*it)["type"].get<std::string>() << ">* " << it.key() << "=new Variable<" << (*it)["type"].get<std::string>() << ">(\"" << it.key() << "\");" << std::endl;
		}
		std::cout << "\tNameSpace::active_stack->add_Variable(" << it.key() << ");" << std::endl;
	}		
	
	//main_commands
	for (json::iterator it = main_commands.begin(); it != main_commands.end(); ++it) {
		std::cout << "\tPipeLine::active_pipeline->add_Command(new Command(" << (*it)["depth"].get<std::string>() << "," << (*it)["type"].get<std::string>();
		if((*it).find("function") != (*it).end()){
			std::cout << ",new " << (*it)["function"].get<std::string>() << "(";
			if((*it).find("parameters") != (*it).end()){
				int j;
				for(j=0; j < (*it)["parameters"].size()-1; ++j){
					std::cout << (*it)["parameters"].at(j).get<std::string>() << ",";
				}
				std::cout << (*it)["parameters"].at(j).get<std::string>();
			}
			std::cout << "))";
		}
		std::cout << ");" << std::endl;
	}
		
	//function definitions but they should be to the other file
	
		// std::cout << "Variables: " << code["variables"] << std::endl;
		// std::cout << "Functions: " << code["functions"]["factorial"]["parameters"] << std::endl;
		// // write prettified JSON to another file
		// std::ofstream o("deneme.json");
		// o << std::setw(4) << j << std::endl;
		// o.close();

		// std::ofstream deneme("deneme2.json");
		// deneme << std::setw(4) << j2 << std::endl;
		// deneme.close();
	
	std::cout << "}" << std::endl;

	return 0;
}