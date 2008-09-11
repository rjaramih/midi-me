#ifndef PROPERTYWIDGETS_PROPERTYWIDGETSTRING_H
#define PROPERTYWIDGETS_PROPERTYWIDGETSTRING_H

// Includes
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"

// Forward declarations
class QLineEdit;

namespace MidiMe
{
	class PROPERTIESEDITOR_API PropertyWidgetString : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetString(Property *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetString();

		// PropertyWidget functions
		void updateFromProperty();

	private slots:
		void changed();

	private:
		// Member variables
		QLineEdit *m_pLineEdit;
		QString m_prevValue;
	};

	class PROPERTIESEDITOR_API PropertyWidgetCreatorString : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorString() : PropertyWidgetCreator("string") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty) { return new PropertyWidgetString(pProperty); }
		void destroyWidget(PropertyWidget *pWidget) { delete pWidget; }
	};
}

#endif // PROPERTYWIDGETS_PROPERTYWIDGETSTRING_H
