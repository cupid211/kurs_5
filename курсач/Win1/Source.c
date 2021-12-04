#include<Windows.h>
#include<stdio.h>
#include<string.h>
#include <locale.h>
#include "commctrl.h"
#include<stdlib.h>
#include"Header.h"
#include<time.h>

HINSTANCE hinstance;
WNDCLASSA wnd;
HWND hwnd,stat,new, hwnd1,st;
HWND bt_start, bt_add, bt_change, bt_del, bt_work, bt_cancel, bt_statistic, st_about, bt_about, bt_away,st_ab;
HWND hListBox, edit, hListView;
#define bt_idst 2
#define bt_idadd 3
#define bt_idch 4
#define bt_iddel 5
#define bt_idst1 6
#define bt_idwork 8
#define bt_idcancel 9
char *fil;
int count,need,start,new_start,add;
char *str1;
int bol=0;
char all[4];
int bol ;
char *text, *zapas;
int position;
int m,nelzy,upr;
char oshib[3];
int zadanie;
unsigned char tableRus[] = "йцукенгшщзхъфывапролджэячсмитьбю";
HWND hwndList;


void stolb(HWND hwnd)
{
	LVCOLUMN column;
	memset(&column, 0, sizeof(LVCOLUMN));
	column.mask = LVCF_WIDTH | LVCF_TEXT;
	column.cx = 140;
	column.pszText = "Номер";
	ListView_InsertColumn(hwnd, 0, &column);
	column.cx = 140;
	column.pszText = "Ошибок";
	ListView_InsertColumn(hwnd, 1, &column);
	column.cx = 140;
	column.pszText = "Дата";
	ListView_InsertColumn(hwnd, 2, &column);
}

void strocy(HWND hwnd, char stroca[], int c)
{
	int where = 0;
	LVITEM item;
	memset(&item, 0, sizeof(LVITEM));
	item.mask = LVIF_TEXT | LVIF_COLUMNS | LVIF_COLFMT;
	item.pszText = "Readme";
	item.iItem = c;
	char *strochka = (char*)malloc(sizeof(stroca)*sizeof(char));
	for (int i = 0; i < strlen(stroca); i++)
	{
		int j = 0;
		while (stroca[i] != ' ' && stroca[i] != '\n'&& i != strlen(stroca))
		{
			strochka[j]=stroca[i];
			j++;
			i++;
		}
		strochka[j] = '\0';
		if (where == 0)
		{
			item.pszText = strochka;
			ListView_InsertItem(hwnd, &item);
		}
		else
		{
			ListView_SetItemText(hwnd, c, where, strochka);
			
		}
		where++;
	}
}


char *perevod(int chto)
{
	char *strochka = (char*)malloc(sizeof(chto)*sizeof(char));
	_itoa_s(chto, strochka, 5, 10);
	return strochka;
}

void nomerzadaniya()
{
	unsigned int year = 0;
	unsigned int month = 0;
	unsigned int day = 0;
	SYSTEMTIME st;
	GetLocalTime(&st);

	year = st.wYear;
	month = st.wMonth;
	day = st.wDay;
	FILE *file;
	fopen_s(&file, fil, "at");
	fputc('\n', file);
	fputs(perevod(zadanie+1), file);
	fputc(' ', file);
	fputs(oshib, file);
	fputc(' ', file);
	fputs(perevod(day), file);
	fputc('.', file);
	fputs(perevod(month), file);
	fputc('.', file);
 	fputs(perevod(year), file);
	fclose(file);
}

int opredelenie(int what)
{
 	switch (what){
	case 32:
	{
			   return 32;
			   break;
	}
	case 12:
	{
			   return 32;
			   break;
	}
	case (65) :
	{
				  return 244;
				  break;
	}
	case (66) :
	{
				  return 232;
				  break;
	}
	case 67:
	{
			   return 241;
			   break;
	}
	case 68:
	{
			   return 226;
			   break;
	}
	case 69:
	{
			   return 243;
			   break;
	}
	case 70:
	{
			   return 224;
			   break;
	}
	case 71:
	{
			   return 239;
			   break;
	}
	case 72:
	{
			   return 240;
			   break;
	}
	case 73:
	{
			   return 248;
			   break;
	}
	case 74:
	{
			   return 238;
			   break;
	}
	case 75:
	{
			   return 235;
			   break;
	}
	case 76:
	{
			   return 228;
			   break;
	}
	case 77:
	{
			   return 252;
			   break;
	}
	case 78:
	{
			   return 242;
			   break;
	}
	case 79:
	{
			   return 249;
			   break;
	}
	case 80:
	{
			   return 231;
			   break;
	}
	case 81:
	{
			   return 233;
			   break;
	}
	case 82:
	{
			   return 234;
			   break;
	}
	case 83:
	{
			   return 251;
			   break;
	}
	case 84:
	{ 
			   return 229;
			   break;
	}
	case 85:
	{
			   return 227;
			   break;
	}
	case 86:
	{
			   return 236;
			   break;
	}
	case 87:
	{
			   return 246;
			   break;
	}
	case 88:
	{
			   return 247;
			   break;
	}
	case 89:
	{
			   return 237;
			   break;
	}
	case 90:
	{
			   return 255;
			   break;
	}
	case 219:
	{
			   return 245;
			   break;
	}
	case 221:
	{
			   return 250;
			   break;
	}
	case 186:
	{
			   return 230;
			   break;
	}
	case 222:
	{
			   return 253;
			   break;
	}
	case 188:
	{
				return 225;
				break;
	}
	case 190:
	{
				return 254;
				break;
	}
	default: return 0;
	}
}

