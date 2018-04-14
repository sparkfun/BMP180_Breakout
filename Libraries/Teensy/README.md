BMP180_Breakout Teensy Library v2.0
========================================

This archive contains an Teensy library and example sketch showing how to use this sensor. The library must be installed onto your computer in order for the example code to work correctly.

Info About Update
-------------------
* The library is depending **Wire.h** and it supports using of pointers now, so BMP180 can be connected to the i2c interface specified by the user. Also, Arduino devices are supported, even those with multiple i2c interfaces. So, same sketches can be run on Arduino and Teensy. (Just wiring is different.)
* For using with depend of **i2c_t3.h** library, browse "utilyt" directory and use these files as /src. This source code is support just Teensy devices.

Review the example sketch for more information about using.

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE.
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE.
* **library.properties** - General library properties for the Teensy package manager.

Documentation
--------------
1. Download "Teensy" directory that in "Libraries" directory.
2. Compress "Teensy" folder with ".zip" extension.
3. On Arduino IDE, use Include Libraries via ZIP method.

There isn't any documentation with details yet for using. The Example Code is like a documentation for now.


License Information
-------------------

This product is _**open source**_!
This library depends on SparkFUN BMP180 library and https://roboticboat.uk/Teensy/Teensy36/BMP180.html page.
