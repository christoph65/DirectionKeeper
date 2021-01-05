/***************************************************************
 * Name:      MainLoop.h
 * Purpose:   Code for the Main Loop of the Direction Keeper
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2021-01-05
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:
 **************************************************************/

#ifndef MAINLOOP_H
#define MAINLOOP_H
//(*Headers(DirectionKeeperFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
#include <wx/timer.h>

class MainLoop: public wxTimer
{
    private:
        wxTextCtrl* txBearing;
        wxTextCtrl* txPitch;
        wxTextCtrl* txRoll;
        wxTextCtrl* logOutput;
        wxTextCtrl* txLeftMotor;
        wxTextCtrl* txRightMotor;
        int Counter;

        // for cmps 14
        int fdCMPS14;	// File descrition
        int fdSerial;
        // For older raspberry pi modules use "/dev/i2c-0" instead of "/dev/i2c-1" for the i2c port
        char *fileName = "/dev/i2c-1";	// Name of the port we will be using
        char *serialName = "/dev/ttyUSB0";	// Name of the port we will be using
        const int BAUDRATE = 38400;
        int  address = 0x60;	// Address of CMPS11 shifted right one bit
        unsigned char buf[10];	// Buffer for data being read/ written on the i2c bus
        int lastSendCmdValueArray[6];
        void sendMotorSpeed(int chanel, int pwvalue, wxTextCtrl* wxTxDisp);


    public:
        MainLoop (wxTextCtrl* ilogOutput, wxTextCtrl* itxBearing, wxTextCtrl* itxPitch, wxTextCtrl* itxRoll, wxTextCtrl* itxLeftMotor, wxTextCtrl* itxRightMotor);
        void Notify();
        void start();
        void stop();

        int LeftValue;
        int RightValue;
};
#endif // MAINLOOP_H
