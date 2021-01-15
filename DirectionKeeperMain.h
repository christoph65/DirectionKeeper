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
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
#include <wx/timer.h>
#include <wiringSerial.h>
#include "MainLoop.h"
//class wxTextCtrl;

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
        void OnButtonLeftClick(wxCommandEvent& event);
        void OnButtonLeftClick1(wxCommandEvent& event);
        void OnButtonRightClick(wxCommandEvent& event);
        void OnButtonForwardClick(wxCommandEvent& event);
        void OnButtonBackClick(wxCommandEvent& event);
        void OnButtonStopClick(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnTextCtrl1Text1(wxCommandEvent& event);
        void OnbtnKpPlusClick(wxCommandEvent& event);
        void OnbtnKpMinusClick(wxCommandEvent& event);
        void OnbtnKiPlusClick(wxCommandEvent& event);
        void OnbtnKiMinusClick(wxCommandEvent& event);
        void OnbtnKdPlusClick(wxCommandEvent& event);
        void OnbtnKdMinusClick(wxCommandEvent& event);
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
        static const long ID_BUTTON_LEFT;
        static const long ID_BUTTON_RIGHT;
        static const long ID_BUTTON_STOP;
        static const long ID_BUTTON_FORWARD;
        static const long ID_BUTTON_BACK;
        static const long ID_TXLEFTMOTOR;
        static const long ID_TXRIGHTMOTOR;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_BUTTON11;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(DirectionKeeperFrame)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Button4;
        wxButton* Button5;
        wxButton* ButtonBack;
        wxButton* ButtonForward;
        wxButton* ButtonLeft;
        wxButton* ButtonRight;
        wxButton* ButtonStop;
        wxButton* btnKdMinus;
        wxButton* btnKdPlus;
        wxButton* btnKiMinus;
        wxButton* btnKiPlus;
        wxButton* btnKpMinus;
        wxButton* btnKpPlus;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxTextCtrl* LogOutput;
        wxTextCtrl* txBearing;
        wxTextCtrl* txBearingDiff;
        wxTextCtrl* txKDifferential;
        wxTextCtrl* txKIntegral;
        wxTextCtrl* txKProp;
        wxTextCtrl* txLeftMotor;
        wxTextCtrl* txPitch;
        wxTextCtrl* txRightMotor;
        wxTextCtrl* txRoll;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DirectionKeeperMAIN_H
