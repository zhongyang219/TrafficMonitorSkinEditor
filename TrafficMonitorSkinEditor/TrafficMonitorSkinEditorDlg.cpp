
// TrafficMonitorSkinEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TrafficMonitorSkinEditor.h"
#include "TrafficMonitorSkinEditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditorDlg 对话框



CTrafficMonitorSkinEditorDlg::CTrafficMonitorSkinEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrafficMonitorSkinEditorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrafficMonitorSkinEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC, m_text_color_static);
	DDX_Control(pDX, IDC_SKIN_AUTHOR_EDIT, m_skin_author_edit);
	DDX_Control(pDX, IDC_ASSIGN_TEXT_CHECK, m_assign_text_chk);
	DDX_Control(pDX, IDC_UPLOAD_EDIT, m_up_string_edit);
	DDX_Control(pDX, IDC_DOWNLOAD_EDIT, m_down_string_edit);
	DDX_Control(pDX, IDC_CPU_EDIT, m_cpu_string_edit);
	DDX_Control(pDX, IDC_MEMORY_EDIT, m_memory_string_edit);
	DDX_Control(pDX, IDC_NO_ITEM_TEXT_CHECK, m_no_item_text_chk);
	DDX_Control(pDX, IDC_TEXT_HEIGHT_EDIT, m_text_height_edit);
	DDX_Control(pDX, IDC_WND_WIDTH_EDIT, m_window_width_edit);
	DDX_Control(pDX, IDC_WND_HEIGHT_EDIT, m_window_heitht_edit);
	DDX_Control(pDX, IDC_UP_X_EDIT, m_up_x_edit);
	DDX_Control(pDX, IDC_UP_Y_EDIT, m_up_y_edit);
	DDX_Control(pDX, IDC_UP_WIDTH_EDIT, m_up_width_edit);
	DDX_Control(pDX, IDC_NO_UPLOAD_CHECK, m_no_upload_chk);
	DDX_Control(pDX, IDC_DOWN_X_EDIT, m_down_x_edit);
	DDX_Control(pDX, IDC_DOWN_Y_EDIT, m_down_y_edit);
	DDX_Control(pDX, IDC_DOWN_WIDTH_EDIT, m_down_width_edit);
	DDX_Control(pDX, IDC_CNO_DOWNLOAD_HECK, m_no_download_chk);
	DDX_Control(pDX, IDC_CPU_X_EDIT, m_cpu_x_edit);
	DDX_Control(pDX, IDC_CPU_Y_EDIT, m_cpu_y_edit);
	DDX_Control(pDX, IDC_CPU_WIDTH_EDIT, m_cpu_width_edit);
	DDX_Control(pDX, IDC_NO_CPU_CHECK, m_no_cpu_chk);
	DDX_Control(pDX, IDC_MEMORY_X_EDIT, m_memory_x_edit);
	DDX_Control(pDX, IDC_MEMORY_Y_EDIT, m_memory_y_edit);
	DDX_Control(pDX, IDC_MEMORY_WIDTH_EDIT, m_memory_width_edit);
	DDX_Control(pDX, IDC_NO_MEMORY_CHECK, m_no_memory_chk);
	DDX_Control(pDX, IDC_PREVIEW_WIDTH_EDIT, m_preview_width_edit);
	DDX_Control(pDX, IDC_PREVIEW_HEIGHT_EDIT, m_preview_height_edit);
	DDX_Control(pDX, IDC_PREVIEW_X_S_EDIT, m_preview_x_s_edit);
	DDX_Control(pDX, IDC_PREVIEW_Y_S_EDIT, m_preview_y_s_edit);
	DDX_Control(pDX, IDC_PREVIEW_X_L_EDIT, m_preview_x_l_edit);
	DDX_Control(pDX, IDC_PREVIEW_Y_L_EDIT, m_preview_y_l_edit);
}

