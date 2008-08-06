// Includes
#include "XmlElement.h"

using namespace std;


/******************************
* Constructors and destructor *
******************************/

XmlElement::XmlElement()
: m_pParent(0), m_pNextSibling(0)
{
}

XmlElement::~XmlElement()
{
}


/************************
* Get and set functions *
************************/


/******************
* Other functions *
******************/

const string &XmlElement::getAttribute(const string &attribute) const
{
	static string emptyString;

	AttributeMap::const_iterator it = m_attributes.find(attribute);
	return (it == m_attributes.end()) ? emptyString : it->second;
}

void XmlElement::setAttributes(const AttributeMap &attributes)
{
	m_attributes.clear();

	AttributeMap::const_iterator it;
	for(it = attributes.begin(); it != attributes.end(); ++it)
		m_attributes[it->first] = it->second;
}

void XmlElement::addChild(XmlElement *pChild)
{
	if(!m_children.empty())
		m_children.back()->setNextSibling(pChild);

	m_children.push_back(pChild);
}


/****************
* DOM functions *
****************/

XmlElement *XmlElement::getFirstChild() const
{
	if(m_children.empty())
		return 0;

	return m_children.front();
}

XmlElement *XmlElement::getFirstChild(const string &name) const
{
	ElementList::const_iterator it;
	for(it = m_children.begin(); it != m_children.end(); ++it)
	{
		XmlElement *pElement = *it;

		if(pElement->getName() == name)
			return pElement;
	}

	return 0;
}

XmlElement *XmlElement::getNextSibling() const
{
	return m_pNextSibling;
}

XmlElement *XmlElement::getNextSibling(const string &name) const
{
	XmlElement *pSibling = m_pNextSibling;
	while(pSibling)
	{
		if(pSibling->getName() == name)
			return pSibling;
		
		pSibling = pSibling->getNextSibling();
	}

	return 0;
}