const char * name(char st[])
{
	int k = strlen(st);
	if (st[strlen(st)-1] == '\n')
		k--;
	char *str1 = (char*)calloc(k+5, sizeof(char));
	for (int i = 0; i < k; i++)
	{
		str1[i] = st[i];
	}
	str1[k ] = '.';
	str1[k +1] = 't';
	str1[k +2] = 'x';
	str1[k +3] = 't';
	return str1;

}

void WinShow(HWND hwnd)
{
	HDC dc;
	PAINTSTRUCT ps;
	dc = BeginPaint(hwnd, &ps);

	HBRUSH hb;

	hb = (HBRUSH)CreateSolidBrush(RGB(0,255,72));
	SelectObject(dc, hb);

	Rectangle(dc, 1170, 650, 1290, 695);

	Rectangle(dc,1170,600,1290,645);
	HWND st1 = CreateWindow("static", "SHIFT", WS_VISIBLE | WS_CHILD, 1180, 610, 45, 15, hwnd1, (HMENU)1111, NULL, NULL);
	Rectangle(dc, 1190, 550, 1290, 595);
	HWND st2 = CreateWindow("static", "<- ENTER", WS_VISIBLE | WS_CHILD, 1200, 560, 70, 15, hwnd1, (HMENU)1111, NULL, NULL);
	Rectangle(dc, 1215, 500, 1290, 545);
	HWND st3 = CreateWindow("static", "\|/", WS_VISIBLE | WS_CHILD, 1225, 510, 30, 15, hwnd1, (HMENU)1111, NULL, NULL);
	Rectangle(dc, 1200, 450, 1290, 495);
	HWND st4 = CreateWindow("static", "<-Backspace", WS_VISIBLE | WS_CHILD, 1205, 460, 90, 15, hwnd1, (HMENU)1111, NULL, NULL);
	Rectangle(dc, 910, 450, 955, 495);
	Rectangle(dc, 850, 450, 895, 495);
	Rectangle(dc, 790, 450, 835, 495);

	hb = (HBRUSH)CreateSolidBrush(RGB(0, 255, 72));
	Rectangle(dc, 730, 450, 775, 495);
	Rectangle(dc, 670, 450, 715, 495);
	Rectangle(dc, 610, 450, 655, 495);
	Rectangle(dc, 550, 450, 595, 495);
	Rectangle(dc, 490, 450, 535, 495);
	Rectangle(dc, 430, 450, 475, 495);
	Rectangle(dc, 370, 450, 415, 495);
	Rectangle(dc, 310, 450, 355, 495);
	Rectangle(dc, 250, 450, 295, 495);
	// следующий цвет

	EndPaint(hwnd, &ps);
	return 0;
}

void tofile()
{
	FILE *ourfile;
	fopen_s(&ourfile, "Пользователи.txt", "wt");
	count = SendMessage(hListBox, LB_GETCOUNT, NULL, NULL);
	for (int i = 0; i <= count-1; i++)
	{ 
		int len = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)i, NULL);
		char *str1 = (char*)malloc(len*sizeof(char));
		SendMessage(hListBox, LB_GETTEXT, (WPARAM)i, str1);
		fputs(str1, ourfile);
		if (i != count-1)
		{
				if (str1[strlen(str1)-1] !="\n")
				fputc('\n', ourfile);
		}
	}
	fclose(ourfile);
}

void del( char str1[])
{
	remove(str1);
}

void sozdanie(char str1[])
{
	
	FILE *file;
	fopen_s(&file, str1, "w+t");
	fclose(file);
}

void zapoln(char *where)
{
	FILE *file;

	fopen_s(&file, where, "rt");
	while (!feof(file))
	{
		wchar_t res[100];
		char str[100];
		setlocale(LC_ALL, "Rus");
		fgets(str, 100, file);
		if (strcmp("\n", str) != 0)
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)str);
	}
	fclose(file);

}

