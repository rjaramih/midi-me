// Includes
#include "SimpleDomParser.h"
#include "XmlElement.h"

using namespace std;


/******************************
* Constructors and destructor *
******************************/

SimpleDomParser::SimpleDomParser()
: m_pRootElement(0)
{
}

SimpleDomParser::~SimpleDomParser()
{
	clear();
}


/************************
* Get and set functions *
************************/


/******************
* Other functions *
******************/

void SimpleDomParser::clear()
{
	// Clear the context stack
	while(!m_contextStack.empty())
		m_contextStack.pop();

	// Clear the xml elements
	ElementList::iterator it;
	for(it = m_elements.begin(); it != m_elements.end(); ++it)
		delete *it;
	m_elements.clear();

	// No root element
	m_pRootElement = 0;
}

void SimpleDomParser::startParsing(const string &filename)
{
	clear();
}

void SimpleDomParser::startTag(string name, AttributeMap attributes)
{
	// Create a new element
	XmlElement *pElement = new XmlElement();
	pElement->setName(name);
	pElement->setAttributes(attributes);
	if(m_contextStack.empty()) // Root element?
		m_pRootElement = pElement;
	else
	{
		// Establish child-parent relation
		m_contextStack.top()->addChild(pElement);
		pElement->setParent(m_contextStack.top());
	}

	// Put the element in the list
	m_elements.push_back(pElement);

	// Put this element on the context stack
	m_contextStack.push(pElement);
}

void SimpleDomParser::endTag(string name)
{
	// Pop the element from the context stack
	m_contextStack.pop();
}

void SimpleDomParser::content(string text, const string &context)
{
	// This can only occur inside a context (actually, only in a leaf of the xml tree)
	assert(!m_contextStack.empty());

	m_contextStack.top()->setContent(text);
}


/**********************
* Protected functions *
**********************/
