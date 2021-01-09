/***************************************************************
 * Name:      DirectionControler.cpp
 * Purpose:   PID-Controler and keeping communication
 *            Over I2C with CMPS14 (compass)
 *            Over serial with Arduino for motor control
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2021-01-08
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:
 **************************************************************/

#include <sys/ioctl.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <ctime>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <wiringSerial.h>
#include "DirectionControler.h"

DirectionControler::DirectionControler()
{
    // Constructor
    MotorPwLeftValueActual = 0;
    MotorPwRightValueActual = 0;
    MotorPwLeftValueActual = 0;
    MotorPwRightValueActual = 0;
    Bearing = 0;
    Roll = 0;
    Pitch = 0;
}

bool DirectionControler::Start(){
    logDirCtrlFunc.open ("logDirCtrlFunc.log", std::ofstream::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    logDirCtrlFunc << "DirectionControler started: " << dt;

    if ((fdCMPS14 = open(fileName, O_RDWR)) < 0) {
        // Open port for reading and writing
        logDirCtrlFunc << "Failed to open i2c port\r\n";
        return false;
    } else {
        logDirCtrlFunc << "Successfully i2c port opened\r\n";
    }

    if ((fdSerial = serialOpen(serialName, BAUDRATE)) < 0) {
        // Open port for reading and writing
        logDirCtrlFunc << "Failed to open serial port\r\n";
        return false;
    } else {
        logDirCtrlFunc << "Successfully serial port opened\r\n";
    }

    if (ioctl(fdCMPS14, I2C_SLAVE, address) < 0) {
		// Set the port options and set the address of the device we wish to speak to
		logDirCtrlFunc << "Unable to get bus access to talk to slave\r\n";
        return false;
	} else {
		logDirCtrlFunc << "Successfully portoptions & address set of slavedevice\r\n";
	}
	return true;
}

void DirectionControler::Notify() {

    readFromCMPS14();

    /* neu: directionPID */
    /* Steuergröße y als Input für Regler ist numerischer Wert. Wird immer umgerechnet */
    /* in die Differenz aus von PW Left und Right */
    /* todo: Regelstrecke genau definieren - Richtung ist w (Sollwert alias Führungsgröße) */

    /* todo logging of data - sollte leicht sein */
	// todo log all values to a file

    MotorPwLeftValueActual = sendMotorSpeed(0, MotorPwLeftValueSet);
    MotorPwRightValueActual = sendMotorSpeed(1, MotorPwRightValueSet);

	/* serial Commands from Arduino UI */
	/* >> Set Direction */
	/* >> Turn left or right some degree */
	/* >> Turn off - richtiger shutdown, dass alles sauber beendet wird */
}


void DirectionControler::readFromCMPS14(){
    buf[0] = 0; // this is the register we wish to read from

    // Send register to read from
    WriteErrorI2C_bool = false;
	if ((write(fdCMPS14, buf, 1)) != 1) WriteErrorI2C_bool = true;

	// Read back data into buf[]
    ReadErrorI2C_bool = false;
	if (read(fdCMPS14, buf, 6) != 6) {
       ReadErrorI2C_bool = true;
	} else {
		unsigned char highByte = buf[2];
		unsigned char lowByte = buf[3];
		unsigned int result = (highByte <<8) + lowByte;	// Calculate the bearing as a word
		Bearing = (float)result;
		Bearing = Bearing / 10;

		if(buf[4] > 128)	// Format pitch so it shows as positive negative range
			Pitch = buf[4] - 256;
		else
            Pitch = buf[4];

		if(buf[5] > 128)	// Format roll so it shows as positive negative range
			Roll = buf[5] - 256;
		else
            Roll = buf[5];
	}
}


/* 	Only sends if value changes */
// Idea Refactoring
// Make Class for a motor. At construction give the channel number it is connected.
int DirectionControler::sendMotorSpeed(int chanel, int pwvalue){
	char strptr[50];
	if (pwvalue > 125) pwvalue = 125;
	if (pwvalue < -125) pwvalue = -125;
	if (pwvalue != lastSendCmdValueArray[chanel]) {
        lastSendCmdValueArray[chanel] = pwvalue;
        sprintf(strptr, "C%d%02X\r", chanel + 1,lastSendCmdValueArray[chanel]);
        // delete the preceeding "FFFFFF" if value is minus
        // not needed in Ardouino C++
        if (lastSendCmdValueArray[chanel] < 0) {
            strptr[2] = strptr[8];
            strptr[3] = strptr[9];
            strptr[4] = strptr[10];
            strptr[5] = strptr[11];
            strptr[6] = strptr[12];
        }
        // serialPrintf(fdSerial,"test");
        // serialPutchar(fdSerial,'y');
        serialPuts(fdSerial, strptr);
	}
	return (pwvalue);
}

void DirectionControler::Close() {
    serialClose(fdSerial);
    close(fdCMPS14);
    time_t now = time(0);
    char* dt = ctime(&now);
    logDirCtrlFunc << "Stopped: " << dt << endl;
    logDirCtrlFunc.close();
}
