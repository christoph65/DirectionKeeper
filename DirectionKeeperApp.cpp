/***************************************************************
 * Name:      DirectionKeeperApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Christoph Kunz (christoph.kunz65@gmail.com)
 * Created:   2020-06-01
 * Copyright: Christoph Kunz (www.chrisfishing.de)
 * License:   MIT License
 **************************************************************/

#include "DirectionKeeperApp.h"

//(*AppHeaders
#include "DirectionKeeperMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DirectionKeeperApp);

bool DirectionKeeperApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	DirectionKeeperFrame* Frame = new DirectionKeeperFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
