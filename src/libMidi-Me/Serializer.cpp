// Includes
#include "Serializer.h"
#include "Chain.h"
#include "Input.h"
#include "Output.h"
#include "ChainStart.h"
#include "ChainEnd.h"
#include "Processor.h"
#include "InputDevice.h"
#include "MidiOutput.h"
#include <Properties/StandardProperties.h>
using namespace MidiMe;

#include <XmlParser/SimpleDomParser.h>
#include <fstream>


/******************************
* Constructors and destructor *
******************************/

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
}


/******************
* Other functions *
******************/

bool Serializer::load(Chain *pChain, const string &filename)
{
	// Try to load the XML file
	SimpleDomParser parser;
	if(!parser.parse(filename, false)) //!< @todo Create DTD to check from
	{
		setLastError("Error parsing '" + filename + "': " + parser.getLastError());
		return false;
	}
	
	//! @todo Parse the DOM
	return true;
}

bool Serializer::save(Chain *pChain, const string &filename)
{
	// Try to open the file
	std::ofstream stream(filename.c_str());
	if(!stream)
	{
		setLastError("Error opening output stream for '" + filename + "'");
		return false;
	}

	if(!writeHeader(stream))
	{
		setLastError("Error writing the header");
		return false;
	}

	if(!writeChain(stream, pChain))
	{
		setLastError("Error writing the chain");
		return false;
	}
	
	return true;
}


/*****************
* Read functions *
*****************/


/******************
* Write functions *
******************/

bool Serializer::writeHeader(std::ostream &stream)
{
	stream << "<?xml version=\"1.0\"?>\n";
	stream << "<!DOCTYPE chain SYSTEM \"chain.dtd\">\n\n";

	return true;
}

bool Serializer::writeChain(std::ostream &stream, Chain *pChain)
{
	stream << "<chain>\n";

	// Serialize chain starts
	const ChainStartSet &start = pChain->getChainStart();
	for(ChainStartSet::const_iterator it = start.begin(); it != start.end(); ++it)
		writeChainStart(stream, *it);

	stream << "\n";

	// Serialize processors
	const ProcessorSet &processors = pChain->getProcessors();
	for(ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it)
		writeProcessor(stream, *it);

	stream << "\n";

	// Serialize chain ends
	const ChainEndSet &end = pChain->getChainEnd();
	for(ChainEndSet::const_iterator it = end.begin(); it != end.end(); ++it)
		writeChainEnd(stream, *it);

	stream << "</chain>\n";

	return true;
}

bool Serializer::writeChainStart(std::ostream &stream, ChainStart *pStart)
{
	stream << "\t<start";
	stream << " device=\"" << pStart->getDevice()->getName() << "\"";
	stream << " outputID=\"" << pStart->getOutputID() << "\"";
	stream << " />\n";

	return true;
}

bool Serializer::writeChainEnd(std::ostream &stream, ChainEnd *pEnd)
{
	stream << "\t<end";
	stream << " channel=\"" << pEnd->getChannel() << "\"";
	stream << " controller=\"" << pEnd->getController() << "\"";
	stream << " startValue=\"" << pEnd->getStartValue() << "\"";
	stream << " endValue=\"" << pEnd->getEndValue() << "\"";
	stream << " />\n";

	return true;
}

bool Serializer::writeProcessor(std::ostream &stream, Processor *pProcessor)
{
	stream << "\t<processor type=\"" << pProcessor->getType() << "\">\n";
	writeProperties(stream,  pProcessor, 1);
	stream << "\t</processor>\n";
	return true;
}

bool Serializer::writeConnection(std::ostream &stream, Output *pOutput)
{
	//! @todo Implement this: in- and outputs need IDs
	//cerr << "\t<connection from=\"" << pOutput->getID() << "\" to=\"" << << "\" />\n";
	return true;
}

bool Serializer::writeProperties(std::ostream &stream, PropertyCollection *pProperties, unsigned int indentLevel)
{
	// Write all the properties
	const PropertyList &props = pProperties->getPropertiesList();
	PropertyList::const_iterator it;
	for(it = props.begin(); it != props.end(); ++it)
	{
		Property *pProperty = *it;
		writeProperty(stream, pProperty, indentLevel + 1);
	}

	return true;
}

bool Serializer::writeProperty(std::ostream &stream, Property *pProperty, unsigned int indentLevel)
{
	if(pProperty->getType() == "compound")
	{
		writeTabs(stream, indentLevel);
		stream << "<property type=\"compound\" name=\"" << pProperty->getName() << "\">" << endl;

		CompoundProperty *pCompound = (CompoundProperty *) pProperty;
		const PropertyMap &children = pCompound->getProperties();
		for(PropertyMap::const_iterator it = children.begin(); it != children.end(); ++it)
			writeProperty(stream, it->second, indentLevel + 1);

		writeTabs(stream, indentLevel);
		stream << "</property>" << endl;
	}
	else
	{
		writeTabs(stream, indentLevel);
		stream << "<property type=\"" << pProperty->getType();
		stream << "\" name=\"" << pProperty->getName();
		stream << "\" value=\"" << pProperty->toString() << "\" />" << endl;
	}

	return true;
}

void Serializer::writeTabs(std::ostream &stream, unsigned int num)
{
	for(unsigned int i = 0; i < num; ++i)
		stream << "\t";
}
