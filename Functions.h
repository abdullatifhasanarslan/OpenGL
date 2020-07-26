#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>

#define	NORMAL 0
#define	IF 1
#define	ELSE_IF 2
#define	ELSE 3
#define	WHILE 4
#define	OPEN_SCOPE 5
#define	CLOSE_SCOPE 6
#define	CLOSE_LOOP_SCOPE 7



class Function{
	public:
		Function();
		~Function();
		virtual void display(int x, int y)=0;
		virtual void implement()=0;
		std::string name;
		bool result;
	private:

	protected:
		int x, y, width, height;

};

class Command{
	public:
		Command(int level=0, int type=0, Function* func=NULL);
		void display(int x, int y);
		void implement();
		int get_type();
		int get_level();
		bool is_active();
		void disable();
		void activate();
	private:
		bool active;
		int level;
		int type;
		Function* func;
	protected:

};


class PipeLine{
	public:
		PipeLine();
		PipeLine(PipeLine* parent);
		void display();
		void add_Command(Command* command);
		void step();
		std::vector<Command*> commands;
		PipeLine* parent;
		static PipeLine* active_pipeline;
		void come_back(int level);
		void skip(int level);
		void disable_else(int level);
	private:
		unsigned int current;
		
	protected:
		
};
#endif