BEGIN_MESSAGE_MAP(CTrafficMonitorSkinEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_STATIC_CLICKED, &CTrafficMonitorSkinEditorDlg::OnStaticClicked)
	ON_COMMAND(ID_APP_ABOUT, &CTrafficMonitorSkinEditorDlg::OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, &CTrafficMonitorSkinEditorDlg::OnFileOpen)
	//ON_BN_CLICKED(IDC_BUTTON1, &CTrafficMonitorSkinEditorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LARGE_WINDOW_RADIO, &CTrafficMonitorSkinEditorDlg::OnBnClickedLargeWindowRadio)
	ON_BN_CLICKED(IDC_SMALL_WINDOW_RADIO, &CTrafficMonitorSkinEditorDlg::OnBnClickedSmallWindowRadio)
	ON_BN_CLICKED(IDC_ASSIGN_TEXT_CHECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedAssignTextCheck)
	ON_EN_CHANGE(IDC_UPLOAD_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeUploadEdit)
	ON_EN_CHANGE(IDC_DOWNLOAD_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeDownloadEdit)
	ON_EN_CHANGE(IDC_CPU_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeCpuEdit)
	ON_EN_CHANGE(IDC_MEMORY_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryEdit)
	ON_EN_CHANGE(IDC_PREVIEW_WIDTH_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangePreviewWidthEdit)
	ON_EN_CHANGE(IDC_PREVIEW_HEIGHT_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangePreviewHeightEdit)
	ON_EN_CHANGE(IDC_PREVIEW_X_S_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangePreviewXSEdit)
	ON_EN_CHANGE(IDC_PREVIEW_Y_S_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangePreviewYSEdit)
	ON_EN_CHANGE(IDC_PREVIEW_X_L_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangePreviewXLEdit)
	ON_EN_CHANGE(IDC_PREVIEW_Y_L_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangePreviewYLEdit)
	ON_EN_CHANGE(IDC_TEXT_HEIGHT_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeTextHeightEdit)
	ON_BN_CLICKED(IDC_NO_ITEM_TEXT_CHECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedNoItemTextCheck)
	ON_EN_CHANGE(IDC_WND_WIDTH_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeWndWidthEdit)
	ON_EN_CHANGE(IDC_WND_HEIGHT_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeWndHeightEdit)
	ON_EN_CHANGE(IDC_UP_X_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeUpXEdit)
	ON_EN_CHANGE(IDC_UP_Y_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeUpYEdit)
	ON_EN_CHANGE(IDC_UP_WIDTH_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeUpWidthEdit)
	ON_EN_CHANGE(IDC_DOWN_X_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeDownXEdit)
	ON_EN_CHANGE(IDC_DOWN_Y_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeDownYEdit)
	ON_EN_CHANGE(IDC_DOWN_WIDTH_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeDownWidthEdit)
	ON_EN_CHANGE(IDC_CPU_X_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeCpuXEdit)
	ON_EN_CHANGE(IDC_CPU_Y_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeCpuYEdit)
	ON_EN_CHANGE(IDC_CPU_WIDTH_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeCpuWidthEdit)
	ON_EN_CHANGE(IDC_MEMORY_X_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryXEdit)
	ON_EN_CHANGE(IDC_MEMORY_Y_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryYEdit)
	ON_EN_CHANGE(IDC_MEMORY_WIDTH_EDIT, &CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryWidthEdit)
	ON_BN_CLICKED(IDC_NO_UPLOAD_CHECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedNoUploadCheck)
	ON_BN_CLICKED(IDC_CNO_DOWNLOAD_HECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedCnoDownloadHeck)
	ON_BN_CLICKED(IDC_NO_CPU_CHECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedNoCpuCheck)
	ON_BN_CLICKED(IDC_NO_MEMORY_CHECK, &CTrafficMonitorSkinEditorDlg::OnBnClickedNoMemoryCheck)
	ON_NOTIFY(UDN_DELTAPOS, SPIN_ID, &CTrafficMonitorSkinEditorDlg::OnDeltaposSpin)		//响应所有文本编辑控件微调按钮的点击事件（每个微调按钮的ID都一样）
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditorDlg 消息处理程序

