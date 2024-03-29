// Includes
#include "Serializer.h"
#include "Chain.h"
#include "Input.h"
#include "Output.h"
#include "ChainStart.h"
#include "ChainEnd.h"
#include "Processor.h"
#include "Connection.h"
#include "InputDevice.h"
#include "MidiOutput.h"
#include "DeviceManager.h"
#include <Properties/StandardProperties.h>
#include <Properties/StringUtil.h>
using namespace MidiMe;

#include <XmlParser/SimpleDomParser.h>
#include <XmlParser/XmlElement.h>
#include <fstream>


/******************************
* Constructors and destructor *
******************************/

Serializer::Serializer()
: m_pChain(0), m_currentOutputID(0), m_currentInputID(0)
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
	m_pChain = pChain;
	if(!m_pChain)
	{
		setLastError("Null chain");
		return false;
	}

	m_outputs.clear();
	m_inputs.clear();

	// Try to load the XML file
	SimpleDomParser parser;
	if(!parser.parse(filename, false)) //!< @todo Create DTD to check from
	{
		setLastError("Error parsing '" + filename + "': " + parser.getLastError());
		return false;
	}

	XmlElement *pChainEl = parser.getRootElement();
	if(pChainEl->getName() != "chain")
	{
		setLastError("The root element is not 'chain'");
		return false;
	}

	// Parse the chain
	if(!readChain(pChainEl))
		return false;
	
	return true;
}

