/***************************************************************
 * Name:      DirectionControler.cpp
 * Purpose:   PID-Controler for keeping direction
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2021-01-08
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:
 **************************************************************/
#ifndef DIRECTIONCONTROLER_H
#define DIRECTIONCONTROLER_H

#include <fstream>
using namespace std;

class DirectionControler
{
    public:
        DirectionControler();
        void Notify();
        bool Start();
        void Close();
        int MotorPwLeftValueActual;
        int MotorPwRightValueActual;
        int MotorPwLeftValueSet;
        int MotorPwRightValueSet;
        float Bearing;
        int Roll;
        int Pitch;
        bool ReadErrorI2C_bool;
        bool WriteErrorI2C_bool;

    protected:

    private:
        // for cmps 14
        int fdCMPS14;	// File descrition
        int fdSerial;
        // For older raspberry pi modules use "/dev/i2c-0" instead of "/dev/i2c-1" for the i2c port
        char *fileName = "/dev/i2c-1";	// Name of the port we will be using
        char *serialName = "/dev/ttyUSB0";	// Name of the port we will be using
        const int BAUDRATE = 38400;
        int  address = 0x60;	// Address of CMPS11 shifted right one bit
        unsigned char buf[10];	// Buffer for data being read/ written on the i2c bus
        // for PW Control
        int lastSendCmdValueArray[6];
        int sendMotorSpeed(int chanel, int pwvalue);
        void readFromCMPS14();
        // for logging
        ofstream logDirCtrlFunc;
};

#endif // DIRECTIONCONTROLER_H
