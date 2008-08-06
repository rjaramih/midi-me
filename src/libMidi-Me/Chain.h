#ifndef MIDIME_CHAIN_H
#define MIDIME_CHAIN_H

// Includes
#include "global.h"
#include "LastError.h"
#include <set>

// Forward declarations
class RtMidiOut;

namespace MidiMe
{
	// Forward declarations
	class ValueInput;
	typedef std::set<ValueInput *> ValueInputSet;

	class RangeInput;
	typedef std::set<RangeInput *> RangeInputSet;

	class ValueOutput;
	typedef std::set<ValueOutput *> ValueOutputSet;
	
	class RangeOutput;
	typedef std::set<RangeOutput *> RangeOutputSet;

	class Processor;
	typedef std::set<Processor *> ProcessorSet;

	/** A Midi-Me chain contains all items to convert device input signals to midi-out signals.
		You can load and save a chain from/to file, and check if there are non-saved changes.
	*/
	class LIBMIDIME_API Chain: public LastError
	{
	public:
		// Constructors and destructor
		Chain();
		virtual ~Chain();

		// Serialization
		const string &getCurrentFile() const { return m_currentFile; }
		bool isDirty() const { return m_dirty; }
		bool loadSettings(const string &filename);
		bool saveSettings();
		bool saveSettings(const string &filename);
    
	protected:
		// Other functions
		void convertAxis(int axis, int value);

		// Member variables
		bool m_started;

		ValueInputSet m_valueInputs;
		RangeInputSet m_rangeInputs;

		string m_currentFile; //!< The current file, if one is opened or the settings are saved
		bool m_dirty; //!< True if something has changed to this chain since the last load or save
	};
}

#endif // MIDIME_CHAIN_H
