// Midterm.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Midterm.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#define MAX_LOADSTRING 100

CData g_data;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MIDTERM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MIDTERM));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MIDTERM));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MIDTERM);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, _T("Quản lý chi tiêu"), WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, 550, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	TCHAR PaymentTypes[7][20] = {
		TEXT("Ăn uống"), TEXT("Di chuyển"), TEXT("Nhà cửa"), TEXT("Xe cộ"), TEXT("Nhu yếu phẩm"), TEXT("Dịch vụ")
	};
	TCHAR A[20];
	memset(&A, 0, sizeof(A));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	hwnd = CreateWindowEx(0, L"BUTTON", L"Thêm một loại chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 10, 500, 70, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	
	hwnd = CreateWindowEx(0, L"STATIC", L"Loại chi tiêu", WS_CHILD | WS_VISIBLE, 30, 30, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_Add_Type = CreateWindow(WC_COMBOBOX, L"", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | WS_TABSTOP, 30, 50, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_Add_Type, WM_SETFONT, WPARAM(hFont), TRUE);
	for (int i = 0; i < 6; i++)
	{
		wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)PaymentTypes[i]);
		SendMessage(txt_Add_Type, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
	}

	hwnd = CreateWindowEx(0, L"BUTTON", L"Thêm", WS_CHILD | WS_VISIBLE | BS_CENTER | WS_BORDER | BS_PUSHBUTTON, 450, 20, 55, 55, hWnd, (HMENU)IDC_BUTTON_ADD, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	hwnd = CreateWindowEx(0, L"STATIC", L"Nội dung", WS_CHILD | WS_VISIBLE, 150, 30, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_Add_Content = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 150, 50, 150, 22, hWnd, NULL, hInst, NULL);
	SendMessage(txt_Add_Content, WM_SETFONT, WPARAM(hFont), TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	hwnd = CreateWindowEx(0, L"STATIC", L"Số tiền (VNĐ)", WS_CHILD | WS_VISIBLE, 320, 30, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_Add_Cost = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 320, 50, 120, 22, hWnd, NULL, hInst, NULL);
	SendMessage(txt_Add_Cost, WM_SETFONT, WPARAM(hFont), TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	hwnd = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, L"BUTTON", L"Toàn bộ danh sách các chi tiêu", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 120, 500, 170, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
	
	//txt_Add_listPayment = CreateWindowEx(0, (LPCWSTR)WC_LISTVIEW, L"", WS_CHILD | WS_BORDER | WS_HSCROLL | WS_VSCROLL | WS_VISIBLE, 30, 150, 470, 100, hWnd, NULL, hInst, NULL);
	//txt_Add_listPayment = CreateListView(hWnd);
	SendMessage(txt_Add_listPayment, WM_SETFONT, WPARAM(hFont), TRUE);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, L"BUTTON", L"Thông tin thống kê", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 20, 300, 500, 250, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"Tổng cộng:", WS_CHILD | WS_VISIBLE, 150, 320, 100, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	hwnd = CreateWindowEx(0, L"STATIC", L"VNĐ", WS_CHILD | WS_VISIBLE, 350, 320, 30, 20, hWnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_TotalCost = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE, 220, 317, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_TotalCost, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_EatPercent = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE | WS_DISABLED, 320, 350, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_EatPercent, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_MovingPercent = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE | WS_DISABLED, 320, 380, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_MovingPercent, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_HousePercent = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE | WS_DISABLED, 320, 410, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_HousePercent, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_TrafficPercent = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE | WS_DISABLED, 320, 440, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_TrafficPercent, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_SupplyPercent = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE | WS_DISABLED, 320, 470, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_SupplyPercent, WM_SETFONT, WPARAM(hFont), TRUE);

	txt_ServicePercent = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_BORDER | SS_LEFT | WS_VISIBLE | WS_DISABLED, 320, 500, 120, 20, hWnd, NULL, hInst, NULL);
	SendMessage(txt_ServicePercent, WM_SETFONT, WPARAM(hFont), TRUE);

	//Danh sách chi tiêu:
	txt_Add_listPayment = CreateListView(hWnd);

	memset(&LvCol, 0, sizeof(LvCol)); // Reset Column
	InitListViewColumns(txt_Add_listPayment);
	/////////////////////////////////////////////////////////////////////
	g_data.getDataFromDisk();
	InsertListViewItems(txt_Add_listPayment, g_data);
	// Cập nhật số tiền sau khi load
	WCHAR* bufferTotalCost;
	bufferTotalCost = new WCHAR[256];
	wsprintf(bufferTotalCost, L"%d", g_data.getTotalCost());
	SetWindowText(txt_TotalCost, bufferTotalCost);
	UpdateWindow(txt_TotalCost);
	// Tính số tiền của mỗi loại để vẽ biểu đồ

	g_data.CalculateEachCost();

	//Cập nhất tỉ lệ biểu đồ:
	//g_data.setPaymentPercent();
	
	return true;
}
void OnDestroy(HWND hWnd)
{
	g_data.saveDataToDisk();
	PostQuitMessage(0);
}
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int size1 = 0; int size2 = 0; int size3 = 0;
	switch (id)
	{
	case IDC_BUTTON_ADD:
	{
		size1 = GetWindowTextLength(txt_Add_Type);
		size2 = GetWindowTextLength(txt_Add_Content);
		size3 = GetWindowTextLength(txt_Add_Cost);
		if (size1 == 0 || size2 == 0 || size3 == 0)
		{
			MessageBox(0, L"Bạn chưa nhập đủ thông tin", L"ERROR", MB_ICONINFORMATION | MB_OK);
			break;
		}
		DataStruct buffer;
		buffer.PaymentType = new WCHAR[size1 + 1];
		buffer.Content = new WCHAR[size2 + 1];
		buffer.Cost = new WCHAR[size3 + 1];
		GetWindowText(txt_Add_Type, &buffer.PaymentType[0], size1 + 1);
		GetWindowText(txt_Add_Content, &buffer.Content[0], size2 + 1);
		GetWindowText(txt_Add_Cost, &buffer.Cost[0], size3 + 1);
		buffer.PaymentType.resize(size1);
		buffer.Content.resize(size2);
		buffer.Cost.resize(size3);
		if (is_number(buffer.Cost))
			g_data.push_back(buffer);
		else
		{
			MessageBox(hWnd, L"Yêu cầu nhập số tiền ở dạng số!", L"Lỗi!!", MB_ICONINFORMATION | MB_OK);
			break;
		}

		InsertListViewItems(txt_Add_listPayment, g_data, g_data.getSize() - 1);
		UpdateWindow(txt_Add_listPayment);
		
		// Tính tổng số tiền chi trả:
		WCHAR* bufferTotalCost;
		bufferTotalCost = new WCHAR[256];
		wsprintf(bufferTotalCost, L"%d", g_data.getTotalCost());
		SetWindowText(txt_TotalCost, bufferTotalCost);
		UpdateWindow(txt_TotalCost);
		// Tính chi phí cho mỗi loại chi tiêu:
		g_data.CalculateEachCost();
		g_data.CalculateAngle();
	}
		break;
	}
	
}
void OnPaint(HWND hWnd)
{
	COLORREF Color[6] = { Red, Blue, Green, Yellow, Orange, Cyan };
	
	PAINTSTRUCT ps;
	//HDC *hdc=new HDC[6];
	HDC hdc[6];
	HBRUSH hBrush[6];
	//Tính dữ liệu các góc:
	g_data.CalculateAngle();
	//lấy dữ liệu các góc:
	CDrawingInfo *CDraw;
	CRectangle * CRect;
	CDraw = g_data.getAngle();
	CRect = g_data.getRectangleInfo();
	//Vẽ biểu đồ:
	for (int i = 0; i < 6; i++)
	{
		hdc[i] = GetDC(hWnd);
		BeginPath(hdc[i]);
		SelectObject(hdc[i], GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc[0], Color[i]);
		MoveToEx(hdc[i], CDraw[i].nX, CDraw[i].nY, (LPPOINT)NULL);
		AngleArc(hdc[i], CDraw[i].nX, CDraw[i].nY, CDraw[i].dwRadius, CDraw[i].xStartAngle, CDraw[i].xSweepAngle);
		LineTo(hdc[i], CDraw[i].nX, CDraw[i].nY);
		EndPath(hdc[i]);
		StrokeAndFillPath(hdc[i]);
		
		hBrush[i]= CreateSolidBrush(Color[i]);
		SelectObject(hdc[i], hBrush[i]);

		Rectangle(hdc[i], CRect[i].nLeft, CRect[i].nTop, CRect[i].nRight, CRect[i].nBottom);
		DeleteObject(hBrush[i]);

		ReleaseDC(hWnd, hdc[i]);
	}
	g_data.setPaymentPercent();
	EndPaint(hWnd, &ps);
}

CData::CData()
{
	Data.resize(0);
	WCHAR buffer[300];
	GetCurrentDirectory(300, buffer);
	wsprintf(path, L"%s\\data.txt", buffer);
	// Khởi tạo drawing info
	DrawingInfo = new CDrawingInfo[6];
	for (int i = 0; i < 6; i++)
	{
		DrawingInfo[i].nX = 140;
		DrawingInfo[i].nY = 445;
		DrawingInfo[i].dwRadius = 95;
		DrawingInfo[i].xStartAngle = 0;
		DrawingInfo[i].xSweepAngle = 0;
	}
	RetangleInfo = new CRectangle[6];
	RetangleInfo[0].nLeft = 250; RetangleInfo[0].nRight = 310; RetangleInfo[0].nTop = 350;  RetangleInfo[0].nBottom = 370;
	RetangleInfo[1].nLeft = 250; RetangleInfo[1].nRight = 310; RetangleInfo[1].nTop = 380;  RetangleInfo[1].nBottom = 400;
	RetangleInfo[2].nLeft = 250; RetangleInfo[2].nRight = 310; RetangleInfo[2].nTop = 410;  RetangleInfo[2].nBottom = 430;
	RetangleInfo[3].nLeft = 250; RetangleInfo[3].nRight = 310; RetangleInfo[3].nTop = 440;  RetangleInfo[3].nBottom = 460;
	RetangleInfo[4].nLeft = 250; RetangleInfo[4].nRight = 310; RetangleInfo[4].nTop = 470;  RetangleInfo[4].nBottom = 490;
	RetangleInfo[5].nLeft = 250; RetangleInfo[5].nRight = 310; RetangleInfo[5].nTop = 500;  RetangleInfo[5].nBottom = 520;
}

CData::~CData(){

}

DataStruct CData::getData(int i)
{
	return Data[i];
}

void CData::push_back(DataStruct a)
{
	Data.push_back(a);
}

void CData::getDataFromDisk()
{
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);  // UTF-8
	wfstream fi(path, ios::in);
	fi.imbue(loc);
	if (fi)
	{
		while (!fi.eof())
		{
			DataStruct buffer;
			//buffer.Content = new TCHAR[30];
			//buffer.Cost = new TCHAR[30];
			//buffer.PaymentType = new TCHAR[30];
			
			//fi >> buffer.PaymentType >> buffer.Content >> buffer.Cost;
			getline(fi, buffer.PaymentType, L'\t ');
			getline(fi, buffer.Content, L'\t ');
			getline(fi, buffer.Cost, L'\n ');
			//Xử lý dữ liệu:
			while (buffer.PaymentType[0] == 65279 || buffer.PaymentType[0] == 32)
			{
				buffer.PaymentType.erase(0, 1);
			}
			while (buffer.Cost[0] == 65279 || buffer.Cost[0] == 32)
			{
				buffer.Cost.erase(0, 1);
			}
			while (buffer.Content[0] == 65279 || buffer.Content[0] == 32)
			{
				buffer.Content.erase(0, 1);
			}
			if (buffer.PaymentType.size() != 0)
				g_data.push_back(buffer);
		}
	}
	else
		MessageBox(0, L"ERROR", L"Không tìm thấy file g_data", MB_ICONINFORMATION | MB_OK);
	fi.close();
}

