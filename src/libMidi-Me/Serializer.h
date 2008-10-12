#ifndef MIDIME_SERIALIZER_H
#define MIDIME_SERIALIZER_H

// Includes
#include "global.h"
#include "LastError.h"
#include <vector>
#include <map>

// Forward declarations
class XmlElement;

namespace MidiMe
{
	// Forward declarations
	class Chain;
	class ChainStart;
	class ChainEnd;
	class Processor;
	class Input; class Output;
	class Connection;
	class PropertyCollection; class Property; class CompoundProperty;

	/** This class is used to serialize Midi-Me converter settings. */
	class LIBMIDIME_API Serializer: public LastError
	{
	public:
		// Constructors and destructor
		Serializer();
		virtual ~Serializer();

		// Other functions
		bool load(Chain *pChain, const string &filename);
		bool save(Chain *pChain, const string &filename);

	protected:
		// Read functions
		bool readChain(XmlElement *pChainEl);
		bool readChainStart(XmlElement *pElement);
		bool readChainEnd(XmlElement *pElement);
		bool readProcessor(XmlElement *pElement);
		bool readConnection(XmlElement *pElement);
		void readProperties(XmlElement *pElement, PropertyCollection *pProperties);
		void readCompoundProperty(XmlElement *pElement, CompoundProperty *pProperty);

		// Write functions
		bool writeHeader(std::ostream &stream);
		bool writeChain(std::ostream &stream, Chain *pChain);
		bool writeChainStart(std::ostream &stream, ChainStart *pStart);
		bool writeChainEnd(std::ostream &stream, ChainEnd *pEnd);
		bool writeProcessor(std::ostream &stream, Processor *pProcessor);
		bool writeConnection(std::ostream &stream, Connection *pConnection);
		bool writeProperties(std::ostream &stream, PropertyCollection *pProperties, unsigned int indentLevel);
		bool writeProperty(std::ostream &stream, Property *pProperty, unsigned int indentLevel);
		void writeTabs(std::ostream &stream, unsigned int num);

		// Member variables
		Chain *m_pChain;

		typedef std::vector<Output *> OutputVector;
		OutputVector m_outputs;

		typedef std::vector<Input *> InputVector;
		InputVector m_inputs;

		typedef std::map<Output *, unsigned int> OutputIDMap;
		OutputIDMap m_outputIDs;
		unsigned int m_currentOutputID;

		typedef std::map<Input *, unsigned int> InputIDMap;
		InputIDMap m_inputIDs;
		unsigned int m_currentInputID;
	};
}

#endif // MIDIME_SERIALIZER_H