bool Serializer::save(Chain *pChain, const string &filename)
{
	m_pChain = pChain;
	if(!m_pChain)
	{
		setLastError("Null chain");
		return false;
	}

	m_outputIDs.clear();
	m_inputIDs.clear();
	m_currentOutputID = m_currentInputID = 0;

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

bool Serializer::readChain(XmlElement *pChainEl)
{
	// Read chain start
	XmlElement *pEl = pChainEl->getFirstChild("start");
	while(pEl)
	{
		if(!readChainStart(pEl))
		{
			setLastError("Error reading chain start");
			return false;
		}

		pEl = pEl->getNextSibling("start");
	}

	// Read chain end
	pEl = pChainEl->getFirstChild("end");
	while(pEl)
	{
		if(!readChainEnd(pEl))
		{
			setLastError("Error reading chain end");
			return false;
		}

		pEl = pEl->getNextSibling("end");
	}

	// Read processors
	pEl = pChainEl->getFirstChild("processor");
	while(pEl)
	{
		if(!readProcessor(pEl))
		{
			setLastError("Error reading processor");
			return false;
		}

		pEl = pEl->getNextSibling("processor");
	}

	// Read connections
	pEl = pChainEl->getFirstChild("connection");
	while(pEl)
	{
		if(!readConnection(pEl))
		{
			setLastError("Error reading connection");
			return false;
		}

		pEl = pEl->getNextSibling("connection");
	}

	return true;
}

bool Serializer::readChainStart(XmlElement *pElement)
{
	// The device name (required attribute)
	const string &name = pElement->getAttribute("device");

	InputDevice *pDevice = DeviceManager::getInstance().getInputDevice(name);
	if(!pDevice)
		return false;

	// The output ID (required attribute)
	unsigned int outputID = StringUtil::toUInt(pElement->getAttribute("outputID"));

	// Add the chain start
	ChainStart *pStart = m_pChain->addChainStart(pDevice, outputID);

	// Read properties
	readProperties(pElement, pStart);

	// Index the output
	m_outputs.push_back(pStart->getOutput());
	
	return (pStart != 0);
}

bool Serializer::readChainEnd(XmlElement *pElement)
{
	// Add the chain end
	ChainEnd *pEnd = m_pChain->addChainEnd();
	if(!pEnd)
		return false;

	// Read properties
	readProperties(pElement, pEnd);

	// Index the input
	m_inputs.push_back(pEnd->getInput());
	
	return true;
}

bool Serializer::readProcessor(XmlElement *pElement)
{
	// The processor type (required)
	const string &type = pElement->getAttribute("type");

	Processor *pProcessor = m_pChain->addProcessor(type);
	if(!pProcessor)
		return false;

	// Read properties
	readProperties(pElement, pProcessor);

	// Index the outputs
	const OutputList &outputs = pProcessor->getOutputs();
	for(OutputList::const_iterator it = outputs.begin(); it != outputs.end(); ++it)
		m_outputs.push_back(*it);
	
	// Index the inputs
	const InputList &inputs = pProcessor->getInputs();
	for(InputList::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
		m_inputs.push_back(*it);
	
	return true;
}

/** Connect the previously created components. */
bool Serializer::readConnection(XmlElement *pElement)
{
	// Note: the IDs only match if the elements get read and written in the same order!
	unsigned int outputID = StringUtil::toUInt(pElement->getAttribute("outputID"));
	unsigned int inputID = StringUtil::toUInt(pElement->getAttribute("inputID"));

	if(m_outputs.size() <= outputID || m_inputs.size() <= inputID)
		return false;

	Output *pOutput = m_outputs.at(outputID);
	Input *pInput = m_inputs.at(inputID);

	// Create the connection
	Connection *pConnection = m_pChain->addConnection(pInput, pOutput);
	if(!pConnection)
		return false;

	// Read properties
	readProperties(pElement, pConnection);
	return true;
}

void Serializer::readProperties(XmlElement *pElement, PropertyCollection *pProperties)
{
	XmlElement *pPropEl = pElement->getFirstChild("property");
	while(pPropEl)
	{
		const string &type = pPropEl->getAttribute("type");
		const string &name = pPropEl->getAttribute("name");
		Property *pProperty = pProperties->getProperty(name);

		if(pProperty)
		{
			if(type == "compound")
				readCompoundProperty(pPropEl, (CompoundProperty *) pProperty);
			else
				pProperty->fromString(pPropEl->getAttribute("value"));
		}

		pPropEl = pPropEl->getNextSibling("property");
	}
}

void Serializer::readCompoundProperty(XmlElement *pElement, CompoundProperty *pProperty)
{
	XmlElement *pPropEl = pElement->getFirstChild("property");
	while(pPropEl)
	{
		const string &type = pPropEl->getAttribute("type");
		const string &name = pPropEl->getAttribute("name");
		Property *pChildProp = pProperty->getProperty(name);

		if(pChildProp)
		{
			if(type == "compound")
				readCompoundProperty(pPropEl, (CompoundProperty *) pChildProp);
			else
				pChildProp->fromString(pPropEl->getAttribute("value"));
		}

		pPropEl = pPropEl->getNextSibling("property");
	}
}


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

	// Serialize chain ends
	const ChainEndSet &end = pChain->getChainEnd();
	for(ChainEndSet::const_iterator it = end.begin(); it != end.end(); ++it)
		writeChainEnd(stream, *it);

	stream << "\n";

	// Serialize processors
	const ProcessorSet &processors = pChain->getProcessors();
	for(ProcessorSet::const_iterator it = processors.begin(); it != processors.end(); ++it)
		writeProcessor(stream, *it);

	stream << "\n";

	// Serialize the connections
	const ConnectionMap &connections = pChain->getConnections();
	for(ConnectionMap::const_iterator it = connections.begin(); it != connections.end(); ++it)
		writeConnection(stream, it->second);

	stream << "</chain>\n";

	return true;
}

bool Serializer::writeChainStart(std::ostream &stream, ChainStart *pStart)
{
	stream << "\t<start";
	stream << " device=\"" << pStart->getDevice()->getName() << "\"";
	stream << " outputID=\"" << pStart->getOutputID() << "\">" << endl;

	writeProperties(stream,  pStart, 1);
	
	stream << "\t</start>" << endl;

	// Index the output
	m_outputIDs[pStart->getOutput()] = m_currentOutputID++;

	return true;
}

bool Serializer::writeChainEnd(std::ostream &stream, ChainEnd *pEnd)
{
	stream << "\t<end>" << endl;
	writeProperties(stream,  pEnd, 1);
	stream << "\t</end>" << endl;

	// Index the input
	m_inputIDs[pEnd->getInput()] = m_currentInputID++;

	return true;
}

bool Serializer::writeProcessor(std::ostream &stream, Processor *pProcessor)
{
	stream << "\t<processor type=\"" << pProcessor->getType() << "\">" << endl;;
	writeProperties(stream,  pProcessor, 1);
	stream << "\t</processor>" << endl;

	// Index the outputs
	const OutputList &outputs = pProcessor->getOutputs();
	for(OutputList::const_iterator it = outputs.begin(); it != outputs.end(); ++it)
		m_outputIDs[*it] = m_currentOutputID++;
	
	// Index the inputs
	const InputList &inputs = pProcessor->getInputs();
	for(InputList::const_iterator it = inputs.begin(); it != inputs.end(); ++it)
		m_inputIDs[*it] = m_currentInputID++;
	
	return true;
}

bool Serializer::writeConnection(std::ostream &stream, Connection *pConnection)
{
	stream << "\t<connection";
	stream << " outputID=\"" << m_outputIDs[pConnection->getOutput()] << "\"";
	stream << " inputID=\"" << m_inputIDs[pConnection->getInput()] << "\">" << endl;
	
	writeProperties(stream,  pConnection, 1);

	stream << "\t</connection>" << endl;

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
