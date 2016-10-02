#include <windows.h>
#include <CommCtrl.h>
#include <tchar.h>
#include "resource.h"


#pragma comment(lib, "ComCtl32.lib")

	//const UNIT valMin=0;
	//const UNIT valMax=200;

BOOL CALLBACK DlgProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, 
				   LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hDlg;
    MSG msg;
    BOOL ret;

    InitCommonControls();
    hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DLG), 0, DlgProc);
    ShowWindow(hDlg, nCmdShow);

	while(GetMessage (&msg, NULL, 0, 0))
	{
		if(hDlg == 0 || !IsDialogMessage (hDlg, &msg))
		{
			TranslateMessage(&msg) ;
			DispatchMessage(&msg) ;
		}
	}
    return msg.wParam ;
}


BOOL CALLBACK DlgProc (HWND hDlg, UINT uMsg,
                           WPARAM wParam, LPARAM lParam)
{
    //char valMax = 100;
	//char valMin = 200;
	HWND hSpin, hEdit, hSlider,hwnd;
	LPNMUPDOWN lpnmud;
	UINT nCode;
    TCHAR szText[56], szEdit[10];
	int iPos;

	switch(uMsg)
	{
    case WM_INITDIALOG:
		 hSpin = GetDlgItem(hDlg, IDC_SPIN);
		 SendMessage(hSpin, UDM_SETRANGE, 0, MAKELPARAM(1023, 0));
		 SendMessage(hSpin, UDM_SETPOS, 0, 55);
		 hSlider = GetDlgItem(hDlg, IDC_SLIDER);
		 SendMessage(hSlider, TBM_SETRANGE, TRUE, MAKEWPARAM(0, 1023));
		 SendMessage(hSlider, TBM_SETTICFREQ, 50, 0);
		 
		 SendMessage(hSlider, TBM_SETPOS, TRUE, 55);


		 hwnd = GetDlgItem(hDlg,IDC_SCROLLBAR);
		 SetScrollRange (hwnd, SB_CTL, 0, 100, FALSE) ;
         SetScrollPos (hwnd, SB_CTL, 4, TRUE);

		 return TRUE;
 
    case WM_COMMAND:
     	 if (LOWORD(wParam) == IDC_EDIT) 
             if (HIWORD(wParam) == EN_CHANGE)
                GetWindowText(lParam, szEdit, 4);
		        
		 return TRUE;
		 
    case WM_VSCROLL:
		 if (LOWORD(wParam) == IDC_SLIDER)
		 {
			hEdit = GetDlgItem(hDlg,IDC_EDIT);
		    hwnd = GetDlgItem(hDlg,IDC_SLIDER);
		    iPos = SendMessage(hwnd, TBM_GETPOS, 0, 0);
            itoa(iPos, szEdit, 10);
		    SetWindowText(hEdit, szEdit);
			return TRUE;
		 } 
		 else
		    return FALSE;
    
	case WM_NOTIFY:
		 nCode =  ((LPNMHDR)lParam)->code;
		 lpnmud  = (LPNMUPDOWN)lParam;
		 wsprintf(szText, "%i --  %i -- %i", nCode, lpnmud->iPos, lpnmud->iDelta);
		 if (LOWORD(wParam) == IDC_SPIN)
		 {
			hEdit = GetDlgItem(hDlg,IDC_SHOW);  
            SetWindowText(hEdit,szText);
		 }
		 return TRUE;
		 
         
	case WM_CLOSE: /* there are more things to go here, */
		 DestroyWindow(hDlg);
         return TRUE; /* just continue reading on... */

	case WM_DESTROY:
		 PostQuitMessage(0);
         return TRUE;
	}

	return FALSE;
}