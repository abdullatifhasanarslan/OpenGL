#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>

#define	NORMAL 0

class Function{
	public:
		Function();
		~Function();
	private:

	protected:

};

class Command{
	public:
		Command(int level, int type);
		void display(int x, int y);
	private:
		int level;
		int type;
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