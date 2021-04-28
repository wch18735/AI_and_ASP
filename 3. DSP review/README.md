# DSP review

You can intuitively get an idea of what fourier transform is.
<p align="center"><img src="./img/AI_speech_3주차-02.jpg" width="500"></img></p>

## Fourier Transform
Fourier transform changes a view for signals. We are familier with seeing x-axis as continuous time. The normal graph changes by fourier transform to have x-axis as frequency. These concept is applied to not only continuous time domain, but also to discrete time domain and just discrete slots. These are named to `CTFT (Continuous-Time Fourier Transform)`, `DTFT (Discrete-Time Fourier Transform)`, `DFT (Discrete Fourier Transform)`. More details about systems equation analysis are in Signal ans System lectures. 
<br></br>

## CTFT and DTFT
In signals and system, you've learned about correlation as follows:  
<p align="center"><img src="./img/correlation.png" width="120"></img></p>
Basis signal of continuous time signal with fundamental frequency f<sub>0</sub> is as follows:
<p align="center"><img src="./img/basis_signal.png" width="50"></img></p>
As fourier transform is represented to correlation between x(t) and basis signal, transformed X(f) and verse x(t) are as follows:
<p align="center"><img src="./img/fourier_transform.png" width="200"></img></p>
<p align="center"><img src="./img/ft_verse.png" width="200"></img></p>

These are quite easily able to understand when you apply the x(t) to frequency domain. It would be explained that "If you want to get a signal at very right t<sub>0</sub> time, you need to sum all the frequencies over f-domain and coefficient of them individually". This interperetation is applied to X(f) in exactly same way.  
Then what is DTFT? See a figure below.  
![discrete](./img/conversion_discrete.JPG)  
Sampling is multiplication with signals and impulse train with sampling period T. And multiplication on time domain is transformed to convolution on frequency domain. This concepts are explained following figure.  
![discrete](./img/conversion_discrete_full.jpg)  
There are helpful notes to make you understand more clearly in the `pdf folder`.

## DFT Notes (N-Point)
Following pages are personal notes. If you find something wrong, please make an issue in github. Conclusion of DFT is that it has to take N positive integer point which is resolution of frequency. Then selected points get a convolution with basic signal represented with N and k. In the pdf, `k` means resolution of frequency. For example, if our sampling frequency is 8,000Hz and we take 100 point DFT, this frequency resolution of DFT is going to be 80Hz.  
  
<p align="center"><img src="./img/AI_speech_3주차-01.jpg"></img></p>
<p align="center"><img src="./img/AI_speech_3주차-03.jpg"></img></p>
<p align="center"><img src="./img/AI_speech_3주차-04.jpg"></img></p>
<p align="center"><img src="./img/AI_speech_3주차-05.jpg"></img></p>
<p align="center"><img src="./img/AI_speech_3주차-06.jpg"></img></p>
<p align="center"><img src="./img/AI_speech_3주차-07.jpg"></img></p>
<p align="center"><img src="./img/AI_speech_3주차-08.jpg"></img></p>

## Short-Time Fourier Transform



## Reference
- https://web.stanford.edu/class/ee179/lectures/notes11.pdf
- https://lmb.informatik.uni-freiburg.de/lectures/old_lmb/bildverarbeitung/Exercise07/GibbsPhenomena.pdf