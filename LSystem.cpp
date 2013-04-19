#include "precomp.h"
#include "LSystem.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
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

const char* Token::createToken(const char* pCurrent)
{
	std::string currentString;

	bool fShouldReadParamsNext = false;
	bool fReadingParams = false;
	bool fDoneReadingParams = false;
	std::string attribScaleValue = "";

	while (*pCurrent != '\0' && !fDoneReadingParams)
	{
		char ch = *pCurrent++;
		if (fReadingParams || fShouldReadParamsNext)
		{
			if (ch == '(')
			{
				fReadingParams = true;
			}
			else if (ch == ')')
			{
				fDoneReadingParams = true;
			}
			else
			{
				if (!fReadingParams) //We come to a new token, without encountering any parameters <Assume well formed>
				{
					pCurrent--;
					break;
				}
				else if (isalpha(ch))
				{
					float scaleValue = 1;
					if (!attribScaleValue.empty())
					{
						scaleValue = atof(attribScaleValue.c_str());
					}
					m_params.insert(std::pair<char, float>(ch, scaleValue));
					attribScaleValue = "";
				}
				else if (ch == ',')
				{
					//Do nothing. this can be exploited to allow for variable length names for params
				}
				else
				{
					attribScaleValue.push_back(ch);
				}
			}
		}
		else
		{
			m_alpha = ch;
			fShouldReadParamsNext = true;
		}
	}
	return pCurrent;
}

std::string ExpandedToken::getStringForToken() const throw()
{
	std::string stringForToken;
	stringForToken.push_back(m_alpha);
	for (std::map<char, float>::const_iterator attrib = m_params.cbegin(); attrib != m_params.cend(); attrib++)
	{
		if (attrib == m_params.cbegin())
		{
			stringForToken.push_back('(');
		}
		else
		{
			stringForToken.push_back(',');
		}
		stringForToken.push_back(attrib->first);
		stringForToken.push_back(':');
		std::stringstream ss (std::stringstream::in | std::stringstream::out);
		ss << attrib->second;
		stringForToken.append(ss.str());		
	}
	if (m_params.size() > 0)
	{
		stringForToken.push_back(')');
	}
	
	return stringForToken;
}

const char* ExpandedToken::createToken(const char* pCurrent)
{
	std::string currentString;

	bool fShouldReadParamsNext = false;
	bool fReadingParams = false;
	bool fDoneReadingParams = false;
	std::string attribScaleValue = "";

	while (*pCurrent != '\0' && !fDoneReadingParams)
	{
		char ch = *pCurrent++;
		if (fReadingParams || fShouldReadParamsNext)
		{
			if (ch == '(')
			{
				fReadingParams = true;
			}
			else if (ch == ')')
			{
				fDoneReadingParams = true;
			}
			else
			{
				if (!fReadingParams) //We come to a new token, without encountering any parameters <Assume well formed>
				{
					pCurrent--;
					break;
				}
				else if (isalpha(ch))
				{
					assert(*pCurrent == ':');
					pCurrent++; //Skip the ':'

					std::string paramValue = "";
					while (*pCurrent != ')' && *pCurrent != ',')
					{
						paramValue.push_back(*pCurrent);
						pCurrent++;
					}
					float fParamValue = atof(paramValue.c_str());
					m_params.insert(std::pair<char, float>(ch, fParamValue));
					attribScaleValue = "";
				}
				else
				{
					assert(ch == ','); //This is the only other valid case
				}
			}
		}
		else
		{
			m_alpha = ch;
			fShouldReadParamsNext = true;
		}
	}
	return pCurrent;
}

void ExpandedToken::createToken(const ExpandedToken& currentToken, const Token& tokenToUse)
{
	m_alpha = tokenToUse.getChar();
	for (std::map<char, float>::const_iterator paramIt = tokenToUse.cParamBegin(); paramIt != tokenToUse.cParamEnd(); paramIt++)
	{
		float boundValueForParam = currentToken.getParamValueForKey(paramIt->first);
		float expandedValue = paramIt->second * boundValueForParam;
		m_params.insert(std::pair<char, float>(paramIt->first, expandedValue));
	}
}


