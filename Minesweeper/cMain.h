#pragma once
#include "wx/wx.h"
class cMain: public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int mineFieldWidth= 10;
	int mineFieldHeight = 10;
	wxButton** btn;

	int* mineField = nullptr;
	bool bFirstClicked = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

