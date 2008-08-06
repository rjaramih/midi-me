#ifndef MIDIME_INPUTDEVICEWIDGET_H
#define MIDIME_INPUTDEVICEWIDGET_H

// Includes
#include "global.h"
#include <QtGui/QGraphicsView>
#include <libMidi-Me/DeviceManager.h> // TEMP
#include <libMidi-Me/InputDevice.h>
#include <map>

// Forward declarations
class QGraphicsScene;

namespace MidiMe
{
	// Forward declarations
	class InputDevice;
	class ValueOutput; class RangeOutput;

	/** This widget displays the state of an input device. */
	class InputDeviceWidget: public QGraphicsView, protected InputDevice::Listener, protected DeviceManager::Listener
	{
	public:
		// Constructors and destructor
		InputDeviceWidget(InputDevice *pDevice, QWidget *pParent = 0);
		virtual ~InputDeviceWidget();

		// Other functions
		void update();
    
	protected:
		// Events
		void resizeEvent(QResizeEvent *pEvent);

		// InputDevice::Listener functions
		void onValueStart(ValueOutput *pOutput);
		void onValueStop(ValueOutput *pOutput);
		void onValueChanged(RangeOutput *pOutput, int value);

		// TEMP: DeviceManager::Listener functions
		void onDeviceAdded(InputDevice *pDevice);
		void onDeviceRemoving(InputDevice *pDevice);

		// Member variables
		InputDevice *m_pDevice;
		QGraphicsScene *m_pScene;

		typedef std::map<ValueOutput *, QGraphicsEllipseItem *> ValueItemMap;
		ValueItemMap m_valueItems;

		typedef std::map<RangeOutput *, QGraphicsRectItem *> RangeItemMap;
		RangeItemMap m_rangeItems;
	};
}

#endif // MIDIME_INPUTDEVICEWIDGET_H
