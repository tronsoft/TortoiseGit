// TortoiseGit - a Windows shell extension for easy version control

// Copyright (C) 2007-2009 - TortoiseGit

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

// MergeDlg.cpp : implementation file
//

#include "stdafx.h"

#include "Git.h"
#include "TortoiseProc.h"
#include "MergeDlg.h"
#include "AppUtils.h"

#include "Messagebox.h"
// CMergeDlg dialog

IMPLEMENT_DYNAMIC(CMergeDlg, CResizableStandAloneDialog)

CMergeDlg::CMergeDlg(CWnd* pParent /*=NULL*/)
	: CResizableStandAloneDialog(CMergeDlg::IDD, pParent),
	CChooseVersion(this)
{
	
	m_pDefaultText = _T("<Auto Generated by Git>");
	m_bNoFF=false;
	m_bSquash=false;
	m_bNoCommit=false;
}

CMergeDlg::~CMergeDlg()
{
}

void CMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	CHOOSE_VERSION_DDX;

	DDX_Check(pDX,IDC_CHECK_NOFF,this->m_bNoFF);
	DDX_Check(pDX,IDC_CHECK_SQUASH,this->m_bSquash);
	DDX_Check(pDX,IDC_CHECK_NOCOMMIT,this->m_bNoCommit);
	DDX_Control(pDX, IDC_LOGMESSAGE, m_cLogMessage);
}


BEGIN_MESSAGE_MAP(CMergeDlg, CResizableStandAloneDialog)
	CHOOSE_VERSION_EVENT
	ON_BN_CLICKED(IDOK, &CMergeDlg::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL CMergeDlg::OnInitDialog()
{
	CResizableStandAloneDialog::OnInitDialog();
	CAppUtils::MarkWindowAsUnpinnable(m_hWnd);

	CHOOSE_VERSION_ADDANCHOR;

	AddAnchor(IDC_GROUP_OPTION, TOP_LEFT, TOP_RIGHT);
	AddAnchor(IDC_STATIC_MERGE_MESSAGE,TOP_LEFT,BOTTOM_RIGHT);
	AddAnchor(IDC_LOGMESSAGE,TOP_LEFT,BOTTOM_RIGHT);
	
	AddAnchor(IDOK,BOTTOM_RIGHT);
	AddAnchor(IDCANCEL,BOTTOM_RIGHT);
	AddAnchor(IDHELP, BOTTOM_RIGHT);

	this->AddOthersToAnchor();

	CheckRadioButton(IDC_RADIO_BRANCH,IDC_RADIO_VERSION,IDC_RADIO_BRANCH);
	this->SetDefaultChoose(IDC_RADIO_BRANCH);

	CString sWindowTitle;
	GetWindowText(sWindowTitle);
	CAppUtils::SetWindowTitle(m_hWnd, g_Git.m_CurrentDir, sWindowTitle);

	Init();

	m_ProjectProperties.ReadProps(CTGitPath(g_Git.m_CurrentDir));

	m_cLogMessage.Init(m_ProjectProperties);
	m_cLogMessage.SetFont((CString)CRegString(_T("Software\\TortoiseGit\\LogFontName"), _T("Courier New")), (DWORD)CRegDWORD(_T("Software\\TortoiseGit\\LogFontSize"), 8));
	m_cLogMessage.RegisterContextMenuHandler(this);

	m_cLogMessage.SetText(m_pDefaultText);
	
	EnableSaveRestore(_T("MergeDlg"));

	return TRUE;
}

// CMergeDlg message handlers


void CMergeDlg::OnBnClickedOk()
{
	this->UpdateData(TRUE);

	this->UpdateRevsionName();

	this->m_strLogMesage = m_cLogMessage.GetText() ;
	if( m_strLogMesage == CString(this->m_pDefaultText) )
	{
		m_strLogMesage.Empty();
	}

	OnOK();
}

void CMergeDlg::OnDestroy()
{
	WaitForFinishLoading();
	__super::OnDestroy();
}
