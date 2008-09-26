#ifndef PROPERTIESEDITOR_PROPERTYWIDGETCOMPOUND_H
#define PROPERTIESEDITOR_PROPERTYWIDGETCOMPOUND_H

// Includes
#include "global.h"
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"

// Forward declarations
class QLabel;

namespace MidiMe
{
	class PROPERTIESEDITOR_API PropertyWidgetCompound : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetCompound(Property *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetCompound();

		// PropertyWidget functions
		void updateFromProperty();

	public slots:
		void changed();

	private:
		// Member variables
		QLabel *m_pLabel;
	};

	class PROPERTIESEDITOR_API PropertyWidgetCreatorCompound : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorCompound() : PropertyWidgetCreator("compound") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty) { return new PropertyWidgetCompound(pProperty); }
		void destroyWidget(PropertyWidget *pWidget) { delete pWidget; }
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETCOMPOUND_H
