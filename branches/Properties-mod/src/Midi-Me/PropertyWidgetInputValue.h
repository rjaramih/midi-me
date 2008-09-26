#ifndef MIDIME_PROPERTYWIDGETREAL_H
#define MIDIME_PROPERTYWIDGETREAL_H

// Includes
#include <PropertiesEditor/PropertyWidget.h>
#include <PropertiesEditor/PropertyWidgetCreator.h>

// Forward declarations
class QDoubleSpinBox;
class QToolButton;

namespace MidiMe
{
	// Forward declarations
	class InputValueProperty;

	class PropertyWidgetInputValue : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetInputValue(InputValueProperty *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetInputValue();

		// PropertyWidget functions
		void updateFromProperty();

	public slots:
		void setFromInput();

	private slots:
		void changed(double value);

	private:
		// Member variables
		QDoubleSpinBox *m_pDoubleSpinBox;
		QToolButton *m_pSetFromInputButton;
	};

	class PropertyWidgetCreatorInputValue : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorInputValue() : PropertyWidgetCreator("InputValue") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty);
		void destroyWidget(PropertyWidget *pWidget);
	};
}

#endif // MIDIME_PROPERTYWIDGETREAL_H
