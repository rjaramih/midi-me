#ifndef PROPERTIESEDITOR_PROPERTYWIDGETINT_H
#define PROPERTIESEDITOR_PROPERTYWIDGETINT_H

// Includes
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"

// Forward declarations
class QSpinBox;

namespace MidiMe
{
	class PROPERTIESEDITOR_API PropertyWidgetInt : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetInt(Property *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetInt();

		// PropertyWidget functions
		void updateFromProperty();

	private slots:
		void changed(int value);

	private:
		// Member variables
		QSpinBox *m_pSpinBox;
	};

	class PROPERTIESEDITOR_API PropertyWidgetCreatorInt : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorInt() : PropertyWidgetCreator("int") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty) { return new PropertyWidgetInt(pProperty); }
		void destroyWidget(PropertyWidget *pWidget) { delete pWidget; }
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETINT_H
