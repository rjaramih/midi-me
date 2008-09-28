#ifndef MIDIME_SERIALIZER_H
#define MIDIME_SERIALIZER_H

// Includes
#include "global.h"
#include "LastError.h"
#include <map>

namespace MidiMe
{
	// Forward declarations
	class Chain;
	class ChainStart;
	class ChainEnd;
	class Processor;
	class Output;
	class PropertyCollection; class Property;

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
		bool readChain(std::istream &stream, Chain *pChain);

		// Write functions
		bool writeHeader(std::ostream &stream);
		bool writeChain(std::ostream &stream, Chain *pChain);
		bool writeChainStart(std::ostream &stream, ChainStart *pStart);
		bool writeChainEnd(std::ostream &stream, ChainEnd *pEnd);
		bool writeProcessor(std::ostream &stream, Processor *pProcessor);
		bool writeConnections(std::ostream &stream, Chain *pChain);
		bool writeProperties(std::ostream &stream, PropertyCollection *pProperties, unsigned int indentLevel);
		bool writeProperty(std::ostream &stream, Property *pProperty, unsigned int indentLevel);
		void writeTabs(std::ostream &stream, unsigned int num);

		// Member variables
		Chain *m_pChain;

		typedef std::map<ChainStart *, unsigned int> StartIDMap;
		StartIDMap m_startIDs;

		typedef std::map<ChainEnd *, unsigned int> EndIDMap;
		EndIDMap m_endIDs;

		typedef std::map<Processor *, unsigned int> ProcessorIDMap;
		ProcessorIDMap m_processorIDs;
	};
}

#endif // MIDIME_SERIALIZER_H
