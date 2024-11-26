#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)

wxEND_EVENT_TABLE()

cMain::cMain(): wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(30, 30), wxSize(800, 600))
{
	btn = new wxButton*[mineFieldWidth * mineFieldHeight];
	wxGridSizer* grid = new wxGridSizer(mineFieldWidth, mineFieldHeight, 0, 0);

	mineField = new int[mineFieldWidth * mineFieldHeight];

	wxFont font(14, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int i{ 0 }; i < mineFieldWidth; i++)
	{
		for (int j{ 0 }; j < mineFieldHeight; j++)
		{
			btn[j * mineFieldWidth + i] = new wxButton(this, 10000 + (j * mineFieldWidth + i));
			btn[j * mineFieldWidth + i]->SetFont(font);
			grid->Add(btn[j * mineFieldWidth + i], 1, wxEXPAND | wxALL);
			
			btn[j * mineFieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			mineField[j * mineFieldWidth + i] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();
}
cMain::~cMain()
{
	delete []btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	// Get coordinate of button in array
	int x = (evt.GetId() - 10000) % mineFieldWidth;
	int y = (evt.GetId() - 10000) / mineFieldWidth;

	if (bFirstClicked)
	{
		int mines = (mineFieldWidth * mineFieldHeight) / 4;
		
		while (mines) 
		{
			int rx = rand() % mineFieldWidth;
			int ry = rand() % mineFieldHeight;

			if (mineField[ry * mineFieldHeight + rx] == 0 && rx != x && ry != y)
			{
				mineField[ry * mineFieldHeight + rx] = -1;
				mines--;
			}
		}
		bFirstClicked = false;
	}

	// Disable button, preventing another press
	btn[y * mineFieldHeight + x]->Enable(false);

	if (mineField[y * mineFieldHeight + x] == -1)
	{
		wxMessageBox("Game Over! Lousy Bro");

		// Reset
		bFirstClicked = true;
		for (int i{ 0 }; i < mineFieldWidth; i++)
		{
			for (int j{ 0 }; j < mineFieldHeight; j++)
			{
				mineField[j * mineFieldWidth + i] = 0;
				btn[j * mineFieldWidth + i]->SetLabel("");
				btn[j * mineFieldWidth + i]->Enable(true);
			}
		}
	}
	else
	{
		//Count neighbouring mines
		int mine_count = 0;
		for (int i{ -1 }; i < 2; i++)
		{
			for (int j{ -1 }; j < 2; j++)
			{
				if (x + i >= 0 && x + i < mineFieldWidth && y + j >= 0 && y + j < mineFieldHeight)
				{
					if (mineField[(y + j) * mineFieldWidth + (x + i)] == -1)
					{
						mine_count++;
					}
				}
			}
		}

		// Update button label to show minecount above 0
		if (mine_count > 0) {
			btn[y * mineFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}
