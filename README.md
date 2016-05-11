# STM32F10X-GCC-Encoder_Improved
STM32F10X-GCC-Encoder code, improved with doubleclick and long click functionality

Volume encoder functionality was introduced in a previous version of the code, at:

https://github.com/ahmetonat/STM32F10X-GCC-Encoder.git

This code also implements double click and long click function. The code is provided as a full project which will compile with GCC ARM Embedded from:  https://launchpad.net/gcc-arm-embedded 

The two files that should be included in your own code are: "encoder_dc.c" and "encoder_dc.h" 

In encoder_dc.c, the function void init_ENC (void) should be called once for initialization. int EncRead_Guarded(void) should be called every millisecond. It manages read of the keys, debounce using a DSP low pass filter, and the logic necessary for the encoder reading, double click and long press. It returns: UP, DOWN, NOCHANGE, CLICK, LONGPRESS_EVENT, DOUBLECLICK_EVENT. Rotation of the encoder has higher priority over presses. So if the encoder is rotated while pressed, UP or DOWN event is generated. NOCHANGE is returned for no activity.

The logic for the double click and long press are fairly involved so no errors or missed signals occur. The state transition diagram is shown in the file "StateTransitionDiagram.pdf".

The encoder pins are connected to GPIO pins and no hardware quadrature encoder counters are used since the pulse rate is low. After connecting up the encoder, you should define the appropriate pins in the file encoder_dc.h.

More information to be found at the previous version of the code: https://github.com/ahmetonat/STM32F10X-GCC-Encoder.git
