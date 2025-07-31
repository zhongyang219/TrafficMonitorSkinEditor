#pragma once
#include "afxdialogex.h"
#include "EditableListCtrl.h"
#include <map>
#include <string>

// CEditPluginMapDlg 对话框

class CEditPluginMapDlg : public CDialog
{
	DECLARE_DYNAMIC(CEditPluginMapDlg)

public:
	CEditPluginMapDlg(const std::map<std::string, std::string>& plugin_map, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditPluginMapDlg();

	const std::map<std::string, std::string>& GetPluginMap();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_PLUGIN_MAP_DIALOG };
#endif

private:
	CEditableListCtrl m_list_ctrl;
	std::map<std::string, std::string> m_plugin_map;
	CSize m_min_size;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
