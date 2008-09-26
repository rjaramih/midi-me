#ifndef MIDIME_GENERICPROPERTY_H
#define MIDIME_GENERICPROPERTY_H

// Includes
#include "global.h"
#include "Property.h"
#include "FastDelegate.h"

namespace MidiMe
{
	// Forward declarations

	/** This class is a templated version of a generic property.
		It can be used to easily create a lot of property types.
	*/
	template<class GetType, class SetType = GetType>
	class PROPERTIES_API GenericProperty: public Property
	{
	public:
		// Typedefs
		typedef fastdelegate::FastDelegate0<GetType> GetFunctor;
		typedef fastdelegate::FastDelegate1<SetType> SetFunctor;

	protected:
		// Member variables
		GetFunctor m_getFunctor;
		SetFunctor m_setFunctor;

	public:
		// Constructors and destructor
		GenericProperty(PropertyCollection *pCollection, const string &name, const GetFunctor &getter, const SetFunctor &setter)
			: Property(pCollection, name), m_getFunctor(getter), m_setFunctor(setter) {}
		virtual ~GenericProperty() {}

		// Get/set
		GetType getValue() const { return m_getFunctor(); }
		void setValue(SetType value) { if(value != getValue()) { m_setFunctor(value); fireChanged(); } }
	};
}

#endif // MIDIME_GENERICPROPERTY_H
