#ifndef _LSYSTEM_H_
#define _LSYSTEM_H_

#include <map>

class Token
{
protected:
	char m_alpha;
	typedef std::map<char, float> TokenParams;
	TokenParams m_params;

public:
	Token() {}
	virtual ~Token() {}
	virtual const char* createToken(const char* ptr);
	char getChar() const throw() { return m_alpha; }
	typedef TokenParams::iterator iterator;
	typedef TokenParams::const_iterator const_iterator;
	iterator paramBegin() { return m_params.begin(); }
	iterator paramEnd() { return m_params.end(); }
	const_iterator cParamBegin() const { return m_params.cbegin(); }
	const_iterator cParamEnd() const { return m_params.cend(); }
};

class ExpandedToken : public Token
{
public:
	ExpandedToken() {}
	~ExpandedToken() {}
	const char* createToken(const char* ptr) override;
	void createToken(const ExpandedToken& currentToken, const Token& tokenToUse);
	float getParamValueForKey(char key) const throw() { return m_params.find(key)->second; }
	std::string getStringForToken() const throw();
};

class ProductionLHS
{
private:
	Token m_token;
	//std::List<Conditions> m_conditions;
public:
	ProductionLHS(const std::string& lhs);
	bool matches(const Token& token) const throw();
};

class ProductionRHS
{
private:
	typedef std::vector<Token> TokenList;
	TokenList m_tokens;
public:
	ProductionRHS(const std::string& rhs);
	typedef TokenList::iterator iterator;
	typedef TokenList::const_iterator const_iterator;
	iterator begin() { return m_tokens.begin(); }
	iterator end() { return m_tokens.end(); }
	const_iterator cbegin() const { return m_tokens.cbegin(); }
	const_iterator cend() const { return m_tokens.cend(); }
};

class Production
{
private:
	ProductionLHS m_lhs;
	ProductionRHS m_rhs;
	float m_probability;

public:
	Production(std::string lhs, std::string rhs, float probability) : m_lhs(lhs), m_rhs(rhs), m_probability(probability) {}
	float probability() const throw() { return m_probability; }
	bool matches(const Token& token) const throw() { return m_lhs.matches(token); }
	void applyTo(const ExpandedToken& token, std::string& resultString) const throw();
};

class LSystem
{
private:
	std::unique_ptr<std::vector<Production>> m_pProductions;
	std::unique_ptr<ExpandedToken> m_pAxiom;
	std::string m_currentString;
	int m_numDerivations;

	void getProductionsFor(const Token& currentToken, __out std::vector<const Production*>& matchingProductions) const throw();
	std::string getNextToken(const char* pCurrent) const throw();
	void expandCurrentToken(const ExpandedToken& currentToken, __inout std::string& resultString, const std::vector<const Production*>& matchingProductions) const throw();

public:
	LSystem(int numDerivations, std::unique_ptr<ExpandedToken> pAxiom, std::unique_ptr<std::vector<Production>>& productions) : m_numDerivations(numDerivations), 
																											m_pAxiom(std::move(pAxiom)), 
																											m_pProductions(std::move(productions)){ m_currentString = m_pAxiom->getStringForToken(); }
	void applyRules();
	const std::string& getCurrentValue() const throw() { return m_currentString; }
	const int getNumDerivations() { return m_numDerivations; }
};

class LSystemBuilder
{
public:
	static std::unique_ptr<LSystem> buildLSystem(std::string fileName);
};

#endif//LSYSTEM_H_