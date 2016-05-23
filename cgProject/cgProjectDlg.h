
// cgProjectDlg.h : 头文件
//

#pragma once
#include <queue>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include "afxcmn.h"

#define check(k,i,j) (*MatAt(k, i, j) > 0)
#define VECTW 900
#define VECTH 600

struct edge
{
	int x1, y1, x2, y2;
	int vertical = (x1 == x2);
};

struct net
{
	double x;
	double dx;
	int ymax;
	net* next;
};

// CcgProjectDlg 对话框
class CcgProjectDlg : public CDialogEx
{
// 构造
public:
	CcgProjectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_cgProject_DIALOG };
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

private:
	void MatSmooth(cv::Mat &map1, cv::Mat &map2);
	void line_bresenham(cv::Mat &vecmat, CvPoint t1, CvPoint t2);
	void fillcontour(cv::Mat &imgmat);
	double CcgProjectDlg::CalcCoeff(int nn, int k);
	void DrawBezierPoint(cv::Mat &vecmat, int points[][2], double t, int n);
	void DrawBezier(cv::Mat &vecmat, int points[][2], int n);
	//CWinThread* thread_plot3d;

public:
	IplImage* edge;
	int keydots[100][2];
	int keydotcnt, edgecnt;
	int edges[100][100][2];
	cv::Mat vecmat;

	afx_msg void OnBnClickedButtoncreatedotfont();
	afx_msg void OnBnClickedButtondisp1x();
	afx_msg void OnBnClickedButtondisp2x();
	afx_msg void OnBnClickedButtondisp4x();
	afx_msg void OnBnClickedButtoncreatevector();
	afx_msg void OnBnClickedButtonloadvector();
	afx_msg void OnBnClickedButtondispvect1();
	afx_msg void OnBnClickedButtondispvect2();
	afx_msg void OnBnClickedButtondispvect3();
	afx_msg void OnBnClickedButtoncreatevectorauto();
	CSliderCtrl m_SLIDERepsilon;
	afx_msg void OnBnClickedButtonvectfill();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtondispvectb1();
	afx_msg void OnBnClickedButtondispvectb2();
	afx_msg void OnBnClickedButtoncreatebfont();
	afx_msg void OnBnClickedButtondispvectb3();
	afx_msg void OnBnClickedButtonvectfillb();
	afx_msg void OnBnClickedButtonteapot();
	afx_msg void OnBnClickedButton3dtext();
	afx_msg void OnBnClickedButton3dtexttexture();
};
