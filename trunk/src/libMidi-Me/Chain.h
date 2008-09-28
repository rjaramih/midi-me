#ifndef MIDIME_CHAIN_H
#define MIDIME_CHAIN_H

// Includes
#include "global.h"
#include "LastError.h"
#include <Properties/PropertyCollection.h>
#include <set>

// Forward declarations
class RtMidiOut;

namespace MidiMe
{
	// Forward declarations
	class InputDevice;
	class MidiOutput;

	class Input;
	typedef std::map<unsigned int, Input *> InputMap;

	class Output;
	typedef std::map<unsigned int, Output *> OutputMap;

	class ChainStart;
	typedef std::set<ChainStart *> ChainStartSet;

	class ChainEnd;
	typedef std::set<ChainEnd *> ChainEndSet;

	class Processor;
	typedef std::set<Processor *> ProcessorSet;

#if 0
	class Connection;
	typedef std::map<Output *, Connection *> ConnectionMap;
#endif


	/** A Midi-Me chain contains all items to convert device input signals to midi-out signals.
		You can load and save a chain from/to file, and check if there are non-saved changes.
	*/
	class LIBMIDIME_API Chain: public LastError, public PropertyCollection
	{
	public:
		class LIBMIDIME_API Listener
		{
		public:
			virtual ~Listener() {}
			virtual void onStartAdded(ChainStart *pStart) = 0;
			virtual void onStartRemoving(ChainStart *pStart) = 0;
			virtual void onEndAdded(ChainEnd *pEnd) = 0;
			virtual void onEndRemoving(ChainEnd *pEnd) = 0;
			virtual void onProcessorAdded(Processor *pProcessor) = 0;
			virtual void onProcessorRemoving(Processor *pProcessor) = 0;
#if 0
			virtual void onConnectionAdded(Connection *pConnection) = 0;
			virtual void onConnectionRemoving(Connection *pConnection) = 0;
#endif
		};

		// Constructors and destructor
		Chain();
		virtual ~Chain();

		// Chain start
		const ChainStartSet &getChainStart() const;
		size_t numChainStartItems() const;
		ChainStart *addChainStart(InputDevice *pDevice, unsigned int outputID);
		void removeChainStart(ChainStart *pStart);
		void clearChainStart();

		// Chain end
		const ChainEndSet &getChainEnd() const;
		size_t numChainEndItems() const;
		ChainEnd *addChainEnd();
		void removeChainEnd(ChainEnd *pEnd);
		void clearChainEnd();

		// Processors
		const ProcessorSet &getProcessors() const;
		size_t numProcessors() const;
		Processor *addProcessor(const string &type);
		void removeProcessor(Processor *pProcessor);
		void clearProcessors();

#if 0
		// Connections
		const ConnectionMap &getConnections() const;
		size_t numConnections() const;
		Connection *addConnection(Input *pInput, Output *pOutput);
		void removeConnection(Connection *pConnection);
		void clearConnections();
#endif

		// Inputs and outputs
		const InputMap &getAllInputs() const;
		Input *getInput(unsigned int id) const;
		const OutputMap &getAllOutputs() const;
		Output *getOutput(unsigned int id) const;

		// Listeners
		void addListener(Listener *pListener);
		void removeListener(Listener *pListener);

		// Serialization
		const string &getCurrentFile() const { return m_currentFile; }
		bool isDirty() const { return m_dirty; }
		bool load(const string &filename);
		bool save();
		bool save(const string &filename);

		// Other functions
		void clear();
		void step(float seconds);
    
	protected:
		// Protected functions
		void fireStartAdded(ChainStart *pStart);
		void fireStartRemoving(ChainStart *pStart);
		void fireEndAdded(ChainEnd *pEnd);
		void fireEndRemoving(ChainEnd *pEnd);
		void fireProcessorAdded(Processor *pProcessor);
		void fireProcessorRemoving(Processor *pProcessor);
#if 0
		void fireConnectionAdded(Connection *pConnection);
		void fireConnectionRemoving(Connection *pConnection);
#endif

		// Member variables
		bool m_started;

		ChainStartSet m_startItems;
		ChainEndSet m_endItems;
		ProcessorSet m_processors;
#if 0
		ConnectionMap m_connections;
#endif

		InputMap m_inputs;
		OutputMap m_outputs;

		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;

		string m_currentFile; //!< The current file, if one is opened or the settings are saved
		bool m_dirty; //!< True if something has changed to this chain since the last load or save
	};
}

#endif // MIDIME_CHAIN_H
