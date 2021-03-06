/***************************************************************
 * Name:      MainLoop.cpp
 * Purpose:   Code for the Main Loop of the Direction Keeper
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2021-01-05
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:
 **************************************************************/

#include <wx/msgdlg.h>
#include "MainLoop.h"

//MainLoop::MainLoop()
//{
//    //ctor
//}

//MainLoop::~MainLoop()
//{
//    //dtor
//}

MainLoop::MainLoop(wxTextCtrl* ilogOutput, wxTextCtrl* itxBearing,
                   wxTextCtrl* itxPitch, wxTextCtrl* itxRoll, wxTextCtrl* itxLeftMotor,
                   wxTextCtrl* itxRightMotor, wxTextCtrl* itxBearingDiff,
                   wxTextCtrl* itxKProp, wxTextCtrl* itxKIntegral, wxTextCtrl* itxKDifferential) : wxTimer()
{
    // fill pointers to fields in the GUI
    MainLoop::txBearing = itxBearing;
    MainLoop::txPitch = itxPitch;
    MainLoop::txRoll = itxRoll;
    MainLoop::logOutput = ilogOutput;
    MainLoop::txRightMotor = itxRightMotor;
    MainLoop::txLeftMotor = itxLeftMotor;
    MainLoop::txBearingDiff = itxBearingDiff;
    MainLoop::txKProp = itxKProp;
    MainLoop::txKIntegral = itxKIntegral;
    MainLoop::txKDifferential = itxKDifferential;


    logOutput->Clear();
    *logOutput << "Started DirectionKeeper V0.0 alpha\r";

    LeftValue = 0;
    RightValue = 0;
}


/* Notification from Timer - this is called with every timer interrupt */
void MainLoop::Notify()
{
    char outString[255];

    directionControler->MotorPwLeftValueSet = LeftValue;
    directionControler->MotorPwRightValueSet = RightValue;
    directionControler->Notify();
    LeftValue = directionControler->MotorPwLeftValueActual();
    RightValue = directionControler->MotorPwRightValueActual();


    sprintf(outString, "%d",LeftValue);
    txLeftMotor->Clear();
    *txLeftMotor << outString;
    sprintf(outString, "%d",RightValue);
    txRightMotor->Clear();
    *txRightMotor << outString;

	if (directionControler->WriteErrorI2C_bool) {
		// Send register to read from
		*logOutput << "Error writing to i2c slave\r";
	}

	if (directionControler->ReadErrorI2C_bool) {	// Read back data into buf[]
		*logOutput << "Error unable to read from slave\r";
	} else {
        txBearing->Clear();
        txBearingDiff->Clear();
        txPitch->Clear();
        txRoll->Clear();

		sprintf(outString, "%f",directionControler->Bearing);
		*txBearing << outString;
        sprintf(outString, "%f",directionControler->BearingDiff);
        *txBearingDiff << outString;
        sprintf(outString, "%d",directionControler->Pitch);
		*txPitch << outString;
		sprintf(outString, "%d",directionControler->Roll);
		*txRoll << outString;

        txKProp->Clear();
        txKIntegral->Clear();
        txKDifferential->Clear();
		sprintf(outString, "%f",directionControler->KProp);
		*txKProp << outString;
		sprintf(outString, "%f",directionControler->KIntegral);
		*txKIntegral << outString;
		sprintf(outString, "%f",directionControler->KDifferential);
		*txKDifferential << outString;


	}

	// Button to set direction (set unset) toggle with display
	// Button to change direction
	// evaluate Bearing and calculate change on motorspeed if not in correct direction

}

void MainLoop::Start()
{
    wxTimer::Start(timerInMs); // should be in ms
    // logging on the Gui
    *logOutput << "Successfully timer started\r";
    // std::cout << "Successfully MainLoop started\r";
    directionControler = new DirectionControler();
    if (directionControler->Start(timerInMs))
        *logOutput << "DirectionControler sucessfully started\r";
    else
        *logOutput << "DirectionControler failed to start\r";
}

void MainLoop::Stop()
{
    wxTimer::Stop();
    directionControler->Close();
}

void MainLoop::TogleLaneKeeping()
{
    if (directionControler->EnableDirectionKeeping)
        directionControler->EnableDirectionKeeping = false;
    else
        directionControler->EnableDirectionKeeping = true;
}
