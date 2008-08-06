#ifndef XMLELEMENT_H
#define XMLELEMENT_H

// Includes
#include "global.h"
#include "XmlParser.h"

#include <vector>
using std::vector;

// Forward declarations

/**
	A simple XML element, consisting of	a name, attributes and content (only a leave element can have content).
	An element has a parent (0 for the root element) and children(none for a leave element).
*/
class XMLPARSER_API XmlElement
{
protected:
	// Typedefs
	typedef vector<XmlElement *> ElementList;

	// Member variables
	string m_name;
	AttributeMap m_attributes;
	string m_content;
	
	XmlElement *m_pParent;
	XmlElement *m_pNextSibling;
	ElementList m_children;

public:
	// Constructors and destructor
	XmlElement();
	virtual ~XmlElement();

	// Name
	const string &getName() const { return m_name; }
	void setName(const string &name) { m_name = name; }

	// Attributes
	const AttributeMap &getAttributes() const { return m_attributes; }
	void setAttributes(const AttributeMap &attributes);
	const string &getAttribute(const string &attribute) const;
	void setAttribute(const string &attribute, const string &value) { m_attributes[attribute] = value; }
	bool hasAttribute(const string &attribute) const { return (m_attributes.find(attribute) != m_attributes.end()); }

	// Content
	const string &getContent() const { return m_content; }
	void setContent(const string &content) { m_content = content; }

	// Parent
	XmlElement *getParent() const { return m_pParent; }
	void setParent(XmlElement *pParent) { m_pParent = pParent; }
	bool isRoot() const { return (m_pParent == 0); }

	// Children
	unsigned int numChildren() const { return m_children.size(); }
	const ElementList &getChildren() const { return m_children; }
	XmlElement *getChild(unsigned int i) const { return m_children.at(i); }
	void addChild(XmlElement *pChild);
	bool isLeaf() const { return m_children.empty(); }

	// DOM functions
	XmlElement *getFirstChild() const;
	XmlElement *getFirstChild(const string &name) const;

	XmlElement *getNextSibling() const;
	XmlElement *getNextSibling(const string &name) const;

protected:
	// Protected functions
	void setNextSibling(XmlElement *pElement) { m_pNextSibling = pElement; }
};

#endif // XMLELEMENT_H
