/***************************************************************
 * Name:      DirectionKeeperMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2020-06-01
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:
 **************************************************************/

#include "DirectionKeeperMain.h"
#include <wx/msgdlg.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <wiringSerial.h>

//(*InternalHeaders(DirectionKeeperFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

// Constructor on create

MainLoop::MainLoop(wxTextCtrl* logOutput, wxTextCtrl* txBearing, wxTextCtrl* txPitch, wxTextCtrl* txRoll) : wxTimer()
{
    // fill pointers to fields in the GUI
    MainLoop::txBearing = txBearing;
    MainLoop::txPitch = txPitch;
    MainLoop::txRoll = txRoll;
    MainLoop::logOutput = logOutput;
    Counter = 0;

    logOutput->Clear();
    *logOutput << "Started DirectionKeeper V0.0 alpha\r";
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

	// TODO Serial Values check and then send out the complete command
	// Needs to convert input values to Command

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


//(*IdInit(DirectionKeeperFrame)
const long DirectionKeeperFrame::ID_TXBEARING = wxNewId();
const long DirectionKeeperFrame::ID_TXPITCH = wxNewId();
const long DirectionKeeperFrame::ID_LOGOUTPUT = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT1 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT2 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT3 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT4 = wxNewId();
const long DirectionKeeperFrame::ID_TXROLL = wxNewId();
const long DirectionKeeperFrame::idMenuQuit = wxNewId();
const long DirectionKeeperFrame::idMenuAbout = wxNewId();
const long DirectionKeeperFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DirectionKeeperFrame,wxFrame)
    //(*EventTable(DirectionKeeperFrame)
    //*)
END_EVENT_TABLE()

DirectionKeeperFrame::DirectionKeeperFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(DirectionKeeperFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("DirectionKeeper"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1041,450));
    SetMaxSize(wxSize(-1,-1));
    txBearing = new wxTextCtrl(this, ID_TXBEARING, _("Text"), wxPoint(136,32), wxSize(120,26), 0, wxDefaultValidator, _T("ID_TXBEARING"));
    txPitch = new wxTextCtrl(this, ID_TXPITCH, _("Text"), wxPoint(136,80), wxSize(120,32), 0, wxDefaultValidator, _T("ID_TXPITCH"));
    LogOutput = new wxTextCtrl(this, ID_LOGOUTPUT, _("Text"), wxPoint(480,56), wxSize(536,376), wxTE_MULTILINE, wxDefaultValidator, _T("ID_LOGOUTPUT"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Log Output"), wxPoint(480,32), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Bearing"), wxPoint(40,40), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Pitch"), wxPoint(40,88), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Roll"), wxPoint(40,136), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    txRoll = new wxTextCtrl(this, ID_TXROLL, _("Text"), wxPoint(136,128), wxSize(120,32), 0, wxDefaultValidator, _T("ID_TXROLL"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_TXBEARING,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&DirectionKeeperFrame::OnTextCtrl1Text);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DirectionKeeperFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DirectionKeeperFrame::OnAbout);
    //*)

    mainLoop = new MainLoop (LogOutput, txBearing, txPitch, txRoll);
    mainLoop->start();

}

DirectionKeeperFrame::~DirectionKeeperFrame()
{
    //(*Destroy(DirectionKeeperFrame)
    //*)
    mainLoop->stop();
}

void DirectionKeeperFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void DirectionKeeperFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void DirectionKeeperFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}
