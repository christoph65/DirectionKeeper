/***************************************************************
 * Name:      DirectionKeeperMain.h
 * Purpose:   Defines Application Frame
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2020-06-01
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:   MIT License
 **************************************************************/

#ifndef DirectionKeeperMAIN_H
#define DirectionKeeperMAIN_H

//(*Headers(DirectionKeeperFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
#include <wx/timer.h>
#include <wiringSerial.h>
//class wxTextCtrl;

class MainLoop : public wxTimer
{
    private:
        wxTextCtrl* txBearing;
        wxTextCtrl* txPitch;
        wxTextCtrl* txRoll;
        wxTextCtrl* logOutput;
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
        int8_t lastSendCmdValueArray[6];


    public:
        MainLoop (wxTextCtrl* logOutput, wxTextCtrl* txBearing, wxTextCtrl* txPitch, wxTextCtrl* txRoll);
        void Notify();
        void start();
        void stop();
};


class DirectionKeeperFrame: public wxFrame
{
    public:

        DirectionKeeperFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~DirectionKeeperFrame();

    private:

        MainLoop* mainLoop;

        //(*Handlers(DirectionKeeperFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        //*)

        //(*Identifiers(DirectionKeeperFrame)
        static const long ID_TXBEARING;
        static const long ID_TXPITCH;
        static const long ID_LOGOUTPUT;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_TXROLL;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DirectionKeeperFrame)
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStatusBar* StatusBar1;
        wxTextCtrl* LogOutput;
        wxTextCtrl* txBearing;
        wxTextCtrl* txPitch;
        wxTextCtrl* txRoll;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DirectionKeeperMAIN_H