LRESULT  WINAPI WindProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	else 
	    if (message == WM_COMMAND)
	    {
			switch (LOWORD(wparam)) 
	case bt_idst:
			{
				start = 0;
				bol = 0;
				hListBox = CreateWindow("listbox", NULL,
					WS_CHILD | WS_VISIBLE | LBS_STANDARD |
					LBS_WANTKEYBOARDINPUT,
					150, 30, 400, 400,
					hwnd, 0, hinstance, NULL);
				bt_add = CreateWindow("button", "Добавить", WS_VISIBLE | WS_CHILD, 10, 40, 100, 40, hwnd, (HMENU)bt_idadd, NULL, NULL);
				bt_change = CreateWindow("button", "Изменить", WS_VISIBLE | WS_CHILD, 10, 90, 100, 40, hwnd, (HMENU)bt_idch, NULL, NULL);
				bt_del = CreateWindow("button", "Удалить", WS_VISIBLE | WS_CHILD, 10, 140, 100, 40, hwnd, (HMENU)bt_iddel, NULL, NULL);
				bt_work = CreateWindow("button", "Начать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 40, hwnd, (HMENU)bt_idwork, NULL, NULL);

				DestroyWindow(bt_start);
				zapoln("Пользователи.txt");
				SendMessage(hListBox, LB_SETCURSEL, 0, 0);
				DestroyWindow(st_about);
				bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9943, NULL, NULL);
			
				break; 
	case 9943:
	{
				DestroyWindow(bt_change);
				 DestroyWindow(bt_del);
				 DestroyWindow(bt_work);
				 DestroyWindow(bt_about);
				 DestroyWindow(hListBox);
				 st_ab = CreateWindow("static", "           На данном этапе необходимо выбрать пользователя.\n\nНачать\nЕсли вы уже хоть раз выполняли задание, то ваша учётная запсь существует и вам только необходимо нажать кнопку 'Начать'для наxала работы.\n\nДобавить\nЕсли же вы впервые открываете это приложение и не можете найти себя, то вам всего лишь необходимо нажать на кнопку 'Добавить' и ввести свое имя пользования.\n\nУдалить\nТак же вы можете удалить пользователя, нажав на кнопку 'Удалить', если вам уже не нужен этот профиль или хотите начать заново\n\nИзменить\nЕсли вам уже не нравится ваше имя пользования, то вы, конечно же, можете его поменять, не потеряв данных", WS_VISIBLE | WS_CHILD, 10, 10, 600, 410, hwnd, (HMENU)1481, NULL, NULL);
				 bt_away = CreateWindow("button", "Hазад", WS_VISIBLE | WS_CHILD, 250, 340, 100, 40, hwnd, (HMENU)9013, NULL, NULL);
				 break;
	}
	case 9983:
	{
				 DestroyWindow(bt_change);
				 DestroyWindow(bt_del);
				 DestroyWindow(bt_work);
				 DestroyWindow(bt_about);
				 DestroyWindow(hListBox);
				 st_ab = CreateWindow("static", "           На данном этапе необходимо выбрать упражнение.\n\nНачать\nВыбрав упражнение, которое находится в диапозоне от текeщего, которое находится на странице, до первого, нажать на кнопку 'Начать' и получим окно для выполненния задания. Переход к следующемувозможен только при окончании текущего.\n\nСтатистика\nНажав на пользователя и выбрав кнопку 'Статистика', можно получить полную статистику по выполнению своих упражнений: номер, кол-во ошибок и дата выполнения. Но воспользоваться можно только при выполнении хотя бы одного упражнения\n\nИзменить пользователя\nВернуться в предыдущее окно для авторизации", WS_VISIBLE | WS_CHILD, 10, 10, 600, 410, hwnd, (HMENU)1481, NULL, NULL);
				 bt_away = CreateWindow("button", "Hазад", WS_VISIBLE | WS_CHILD, 250, 340, 100, 40, hwnd, (HMENU)9023, NULL, NULL);
				 break;
	}
	case 9023:
	{
				 fil = name(str1);
				 DestroyWindow(st_ab);
				 DestroyWindow(bt_away);
				 bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9983, NULL, NULL);
				 bt_start = CreateWindow("BUTTON", "Начать", WS_CHILD | WS_VISIBLE, 10, 40, 180, 40, hwnd, (HMENU)1001, NULL, NULL);
				 bt_change = CreateWindow("BUTTON", "Изменить ползователя", WS_CHILD | WS_VISIBLE, 10, 90, 180, 40, hwnd, (HMENU)1010, NULL, NULL);
				 bt_statistic = CreateWindow("BUTTON", "Статистика", WS_CHILD | WS_VISIBLE, 10, 140, 180, 40, hwnd, (HMENU)1011, NULL, NULL);
				 hListBox = CreateWindow("listbox", NULL,
					 WS_CHILD | WS_VISIBLE |
					 LBS_WANTKEYBOARDINPUT | !LBS_SORT,
					 200, 30, 400, 400,
					 hwnd, 0, hinstance, NULL);
				 zapoln("Задания.txt");
				 stat = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 10, 200, 40, 30, hwnd, (HMENU)1111, NULL, NULL);
				 FILE *file;
				 char which[10] = "";
				 fopen_s(&file, fil, "rt");
				 strcpy_s(all, 4, "0");
				 while (!feof(file))
				 {
					 char str[18] = "";
					 setlocale(LC_ALL, "Rus");
					 fgets(str, 18, file);
					 if (strcmp(str, "") != 0)
					 {
						 int j = atoi(&str[0]);
						 if (str[1] != ' ')
							 j += atoi(&str[1]);
						 int l = atoi(all);
						 if (j > l)
							 _itoa_s(j, all, 2, 10);
					 }
				 }
				 int j = atoi(all);
				 j++;
				 _itoa_s(j, all, 2, 10);
				 SetWindowText(stat, all);
				 fclose(file);
				 SendMessage(hListBox, LB_SETCURSEL, 0, 0);
				 upr = 1;
				 break;
	}
	case 9013:
	{			 bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9943, NULL, NULL);
				 bt_add = CreateWindow("button", "Добавить", WS_VISIBLE | WS_CHILD, 10, 40, 100, 40, hwnd, (HMENU)bt_idadd, NULL, NULL);
				 bt_change = CreateWindow("button", "Изменить", WS_VISIBLE | WS_CHILD, 10, 90, 100, 40, hwnd, (HMENU)bt_idch, NULL, NULL);
				 bt_del = CreateWindow("button", "Удалить", WS_VISIBLE | WS_CHILD, 10, 140, 100, 40, hwnd, (HMENU)bt_iddel, NULL, NULL);
				 bt_work = CreateWindow("button", "Начать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 40, hwnd, (HMENU)bt_idwork, NULL, NULL);
				 hListBox = CreateWindow("listbox", NULL,
					 WS_CHILD | WS_VISIBLE | LBS_STANDARD |
					 LBS_WANTKEYBOARDINPUT,
					 150, 30, 400, 400,
					 hwnd, 0, hinstance, NULL);
				 zapoln("Пользователи.txt");
				 SendMessage(hListBox, LB_SETCURSEL, 0, 0);
				DestroyWindow(st_ab);
				DestroyWindow(bt_away);
				break;
	}
			case bt_idadd:
			{
							 setlocale(LC_ALL, "Rus");
							 edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 30, 130, 80, hwnd,NULL, NULL, NULL);
							 DestroyWindow(bt_add);
							 bt_add = CreateWindow("button", "ok", WS_VISIBLE | WS_CHILD, 20, 230, 100, 40, hwnd, (HMENU)bt_idst1, NULL, NULL);
							 bt_cancel = CreateWindow("button", "отмена", WS_VISIBLE | WS_CHILD, 20, 280, 100, 40, hwnd, (HMENU)bt_idcancel, NULL, NULL);
							 DestroyWindow(bt_change);
							 DestroyWindow(bt_del);
							 DestroyWindow(bt_work);
							 DestroyWindow(bt_about);
							 bol = 0;
							 add = 1;
							 new_start = 0;
							 break;
			}
			case bt_iddel:
			{
							 int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
							 if (i >= 0)
							 {
								 int len = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)i, NULL);
								 char *str1 = (char*)malloc((len - 1) * sizeof(char));
								 SendMessage(hListBox, LB_GETTEXT, (WPARAM)i, str1);
								 SendMessage(hListBox, LB_DELETESTRING, (WPARAM)i, 0);
								 del(name(str1));
								 tofile();
							 }
							 else
							 {
								 ShowWindow(hwnd, SW_HIDE);
								 mistake("А что удалять!");
								 ShowWindow(hwnd, SW_SHOW);
								 // необходимо сообщение о ошибке
							 }
							 break;
			}
			case bt_idch:
			{               
							int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
							if (i >= 0)
							{
								add = 1;
								new_start = 0;
								SendMessage(hListBox, LB_SETCARETINDEX, 0, 0);
								setlocale(LC_ALL, "Rus");
								edit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 30, 130, 80, hwnd, NULL, NULL, NULL);
								DestroyWindow(bt_add);
								DestroyWindow(bt_about);
								bt_add = CreateWindow("button", "ok", WS_VISIBLE | WS_CHILD, 20, 230, 100, 40, hwnd, (HMENU)bt_idst1, NULL, NULL);
								bt_cancel = CreateWindow("button", "отмена", WS_VISIBLE | WS_CHILD, 20, 280, 100, 40, hwnd, (HMENU)bt_idcancel, NULL, NULL);
								DestroyWindow(bt_change);
								DestroyWindow(bt_del);
								DestroyWindow(bt_work);
								int len = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)i, NULL);
								char *str1 = (char*)malloc(len*sizeof(char));
								SendMessage(hListBox, LB_GETTEXT, (WPARAM)i, str1);
								SetWindowText(edit, str1);
								bol = 1;
								need = i;
							}
							else
							{
								ShowWindow(hwnd, SW_HIDE);
								mistake("Выберите сперва персонажа!");
								ShowWindow(hwnd, SW_SHOW);
								// необходимо сообщение о ошибке
							}
							break;
			}
			case bt_idst1:
			{
							 setlocale(LC_ALL, "Rus");
							 int len = SendMessage(edit, EM_LINELENGTH, NULL, NULL);
							 if (len > 0)
							 {
								 char *str1 = (char*)malloc((len + 1)*sizeof(char));
								 GetWindowText(edit, str1, len + 1);
								 int find = SendMessage(hListBox, LB_FINDSTRING, 0, str1);
								 if (find != -1)
								 {

									 ShowWindow(hwnd, SW_HIDE);

									 mistake("Пользователь с таким именем существует!");
									 ShowWindow(hwnd, SW_SHOW);
									 break;
								 }
								 add = 0;
								 new_start = 1;
								 if (bol)
								 {
									 int len = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)need, NULL);
									 char *old = (char*)malloc(len - 1 * sizeof(char));
									 SendMessage(hListBox, LB_GETTEXT, (WPARAM)need, old);
									 SendMessage(hListBox, LB_DELETESTRING, (WPARAM)need, 0);
									 rename(name(old), name(str1));
								 }
								 else
								 {
									 sozdanie(name(str1));
								 }
								 SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)str1);
								 DestroyWindow(bt_add);
								 DestroyWindow(bt_cancel);
								 bt_add = CreateWindow("button", "Добавить", WS_VISIBLE | WS_CHILD, 10, 40, 100, 40, hwnd, (HMENU)bt_idadd, NULL, NULL);
								 bt_change = CreateWindow("button", "Изменить", WS_VISIBLE | WS_CHILD, 10, 90, 100, 40, hwnd, (HMENU)bt_idch, NULL, NULL);
								 bt_del = CreateWindow("button", "Удалить", WS_VISIBLE | WS_CHILD, 10, 140, 100, 40, hwnd, (HMENU)bt_iddel, NULL, NULL);
								 bt_work = CreateWindow("button", "Начать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 40, hwnd, (HMENU)bt_idwork, NULL, NULL);
								 DestroyWindow(edit);
								 tofile();
								 bol = 0;
							 }
							 else
							 {
								 ShowWindow(hwnd, SW_HIDE);
								 mistake("Заполните строку!");
								 ShowWindow(hwnd, SW_SHOW);
								 // необходимо сообщение о ошибке
							 }

							 break;
			}
			case bt_idwork:
			{
							  int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
							  if (i >= 0)
							  {
								  
								  int len = SendMessage(hListBox,LB_GETTEXTLEN, (WPARAM)i, NULL);
								  char *str2 = (char*)malloc(len-1*sizeof(char));
								  SendMessage(hListBox, LB_GETTEXT, (WPARAM)i, str2);
								  fil = (char*)malloc(len - 1 * sizeof(char));
								  str1 = str2;
								  fil = name(str2);
								  DestroyWindow(hListBox);
								  DestroyWindow(bt_add);
								  DestroyWindow(bt_change);
								  DestroyWindow(bt_del);
								  DestroyWindow(bt_work);
								  DestroyWindow(bt_about);
								  bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9983, NULL, NULL);
								  bt_start = CreateWindow("BUTTON", "Начать", WS_CHILD | WS_VISIBLE, 10, 40, 180, 40, hwnd, (HMENU)1001, NULL, NULL);
								  bt_change = CreateWindow("BUTTON", "Изменить ползователя", WS_CHILD | WS_VISIBLE, 10, 90, 180, 40, hwnd, (HMENU)1010, NULL, NULL);
								  bt_statistic = CreateWindow("BUTTON", "Статистика", WS_CHILD | WS_VISIBLE, 10, 140, 180, 40, hwnd, (HMENU)1011, NULL, NULL);
								  hListBox = CreateWindow("listbox", NULL,
									  WS_CHILD | WS_VISIBLE | 
									  LBS_WANTKEYBOARDINPUT| !LBS_SORT,
									  200, 30, 400, 400,
									  hwnd, 0, hinstance, NULL);
								  zapoln("Задания.txt");
								  stat = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 10, 200, 40, 30, hwnd, (HMENU)1111, NULL, NULL);
								  FILE *file;
								  char which[10]="";
								  fopen_s(&file, fil, "rt");
								  strcpy_s(all, 4, "0");
								  while (!feof(file))
								  {
									  char str[18]="";
									  setlocale(LC_ALL, "Rus");
									  fgets(str, 18, file);
									  if (strcmp(str, "") != 0)
									  {
										  int j = atoi(&str[0]) ;
										  if (str[1]!=' ')
											  j += atoi(&str[1]);
										  int l = atoi(all);
										  if (j > l)
											  _itoa_s(j, all, 2, 10);
									  }
								  }
								  int j = atoi(all);
								  j++;
								  _itoa_s(j, all, 2, 10);
								  SetWindowText(stat, all);
								  fclose(file);
								  SendMessage(hListBox, LB_SETCURSEL, 0, 0);
								  upr = 1;
							  }
							  else
							  {
								  ShowWindow(hwnd, SW_HIDE);
								  mistake("Вам надо выбрать себя!");
								  ShowWindow(hwnd, SW_SHOW);
								  // необходимо сообщение о ошибке
							  }
							  break;
			}
			case bt_idcancel:
			{
								DestroyWindow(bt_add);
								DestroyWindow(bt_cancel);
								bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9943, NULL, NULL);
								bt_add = CreateWindow("button", "Добавить", WS_VISIBLE | WS_CHILD, 10, 40, 100, 40, hwnd, (HMENU)bt_idadd, NULL, NULL);
								bt_change = CreateWindow("button", "Изменить", WS_VISIBLE | WS_CHILD, 10, 90, 100, 40, hwnd, (HMENU)bt_idch, NULL, NULL);
								bt_del = CreateWindow("button", "Удалить", WS_VISIBLE | WS_CHILD, 10, 140, 100, 40, hwnd, (HMENU)bt_iddel, NULL, NULL);
								bt_work = CreateWindow("button", "Начать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 40, hwnd,(HMENU) bt_idwork, NULL, NULL);
								DestroyWindow(edit);
								bol = 0;
								break;
			}
			case 1010:// выход из выбора упражнений
			{
						  upr = 0;
						  new_start = 1;
						 DestroyWindow(stat);
						 DestroyWindow(bt_change);
						 DestroyWindow(bt_start);
						 DestroyWindow(bt_statistic);
						 DestroyWindow(hListBox);
						 DestroyWindow(bt_about);
						 hListBox = CreateWindow("listbox", NULL,
							 WS_CHILD | WS_VISIBLE | LBS_STANDARD |
							 LBS_WANTKEYBOARDINPUT,
							 150, 30, 400, 400,
							 hwnd, 0, hinstance, NULL);
						 bt_add = CreateWindow("button", "Добавить", WS_VISIBLE | WS_CHILD, 10, 40, 100, 40, hwnd, (HMENU)bt_idadd, NULL, NULL);
						 bt_change = CreateWindow("button", "Изменить", WS_VISIBLE | WS_CHILD, 10, 90, 100, 40, hwnd, (HMENU)bt_idch, NULL, NULL);
						 bt_del = CreateWindow("button", "Удалить", WS_VISIBLE | WS_CHILD, 10, 140, 100, 40, hwnd, (HMENU)bt_iddel, NULL, NULL);
						 bt_work = CreateWindow("button", "Начать", WS_VISIBLE | WS_CHILD, 10, 190, 100, 40, hwnd, (HMENU)bt_idwork, NULL, NULL);
						 bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9943, NULL, NULL);
						 DestroyWindow(bt_start);
						 zapoln("Пользователи.txt");
						 int i = SendMessage(hListBox, LB_FINDSTRING, 0, str1);
						 SendMessage(hListBox, LB_SETCURSEL, i, 0);
						 break;
			}
			case 1001:// начало работы упражнения
			{
						  int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
						  if (i < atoi(all))
						  {
							  upr = 0;
							  zadanie = i;
							  DestroyWindow(bt_change);
							  DestroyWindow(bt_start);
							  DestroyWindow(bt_statistic);
							  DestroyWindow(hListBox);
							  DestroyWindow(stat);
							  ShowWindow(hwnd, SW_HIDE);
							  hwnd1 = CreateWindow("My Window", "", WS_TILEDWINDOW, 0, 0, 1500, 800, NULL, NULL, NULL, NULL);
							  ShowWindow(hwnd1, SW_SHOW);
							  
							  bt_start = CreateWindow("button", "Заново", WS_VISIBLE | WS_CHILD, 10, 10, 100, 40, hwnd1, (HMENU)0101, NULL, NULL);
							  bt_cancel = CreateWindow("button", "Выход", WS_VISIBLE | WS_CHILD, 10, 50, 100, 40, hwnd1, (HMENU)0102, NULL, NULL);
							  stat = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 200, 10, 1000, 400, hwnd1, (HMENU)1111, NULL, NULL);
							  st = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 90, 100, 10, 20, hwnd1, (HMENU)1999, NULL, NULL);
							  HWND st2 = CreateWindow("static", "Ошибок", WS_VISIBLE | WS_CHILD, 10, 100, 80, 20, hwnd1, (HMENU)1999, NULL, NULL);
							  HWND w = CreateWindow("static", "Допустимое количество ошибок - 30, иначе начинаем заново.\n Чтобы достигнуть результата следуйте основным правилам:\n1. Нельзя смотреть на клавиатуру. Найдите правильное расположение для ваших пальцев (ФЫВА и ОЛДЖ) и после каждого нажатия клавиши дожны вернуться в изначальную позицию\n2. Делайте перерывы. Нельзя переутомляться, а то ошибок будет больше\n\n Результаты будут сохраняться только после выполнения задания", WS_VISIBLE | WS_CHILD, 10, 145, 180, 400, hwnd1, (HMENU)1999, NULL, NULL);
							  FILE *file;
							  char *name = (char*)malloc((sizeof(i+1)+5)*sizeof(char));
							  i++;
							  _itoa_s(i, name, sizeof(i + 1)  + 5, 10);
							  i = strlen(name);
							  name[i] = '.';
							  name[i+ 1] = 't';
							  name[i + 2] = 'x';
							  name[i + 3] = 't';
							  name[i + 4] = '\0';
							  char n[50];
							  fopen_s(&file, name, "rt");
							  text = (char*)malloc(1000*sizeof(char));
							  text[0] = '|';
							  i = 1;
							  while (!feof(file))
							  {
								  fgets(n, 50, file);
								  n[strlen(n)] = '\0';
								  int k;
								  for (k = 0; k < strlen(n); i++, k++)
									  text[i] = n[k];
							  }
							  text[i] = '\0';
							  zapas = (char*)malloc(1000 * sizeof(char));
							  strcpy_s(zapas, 1000, text);
							  SetWindowText(stat,text);
							  oshib[0]='0';
							  oshib[1] = '\0';

							  SetWindowText(st, oshib);
							  fclose(file);
							  bol = 1;
							  
							  position = 1;

							  
						  }
						  else
						  {
							  upr = 0;
							  ShowWindow(hwnd, SW_HIDE);
							  mistake("Вы еще не можете его начать!");
							  ShowWindow(hwnd, SW_SHOW);
							  upr = 1;
							  
							  // сообщение об ошибке
						  }
						 break;

			}
			case 0101:// заново
			{
  						 *oshib = '0';
						 SetWindowText(st, oshib);
						 SetWindowText(stat, zapas);
						 strcpy_s(text, 1000, zapas);
						 position = 1;
						 SetFocus(hwnd);
						 break;
			}
			case 0102:// выход из упражнения
			{
						 ShowWindow(hwnd, SW_HIDE);
						 hwnd = CreateWindow("My Window", "", WS_TILEDWINDOW, 10, 10, 640, 480, NULL, NULL, NULL, NULL);
						 ShowWindow(hwnd, SW_SHOW);
						 upr = 1;
						 bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9943, NULL, NULL);
						 bt_start = CreateWindow("BUTTON", "Начать", WS_CHILD | WS_VISIBLE, 10, 40, 180, 40, hwnd, (HMENU)1001, NULL, NULL);
						 bt_change = CreateWindow("BUTTON", "Изменить ползователя", WS_CHILD | WS_VISIBLE, 10, 90, 180, 40, hwnd, (HMENU)1010, NULL, NULL);
						 bt_statistic = CreateWindow("BUTTON", "Статистика", WS_CHILD | WS_VISIBLE, 10, 140, 180, 40, hwnd, (HMENU)1011, NULL, NULL);
						 hListBox = CreateWindow("listbox", NULL,
							 WS_CHILD | WS_VISIBLE |
							 LBS_WANTKEYBOARDINPUT | !LBS_SORT,
							 200, 30, 400, 400,
							 hwnd, 0, hinstance, NULL);
						 zapoln("Задания.txt");
						 stat = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 10, 200, 40, 30, hwnd, (HMENU)1111, NULL, NULL);
						 SetWindowText(stat, all);
						 bol = 0;
						 break;
			}
			case 1011:// просмотр статистики по упражнениям
			{
						  if (atoi(all) != 1)
						  {
							  upr = 0;
							  DestroyWindow(bt_about);
							  DestroyWindow(bt_change);
							  DestroyWindow(bt_start);
							  DestroyWindow(bt_statistic);
							  DestroyWindow(hListBox);
							  DestroyWindow(stat); 
							  hwndList = CreateWindow(WC_LISTVIEW, "", WS_VISIBLE | WS_CHILD | LVS_SHOWSELALWAYS | LVS_REPORT | WS_BORDER | LVS_EDITLABELS, 200,10, 420,400, hwnd, (HMENU)344, NULL, NULL);
							  stolb(hwndList);
							  bt_work = CreateWindow("button", "Назад", WS_VISIBLE | WS_CHILD, 10, 190, 100, 40, hwnd, (HMENU)228, NULL, NULL);
							  int y = 0;
							  FILE *file;
							  fopen_s(&file, fil, "rt");
							  while (!feof(file))
							  {
								  char str[18] = "";
								  fgets(str, 18, file);
								  if (strcmp(str, "") != 0)
								  {
									  strocy(hwndList, str, y);
									  y++;
								  }

							  }
							  fclose(file);
						  }
						  else
						  {
							  ShowWindow(hwnd, SW_HIDE);
							  mistake("Cтатистика пуста! Начните проходить задания");
							  ShowWindow(hwnd, SW_SHOW);
						  }
						 break;
			}
			case 911:
			{
						DestroyWindow(hwnd);
						break;
			}
			case 228:// выход из статистики
			{
						 upr = 1;
						DestroyWindow(hwndList);
						DestroyWindow(bt_work);
						bt_about = CreateWindow("button", "Help", WS_VISIBLE | WS_CHILD, 10, 240, 100, 40, hwnd, (HMENU)9983, NULL, NULL);
						bt_start = CreateWindow("BUTTON", "Начать", WS_CHILD | WS_VISIBLE, 10, 40, 180, 40, hwnd, (HMENU)1001, NULL, NULL);
						bt_change = CreateWindow("BUTTON", "Изменить ползователя", WS_CHILD | WS_VISIBLE, 10, 90, 180, 40, hwnd, (HMENU)1010, NULL, NULL);
						bt_statistic = CreateWindow("BUTTON", "Статистика", WS_CHILD | WS_VISIBLE, 10, 140, 180, 40, hwnd, (HMENU)1011, NULL, NULL);
						hListBox = CreateWindow("listbox", NULL,
							WS_CHILD | WS_VISIBLE |
							LBS_WANTKEYBOARDINPUT | !LBS_SORT,
							200, 30, 400, 400,
							hwnd, 0, hinstance, NULL);
						zapoln("Задания.txt");
						stat = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 10, 200, 40, 30, hwnd, (HMENU)1111, NULL, NULL);
						FILE *file;
						char which[10] = "";
						fopen_s(&file, fil, "rt");
						while (!feof(file))
						{
							char str[10] = "";
							setlocale(LC_ALL, "Rus");
							fgets(str, 10, file);
							if (strcmp(str, "") != 0)
								strcpy_s(which, 10, str);
						}
						
						SetWindowText(stat, all);
						fclose(file);
						SendMessage(hListBox, LB_SETCURSEL, 0, 0);
						break;
			}
			default:
				break;
		}
		
	}
	else if (message == WM_KEYDOWN)
	{
		if (bol) // работа с упражнениями
		{
			int i = wparam;
			i = opredelenie(i);
			int k = (int)text[position];
			if (k < 0)
				k += 256;
			if (k == 10)
				k += 22;
			if (i==k)
			{
				text[position-1]=text[position];
				position++;
				if(position==strlen(text))
				{
 				    ShowWindow(hwnd, SW_HIDE);
					
				    mistake("Вы прошли задание");
					
					bol = 0;
				
 					int chislo = atoi(all);
					chislo++;
					_itoa_s(chislo, all, sizeof(all), 10);
					hwnd = CreateWindow("My Window", "", WS_TILEDWINDOW, 10, 10, 640, 480, NULL, NULL, NULL, NULL);
					ShowWindow(hwnd, SW_SHOW);

					bt_start = CreateWindow("BUTTON", "Начать", WS_CHILD | WS_VISIBLE, 10, 40, 180, 40, hwnd, (HMENU)1001, NULL, NULL);
					bt_change = CreateWindow("BUTTON", "Изменить ползователя", WS_CHILD | WS_VISIBLE, 10, 90, 180, 40, hwnd, (HMENU)1010, NULL, NULL);
					bt_statistic = CreateWindow("BUTTON", "Статистика", WS_CHILD | WS_VISIBLE, 10, 140, 180, 40, hwnd, (HMENU)1011, NULL, NULL);
					hListBox = CreateWindow("listbox", NULL,
						WS_CHILD | WS_VISIBLE |
						LBS_WANTKEYBOARDINPUT | !LBS_SORT,
						200, 30, 400, 400,
						hwnd, 0, hinstance, NULL);
					zapoln("Задания.txt");
					stat = CreateWindow("static", "", WS_VISIBLE | WS_CHILD, 10, 200, 40, 30, hwnd, (HMENU)1111, NULL, NULL);
					int which = atoi(all);
					if (zadanie == chislo)
					{
						which++;
						_itoa_s(which, all, sizeof(all), 10);
					}
					SetWindowText(stat, all);
					nomerzadaniya();
					//работа с файлом
					
					SendMessage(hListBox, LB_SETCURSEL, 0, 0);

				}
				else
				{
					text[position-1]='|';
					SetWindowText(stat, text);
				}
				 
			}
			else 
			{
				bol = 0;
				m = 1;
			    ShowWindow(hwnd, SW_HIDE);
				mistake("Неверный символ!");
				ShowWindow(hwnd, SW_SHOW);
				
				m = 0;
				int i = atoi(oshib);
 				i++;

 				_itoa_s(i, oshib, sizeof(oshib), 10);
				DestroyWindow(st);
				st = CreateWindow("static",oshib, WS_VISIBLE | WS_CHILD, 90, 100, 20, 20, hwnd, NULL, NULL, NULL);
				if (i == 20)
				{
					nelzy = 1;
					ShowWindow(hwnd, SW_HIDE);
					mistake("Предел ошибок! Начните заново");
					ShowWindow(hwnd, SW_SHOW);
				}
				else
 					bol = 1;
			}
		}
		else 
		if (m)
		{
			if (wparam == 13)
			{
				DestroyWindow(hwnd);
			}
		}
		else 
		if (nelzy)
		{
			ShowWindow(hwnd, SW_HIDE);
			mistake("Предел ошибок! Начните заново");
			ShowWindow(hwnd, SW_SHOW);
		}
		else if (start)
		{
			if (wparam == 13)
			{
				start = 0;
				new_start = 1;
				message = WM_COMMAND;
				wparam = bt_idst;
				WindProc(hwnd, message, wparam, lparam);
			}
		}
		else if (new_start)
		{
			if (wparam == 13)
			{
				new_start = 0;
				message = WM_COMMAND;
				wparam = bt_idwork;
				WindProc(hwnd, message, wparam, lparam);
			}
			if (wparam == 40)
			{
				int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				int j = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				if (j-1!=i)
				  i++;
				SendMessage(hListBox, LB_SETCURSEL, i, 0);
			}
			if (wparam == 38)
			{
				int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if (i!=0)
					i--;
				SendMessage(hListBox, LB_SETCURSEL, i, 0);
			}

	}
		else if (add)
		{
			if (wparam == 13)
			{
				
				message = WM_COMMAND;
				wparam = bt_idst1;
				WindProc(hwnd, message, wparam, lparam);
			}
			else if (wparam == 27)
			{
				add = 0;
				new_start = 1;
				message = WM_COMMAND;
				wparam = bt_idcancel;
				WindProc(hwnd, message, wparam, lparam);
			}
		}
		else if (upr)
		{
			if (wparam == 13)
			{

				message = WM_COMMAND;
				wparam = 1001;
				WindProc(hwnd, message, wparam, lparam);
			}
			else if (wparam == 40)
			{
				int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				int j = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				if (j - 1 != i)
					i++;
				SendMessage(hListBox, LB_SETCURSEL, i, 0);
			}
			else if (wparam == 38)
			{
				int i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				if (i != 0)
					i--;
				SendMessage(hListBox, LB_SETCURSEL, i, 0);
			}
			else if (wparam == 27)
			{
				message = WM_COMMAND;
				wparam = 1010;
				WindProc(hwnd, message, wparam, lparam);
			}
		}
	}
	else if (message == LBN_DBLCLK)
	{
	}
	else
		return DefWindowProcA(hwnd, message, wparam, lparam);
}

