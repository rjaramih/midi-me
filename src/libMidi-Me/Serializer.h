#ifndef MIDIME_SERIALIZER_H
#define MIDIME_SERIALIZER_H

// Includes
#include "global.h"
#include "LastError.h"

namespace MidiMe
{
	// Forward declarations
	class Chain;
	class Processor;
	class Output;

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
		bool writeProcessor(std::ostream &stream, Processor *pProcessor);
		bool writeConnection(std::ostream &stream, Output *pOutput);

		// Member variables
		Chain *m_pChain;
	};
}

#endif // MIDIME_SERIALIZER_H