void CTrafficMonitorSkinEditorDlg::DrawPreview()
{
	m_view->SetSize(m_skin_data.preview_width, m_skin_data.preview_height);
	m_view->Invalidate();
}

void CTrafficMonitorSkinEditorDlg::LayoutDataToUI(bool small_window)
{
	m_text_height_edit.SetValue(m_skin_data.text_height);
	m_no_item_text_chk.SetCheck(m_skin_data.no_text);
	if (small_window)
	{
		m_window_width_edit.SetValue(m_skin_data.width_s);
		m_window_heitht_edit.SetValue(m_skin_data.height_s);

		m_up_x_edit.SetValue(m_skin_data.up_x_s);
		m_up_y_edit.SetValue(m_skin_data.up_y_s);
		m_up_width_edit.SetValue(m_skin_data.up_width_s);
		m_no_upload_chk.SetCheck(!m_skin_data.show_up_s);
		m_down_x_edit.SetValue(m_skin_data.down_x_s);
		m_down_y_edit.SetValue(m_skin_data.down_y_s);
		m_down_width_edit.SetValue(m_skin_data.down_width_s);
		m_no_download_chk.SetCheck(!m_skin_data.show_down_s);
		m_cpu_x_edit.SetValue(m_skin_data.cpu_x_s);
		m_cpu_y_edit.SetValue(m_skin_data.cpu_y_s);
		m_cpu_width_edit.SetValue(m_skin_data.cpu_width_s);
		m_no_cpu_chk.SetCheck(!m_skin_data.show_cpu_s);
		m_memory_x_edit.SetValue(m_skin_data.memory_x_s);
		m_memory_y_edit.SetValue(m_skin_data.memory_y_s);
		m_memory_width_edit.SetValue(m_skin_data.memory_width_s);
		m_no_memory_chk.SetCheck(!m_skin_data.show_memory_s);
	}
	else
	{
		m_window_width_edit.SetValue(m_skin_data.width_l);
		m_window_heitht_edit.SetValue(m_skin_data.height_l);

		m_up_x_edit.SetValue(m_skin_data.up_x_l);
		m_up_y_edit.SetValue(m_skin_data.up_y_l);
		m_up_width_edit.SetValue(m_skin_data.up_width_l);
		m_no_upload_chk.SetCheck(!m_skin_data.show_up_l);
		m_down_x_edit.SetValue(m_skin_data.down_x_l);
		m_down_y_edit.SetValue(m_skin_data.down_y_l);
		m_down_width_edit.SetValue(m_skin_data.down_width_l);
		m_no_download_chk.SetCheck(!m_skin_data.show_down_l);
		m_cpu_x_edit.SetValue(m_skin_data.cpu_x_l);
		m_cpu_y_edit.SetValue(m_skin_data.cpu_y_l);
		m_cpu_width_edit.SetValue(m_skin_data.cpu_width_l);
		m_no_cpu_chk.SetCheck(!m_skin_data.show_cpu_l);
		m_memory_x_edit.SetValue(m_skin_data.memory_x_l);
		m_memory_y_edit.SetValue(m_skin_data.memory_y_l);
		m_memory_width_edit.SetValue(m_skin_data.memory_width_l);
		m_no_memory_chk.SetCheck(!m_skin_data.show_memory_l);
	}
}

void CTrafficMonitorSkinEditorDlg::AllToUI()
{
	m_text_color_static.SetFillColor(m_skin_data.text_color);
	m_skin_author_edit.SetWindowTextW(m_skin_data.skin_author.c_str());
	m_assign_text_chk.SetCheck(m_asign_item_text);

	m_up_string_edit.SetWindowTextW(m_skin_data.up_string.c_str());
	m_down_string_edit.SetWindowTextW(m_skin_data.down_string.c_str());
	m_cpu_string_edit.SetWindowTextW(m_skin_data.cpu_string.c_str());
	m_memory_string_edit.SetWindowTextW(m_skin_data.memory_string.c_str());

	m_up_string_edit.EnableWindow(m_asign_item_text);
	m_down_string_edit.EnableWindow(m_asign_item_text);
	m_cpu_string_edit.EnableWindow(m_asign_item_text);
	m_memory_string_edit.EnableWindow(m_asign_item_text);

	LayoutDataToUI(m_edit_small_window);

	m_preview_width_edit.SetValue(m_skin_data.preview_width);
	m_preview_height_edit.SetValue(m_skin_data.preview_height);
	m_preview_x_s_edit.SetValue(m_skin_data.preview_x_s);
	m_preview_y_s_edit.SetValue(m_skin_data.preview_y_s);
	m_preview_x_l_edit.SetValue(m_skin_data.preview_x_l);
	m_preview_y_l_edit.SetValue(m_skin_data.preview_y_l);
}

