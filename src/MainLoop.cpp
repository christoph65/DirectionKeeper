/***************************************************************
 * Name:      MainLoop.cpp
 * Purpose:   Code for the Main Loop of the Direction Keeper
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2021-01-05
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:
 **************************************************************/

#include <wx/msgdlg.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <wiringSerial.h>
#include "MainLoop.h"

//MainLoop::MainLoop()
//{
//    //ctor
//}

//MainLoop::~MainLoop()
//{
//    //dtor
//}

MainLoop::MainLoop(wxTextCtrl* ilogOutput, wxTextCtrl* itxBearing, wxTextCtrl* itxPitch, wxTextCtrl* itxRoll, wxTextCtrl* itxLeftMotor, wxTextCtrl* itxRightMotor) : wxTimer()
{
    // fill pointers to fields in the GUI
    MainLoop::txBearing = itxBearing;
    MainLoop::txPitch = itxPitch;
    MainLoop::txRoll = itxRoll;
    MainLoop::logOutput = ilogOutput;
    MainLoop::txRightMotor = itxRightMotor;
    MainLoop::txLeftMotor = itxLeftMotor;
    Counter = 0;

    logOutput->Clear();
    *logOutput << "Started DirectionKeeper V0.0 alpha\r";

    LeftValue = 0;
    RightValue = 0;
}


// this is called with every timer interrupt
void MainLoop::Notify()
{
    // Evaluate CMPS14 and show the values in the dialog

    txBearing->Clear();
    txPitch->Clear();
    txRoll->Clear();

    buf[0] = 0; // this is the register we wish to read from

	if ((write(fdCMPS14, buf, 1)) != 1) {
		// Send register to read from
		*logOutput << "Error writing to i2c slave\r";
	}

	if (read(fdCMPS14, buf, 6) != 6) {	// Read back data into buf[]
		*logOutput << "Error unable to read from slave\r";
	} else {
		// printf("Software v: %u \n",buf[0]);
		// printf("Bearing as byte: %u \n",buf[1]);

		char outString[255];
		unsigned char highByte = buf[2];
		unsigned char lowByte = buf[3];
		unsigned int result = (highByte <<8) + lowByte;	// Calculate the bearing as a word
		sprintf(outString, "%u.%u",result / 10, result %10);
		*txBearing << outString;

		if(buf[4] > 128) {	// Format pitch so it shows as positive negative range
			buf[4] = 0 - buf[4];
			sprintf(outString, "-%u",buf[4]);
		} else {
			sprintf(outString, "%u",buf[4]);
		}
		*txPitch << outString;

		if(buf[5] > 128) {	// Format roll so it shows as positive negative range
			buf[5] = 0 - buf[5];
			sprintf(outString, "-%u",buf[5]);
		} else {
			sprintf(outString, "%u",buf[5]);
		}
		*txRoll << outString;
	}

    // serialPrintf(fdSerial,"test");
	// serialPutchar(fdSerial,'y');
    sendMotorSpeed(0,LeftValue,txLeftMotor);
    sendMotorSpeed(1,RightValue,txRightMotor);

	// TODO Serial Values check and then send out the complete command
	// Needs to convert input values to Command

}

void MainLoop::sendMotorSpeed(int chanel, int pwvalue, wxTextCtrl* wxTxDisp){
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
        wxTxDisp->Clear();
        *wxTxDisp << strptr;
        serialPuts(fdSerial, strptr);
	}
}

void MainLoop::start()
{
    wxTimer::Start(10);
    *logOutput << "Successfully timer started\r";

    if ((fdCMPS14 = open(fileName, O_RDWR)) < 0) {
        // Open port for reading and writing
        *logOutput << "Failed to open i2c port\r";
    } else {
        *logOutput << "Successfully i2c port opened\r";
    }

    if ((fdSerial = serialOpen(serialName, BAUDRATE)) < 0) {
        // Open port for reading and writing
        *logOutput << "Failed to open serial port\r";
    } else {
        *logOutput << "Successfully serial port opened\r";
    }

    if (ioctl(fdCMPS14, I2C_SLAVE, address) < 0) {
		// Set the port options and set the address of the device we wish to speak to
		*logOutput << "Unable to get bus access to talk to slave\r";
	} else {
		*logOutput << "Successfully portoptions & address set of slavedevice\r";
	}

}

void MainLoop::stop()
{
    wxTimer::Stop();
    serialClose(fdSerial);
    close(fdCMPS14);
}
