#ifndef _LSYSTEM_H_
#define _LSYSTEM_H_

class Production
{
private:
	std::string m_lhs;
	std::string m_rhs;
public:
	Production(std::string lhs, std::string rhs) : m_lhs(lhs), m_rhs(rhs){}
	const std::string& LHS() const throw(){ return m_lhs; }
	const std::string& RHS() const throw(){ return m_rhs; }
};

class LSystem
{
private:
	std::unique_ptr<std::vector<Production>> m_pProductions;
	std::string m_axiom;
	std::string m_currentString;
public:
	LSystem(std::string axiom, std::unique_ptr<std::vector<Production>>& productions) : m_axiom(axiom), m_pProductions(std::move(productions)){ m_currentString = m_axiom; }
	void applyRules();
	const std::string& getCurrentValue() const throw() { return m_currentString; }
};

class LSystemBuilder
{
public:
	static std::unique_ptr<LSystem> buildLSystem(std::string fileName);
};

#endif//LSYSTEM_H_