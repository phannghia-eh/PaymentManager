#pragma once

#include "resource.h"

#include <windowsX.h>
#include <winuser.h>
#include <commctrl.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
//thư viện convert UTF-8
#include <io.h> 
#include <locale>
#include <codecvt>

using namespace std;

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);

HWND hwnd;
HWND txt_Add_Type;
HWND txt_Add_Button;
HWND txt_Add_listPayment;
HWND txt_Add_Content;
HWND txt_Add_Cost;
HWND txt_TotalCost;

HWND txt_EatPercent;
HWND txt_MovingPercent;
HWND txt_HousePercent;
HWND txt_TrafficPercent;
HWND txt_SupplyPercent;
HWND txt_ServicePercent;

//For SELCHANGE
LRESULT sel = -1, selns = 0;
//Make ListView
LVCOLUMN LvCol; // Make Coluom struct for ListView
LVITEM LvItem;  // ListView Item struct
LV_DISPINFO lvd;
struct DataStruct{
	wstring PaymentType;
	wstring Content;
	wstring Cost;
};
struct CDrawingInfo
{
	int nX;
	int nY;
	DWORD dwRadius;
	float xStartAngle;
	float xSweepAngle;
};
struct CRectangle
{
	int nLeft;
	int nTop;
	int nRight;
	int nBottom;
};
class CData{
	vector<DataStruct> Data;
	CDrawingInfo* DrawingInfo;
	CRectangle* RetangleInfo;
	WCHAR path[300];
	int m_totalCost = 0;
	int m_eatingCost = 0;
	int m_movingCost = 0;
	int m_houseCost = 0;
	int m_trafficCost = 0;
	int m_supplyCost = 0;
	int m_serviceCost = 0;
public:
	CData();
	~CData();

	DataStruct getData(int i);
	int getSize();
	void push_back(DataStruct a);

	void getDataFromDisk();
	void saveDataToDisk();

	void CalculateEachCost();
	int getTotalCost();

	void CalculateAngle();
	CDrawingInfo* getAngle();
	CRectangle* getRectangleInfo();
	void setPaymentPercent();
};


HWND CreateListView(HWND hwndParent);
BOOL InitListViewColumns(HWND hWndListView);
BOOL InsertListViewItems(HWND hWndListView, CData data);
BOOL InsertListViewItems(HWND hWndListView, CData g_data, int startPos);
bool is_number(wstring s);
int ConvertPaymentType(wstring s);