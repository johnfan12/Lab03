
// AutopilotDlg.h: 头文件
//

#pragma once
#include <vector>


// CAutopilotDlg 对话框
class CAutopilotDlg : public CDialogEx
{
// 构造
public:
	CAutopilotDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTOPILOT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	std::vector<CPoint> m_points;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int currentPointIndex;
	CPoint currentPoint;
	CClientDC* m_pDC;
	afx_msg void OnDestroy();
	double ratio, dx, dy, distance;
	CPoint nextPoint;
	double step;
};
