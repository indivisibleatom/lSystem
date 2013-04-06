#include "precomp.h"
#include "LSystem.h"
#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"

namespace
{
	enum ParserState
	{
		Invalid,
		ParseAxiom,
		ParseProduction,
	};
}

std::unique_ptr<LSystem> LSystemBuilder::buildLSystem(std::string fileName)
{
	std::fstream lsystemFile;
	lsystemFile.open(fileName, std::ios_base::in);
	ParserState parserState;
	
	std::string axiom;
	std::unique_ptr<std::vector<Production>> productions(new std::vector<Production>());
	std::vector<std::string> productionValues;
	
    std::string readLine;
	while (std::getline(lsystemFile, readLine))
	{
		if (std::string("Axiom").compare(readLine) == 0)
		{
			parserState = ParseAxiom;
			continue;
		}
		else if (std::string("Productions").compare(readLine) == 0)
		{
			parserState = ParseProduction;
			continue;
		}

		switch(parserState)
		{
		case ParseAxiom: axiom = readLine;
			break;
		case ParseProduction: split(readLine, '>', productionValues);
			assert(productionValues.size() == 2);
			productions->push_back(Production(productionValues[0], productionValues[1]));
			productionValues.clear();
			break;
		}
	}

	std::unique_ptr<LSystem> pSystem(new LSystem(axiom, productions));
	return pSystem;
}

void LSystem::applyRules()
{
	std::string newString;
	for (std::string::const_iterator currentChar = m_currentString.cbegin(); currentChar != m_currentString.cend(); currentChar++)
	{
		for (std::vector<Production>::const_iterator currentProduction = m_pProductions->cbegin(); currentProduction != m_pProductions->cend(); currentProduction++)
		{
			if (std::string(currentChar, currentChar+1).compare(currentProduction->LHS()) == 0)
			{
				newString.append(currentProduction->RHS());
			}
		}
	}
	m_currentString = newString;
	std::cout<<newString;
}
