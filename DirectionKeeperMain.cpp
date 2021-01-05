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
#include "MainLoop.h"

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


//(*IdInit(DirectionKeeperFrame)
const long DirectionKeeperFrame::ID_TXBEARING = wxNewId();
const long DirectionKeeperFrame::ID_TXPITCH = wxNewId();
const long DirectionKeeperFrame::ID_LOGOUTPUT = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT1 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT2 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT3 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT4 = wxNewId();
const long DirectionKeeperFrame::ID_TXROLL = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON_LEFT = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON_RIGHT = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON_STOP = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON_FORWARD = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON_BACK = wxNewId();
const long DirectionKeeperFrame::ID_TXLEFTMOTOR = wxNewId();
const long DirectionKeeperFrame::ID_TXRIGHTMOTOR = wxNewId();
const long DirectionKeeperFrame::idMenuQuit = wxNewId();
const long DirectionKeeperFrame::idMenuAbout = wxNewId();
const long DirectionKeeperFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DirectionKeeperFrame,wxFrame)
    //(*EventTable(DirectionKeeperFrame)
    //*)
END_EVENT_TABLE()

// Constructor on create

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
    ButtonLeft = new wxButton(this, ID_BUTTON_LEFT, _("Left"), wxPoint(64,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LEFT"));
    ButtonRight = new wxButton(this, ID_BUTTON_RIGHT, _("Right"), wxPoint(240,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_RIGHT"));
    ButtonStop = new wxButton(this, ID_BUTTON_STOP, _("Stop"), wxPoint(152,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_STOP"));
    ButtonForward = new wxButton(this, ID_BUTTON_FORWARD, _("Forward"), wxPoint(152,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_FORWARD"));
    ButtonBack = new wxButton(this, ID_BUTTON_BACK, _("Back"), wxPoint(152,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_BACK"));
    txLeftMotor = new wxTextCtrl(this, ID_TXLEFTMOTOR, _("Text"), wxPoint(64,192), wxSize(86,32), 0, wxDefaultValidator, _T("ID_TXLEFTMOTOR"));
    txRightMotor = new wxTextCtrl(this, ID_TXRIGHTMOTOR, _("Text"), wxPoint(240,192), wxSize(86,32), wxTE_RIGHT, wxDefaultValidator, _T("ID_TXRIGHTMOTOR"));
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
    Connect(ID_BUTTON_LEFT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnButtonLeftClick1);
    Connect(ID_BUTTON_RIGHT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnButtonRightClick);
    Connect(ID_BUTTON_STOP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnButtonStopClick);
    Connect(ID_BUTTON_FORWARD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnButtonForwardClick);
    Connect(ID_BUTTON_BACK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnButtonBackClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DirectionKeeperFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DirectionKeeperFrame::OnAbout);
    //*)

    mainLoop = new MainLoop (LogOutput, txBearing, txPitch, txRoll, txLeftMotor, txRightMotor);
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

void DirectionKeeperFrame::OnButtonLeftClick1(wxCommandEvent& event)
{
    mainLoop->LeftValue = mainLoop->LeftValue - 1;
    mainLoop->RightValue = mainLoop->RightValue + 1;
}

void DirectionKeeperFrame::OnButtonRightClick(wxCommandEvent& event)
{
    mainLoop->LeftValue = mainLoop->LeftValue + 1;
    mainLoop->RightValue = mainLoop->RightValue - 1;
}

void DirectionKeeperFrame::OnButtonForwardClick(wxCommandEvent& event)
{
    if( mainLoop->RightValue == 0 && mainLoop->LeftValue == 0){
        mainLoop->LeftValue = 0x10 - 3;
        mainLoop->RightValue = 0x10 - 3;
    }

    mainLoop->LeftValue = mainLoop->LeftValue + 3;
    mainLoop->RightValue = mainLoop->RightValue + 3;
}

void DirectionKeeperFrame::OnButtonBackClick(wxCommandEvent& event)
{
    if( mainLoop->RightValue == 0 && mainLoop->LeftValue == 0){
        mainLoop->LeftValue = -4;
        mainLoop->RightValue = -10;
    }

    mainLoop->LeftValue = mainLoop->LeftValue - 3;
    mainLoop->RightValue = mainLoop->RightValue - 3;
}

void DirectionKeeperFrame::OnButtonStopClick(wxCommandEvent& event)
{
    mainLoop->RightValue = 0;
    mainLoop->LeftValue = 0;
}