HWND CreateListView(HWND hwndParent)
{
	INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	RECT rcClient;                       // The parent window's client area.

	GetClientRect(hwndParent, &rcClient);

	// Create the list-view window in report view with label editing enabled.
	HWND hWndListView = CreateWindow(WC_LISTVIEW,
		L"",
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS | WS_VISIBLE,
		30, 150, 470, 125,
		hwndParent,
		NULL,
		hInst,
		NULL);

	return (hWndListView);
}
BOOL InitListViewColumns(HWND hWndListView)
{
	WCHAR szText[3][256] = { L"Loại chi tiêu", L"Nội dung", L"Số tiền" };     // Temporary buffer.
	LVCOLUMN lvc;
	int iCol;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	// Add the columns.
	for (iCol = 0; iCol < 3; iCol++)
	{
		lvc.iSubItem = iCol;
		lvc.pszText = szText[iCol];
		lvc.cx = 100;               // Width of column in pixels.

		if (1 == iCol)
		{
			lvc.cx = 270;
			lvc.fmt = LVCFMT_CENTER;
		}
		// Load the names of the column headings from the string resources.
		//LoadString(hInst, NULL, szText[iCol], sizeof(szText) / sizeof(szText[0]));

		// Insert the columns into the list view.
		if (ListView_InsertColumn(hWndListView, iCol, &lvc) == -1)
			return FALSE;
	}

	return TRUE;
}
BOOL InsertListViewItems(HWND hWndListView, CData g_data)
{
	LVITEM lvI;
	for (int index = 0; index < g_data.getSize(); index++)
	{
		DataStruct Buffer;

		//TCHAR* Buffer1 = new TCHAR[g_data.getData(index).PaymentType.size()+1];
		//Buffer1[g_data.getData(index).PaymentType.size() + 1] = 0;
		//std::copy(g_data.getData(index).PaymentType.begin(), g_data.getData(index).PaymentType.end(), Buffer1);
		Buffer.PaymentType = g_data.getData(index).PaymentType;
		Buffer.Content = g_data.getData(index).Content;
		Buffer.Cost = g_data.getData(index).Cost;

		// nạp cột đầu - Loại chi tiêu:
		lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lvI.iItem = index;
	
		lvI.iSubItem = 0;
		lvI.pszText = &Buffer.PaymentType[0];
		lvI.state = 0;
		ListView_InsertItem(hWndListView, &lvI);
		//Nạp các cột còn lại (Content, Cost)
		lvI.mask = LVIF_TEXT;

		//Cột đầu tiên là Content
		lvI.iSubItem = 1;
		lvI.pszText = &Buffer.Content[0];
		ListView_SetItem(hWndListView, &lvI);

		//Cột tiếp theo là Cost
		lvI.iSubItem = 2;
		lvI.pszText = &Buffer.Cost[0];
		ListView_SetItem(hWndListView, &lvI);

	}

	return TRUE;
}
BOOL InsertListViewItems(HWND hWndListView, CData g_data, int startPos)
{
	LVITEM lvI;
	for (int index = startPos; index < g_data.getSize(); index++)
	{
		DataStruct Buffer;

		//TCHAR* Buffer1 = new TCHAR[g_data.getData(index).PaymentType.size()+1];
		//Buffer1[g_data.getData(index).PaymentType.size() + 1] = 0;
		//std::copy(g_data.getData(index).PaymentType.begin(), g_data.getData(index).PaymentType.end(), Buffer1);
		Buffer.PaymentType = g_data.getData(index).PaymentType;
		Buffer.Content = g_data.getData(index).Content;
		Buffer.Cost = g_data.getData(index).Cost;

		// nạp cột đầu - Loại chi tiêu:
		lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lvI.iItem = index;

		lvI.iSubItem = 0;
		lvI.pszText = &Buffer.PaymentType[0];
		lvI.state = 0;
		ListView_InsertItem(hWndListView, &lvI);
		//Nạp các cột còn lại (Content, Cost)
		lvI.mask = LVIF_TEXT;

		//Cột đầu tiên là Content
		lvI.iSubItem = 1;
		lvI.pszText = &Buffer.Content[0];
		ListView_SetItem(hWndListView, &lvI);

		//Cột tiếp theo là Cost
		lvI.iSubItem = 2;
		lvI.pszText = &Buffer.Cost[0];
		ListView_SetItem(hWndListView, &lvI);

	}

	return TRUE;
}
int CData::getSize()
{
	return Data.size();
}

