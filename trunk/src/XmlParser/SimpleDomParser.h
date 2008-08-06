#ifndef SIMPLEDOMPARSER_H
#define SIMPLEDOMPARSER_H

// Includes
#include "global.h"
#include "XmlParser.h"

#include <vector>
#include <stack>

// Forward declarations
class XmlElement;


/**
	This is a simple DOM parser, containing a tree of xml elements.
	You can traverse the tree using the root element, and the child-parent relations.
*/
class XMLPARSER_API SimpleDomParser: public XmlParser
{
protected:
	// Typedefs
	typedef std::vector<XmlElement *> ElementList;

	// Member variables
	ElementList m_elements;
	XmlElement *m_pRootElement;
	std::stack<XmlElement *> m_contextStack;

public:
	// Constructors and destructor
	SimpleDomParser();
	virtual ~SimpleDomParser();

	// Get functions
	bool hasElements() const { return !m_elements.empty(); }
	XmlElement *getRootElement() const { return m_pRootElement; }

	// Other functions
	void clear();

protected:
	// Overloaded functions
	void startParsing(const string &filename);
	//void doneParsing(const string &filename);
	//void header(string version, string encoding, int standalone);
	void startTag(string name, AttributeMap attributes);
	void endTag(string name);
	void content(string text, const string &context);
};

#endif // SIMPLEDOMPARSER_H
