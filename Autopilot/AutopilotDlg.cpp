
// AutopilotDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Autopilot.h"
#include "AutopilotDlg.h"
#include "afxdialogex.h"
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAutopilotDlg 对话框



CAutopilotDlg::CAutopilotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AUTOPILOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutopilotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAutopilotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BUTTON1, &CAutopilotDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CAutopilotDlg::OnBnClickedButton2)
ON_WM_TIMER()
ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAutopilotDlg 消息处理程序

BOOL CAutopilotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码
	m_pDC = new CClientDC(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAutopilotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAutopilotDlg::OnPaint()
{
	CPaintDC dc(this);

	CPen pen(PS_SOLID, 2, RGB(0, 0, 0)); // 使用黑色笔绘制连线
	CBrush brush(RGB(255, 0, 0)); // 使用红色刷子绘制点

	// 选择绘图对象
	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	// 定义平行线的距离
	int d = 10;

	// 绘制平行线
	if (m_points.size() > 1)
	{
		for (size_t i = 0; i < m_points.size() - 1; i++)
		{
			// 计算原始线段的斜率和长度
			double k = (double)(m_points[i + 1].y - m_points[i].y) / (m_points[i + 1].x - m_points[i].x);
			double l = sqrt((double)(m_points[i + 1].y - m_points[i].y) * (m_points[i + 1].y - m_points[i].y) + (m_points[i + 1].x - m_points[i].x) * (m_points[i + 1].x - m_points[i].x));

			// 计算平行线的起点和终点
			CPoint p1, p2, p3, p4;
			p1.x = m_points[i].x - d * k / sqrt(1 + k * k);
			p1.y = m_points[i].y + d / sqrt(1 + k * k);
			p2.x = m_points[i + 1].x - d * k / sqrt(1 + k * k);
			p2.y = m_points[i + 1].y + d / sqrt(1 + k * k);
			p3.x = m_points[i].x + d * k / sqrt(1 + k * k);
			p3.y = m_points[i].y - d / sqrt(1 + k * k);
			p4.x = m_points[i + 1].x + d * k / sqrt(1 + k * k);
			p4.y = m_points[i + 1].y - d / sqrt(1 + k * k);

			// 绘制平行线
			dc.MoveTo(p1);
			dc.LineTo(p2);
			dc.MoveTo(p3);
			dc.LineTo(p4);
		}
	}

	// 恢复绘图对象
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAutopilotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAutopilotDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_points.push_back(point);

	// 重新绘制窗口
	Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}




void CAutopilotDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	   // 清除点坐标
	m_points.clear();

	// 重新绘制窗口
	Invalidate();
}


void CAutopilotDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_points.size() < 2)
	{
		// 若点数不足，提示用户并返回
		AfxMessageBox(_T("点数不足以绘制连线。"));
		return;
	}
	currentPointIndex = 0; // 当前目标点的索引
	currentPoint = m_points[currentPointIndex];
	// 开始运动的逻辑，例如使用定时器
	SetTimer(1, 50, nullptr); // 每100毫秒触发一次定时器事件

}


void CAutopilotDlg::OnTimer(UINT_PTR nIDEvent)
{

		static double step = 5; // 小圆点每次移动的步长

		// 检查当前是否为最后一个目标点
		if (currentPointIndex >= m_points.size() - 1)
		{
			// 停止定时器
			KillTimer(1);
			return;
		}

		// 当前目标点和下一个目标点的坐标
		CPoint nextPoint = m_points[currentPointIndex + 1];

		// 计算小圆点的新位置
		double dx = nextPoint.x - currentPoint.x;
		double dy = nextPoint.y - currentPoint.y;
		double distance = sqrt(dx * dx + dy * dy);
		double ratio = (step > distance) ? 1 : step / distance;
		double newX = currentPoint.x + ratio * dx + 0.5 ;
		double newY = currentPoint.y + ratio * dy + 0.5;
		CPoint newPosition(static_cast<int>(newX), static_cast<int>(newY));


		// 判断是否到达下一个目标点
		if (distance < step)
		{
			// 更新目标点索引
			currentPointIndex++;
		}

		// 获取窗口的设备上下文
		CPen pen(PS_SOLID, 10, RGB(255, 255, 255)); // 使用白色作为画笔颜色
		CPen* pOldPen = m_pDC->SelectObject(&pen); // 选择画笔
		m_pDC->SetROP2(R2_XORPEN); // 设置XOR模式

		// 擦除上一个状态的小圆点
		m_pDC->MoveTo(currentPoint); // 移动到当前位置
		m_pDC->LineTo(currentPoint); // 绘制一个点

		// 绘制当前状态的小圆点
		m_pDC->MoveTo(newPosition); // 移动到新位置
		m_pDC->LineTo(newPosition); // 绘制一个点

		// 还原画笔和模式
		m_pDC->SelectObject(pOldPen); // 还原画笔
		m_pDC->SetROP2(R2_COPYPEN); // 还原模式
		currentPoint = newPosition;

	CDialog::OnTimer(nIDEvent);
}


void CAutopilotDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete m_pDC;
	// TODO: 在此处添加消息处理程序代码
}
