# DSP Review
----

## Basic concept of the physics of sound
I referenced most of information from [this paper](https://jkslp.org/upload/pdf/jkslp-22-2-99.pdf). If you are korean, it's very helpful to understand about what sound is, what is dB scale, what is unit of amplitude, etc.

### Definition of sound
If the sound is explained in view of physics, phenomenon that transfering pressure wave from sound source through the medium. In this situation, sound make sound wave.  

![propagation of sound wave](./img/propagation_of_sound_wave.png)

Medium has a property to return as possible to their places when they are moved by pressure or something. In this process, they also transfer a specific action at some point to other point. Pressure wave occurs when particles in medium vibrate, and this vibration cause a different density of spaces, it's called a compression and rarefraction.  

Speed at which sound is transmitted depends on the type and nature of the medium. Sound which we can hear also depends on temperature, barometric pressure, humidity on atmosphere. Therefore, at average barometric pressure and 15 degree celsius, velocity of sound is about 340.45 m/s.

### Sound wave
At seen above, sound makes wave called sound wave. Each sound wave have a their own different shape and these are largely divided into two gategories, simple, sinwave and complex wave. 

Simplest wave has a sinusoidal from like a monotone. Complex wave is divided into two part again, periodic wave and aperiodic wave. To understand exactly what the differences are, we need to know about frequency, wavelength, amplitude and phase.

#### Frequency and pitch
frequency is that how fast the one pattern is repeatedly observed in unit time. Generally, it's expressed in f, unit is hertz(Hz) or cycle per sec. So 1 Hz is one pattern is observed at 1 second.

Pitch has a word that describes how we feel when we hear a sound at a certain frequency. Higher frequency, higher pitch.

By looking at the scale of frequency, we use octave. This can be expressed as a logarithmic scale with a base of two, and as an octave increase in music, the frequency doubles to be scaled. For example, A note with frequency of 500 Hz goes up one octave to 1,000 Hz.

#### Wavelength and period
Wavelength describes literally a length or distance between same point to point in the wave. It's generally expressed as greek character lambda(&lambda;)

Period which has a concept of time that complete one cycle of vibration or something. It's expressed as a alphabet capital T. These two frequency and wavelength are in inverse proportion relation.

 &fnof; &propto; <sup>1</sup>/<sub>&Tau;</sub>

 #### Amplitude, Sound pressure, Intensity
 In terms of physics, the amplitude can be said to be the amount of particles moving from a stationary state, and in a graphically expressed waveform, the height of the wave is represented.

 The unit of measurement uses decibels (dB), and the amplitude is large, which can be said to be loud. 
 
 In sound, **Amplitude** is the **sound pressure** which means the force of the air molecule pushing the adjacent air molecule by vibration, and the unit of measuremet is Pascal (Pa).

 However, we are more interested in the propagation of sound pressure than the sound pressure itself. The force transmitted along the direction of the wave is called **intensity**, and its unit of measurement is Watt/m<sup>2</sup>.

 Intensity &propto; (sound pressure) <sup>2</sup>

 And the minimum intensity of sound is 10<sup>-16</sup> watt/cm<sup>2</sup>, which is converted to 20 &micro;Pa. This value is *absolute sound threshold*.

 Intensity and amplitude is relevant so if amplitude of wave is large, intensity is also strong. 

 #### Decibels and Sound pressure level
Watt/m<sup>2</sup> and Pa describe an unit of absolute amount of force. On the other hand, There are unit of relative amount of force, it is called as decibel (dB). Decibels are based on logarithmic units, a unit cacultated based on the study of how human auditory organs detect sound intensity. 

The formula for producing this relative energy is as follows:

dB = 10 log<sub>10</sub>(S<sub>1</sub>/S<sub>2</sub>)  *(where, S<sub>1</sub>, S<sub>2</sub> : Intensity)*

We already know about the relationship between intensity and sound pressure. In a graphically expressed sound pressure along time line, the height of the waveform is amplitude. So, we can easily guess the following relationship.

dB = 10 log<sub>10</sub>(S<sub>1</sub>/S<sub>2</sub>) = 10 log<sub>10</sub>(A<sub>1</sub><sup>2</sup>/A<sub>2</sub><sup>2</sup>) = 20 log<sub>10</sub>(A<sub>1</sub>/A<sub>2</sub>)

That's why we use 20 to express when parameter is amplitude. It's from the fact that `Intensity is unit of energy per square measure, and amplitude in sound express unit of pressure which is unit of force per squre measure.`

Decibels depend on reference value positioned into denominator in formula. We generally use *absolute sound threshold* and therefore, the the level of strength calculated based on this value is called the sound pressure level (SPL), and 0 dB SPL means the minimum sound that our ears can hear.

#### Phase
In one cycle of repeated waveforms, the angle of first starting point or the position of any point. Sinusoidal wave represent periodic property, so it is able to be expressed at an angle in relation to a circle.







