#ifndef PROPERTIESEDITOR_PROPERTYWIDGET_H
#define PROPERTIESEDITOR_PROPERTYWIDGET_H

// Includes
#include "global.h"
#include <Properties/Property.h>
#include <QtGui/QWidget>

// Forward declarations
class QGridLayout;

namespace MidiMe
{
	class PROPERTIESEDITOR_API PropertyWidget : public QWidget
	{
		Q_OBJECT

	public:
		// Constructors and destructor
		PropertyWidget(MidiMe::Property *pProperty, QWidget *parent = NULL);
		virtual ~PropertyWidget();

		// Properties
		const MidiMe::Property * getProperty() const { return m_pProperty; }
		Property * getProperty() { return m_pProperty; }
		void setProperty(Property *pProperty) { m_pProperty = pProperty; }

		// Other functions
		bool isModified() const { return m_modified; }

		/// Update the widget so it reflects the property's value (called after a property change)
		virtual void updateFromProperty() = 0;

	protected:
		// Member variables
		QGridLayout *m_pLayout;
		Property *m_pProperty;
		bool m_modified;
	};
}

#endif // PROPERTIESEDITOR_PROPERTYWIDGET_H
