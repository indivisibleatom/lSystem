#include "precomp.h"
#include "LSystemInterpreter.h"
#include "LineDrawable.h"

std::unique_ptr<IDrawable> LSystemInterpreter::interpret(const std::string& string)
{
	const float length = 10;
	const float angle = PI/4;

	std::unique_ptr<LineDrawable> pLineDrawable(new LineDrawable());
	
	m_turtle.reset();
	for (std::string::const_iterator iterator = string.cbegin(); iterator != string.cend(); iterator++)
	{
		switch (*iterator)
		{
		case 'F': 
			{
				Point3Df initPosition = m_turtle.position();
				m_turtle.translate(length);
				Point3Df finalPosition = m_turtle.position();
				pLineDrawable->addPoints(initPosition, finalPosition);
				break;
			}
		case '+': m_turtle.changeHeading(angle);
			break;
		case '-': m_turtle.changeHeading(-angle);
			break;
		case '&': m_turtle.changePitch(angle);
			break;
		case '^': m_turtle.changePitch(-angle);
			break;
		case '\\': m_turtle.changeRoll(angle);
			break;
		case '/': m_turtle.changeRoll(-angle);
			break;
		default: break;
		}
	}
	return std::unique_ptr<IDrawable>(std::move(pLineDrawable));
}