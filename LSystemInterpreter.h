#ifndef _LSYTEMINTERPRETER_H_
#define _LSYTEMINTERPRETER_H_

#include "Turtle.h"
class IDrawable;

class LSystemInterpreter
{
private:
	Turtle m_turtle;

public:
	std::unique_ptr<IDrawable> interpret(const std::string& lString);
};

#endif//_LSYTEMINTERPRETER_H_