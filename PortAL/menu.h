/*
	PortAL - GUIPro Project ( http://obsidev.github.io/guipro/ )

	Author : Glatigny J�r�me <jerome@obsidev.com> - http://www.obsidev.com/

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MENU_H
#define MENU_H

#define ICON_MANAGER
//#define ICON_MANAGER_THREAD

/* ------------------------------------------------------------------------------------------------- */

#include "common.h"
#include "portalConfig.h"
#include <windows.h>

/* ------------------------------------------------------------------------------------------------- */

typedef struct _PortalMenuItem
{
	UINT id;
#ifndef ICON_MANAGER
	HICON icon;
#else
	UINT iconid;
#endif
	wchar_t* text;
	wchar_t* sctext;
	DWORD options;
	struct _PortalMenuItem* next;
} PortalMenuItem;

typedef struct _PortalColors
{
	COLOR16 red;
	COLOR16 green;
	COLOR16 blue;
	// COLOR16 alpha;
} PortalColors;

typedef struct _ColorPair
{
	COLORREF textcolor;
	COLORREF background;
} ColorPair;

typedef struct _PortalMenuDesign
{
	UINT16 border_size;
	UINT16 border_round;
	COLORREF border_color;
	ColorPair* base;
	ColorPair* selected;
	UINT16 background_grandiant_direction;
	COLORREF background_gradiant_start;
	COLORREF background_gradiant_end;
} PortalMenuDesign;

extern PortalMenuDesign* g_PortalMenuDesign;
#ifdef USE_GDI_MENU
extern boolean g_PortalMenuDesignSystem;
#endif

#define MENU_NORMAL		0x0000
#define MENU_TITLE		0x0001
#define MENU_SEP		0x0002
#define MENU_SUB		0x0004
#define MENU_SHOWSC		0x0008

#define LOADRESOURCEICON(a)		(HICON)LoadImage( GetModuleHandle( NULL ), MAKEINTRESOURCE( a ), IMAGE_ICON, 14, 14, LR_LOADTRANSPARENT);

/* ------------------------------------------------------------------------------------------------- */

void InitMenuVars();
void UnInitMenuVars();

BOOL AddMenuItem(HMENU hMenu, UINT uItemID, UINT uType, UINT uState, PortalMenuItem* item);
BOOL AddSubMenu(HMENU hMenu, UINT uItemID, UINT uType, UINT uState, HMENU subMenu, PortalMenuItem* item);

void ShowTrayMenu(PortalProg* p_menu, int param = 0);
HBITMAP LoadIconAsBitmap(UINT nIDResource, int size);
PortalMenuItem* insertItemMenu(PortalProg* prog, PortalMenuItem* item, HMENU hMenu, int* configElem, int* nResult);

HMENU MyCreateMenu(PortalProg* p_menu, int param);
HMENU MyCreateSubMenu(PortalProg* p_menu);
void DestroyMyMenu(BOOL all);
void OnInitMenuPopup(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnUninitMenuPopup(HWND hWnd, WPARAM wParam, LPARAM lParam);
LRESULT OnMenuCharItem(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnMeasureItem(HWND hWnd, WPARAM wParam, LPARAM lParam);
void OnDrawItem(HWND hWnd, WPARAM wParam, LPARAM lParam);

#ifdef USE_GDI_MENU
HBITMAP IconToBitmapPARGB32(UINT uIcon);
HBITMAP IconToBitmap(UINT uIcon);
#endif

/* ------------------------------------------------------------------------------------------------- */

#endif /* MENU_H */
