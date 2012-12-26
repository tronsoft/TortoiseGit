// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2007 - TortoiseSVN

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
#include "stdafx.h"
#include "RebuildIconCacheCommand.h"

#include "ShellUpdater.h"
#include "MessageBox.h"

bool RebuildIconCacheCommand::Execute()
{
	bool bQuiet = !!parser.HasKey(_T("noquestion"));
	if (CShellUpdater::RebuildIcons())
	{
		if (!bQuiet)
			CMessageBox::Show(hwndExplorer, IDS_PROC_ICONCACHEREBUILT, IDS_APPNAME, MB_ICONINFORMATION);
	}
	else
	{
		if (!bQuiet)
			CMessageBox::Show(hwndExplorer, IDS_PROC_ICONCACHENOTREBUILT, IDS_APPNAME, MB_ICONINFORMATION);
	}
	return true;
}