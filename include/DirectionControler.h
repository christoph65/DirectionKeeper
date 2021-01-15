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
        /* Methods */
        DirectionControler(); // constructor
        void Notify(); // continously call from a timer with constant differences
        bool Start(int timerStepInMs); // Call at the start
        void Close(); // Call at the end

        /* control Variables input */
        int MotorPwLeftValueSet; // What the user wants
        int MotorPwRightValueSet;
        bool EnableDirectionKeeping;

        /* Todo: get from UI */
        float KProp;
        float KIntegral;
        float KDifferential;

        /* Status Feedback output */
        int MotorPwLeftValueActual(); // What he gets - should be Refactored to a function readonly
        int MotorPwRightValueActual();
        bool ReadErrorI2C_bool;
        bool WriteErrorI2C_bool;
           /* temporary for testing - todo */
        float BearingDiff;

        /* public Data */
        // Todo Refactoring: make private an make getter method
        float Bearing;
        int Roll;
        int Pitch;

    protected:

    private:
        /** for cmps 14 */
        int fdCMPS14;	// File descrition
        void readFromCMPS14();
        int fdSerial;
        char *fileName = "/dev/i2c-1";	// Name of the port we will be using
                    // For older raspberry pi modules use "/dev/i2c-0" instead of "/dev/i2c-1" for the i2c port
        int  address = 0x60;	// Address of CMPS11 shifted right one bit
        unsigned char buf[10];	// Buffer for data being read/ written on the i2c bus

        /** for PW Control */
        char *serialName = "/dev/ttyUSB0";	// Name of the port we will be using
        const int BAUDRATE = 38400;
        int lastSendCmdValueArray[6]; // to detect if command was already send or should be send again
        int sendMotorSpeed(int chanel, int pwvalue);

        /** for Direction keeping */
        void controlDirectionPID();
        int motorPwLeftValueActual;
        int motorPwRightValueActual;
        bool directionKeepingAlreadyActive;
        int motorPwLeftValueActualStoredAtActivation;
        int motorPwRightValueActualStoredAtActivation;
        float bearingStoredAtActivation;
        float diffSum;
        float diffSumLast;
        float timeStepInMs;
        float pwChange;

        /** for logging */
        void logData ();
        ofstream logDirCtrlFunc;
        ofstream logDirCtrlData;
};

#endif // DIRECTIONCONTROLER_H
