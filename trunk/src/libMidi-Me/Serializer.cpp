// Includes
#include "Serializer.h"
#include "Chain.h"
#include "Input.h"
#include "Output.h"
//#include "Processor.h"
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
	stream << "<!DOCTYPE midi-me SYSTEM \"midi-me.dtd\">\n\n";

	return true;
}

bool Serializer::writeChain(std::ostream &stream, Chain *pChain)
{
	stream << "<chain>\n";

	//! @todo Implement this: chains need input items, output items, and inbetween items
	//pChain->numItems

	stream << "</chain>\n";

	return true;
}

bool Serializer::writeProcessor(std::ostream &stream, Processor *pProcessor)
{
	//! @todo Implement this: processors need an ID and serializable properties
	return true;
}

bool Serializer::writeConnection(std::ostream &stream, ValueOutput *pOutput)
{
	//! @todo Implement this: in- and outputs need IDs
	//cerr << "\t<connection from=\"" << pOutput->getID() << "\" to=\"" << << "\" />\n";
	return true;
}

bool Serializer::writeConnection(std::ostream &stream, RangeOutput *pOutput)
{
	//! @todo Implement this: in- and outputs need IDs
	//cerr << "\t<connection from=\"" << pOutput->getID() << "\" to=\"" << << "\" />\n";
	return true;
}
