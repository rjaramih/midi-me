#ifndef MIDIME_PROPERTY_H
#define MIDIME_PROPERTY_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarations
	class PropertyCollection;

	/** A property is an abstract way of exposing a setting. Most properties will be part of a collection,
		so the listeners of the property collection receive events when the property changes.
		You can also attach one listener to a certain property.
	*/
	class PROPERTIES_API Property
	{
	public:
		/** If you want to receive change events from one certain property, you can derive from this class
			and set the listener on the property you want to monitor.
			@note To minimize the overhead, we only allow one listener for a certain property.
			You can add multiple listeners to a property collection though.
		*/
		class PROPERTIES_API Listener
		{
		public:
			virtual ~Listener() {}

			//! This function is called when the attached property is changed
			virtual void onPropertyChanged(Property *pProperty) = 0;
		};

		// Constructors and destructor
		Property(const string &name);
		virtual ~Property();

		// Info
		virtual const string &getType() const = 0;
		const string &getName() const { return m_name; }

		// Collection
		PropertyCollection *getCollection() const { return m_pCollection; }
		void setCollection(PropertyCollection *pCollection) { m_pCollection = pCollection; }

		// Listener
		Listener *getListener() const { return m_pListener; }
		void setListener(Listener *pListener) { m_pListener = pListener; }
		void clearListener() { m_pListener = 0; }

		// Serialization
		virtual string toString() const = 0;
		virtual void fromString(const string &value) = 0;

		//! Implementations of Property should fire this when the property is changed
		virtual void fireChanged();

	protected:
		// Member variables
		string m_name; //!< A per-collection unique name for this property
		PropertyCollection *m_pCollection; //!< The collection this property belongs to
		Listener *m_pListener; //!< The optional listener attached to this property
	};
}

#endif // MIDIME_PROPERTY_H