void CTrafficMonitorSkinEditorDlg::LoadSkin(const wstring & path)
{
	//载入皮肤布局
	CSkinEditorHelper skin_editor;
	skin_editor.SetSkinPath(path);
	m_skin_data = skin_editor.LoadSkin();
	//载入背景图
	m_background_s.Destroy();
	m_background_l.Destroy();
	m_background_s.Load((path + L"\\background.bmp").c_str());
	m_background_l.Load((path + L"\\background_l.bmp").c_str());
	//设置控件数据
	AllToUI();
	//绘制预览
	DrawPreview();
	SetTitle();
}

void CTrafficMonitorSkinEditorDlg::SetTitle()
{
	wstring title;
	if (m_path.empty())
		title = L"无标题 - TrafficMonitor 皮肤编辑器";
	else
		title = m_path + L" - TrafficMonitor 皮肤编辑器";
	if (m_modified)
		title = L'*' + title;
	SetWindowTextW(title.c_str());
}

void CTrafficMonitorSkinEditorDlg::Modified()
{
	m_modified = true;
	DrawPreview();
	SetTitle();
	m_spin_clicked = false;
}

BOOL CTrafficMonitorSkinEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	theApp.GetDPI(this);

	//m_text_color_static.SetFillColor(RGB(255, 192, 0));
	m_text_color_static.SetLinkCursor(true);

	//初始化预览视图
	m_view = (CDrawScrollView*)RUNTIME_CLASS(CDrawScrollView)->CreateObject();
	CRect rect;
	GetDlgItem(IDC_PREVIEW_GROUP_STATIC)->GetWindowRect(rect);		//获取“预览” group box 的位置
	ScreenToClient(&rect);
	CRect scroll_view_rect{ rect };
	scroll_view_rect.DeflateRect(theApp.DPI(12), theApp.DPI(12));
	scroll_view_rect.top += theApp.DPI(102);
	m_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, scroll_view_rect, this, 3000);
	m_view->InitialUpdate();
	m_view->SetSkinData(&m_skin_data);
	m_view->SetBackImage(&m_background_s, &m_background_l);
	m_view->ShowWindow(SW_SHOW);

	//
	((CButton*)GetDlgItem(IDC_LARGE_WINDOW_RADIO))->SetCheck(TRUE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTrafficMonitorSkinEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTrafficMonitorSkinEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTrafficMonitorSkinEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



afx_msg LRESULT CTrafficMonitorSkinEditorDlg::OnStaticClicked(WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = (CWnd*)wParam;
	if (pWnd == &m_text_color_static)
	{
		CColorDialog dlg;
		if (dlg.DoModal() == IDOK)
		{
			m_skin_data.text_color = dlg.GetColor();
			m_text_color_static.SetFillColor(m_skin_data.text_color);
			DrawPreview();
		}
	}
	return 0;
}


void CTrafficMonitorSkinEditorDlg::OnAppAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CTrafficMonitorSkinEditorDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_path = dlg.GetPathName();
		LoadSkin(m_path);
	}
}


//void CTrafficMonitorSkinEditorDlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	int v = m_text_height_edit.GetValue();
//}


