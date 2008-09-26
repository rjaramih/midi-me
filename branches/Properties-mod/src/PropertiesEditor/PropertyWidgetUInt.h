#ifndef PROPERTIESEDITOR_PROPERTYWIDGETUINT_H
#define PROPERTIESEDITOR_PROPERTYWIDGETUINT_H

// Includes
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"

// Forward declarations
class QSpinBox;

namespace MidiMe
{
	class PROPERTIESEDITOR_API PropertyWidgetUInt : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetUInt(Property *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetUInt();

		// PropertyWidget functions
		void updateFromProperty();

	private slots:
		void changed(int value);

	private:
		// Member variables
		QSpinBox *m_pSpinBox;
	};

	class PROPERTIESEDITOR_API PropertyWidgetCreatorUInt : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorUInt() : PropertyWidgetCreator("uint") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty) { return new PropertyWidgetUInt(pProperty); }
		void destroyWidget(PropertyWidget *pWidget) { delete pWidget; }
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETUINT_H
