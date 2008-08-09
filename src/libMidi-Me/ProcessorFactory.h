#ifndef MIDIME_PROCESSORFACTORY_H
#define MIDIME_PROCESSORFACTORY_H

// Includes
#include "global.h"
#include <map>

namespace MidiMe
{
	// Forward declarations
	class Processor;
	class ProcessorCreator;
	typedef std::map<string, ProcessorCreator *> ProcessorCreatorMap;

	/** Singleton class description */
	class LIBMIDIME_API ProcessorFactory
	{
	private:
		// Private constructors and destructor
		ProcessorFactory();
		ProcessorFactory(const ProcessorFactory &source); //!< Copy constructor, not implemented
		virtual ~ProcessorFactory();

		//! Private assignment operator, not implemented
		ProcessorFactory &operator =(const ProcessorFactory &source);

	public:
		// Singleton function
		static ProcessorFactory &getInstance();

		// Creators
		const ProcessorCreatorMap &getAllCreators() const;
		bool canCreate(const string &type) const;
		ProcessorCreator *getCreator(const string &type) const;

		// Processors
		Processor *createProcessor(const string &type);
		void destroyProcessor(Processor *pProcessor);

	protected:
		// ProcessorCreators register themselves
		void registerCreator(ProcessorCreator *pCreator);
		void unregisterCreator(ProcessorCreator *pCreator);
		friend class ProcessorCreator;

	protected:
		// Member variables
		ProcessorCreatorMap m_creators;
	};
}

#endif // MIDIME_PROCESSORFACTORY_H
