# Midi-Me #

Midi-Me can convert device input signals, such as joystick axes/buttons, racing steer pedals or Wii controller movement to midi-out signals.

You can use this application to control any midi device or application (through a virtual midi device such as [LoopBe](http://www.nerds.de/en/download.html) or [Maple Virtual Midi Cable](http://www.hurchalla.com/Maple_driver.html)) through non-midi-capable devices (in my case, mostly the pedals of my old usb racing steer).

This application is similar to other joystick-to-midi applications (such as [MIDIDriver](http://www.codevis.com/proj_midi.html) and [VMIDIJoy](http://vellocet.com/software/VMIDIJoY.html)), but I created a new one because I didn't particularly like the other ones and they didn't provide the one feature I needed: cutting an axis in arbitrary slices and map different control signals and value ranges to it (I needed that because the null-point of my steering wheel pedals was at -256, other applications could only slice the axis in two, with 0 being the null-point)


## Features ##

Some of the key features of the application are:
  * Input device plugins: support for new types of input devices can be added easily
  * A controller chain converts the input signals to midi-out signals, through a range of easy-to-use controller items such as axis slices, logical operators, ... Plugins can add new controller items

I only use cross-platform libraries such as [OIS](http://www.wreckedgames.com/forum/index.php?board=6.0), [QT](http://trolltech.com/products/qt/) and [RtMidi](http://www.music.mcgill.ca/~gary/rtmidi/) so I can easily support as many platforms as possible (though I personally only have windows and linux machines). Some of the plugins can off course be platform-specific