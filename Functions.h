#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <iostream>

#define	NORMAL 0
#define	IF 1
#define	ELSE 2
#define	OPEN_SCOPE 3
#define	CLOSE_SCOPE 4



class Function{
	public:
		Function();
		~Function();
		virtual void display(int x, int y)=0;
	private:

	protected:

};

class Command{
	public:
		Command(int level=0, int type=0, Function* func=NULL);
		void display(int x, int y);
	private:
		int level;
		int type;
		Function* func;
	protected:

};


class PipeLine{
	public:
		PipeLine();
		void display();
		void add_Command(Command* command);
		std::vector<Command*> commands;
		PipeLine* parent;
		static PipeLine* active_pipeline;
	private:
		
	protected:
		
};
#endif