
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
}

BEGIN_MESSAGE_MAP(CTrafficMonitorSkinEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_STATIC_CLICKED, &CTrafficMonitorSkinEditorDlg::OnStaticClicked)
	ON_COMMAND(ID_APP_ABOUT, &CTrafficMonitorSkinEditorDlg::OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, &CTrafficMonitorSkinEditorDlg::OnFileOpen)
	ON_BN_CLICKED(IDC_BUTTON1, &CTrafficMonitorSkinEditorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTrafficMonitorSkinEditorDlg 消息处理程序

void CTrafficMonitorSkinEditorDlg::DrawPreview()
{
	CSkinEditorHelper skin_editor;
	skin_editor.SetSkinPath(m_path);
	m_skin_data = skin_editor.LoadSkin();
}

void CTrafficMonitorSkinEditorDlg::LayoutDataToUI(bool small_window)
{
	//m_text_height_edit.SetValue()
	//m_window_width_edit.SetValue(m_skin_data.w)
	if (small_window)
	{

	}
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
	m_start_point.x = rect.left + theApp.DPI(12);
	m_start_point.y = rect.top + theApp.DPI(116);
	ScreenToClient(&m_start_point);
	CRect scroll_view_rect(m_start_point, CSize(theApp.DPI(248), theApp.DPI(145)));
	m_view->Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, scroll_view_rect, this, 3000);
	m_view->InitialUpdate();
	m_view->SetSkinData(&m_skin_data);
	m_view->ShowWindow(SW_SHOW);

	m_text_height_edit.SetValue(12);

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
		DrawPreview();
	}
}


void CTrafficMonitorSkinEditorDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int v = m_text_height_edit.GetValue();
}
