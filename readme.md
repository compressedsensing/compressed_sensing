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

The code consists of a prototype of a practical Compresive Sensing (CS) implementation for IoT devices. The code is created as a [Contiki NG](https://github.com/contiki-ng/contiki-ng/wiki) project and is meant for very constrained IoT devices. The code is created with a TelosB as testing device, but can probably be used for other devices aswell.

The code consists of two ways of doing CS. Blockwise CS+EC and just CS+EC. The two public functions which should be used is located in **ec_scheme.h** and is called:

```
void ec_transform(int16_t* signal);
void ec_transform_blockwise(int16_t* signal);
```

### Methodology
The tests made is compared with custom implementations state of art solutions. These are located in the [sister repository](https://github.com/compressedsensing/comcrypt/tree/master)


### Purpose
The purpose of this scheme is to expand network life time by compressing and encrypting a block of data and transmitting it using CS. The blockwise CS+EC scheme consumes less energy than both an approach using only AES on the same block size and transmitting and using both the conventional schemes DCT and DWT followed by AES and transmitting. Reference implementations of these used for comparison is located in the [sister repository](https://github.com/compressedsensing/comcrypt/tree/master)

### Testing the schemes
