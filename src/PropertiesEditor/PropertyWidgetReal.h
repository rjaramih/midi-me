#ifndef PROPERTIESEDITOR_PROPERTYWIDGETREAL_H
#define PROPERTIESEDITOR_PROPERTYWIDGETREAL_H

// Includes
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"

// Forward declarations
class QDoubleSpinBox;

namespace MidiMe
{
	// Forward declarations
	class RealProperty;

	class PROPERTIESEDITOR_API PropertyWidgetReal : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetReal(RealProperty *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetReal();

		// PropertyWidget functions
		void updateFromProperty();

	private slots:
		void changed(double value);

	private:
		// Member variables
		QDoubleSpinBox *m_pDoubleSpinBox;
	};

	class PROPERTIESEDITOR_API PropertyWidgetCreatorReal : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorReal() : PropertyWidgetCreator("real") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty) { return new PropertyWidgetReal((RealProperty *) pProperty); }
		void destroyWidget(PropertyWidget *pWidget) { delete pWidget; }
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETREAL_H
