// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <map>
#include <string>
#include <vector>
#include <vector>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <SFML\Network.hpp>

class NetPlayServer;
class Player;
class wxCloseEvent;
class wxGauge;
class wxStaticText;
class wxWindow;

class PingDialog final : public wxDialog
{
public:
	PingDialog(wxWindow* parent, NetPlayServer* server, std::vector<const Player*> players, const std::string& target_identifier);

	void SetPing(int pid, sf::Uint16 milliseconds);

private:
	void OnClose(wxCloseEvent& event);
	void OnCloseBtnPressed(wxCommandEvent& event);

	NetPlayServer* m_netplay_server;
	std::map<int, wxStaticText*> m_ping_labels;
};