INT CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	FreeConsole();

	HBRUSH hb = (HBRUSH)CreateSolidBrush(RGB(0, 4, 255));
	memset(&wnd, 0, sizeof(WNDCLASSA));
	wnd.lpszClassName = "My Window";
	wnd.hbrBackground = hb;
	wnd.lpfnWndProc = WindProc;
	RegisterClassA(&wnd);


	hwnd = CreateWindow("My Window", "", WS_TILEDWINDOW, 10, 10, 640, 480, NULL, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);

	bt_start = CreateWindow("button", "Начать", WS_VISIBLE | WS_CHILD, 405, 150, 200, 40, hwnd, bt_idst, NULL, NULL);
	st_about = CreateWindow("static", "         Приветствую вас в нашей программе!\n\n\n Здесь вы сможет научиться основам слепого метода печатания.\n\n Во времена технического прогресса возможность быстрого и правильного печатания очень востребована и приветствуется во многих сферах жизни.\n\n\n       Что же вам надо для прекрасной учёбы?\n\n Всего лишь немного времени каждый день для тренировок, усидчивости и выполнение всех упражнений\nНаш курс не очень большой, но он наполнен очень интересными и полезными заданиями. Чтобы получить необходимые навыки, надо пройти весь курс, не лениться и ни в коем случае не забрасывать программу.\n\n\n            Удачи! Я уверен: вы справитесь!", WS_VISIBLE | WS_CHILD, 10, 40, 390, 380, hwnd, (HMENU)1111, NULL, NULL);

	MSG msg;
	m = 0;
	nelzy = 0;
	start = 1;
	add = 0;
	upr = 0;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}