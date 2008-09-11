#ifndef MIDIME_PROPERTYCOLLECTION_H
#define MIDIME_PROPERTYCOLLECTION_H

// Includes
#include "global.h"
#include <list>
#include <map>
#include <set>

namespace MidiMe
{
	// Forward declarations
	class Property;

	// Typedefs
	typedef std::list<Property *> PropertyList;
	typedef std::map<string, Property *> PropertyMap;

	/** A PropertyCollection bundles a set of concrete properties. */
	class PROPERTIES_API PropertyCollection
	{
	public:
		/** Implement this class and add it to a property collection to get events when a property is changed.
			@note Because you get a pointer to the property that is changed, you can use the same listener for multiple collections.
		*/
		class PROPERTIES_API Listener
		{
		public:
			virtual ~Listener() {}

			//! This function is called after a property is successfully added to one of the collections this listener is registered to.
			virtual void onPropertyAdded(Property *pProperty) = 0;

			//! This function is called before a property is removed from one of the collections this listener is registered to.
			virtual void onPropertyRemoving(Property *pProperty) = 0;

			//! This function is called when a property (from one of the collections this listeners is registered) is changed.
			virtual void onPropertyChanged(Property *pProperty) = 0;
		};

	protected:
		// Member variables
		PropertyList m_propertiesList; //!< The properties in their correct order
		PropertyMap m_propertiesMap; //!< The properties mapped on their name, for fast searching

	public:
		// Constructors and destructor
		PropertyCollection();
		virtual ~PropertyCollection();

		// Properties
		const PropertyList &getPropertiesList() const { return m_propertiesList; }
		const PropertyMap &getPropertiesMap() const { return m_propertiesMap; }
		bool hasProperties() const { return !m_propertiesList.empty(); }
		Property *getProperty(const string &name) const;
		void setProperty(const string &name, const string &value);

		// Listeners
		void addListener(Listener *pListener) { m_listeners.insert(pListener); }
		void removeListener(Listener *pListener) { m_listeners.erase(pListener); }

		// Other functions
		void clearProperties();

	protected:
		// Protected functions
		void addProperty(Property *pProperty);
		void removeProperty(Property *pProperty);

		// Listeners
		typedef std::set<Listener *> ListenerSet;
		ListenerSet m_listeners;

		// Properties notify their collection on change
		void fireAdded(Property *pProperty);
		void fireRemoving(Property *pProperty);
		void fireChanged(Property *pProperty);
		friend class Property;
	};
}

#endif // MIDIME_PROPERTYCOLLECTION_H
