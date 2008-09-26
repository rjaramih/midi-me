#ifndef PROPERTIESEDITOR_PROPERTYWIDGETCREATOR_H
#define PROPERTIESEDITOR_PROPERTYWIDGETCREATOR_H

// Includes
#include "global.h"

namespace MidiMe
{
	// Forward declarattions
	class Property;
	class PropertyWidget;

	class PROPERTIESEDITOR_API PropertyWidgetCreator
	{
	public:
		// Constructors and destructor
		PropertyWidgetCreator(const string &type);
		virtual ~PropertyWidgetCreator();

		// Informtation
		const string & getType() const { return m_type; }

		// Abstract functions
		virtual PropertyWidget * createWidget(Property *pProperty) = 0;
		virtual void destroyWidget(PropertyWidget *pWidget) = 0;

	private:
		// Member variables
		string m_type;
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETCREATOR_H
