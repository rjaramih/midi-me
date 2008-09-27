#ifndef MIDIME_SERIALIZER_H
#define MIDIME_SERIALIZER_H

// Includes
#include "global.h"
#include "LastError.h"

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
		bool writeConnection(std::ostream &stream, Output *pOutput);
		bool writeProperties(std::ostream &stream, PropertyCollection *pProperties, unsigned int indentLevel);
		bool writeProperty(std::ostream &stream, Property *pProperty, unsigned int indentLevel);
		void writeTabs(std::ostream &stream, unsigned int num);

		// Member variables
		Chain *m_pChain;
	};
}

#endif // MIDIME_SERIALIZER_H
