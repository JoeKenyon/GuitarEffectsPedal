# GuitarEffectsPedal




Many guitar effects pedals are very expensive and can sometimes be quite overwhelming to new users. They also tend to only have 1 effect per pedal, multi effects pedals exist but these are often more complex than the former. Guitar effects pedal tend to leave out important information, like the exact value of parameters, e.g. the rate of an effect.




This project helps to assist the development of new and potentially more sophisticated guitar effects pedals by exploring effects processing on micro-controllers. By using the STM32F7-46NG development board and standard audio processing theory, we can solve the issues mentioned above by applying effects to an audio signal and outputting the new signal using the WM8994 audio codec.




This project involves the use of various Signal Processing techniques, like filter design and audio processing to create the audio effects. Some simple electronics was used in the pre/post-processing stage to ensure the Micro-Controller receives/outputs meaningful data, this was done using the WM8994 audio codec. The micro-controllers ADC(Analogue to Digital Converter) is used to receive input and convert from an analogue signal to a digital signal. From there a frame of samples is collected, these samples are then altered to provide the effects and the buffer is then written to the DAC(Digital to Analogue Converter). DMA(Direct Memory Access) is used to automate the writing and reading to the sample buffer.



In summary the project can do the following:
- User can adjust the effects in real time.
- Can perform basic audio loop-back.
- Process audio using various effects such as Delay, Flanger, Vibrato, Distortion, Tremolo and WahWah.
- User can turn multiple effects on at once.
- Exact parameter values are shown on screen.
- Simple System architecture so users can reprogram and add new effects easily.
