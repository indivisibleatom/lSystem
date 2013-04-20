#include "precomp.h"
#include "LSystemInterpreter.h"
#include "LineDrawable.h"
#include "Token.h"

std::unique_ptr<IDrawable> LSystemInterpreter::interpret(const std::string& string)
{
	const float length = 10;
	const float angle = PI/4;

	std::unique_ptr<LineDrawable> pLineDrawable(new LineDrawable());
	
	m_turtle.reset();
	StringTokenizer tokenizer(string);
	ExpandedToken currentToken;
	while (tokenizer.getNextToken(currentToken))
	{
		switch (currentToken.getChar())
		{
		case 'F': 
			{
				Point3Df initPosition = m_turtle.position();
				float distance = 100;
				currentToken.getParamValueForKey('l', distance);
				m_turtle.translate(distance);
				Point3Df finalPosition = m_turtle.position();
				pLineDrawable->addPoints(initPosition, finalPosition);
				break;
			}
		case '+': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.changeHeading(angle);
				break;
			}
		case '-': 			
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.changeHeading(-angle);
				break;
			}
		case '&': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.changePitch(angle);
				break;
			}
		case '^': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.changePitch(-angle);
				break;
			}
		case '\\': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.changeRoll(angle);
				break;
			}
		case '/': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.changeRoll(-angle);
				break;
			}
		case '[': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.pushState();
				break;
			}
		case ']': 
			{
				float angle = 45;
				currentToken.getParamValueForKey('a', angle);
				m_turtle.popState();
				break;
			}
		default: break;
		}
	}
	return std::unique_ptr<IDrawable>(std::move(pLineDrawable));
}