void CTrafficMonitorSkinEditorDlg::OnBnClickedLargeWindowRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_small_window = false;
	LayoutDataToUI(m_edit_small_window);
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedSmallWindowRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	m_edit_small_window = true;
	LayoutDataToUI(m_edit_small_window);
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedAssignTextCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	m_asign_item_text = (m_assign_text_chk.GetCheck() != 0);

	m_up_string_edit.EnableWindow(m_asign_item_text);
	m_down_string_edit.EnableWindow(m_asign_item_text);
	m_cpu_string_edit.EnableWindow(m_asign_item_text);
	m_memory_string_edit.EnableWindow(m_asign_item_text);
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeUploadEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_up_string_edit.GetModify())
	{
		CString tmp;
		m_up_string_edit.GetWindowText(tmp);
		m_skin_data.up_string = tmp;
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeDownloadEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_down_string_edit.GetModify())
	{
		CString tmp;
		m_down_string_edit.GetWindowText(tmp);
		m_skin_data.down_string = tmp;
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeCpuEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_cpu_string_edit.GetModify())
	{
		CString tmp;
		m_cpu_string_edit.GetWindowText(tmp);
		m_skin_data.cpu_string = tmp;
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_memory_string_edit.GetModify())
	{
		CString tmp;
		m_memory_string_edit.GetWindowText(tmp);
		m_skin_data.memory_string = tmp;
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangePreviewWidthEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_preview_width_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.preview_width = m_preview_width_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangePreviewHeightEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_preview_height_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.preview_height = m_preview_height_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangePreviewXSEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_preview_x_s_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.preview_x_s = m_preview_x_s_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangePreviewYSEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_preview_y_s_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.preview_y_s = m_preview_y_s_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangePreviewXLEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_preview_x_l_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.preview_x_l = m_preview_x_l_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangePreviewYLEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_preview_y_l_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.preview_y_l = m_preview_y_l_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeTextHeightEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_text_height_edit.GetModify() || m_spin_clicked)
	{
		m_skin_data.text_height = m_text_height_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedNoItemTextCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	m_skin_data.no_text = (m_no_item_text_chk.GetCheck() != 0);
	Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeWndWidthEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_window_width_edit.GetModify() || m_spin_clicked)
	{
		if (m_edit_small_window)
			m_skin_data.width_s = m_window_width_edit.GetValue();
		else
			m_skin_data.width_l = m_window_width_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeWndHeightEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_window_heitht_edit.GetModify() || m_spin_clicked)
	{
		if (m_edit_small_window)
			m_skin_data.height_s = m_window_heitht_edit.GetValue();
		else
			m_skin_data.height_l = m_window_heitht_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeUpXEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_up_x_edit.GetModify() || m_spin_clicked)
	{
		if (m_edit_small_window)
			m_skin_data.up_x_s = m_up_x_edit.GetValue();
		else
			m_skin_data.up_x_l = m_up_x_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeUpYEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_up_y_edit.GetModify() || m_spin_clicked)
	{
		if (m_edit_small_window)
			m_skin_data.up_y_s = m_up_y_edit.GetValue();
		else
			m_skin_data.up_y_l = m_up_y_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeUpWidthEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_up_width_edit.GetModify() || m_spin_clicked)
	{
		if (m_edit_small_window)
			m_skin_data.up_width_s = m_up_width_edit.GetValue();
		else
			m_skin_data.up_width_l = m_up_width_edit.GetValue();
		Modified();
	}
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeDownXEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeDownYEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeDownWidthEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeCpuXEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeCpuYEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeCpuWidthEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryXEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryYEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnEnChangeMemoryWidthEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	//Modified();
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedNoUploadCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	Modified();
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedCnoDownloadHeck()
{
	// TODO: 在此添加控件通知处理程序代码
	Modified();
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedNoCpuCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	Modified();
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedNoMemoryCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	Modified();
}

void CTrafficMonitorSkinEditorDlg::OnDeltaposSpin(NMHDR * pNMHDR, LRESULT * pResult)
{
	//CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)CWnd::FromHandle(pNMHDR->hwndFrom);
	//CEdit* pEdit = (CEdit*)(pSpin->GetBuddy());
	//pEdit->SetModify();
	m_spin_clicked = true;
	*pResult = 0;
}
