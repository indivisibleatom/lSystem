#ifndef _TOKEN_H_
#define _TOKEN_H_

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
	bool getParamValueForKey(char key, __out float& value) const throw();
	std::string getStringForToken() const throw();
};

class StringTokenizer
{
private:
	const std::string& m_string;
	const char* m_pCurPosition;

public:
	StringTokenizer(const std::string& string) throw() : m_string(string) { m_pCurPosition = m_string.c_str(); }
	bool getNextToken(__out ExpandedToken& token) throw();
};

#endif//_TOKEN_H_