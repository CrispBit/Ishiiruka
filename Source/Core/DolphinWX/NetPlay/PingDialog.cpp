// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <wx/button.h>
#include <wx/event.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>

#include "Common/StringUtil.h"
#include "DolphinWX/NetPlay/PingDialog.h"
#include "DolphinWX/NetPlay/NetWindow.h"

PingDialog::PingDialog(wxWindow* parent, NetPlayServer* server, std::vector<const Player*> players, const std::string& target_identifier)
	: wxDialog(parent, wxID_ANY, _("Ping Test")), m_netplay_server(server)
{
	const int space5 = FromDIP(5);

	wxBoxSizer* const main_sizer = new wxBoxSizer(wxVERTICAL);

	main_sizer->AddSpacer(space5);
	main_sizer->Add(new wxStaticText(this, wxID_ANY,
		wxString::Format(_("Testing Ping to:\n%s"), target_identifier),
		wxDefaultPosition, wxDefaultSize,
		wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE),
		0, wxEXPAND | wxLEFT | wxRIGHT, space5);

	for (const Player* player : players)
	{
		wxStaticBoxSizer* const player_szr = new wxStaticBoxSizer(
			wxVERTICAL, this, player->name + " (p" + std::to_string(player->pid) + ")");

		m_ping_labels[player->pid] =
			new wxStaticText(player_szr->GetStaticBox(), wxID_ANY, _("Determining..."));

		player_szr->AddSpacer(space5);
		player_szr->Add(m_ping_labels[player->pid], 0, wxALIGN_CENTER_HORIZONTAL | wxLEFT | wxRIGHT,
			space5);
		player_szr->AddSpacer(space5);
		player_szr->SetMinSize(FromDIP(wxSize(250, -1)));

		main_sizer->AddSpacer(space5);
		main_sizer->Add(player_szr, 0, wxEXPAND | wxLEFT | wxRIGHT, space5);
	}

	main_sizer->AddSpacer(space5);
	main_sizer->Add(CreateStdDialogButtonSizer(wxCLOSE), 0, wxEXPAND | wxLEFT | wxRIGHT, space5);
	main_sizer->AddSpacer(space5);
	SetSizerAndFit(main_sizer);

	Bind(wxEVT_BUTTON, &PingDialog::OnCloseBtnPressed, this, wxID_CLOSE);
	Bind(wxEVT_CLOSE_WINDOW, &PingDialog::OnClose, this);
	SetFocus();
	Center();
}

void PingDialog::SetPing(int pid, sf::Uint16 milliseconds)
{
	if (m_ping_labels[pid] == nullptr)
		return;

	m_ping_labels[pid]->SetLabelText(std::to_string(milliseconds) + "ms");
	Layout();
	Update();
}

void PingDialog::OnClose(wxCloseEvent&)
{
	m_netplay_server->AbortPing();
}

void PingDialog::OnCloseBtnPressed(wxCommandEvent&)
{
	Close();
}