ProductionLHS::ProductionLHS(const std::string& lhs)
{
	const char* tokenEnd = m_token.createToken(lhs.c_str());
}

bool ProductionLHS::matches(const Token& token) const throw()
{
	return (token.getChar() == m_token.getChar());
}

ProductionRHS::ProductionRHS(const std::string& rhs)
{
	const char* pCur = rhs.c_str();
	while (*pCur != '\0')
	{
		Token currentToken;
		pCur = currentToken.createToken(pCur);
		m_tokens.push_back(currentToken);
	}
}

void Production::applyTo(const ExpandedToken& currentToken, std::string& resultString) const throw()
{
	//TODO msati3: can add conditions here
	for (ProductionRHS::const_iterator tokenIt = m_rhs.cbegin(); tokenIt != m_rhs.cend(); tokenIt++)
	{
		ExpandedToken substitutedToken;
		substitutedToken.createToken(currentToken, *tokenIt);
		resultString.append(substitutedToken.getStringForToken());
	}
}

std::unique_ptr<LSystem> LSystemBuilder::buildLSystem(std::string fileName)
{
	std::fstream lsystemFile;
	lsystemFile.open(fileName, std::ios_base::in);
	ParserState parserState;
	int numDerivations = -1;

	std::unique_ptr<ExpandedToken> pAxiom(new ExpandedToken());
	std::unique_ptr<std::vector<Production>> productions(new std::vector<Production>());
	std::vector<std::string> productionValues;
	
    std::string readLine;
	while (std::getline(lsystemFile, readLine))
	{
		const char* pDerivations = NULL;
		if ((pDerivations = strstr(readLine.c_str(), "numDerivations")) !=  nullptr)
		{
			while (!isdigit(*(++pDerivations)));
			numDerivations = atoi(pDerivations);
			continue;
		}
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
		case ParseAxiom: pAxiom->createToken(readLine.c_str());
			break;
		case ParseProduction: split(readLine, '>', productionValues);
			assert(productionValues.size() == 2);
			
			std::vector<std::string> rhsSideProductionValues;
			split(productionValues[1], '&', rhsSideProductionValues);
			assert(productionValues.size() == 2);

			productions->push_back(Production(productionValues[0], rhsSideProductionValues[0], atof(rhsSideProductionValues[1].c_str())));
			productionValues.clear();
			break;
		}
	}

	std::unique_ptr<LSystem> pSystem(new LSystem(numDerivations, std::move(pAxiom), productions));
	return pSystem;
}

void LSystem::getProductionsFor(const Token& currentToken, __out std::vector<const Production*>& matchingProductions) const throw()
{
	for (std::vector<Production>::const_iterator production = m_pProductions->cbegin(); production != m_pProductions->cend(); production++)
	{
		if (production->matches(currentToken))
		{
			matchingProductions.push_back(&*production);
		}
	}
}

void LSystem::expandCurrentToken(const ExpandedToken& currentToken, __inout std::string& resultString, const std::vector<const Production*>& matchingProductions) const throw()
{
	if (matchingProductions.size() == 0)
	{
		resultString.append(currentToken.getStringForToken());
		return;
	}
	int random = rand();
	float value = (float)random/RAND_MAX;
	float cumulativeProbability = 0;
	for (std::vector<const Production*>::const_iterator production = matchingProductions.cbegin(); production != matchingProductions.cend(); production++)
	{
		cumulativeProbability += (*production)->probability();
		if (cumulativeProbability >= value)
		{
			(*production)->applyTo(currentToken, resultString);
		}
	}
}

void LSystem::applyRules()
{
	std::string newString;

	const char* pCur = m_currentString.c_str();
	while (*pCur != '\0')
	{
		ExpandedToken currentToken;
		pCur = currentToken.createToken(pCur);
		std::vector<const Production*> matchingProductions;
		getProductionsFor(currentToken, matchingProductions);
		expandCurrentToken(currentToken, newString, matchingProductions);
	}
	m_currentString = newString;
	std::cout<<newString;
}