int CData::getTotalCost()
{
	int buffer = 0;
	for (int i = 0; i < Data.size(); i++)
	{
		if (is_number(Data[i].Cost))
			buffer += std::stoi(Data[i].Cost);
	}
	return buffer;
}
void CData::saveDataToDisk()
{
	std::locale loc(std::locale(), new std::codecvt_utf8<wchar_t>);  // UTF-8
	wfstream fo(path, ios::out);
	fo.imbue(loc);
	if (fo)
	{
		for (int i = 0; i < Data.size(); i++)
		{
			//fo << Data[i].PaymentType << "/t" << Data[i].Content << "\t" << Data[i].Cost << "\n";
			fo.write(Data[i].PaymentType.c_str(), Data[i].PaymentType.size());
			fo.write(L"\t", 1);
			fo.write(Data[i].Content.c_str(), Data[i].Content.size());
			fo.write(L"\t", 1);
			fo.write(Data[i].Cost.c_str(), Data[i].Cost.size());
			if (i < Data.size() - 1)
				fo.write(L"\n", 1);

		}
	}
	fo.close();
}
void CData::CalculateEachCost()
{
	m_eatingCost = m_movingCost = m_houseCost = m_trafficCost = m_supplyCost = m_serviceCost = 0;
	for (int i = 0; i < Data.size(); i++)
	{
		switch (ConvertPaymentType(Data[i].PaymentType))
		{
		case 1: m_eatingCost += stoi(Data[i].Cost); break;
		case 2: m_movingCost += stoi(Data[i].Cost); break;
		case 3: m_houseCost += stoi(Data[i].Cost); break;
		case 4: m_trafficCost += stoi(Data[i].Cost); break;
		case 5: m_supplyCost += stoi(Data[i].Cost); break;
		case 6:m_serviceCost += stoi(Data[i].Cost); break;
		}
	}
}
void CData::CalculateAngle()
{
	CData::CalculateEachCost();
	if (Data.size() == 0) return;
	DrawingInfo[0].xSweepAngle = 360 * m_eatingCost / getTotalCost();

	DrawingInfo[1].xStartAngle = DrawingInfo[0].xSweepAngle;
	DrawingInfo[1].xSweepAngle = 360 * m_movingCost / getTotalCost();

	DrawingInfo[2].xStartAngle = DrawingInfo[1].xSweepAngle + DrawingInfo[1].xStartAngle;
	DrawingInfo[2].xSweepAngle = 360 * m_houseCost / getTotalCost();		 
																			 
	DrawingInfo[3].xStartAngle = DrawingInfo[2].xSweepAngle + DrawingInfo[2].xStartAngle;
	DrawingInfo[3].xSweepAngle = 360 * m_trafficCost / getTotalCost();		 
																			 
	DrawingInfo[4].xStartAngle = DrawingInfo[3].xSweepAngle + DrawingInfo[3].xStartAngle;
	DrawingInfo[4].xSweepAngle = 360 * m_supplyCost / getTotalCost();		 
																			 
	DrawingInfo[5].xStartAngle = DrawingInfo[4].xSweepAngle + DrawingInfo[4].xStartAngle;
	DrawingInfo[5].xSweepAngle = 360 - DrawingInfo[4].xStartAngle - DrawingInfo[4].xSweepAngle;

}
void CData::setPaymentPercent()
{
	if (Data.size() == 0)
		return;
	WCHAR* buffer;
	buffer = new WCHAR[256];
	int tmp = g_data.getTotalCost();
	wsprintf(buffer, L"%s: %d%%", L"Ăn uống", 100 * m_eatingCost / tmp);
	SetWindowText(txt_EatPercent, buffer);
	wsprintf(buffer, L"%s: %d%%", L"Di chuyển", 100 * m_movingCost / tmp);
	SetWindowText(txt_MovingPercent, buffer);
	wsprintf(buffer, L"%s: %d%%", L"Nhà cửa", 100 * m_houseCost / tmp);
	SetWindowText(txt_HousePercent, buffer);
	wsprintf(buffer, L"%s: %d%%", L"Xe cộ", 100 * m_trafficCost / tmp);
	SetWindowText(txt_TrafficPercent, buffer);
	wsprintf(buffer, L"%s: %d%%", L"Nhu yếu phẩm", 100 * m_supplyCost / tmp);
	SetWindowText(txt_SupplyPercent, buffer);
	wsprintf(buffer, L"%s: %d%%", L"Dịch vụ", 100 - (100 * m_eatingCost / tmp) - (100 * m_movingCost / tmp) - (100 * m_houseCost / tmp) - (100 * m_trafficCost / tmp) - (100 * m_supplyCost / tmp));
	SetWindowText(txt_ServicePercent, buffer);
	if (!buffer)
		delete[] buffer;
}
CDrawingInfo* CData::getAngle()
{
	return DrawingInfo;
}
CRectangle* CData::getRectangleInfo()
{
	return RetangleInfo;
}
bool is_number(wstring s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (((int)s[i] >= 59 || (int)s[i] < 48) && (int)s[i] != 0)
			return false;
	} return true;
}
int ConvertPaymentType(wstring s)
{
	if (s.compare(L"Ăn uống") == 0)
		return 1;
	else if (s.compare(L"Di chuyển") == 0)
		return 2;
	else if (s.compare(L"Nhà cửa") == 0)
		return 3;
	else if (s.compare(L"Xe cộ") == 0)
		return 4;
	else if (s.compare(L"Nhu yếu phẩm") == 0)
		return 5;
	else if (s.compare(L"Dịch vụ") == 0)
		return 6;
}