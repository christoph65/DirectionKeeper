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
#include <wx/font.h>
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
const long DirectionKeeperFrame::ID_BUTTON1 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON2 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON3 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON4 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON5 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT5 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT6 = wxNewId();
const long DirectionKeeperFrame::ID_STATICTEXT7 = wxNewId();
const long DirectionKeeperFrame::ID_TEXTCTRL1 = wxNewId();
const long DirectionKeeperFrame::ID_TEXTCTRL2 = wxNewId();
const long DirectionKeeperFrame::ID_TEXTCTRL3 = wxNewId();
const long DirectionKeeperFrame::ID_TEXTCTRL4 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON6 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON7 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON8 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON9 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON10 = wxNewId();
const long DirectionKeeperFrame::ID_BUTTON11 = wxNewId();
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

    Create(parent, wxID_ANY, _("DirectionKeeper"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(744,474));
    SetMaxSize(wxSize(-1,-1));
    txBearing = new wxTextCtrl(this, ID_TXBEARING, _("Text"), wxPoint(64,48), wxSize(120,26), 0, wxDefaultValidator, _T("ID_TXBEARING"));
    txPitch = new wxTextCtrl(this, ID_TXPITCH, _("Text"), wxPoint(264,8), wxSize(56,32), 0, wxDefaultValidator, _T("ID_TXPITCH"));
    LogOutput = new wxTextCtrl(this, ID_LOGOUTPUT, _("Text"), wxPoint(392,32), wxSize(320,280), wxTE_MULTILINE, wxDefaultValidator, _T("ID_LOGOUTPUT"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Operation Status"), wxPoint(392,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Bearing"), wxPoint(64,16), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Pitch"), wxPoint(216,16), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Roll"), wxPoint(216,48), wxSize(40,22), 0, _T("ID_STATICTEXT4"));
    txRoll = new wxTextCtrl(this, ID_TXROLL, _("Text"), wxPoint(264,40), wxSize(56,32), 0, wxDefaultValidator, _T("ID_TXROLL"));
    ButtonLeft = new wxButton(this, ID_BUTTON_LEFT, _("Left"), wxPoint(64,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LEFT"));
    ButtonRight = new wxButton(this, ID_BUTTON_RIGHT, _("Right"), wxPoint(240,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_RIGHT"));
    ButtonStop = new wxButton(this, ID_BUTTON_STOP, _("Stop"), wxPoint(152,232), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_STOP"));
    ButtonForward = new wxButton(this, ID_BUTTON_FORWARD, _("Forward"), wxPoint(152,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_FORWARD"));
    ButtonBack = new wxButton(this, ID_BUTTON_BACK, _("Back"), wxPoint(152,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_BACK"));
    txLeftMotor = new wxTextCtrl(this, ID_TXLEFTMOTOR, _("Text"), wxPoint(64,192), wxSize(86,32), 0, wxDefaultValidator, _T("ID_TXLEFTMOTOR"));
    txRightMotor = new wxTextCtrl(this, ID_TXRIGHTMOTOR, _("Text"), wxPoint(240,192), wxSize(86,32), wxTE_RIGHT, wxDefaultValidator, _T("ID_TXRIGHTMOTOR"));
    Button1 = new wxButton(this, ID_BUTTON1, _("Set Dir"), wxPoint(152,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("R+1"), wxPoint(240,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button3 = new wxButton(this, ID_BUTTON3, _("L+1"), wxPoint(64,104), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(this, ID_BUTTON4, _("R+10"), wxPoint(240,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button5 = new wxButton(this, ID_BUTTON5, _("L+10"), wxPoint(64,136), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("KProp"), wxPoint(32,312), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("KIntegral"), wxPoint(152,312), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("KDifferential"), wxPoint(272,312), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    txBearingDiff = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxPoint(152,136), wxSize(88,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wxFont txBearingDiffFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Piboto Condensed"),wxFONTENCODING_DEFAULT);
    txBearingDiff->SetFont(txBearingDiffFont);
    txKProp = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxPoint(32,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    txKIntegral = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxPoint(152,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    txKDifferential = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxPoint(272,336), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    btnKpPlus = new wxButton(this, ID_BUTTON6, _("+"), wxPoint(32,368), wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    btnKpMinus = new wxButton(this, ID_BUTTON7, _("-"), wxPoint(88,368), wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    btnKiPlus = new wxButton(this, ID_BUTTON8, _("+"), wxPoint(152,368), wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    btnKiMinus = new wxButton(this, ID_BUTTON9, _("-"), wxPoint(208,368), wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    btnKdPlus = new wxButton(this, ID_BUTTON10, _("+"), wxPoint(272,368), wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    btnKdMinus = new wxButton(this, ID_BUTTON11, _("-"), wxPoint(328,368), wxSize(32,32), 0, wxDefaultValidator, _T("ID_BUTTON11"));
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
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnButton1Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnbtnKpPlusClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnbtnKpMinusClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnbtnKiPlusClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnbtnKiMinusClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnbtnKdPlusClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&DirectionKeeperFrame::OnbtnKdMinusClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DirectionKeeperFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&DirectionKeeperFrame::OnAbout);
    //*)

    mainLoop = new MainLoop (LogOutput, txBearing, txPitch, txRoll, txLeftMotor, txRightMotor, txBearingDiff,
                             txKProp, txKIntegral, txKDifferential);
    mainLoop->Start();

}

DirectionKeeperFrame::~DirectionKeeperFrame()
{
    //(*Destroy(DirectionKeeperFrame)
    //*)
    mainLoop->Stop();
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

void DirectionKeeperFrame::OnButton1Click(wxCommandEvent& event)
{
    mainLoop->TogleLaneKeeping();
}

void DirectionKeeperFrame::OnbtnKpPlusClick(wxCommandEvent& event)
{
    mainLoop->directionControler->KProp += 0.1;
}

void DirectionKeeperFrame::OnbtnKpMinusClick(wxCommandEvent& event)
{
    mainLoop->directionControler->KProp -= 0.1;
}

void DirectionKeeperFrame::OnbtnKiPlusClick(wxCommandEvent& event)
{
    mainLoop->directionControler->KIntegral += 0.001;
}

void DirectionKeeperFrame::OnbtnKiMinusClick(wxCommandEvent& event)
{
    mainLoop->directionControler->KIntegral -= 0.001;
}

void DirectionKeeperFrame::OnbtnKdPlusClick(wxCommandEvent& event)
{
    mainLoop->directionControler->KDifferential += 0.1;
}

void DirectionKeeperFrame::OnbtnKdMinusClick(wxCommandEvent& event)
{
    mainLoop->directionControler->KDifferential -= 0.1;
}
