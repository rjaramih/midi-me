#ifndef PROPERTIESEDITOR_PROPERTYWIDGETBOOL_H
#define PROPERTIESEDITOR_PROPERTYWIDGETBOOL_H

// Includes
#include "global.h"
#include "PropertyWidget.h"
#include "PropertyWidgetCreator.h"

// Forward declarations
class QCheckBox;

namespace MidiMe
{
	class PROPERTIESEDITOR_API PropertyWidgetBool : public PropertyWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidgetBool(Property *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidgetBool();

		// PropertyWidget functions
		void updateFromProperty();

	private slots:
		void changed(int state);

	private:
		// Member variables
		QCheckBox *m_pCheckBox;
	};

	class PROPERTIESEDITOR_API PropertyWidgetCreatorBool : public PropertyWidgetCreator
	{
	public:
		PropertyWidgetCreatorBool() : PropertyWidgetCreator("bool") {}

		// PropertyWidgetCreator functions
		PropertyWidget * createWidget(Property *pProperty) { return new PropertyWidgetBool(pProperty); }
		void destroyWidget(PropertyWidget *pWidget) { delete pWidget; }
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGETBOOL_H
