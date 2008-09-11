#ifndef PROPERTIESEDITOR_PROPERTYWIDGETFACTORY_H
#define PROPERTIESEDITOR_PROPERTYWIDGETFACTORY_H

// Includes
#include "global.h"
#include <map>

namespace MidiMe
{
	// Forward declarations
	class Property;
	class PropertyWidget;
	class PropertyWidgetCreator;

	class PROPERTIESEDITOR_API PropertyWidgetFactory
	{
	public:
		// Types
		typedef std::map<string, PropertyWidgetCreator *> WidgetCreatorMap;

		// Singleton function
		static PropertyWidgetFactory & getInstance();

		// Creators
		const WidgetCreatorMap &getCreators() const { return m_creators; }
		PropertyWidgetCreator * getCreator(const string &type) const;

		// Other functions
		bool canCreate(const string &type) const;
		PropertyWidget * createWidget(Property *pProperty);
		bool destroyWidget(PropertyWidget *pProperty);

	protected:
		// Protected functions
		void registerCreator(PropertyWidgetCreator *pCreator);
		void unregisterCreator(PropertyWidgetCreator *pCreator);
		void createStandardWidgetCreators();
		
		// Creators register themselves
		friend class PropertyWidgetCreator;

	private:
		PropertyWidgetFactory();
		virtual ~PropertyWidgetFactory();

		// Member variables
		WidgetCreatorMap m_creators;
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETFACTORY_H
