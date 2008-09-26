#ifndef MIDIME_PROPERTIES_H
#define MIDIME_PROPERTIES_H

// Includes
#include "global.h"
#include <Properties/GenericProperty.h>

namespace MidiMe
{
	// Forward declarations
	class Input;

	/** A property of this type holds a midi-me value.
		This is like a real value property, but you can attach the property
		to an input and take its current value as property (with the setCurrentValue function)
	*/
	class LIBMIDIME_API InputValueProperty: public GenericProperty<real>
	{
	public:
		// Constructors and destructor
		InputValueProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter, Input *pInput);
		virtual ~InputValueProperty();

		// GenericProperty<real> functions
		static string type;
		const string &getType() const { return type; }

		string toString() const;
		void fromString(const string &value);

		// Associated input
		Input *getInput() const { return m_pInput; }
		void setFromInput();
    
	protected:
		// Member variables
		Input *m_pInput;
	};
}

#endif // MIDIME_PROPERTIES_H
