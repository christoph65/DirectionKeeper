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
#include "DirectionControler.h"

class MainLoop: public wxTimer
{
    private:
        wxTextCtrl* txBearing;
        wxTextCtrl* txPitch;
        wxTextCtrl* txRoll;
        wxTextCtrl* logOutput;
        wxTextCtrl* txLeftMotor;
        wxTextCtrl* txRightMotor;
        DirectionControler* directionControler;

    public:
        MainLoop (wxTextCtrl* ilogOutput, wxTextCtrl* itxBearing, wxTextCtrl* itxPitch, wxTextCtrl* itxRoll, wxTextCtrl* itxLeftMotor, wxTextCtrl* itxRightMotor);
        void Notify();
        void start();
        void stop();

        int LeftValue;
        int RightValue;
};
#endif // MAINLOOP_H
