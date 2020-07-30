# Practical Compressed sensing project for Contiki NG

### Prerequisites
Setup a Contiki NG development environment as you want. Resources can be found [here](https://github.com/contiki-ng/contiki-ng/wiki). The approach with the docker image and a Linux installation is very recommended. And the "Getting started" guide will be based upon that.

### Getting started
1. Clone this repository (or dowload the code) into the examples folder of the Contiki NG project located on your computer.
2. Attach an IoT device (TelosB) to your computer
3. Open a terminal and start the Contiki terminal by writing

```
$ contiker
```
4. Navigate to the compressed_sensing project by probably writing
```
$ cd ./examples/compressed_sensing/
```
5. Install and run the program on the mote as (if your mote is located at /dev/ttyUSB0, otherwise find where it is located):
```
$ make TARGET=sky MOTES=/dev/ttyUSB0 compressed_sensing_end_to_end.upload login
```

6. The program now runs on the mote and you can see the LOG in the terminal.

### Description
This repository consists of the prototype from the project "Design and Prototype of Energy Concealment
Encryption using Compressive Sensing for IoT".
[Insert link to paper here when done]

The code consists of a prototype of a practical Compresive Sensing (CS) implementation for IoT devices. The code is created as a [Contiki NG](https://github.com/contiki-ng/contiki-ng/wiki) project and is meant for very constrained IoT devices. The code is created with a TelosB as testing device, but can probably be used for other devices aswell. As the the device developed for is a TelosB mote with no floating point unit, the fixed point format is used for all Real number operations.

The code consists of two ways of doing CS. Blockwise CS+EC and just CS+EC. The two public functions which should be used is located in **ec_scheme.h** and is called:

```
void ec_transform(int16_t* signal);
void ec_transform_blockwise(int16_t* signal);
```

### Methodology
The tests made is compared with custom implementations state of art solutions. These are located in the [sister repository](https://github.com/compressedsensing/comcrypt/tree/master)


### Purpose
The purpose of this scheme is to expand network life time by compressing and encrypting a block of data and transmitting it using CS. The blockwise CS+EC scheme consumes less energy per hop than both an approach using only AES on the same block size and transmitting and using both the conventional schemes DCT and DWT followed by AES and transmitting. Reference implementations of these used for comparison is located in the [sister repository](https://github.com/compressedsensing/comcrypt/tree/master)

### List of important files
#### cs_config.h
Configuration stuff. This is where you change the N and M variables of the sensing matrix. The N value being the length of the uncompressed signal, and the M value being the length of the compressed/encrypted signal. 

The **EMAX** value is also located there. This is the maximum energy which can be observed in the signals you are processing. The value is in fixed point format. The current format used is a signed 32-bit 16.16 format. The default value is working for the ECG database from the MIT-BIH Arrhythmia Database.

A **DEBUG** flag is located there along with the **LOG_LEVEL** flag. For testing purposes, while measuring the energy uses during processing **DEBUG** should be set to **0** and **LOG_LEVEL** should be set to **LOG_LEVEL_NONE**.

#### project-conf.h
Project configurations. Should not be changed. CUrrent configuration is using nullnet and the largest CCA threshold possible for consistent energy measurements.

#### fixedpoint.c and fixedpoint.h
Fixed point operations used for calculating the EC variable.

#### random_generator.h
Type definitions for LFSRs and NFSRs used for the random generator.

#### ec_scheme.c and ec_scheme.h
As earlier described it consists of two ways of doing CS on signal, with two exposed functions in the .h-file.

#### compressed_sensing_end_to_end.c
Program written to test the schemes. The program is structured in the following way.

In the top a variable containing a signal of length **N_CS**. This signal is in 16-bit Q4.12-format. This signal simulates a signal aquired from an ADC. This signal is the one which is to be compressed and encrypted.

In the middle a Contiki NG process is. This is the actual action of the test. This section is structured as follows:

1. The signal is scaled down by 2^2, to be able to fit the maximum energy observed in the ECG data within the EC variable.
2. The signal is transformed using a CS method. By default it is the blockwise CS+EC method.
3. The resulting signal is converted to bytes to be sure to transmit it correctly.
4. The signal is transmitted in packets of size 102 bytes (maximum packet size in 802.15.4 when all address space is used).

It should be noted that the transmission can be done either with a delay between packets or just sequentially. It is observed for the TelosB that with more than three packets the packets will not be transmitted correctly doing just sequentially transmission, thus the **SEND_PACKETS_WITH_DELAY** flag should be **1**. This will add the minimum delay between packets to be able to transmit the correctly, thus keeping the energy consumption penalty as low as possible. You might have to increase the etimer_set function call delay to **CLOCK_SECOND/11** from **CLOCK_SECOND/10** for some block sizes, depending on how much you transmit.

### Verification and testing
To be able to verify the schemes a signal reconstruction script has been made in a python notebook located in colab. In the following folder [https://drive.google.com/drive/folders/1vnTTLqZaBvs1BCDa4sogXyUq3D5xcy4m?usp=sharing](https://drive.google.com/drive/folders/1vnTTLqZaBvs1BCDa4sogXyUq3D5xcy4m?usp=sharing) lies both a reconstruction folder and a test signals folder. The reconstruction folder contains scripts to reconstruct a compressed signal (both blockwise and the basic scheme) from its hex format. This is the one outputtet from the the test program (compressed_sensing_end_to_end.c) in DEBUG state 1. A compare signal should be provided aswell to be able to see how well the signal was reconstructed and to calculate a PRD.

To be able test the schemes a test signal should be provided in 16-bit format. In the folder mentioned above there is also a folder called **Test signals**. There lies a script called **Mote_test_data_generator** generating a test signal in different block sizes based on a record in the ECG database. This signal can be copied into the test program (just replace the constant value SIGNAL_LEN with the value N_CS). This signal can also be copied in as the compare signal for the reconstruction script mentioned above.

### Testing the schemes
As mentioned the file **compressed_sensing_end_to_end.c** is written as a test program. This program can in debug state measure the amount of clock cycles used for processing (compressing and encrypting) the signal. It also outputs the processed signal in the terminal for verification purposes.

When measuring the energy consumption. The following setup can be applied:

![Image of the circuit setup to measure the energy during one test](./figures/measurement_curcuit-1.jpg?raw=true "Circuit setup")

A signal should be picked for testing. This can be generated from the **Mote_test_data_generator** script choosing the record of your choice. In the desired block size **N_CS** The signal definition should be copied into the **compressed_sensing_end_to_end.c** file.

The proper **N_CS** and **M** values used should be configured in **cs_config.h**. The **N_CS** value should fit the signal length, and the **M** value should fit the desired compression ratio.

Configure **DEBUG** to **0** and **LOG_LEVEL** should be set to **LOG_LEVEL_NONE** in **cs_config.h**.

Program the mote and start it/restart it. The output of the oscilloscope should look similar to this (of course with variations on the time axis):

![Image of an example measurement](./figures/measurement_example.jpg?raw=true "Energy measurement example").

The beginning spike is part of the booting process of the mote and will be constant no matter the scheme and signal. Measure the voltage from just after "boot-spike".
The flat area which follow is the processing of the signal, and the last spikes are the transmitting of the processed signal. Measure the voltage from just after the booting spike to just after the transmission is done. Use this to calculate the energy consumption.