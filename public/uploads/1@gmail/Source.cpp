#include <iostream>
#include <iomanip>
#include "mylib.h"
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

const int MAXLOP = 100;
const string PHAI[] = { "Nam", "Nu" };

//Mon Hoc
struct MONHOC
{
	char MAMH[11];
	char TENMH[51];
	int STCLT;
	int STCTH;
};

struct NODEMONHOC
{
	MONHOC monhoc;
	NODEMONHOC* left;
	NODEMONHOC* right;
};
typedef struct NODEMONHOC* PTRMONHOC;

//Diem
struct DIEMMONHOC
{
	char MAMH[11];
	int LAN;
	float DIEM;
};

struct NODEDIEM
{
	DIEMMONHOC diem;
	NODEDIEM* next;
};
typedef struct NODEDIEM* PTRDIEM;

//Sinhvien
struct SINHVIEN
{
	char MASV[11];
	char HO[51];
	char TEN[21];
	int PHAI;
	char SODT[12];
	PTRDIEM ptrdiem;
};

struct NODESINHVIEN
{
	SINHVIEN sinhvien;
	NODESINHVIEN* next;
};
typedef struct NODESINHVIEN* PTRSV;

//Lop
struct LOP
{
	char MALOP[11];
	char TENLOP[51];
	int namnhaphoc;
	PTRSV ptrsv;
};

struct DSLOP
{
	int n = 0;
	LOP nodes[MAXLOP];
};

//GiaoDien
const int so_itemchinh = 13;
const int dongmenuchinh = 15;
const int dong = 2;
const int cot = 20;
const int Up = 72;
const int UpTrang = 328;
const int Down = 80;
const int DownTrang = 336;
const int F1 = 315;
const int F2 = 316;
const int F3 = 317;
const int F4 = 318;
char thucdonchinh[so_itemchinh][50] = { "1. NHAP DANH SACH LOP             ",
"2. IN DANH SACH LOP THEO NIEN KHOA",
"3. NHAP SINH VIEN                 ",
"4. IN DANH SACH SINH VIEN 1 LOP   ",
"5. NHAP MON HOC                   ",
"6. IN DANH SACH MON HOC           ",
"7. NHAP DIEM MON HOC              ",
"8. IN BANG DIEM MON HOC MOT LOP   ",
"9. IN BANG DIEM TB MOT LOP        ",
"10.IN BANG TONG KET MOT LOP       ",
"11.GHI DATA VAO FILE              ",
"12.DOC DATA TU FILE               ",
"13.THOAT CHUONG TRINH             " };

void Normal() {
	SetColor(15);
	SetBGColor(19);
}

void HighLight() {
	SetColor(15);
	SetBGColor(5);
}

int MenuDongChinh(char td[so_itemchinh][50]){
	Normal();
	system("cls");
	gotoxy(cot + 3, 10); SetColor(14); cout << "DE TAI: QUAN LY SINH VIEN";
	Normal();
	int chon = 0; int i;
	for (i = 0; i < so_itemchinh; i++)
	{
		gotoxy(cot, dongmenuchinh + i);
		cout << td[i];
	}
	HighLight();
	gotoxy(cot, dongmenuchinh + chon);
	cout << td[chon];
	char kytu;
	do {
		kytu = _getch();
		if (kytu == 0) kytu = _getch();
		switch (kytu) {
		case Up:if (chon + 1 >1)
		{
			Normal();
			gotoxy(cot, dongmenuchinh + chon);
			cout << td[chon];
			chon--;
			HighLight();
			gotoxy(cot, dongmenuchinh + chon);
			cout << td[chon];
		}
				break;
		case Down:if (chon + 1 < so_itemchinh)
		{
			Normal();
			gotoxy(cot, dongmenuchinh + chon);
			cout << td[chon];
			chon++;
			HighLight();
			gotoxy(cot, dongmenuchinh + chon);
			cout << td[chon];
		}
				  break;
		case 13: return chon + 1;
		}  // end switch
	} while (1);
}

int keyPressed(){
	int a = _getch();
	if (a == 0 || a == 224){
		a = 256 + _getch();
	}
	return a;
}

void ChuanHoaChuoi(char *c1, char *c2)
{
	int j = 0;
	for (int i = 0; i < strlen(c1); i++)
	{
		if (c1[i] != ' ')
		{
			c2[j++] = c1[i];
		}
	}
	c2[j] = '\0';
}

void KeKhungVuong1Vien(int x1, int x2, int y1, int y2, int mau)
{
	gotoxy(x1, y1); cout << char(218);
	gotoxy(x1, y2); cout << char(192);
	gotoxy(x2, y1); cout << char(191);
	gotoxy(x2, y2); cout << char(217);
	for (int i = x1 + 1; i <= x2 - 1; i++) {
		gotoxy(i, y1); cout << char(196);
		gotoxy(i, y2); cout << char(196);
	}
}

void GiaoDienNhapLop()
{
	Normal();
	system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "THEM LOP" << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(20, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);

	gotoxy(20, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(20, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(20, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(8, 16); cout << "MA LOP";
	gotoxy(30, 16); cout << "TEN LOP";
	gotoxy(51, 16); cout << "NAM HOC";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM LOP";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA LOP";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH LOP";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienXoaLop()
{
	Normal();
	system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "XOA LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA LOP: ";
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(20, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);

	gotoxy(20, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(20, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(20, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(8, 16); cout << "MA LOP";
	gotoxy(30, 16); cout << "TEN LOP";
	gotoxy(51, 16); cout << "NAM HOC";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM LOP";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA LOP";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH LOP";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienHieuChinhLop()
{
	Normal();
	system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "HIEU CHINH LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA LOP: ";
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(20, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);

	gotoxy(20, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(20, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(20, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(8, 16); cout << "MA LOP";
	gotoxy(30, 16); cout << "TEN LOP";
	gotoxy(51, 16); cout << "NAM HOC";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM LOP";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA LOP";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH LOP";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienDSLop()
{
	Normal();
	system("cls");
	gotoxy(cot + 3, dong); SetColor(14); cout << "IN DANH SACH LOP THEO NIEN KHOA" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "NIEN KHOA: " << endl; cout << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(20, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);

	gotoxy(20, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(20, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(20, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(8, 16); cout << "MA LOP";
	gotoxy(30, 16); cout << "TEN LOP";
	gotoxy(51, 16); cout << "NAM HOC";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "IN DS LOP THEO NK";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienNhapSinhVien()
{
	Normal();
	system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "THEM SINH VIEN" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA LOP: " << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(13, 15); cout << char(194);
	gotoxy(30, 15); cout << char(194);
	gotoxy(43, 15); cout << char(194);
	gotoxy(50, 15); cout << char(194);

	gotoxy(13, 43); cout << char(193);
	gotoxy(30, 43); cout << char(193);
	gotoxy(43, 43); cout << char(193);
	gotoxy(50, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(13, i); cout << char(179);
		gotoxy(30, i); cout << char(179);
		gotoxy(43, i); cout << char(179);
		gotoxy(50, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(13, 17); cout << char(197);
	gotoxy(30, 17); cout << char(197);
	gotoxy(43, 17); cout << char(197);
	gotoxy(50, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(5, 16); cout << "MA SV";
	gotoxy(20, 16); cout << "HO SV";
	gotoxy(34, 16); cout << "TEN SV";
	gotoxy(44, 16); cout << "P(0/1)";
	gotoxy(56, 16); cout << "SDT";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM SV LOP HIEN TAI";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA SV";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH SV";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienXoaSinhVien()
{
	Normal();
	system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "XOA SINH VIEN" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA SV : " << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(13, 15); cout << char(194);
	gotoxy(30, 15); cout << char(194);
	gotoxy(43, 15); cout << char(194);
	gotoxy(50, 15); cout << char(194);

	gotoxy(13, 43); cout << char(193);
	gotoxy(30, 43); cout << char(193);
	gotoxy(43, 43); cout << char(193);
	gotoxy(50, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(13, i); cout << char(179);
		gotoxy(30, i); cout << char(179);
		gotoxy(43, i); cout << char(179);
		gotoxy(50, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(13, 17); cout << char(197);
	gotoxy(30, 17); cout << char(197);
	gotoxy(43, 17); cout << char(197);
	gotoxy(50, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(5, 16); cout << "MA SV";
	gotoxy(20, 16); cout << "HO SV";
	gotoxy(34, 16); cout << "TEN SV";
	gotoxy(44, 16); cout << "P(0/1)";
	gotoxy(56, 16); cout << "SDT";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM SV";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA SV LOP HIEN TAI";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH SV";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienHieuChinhSinhVien()
{
	Normal();
	system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "HIEU CHINH SINH VIEN" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA SV : ";
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(13, 15); cout << char(194);
	gotoxy(30, 15); cout << char(194);
	gotoxy(43, 15); cout << char(194);
	gotoxy(50, 15); cout << char(194);

	gotoxy(13, 43); cout << char(193);
	gotoxy(30, 43); cout << char(193);
	gotoxy(43, 43); cout << char(193);
	gotoxy(50, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(13, i); cout << char(179);
		gotoxy(30, i); cout << char(179);
		gotoxy(43, i); cout << char(179);
		gotoxy(50, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(13, 17); cout << char(197);
	gotoxy(30, 17); cout << char(197);
	gotoxy(43, 17); cout << char(197);
	gotoxy(50, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(5, 16); cout << "MA SV";
	gotoxy(20, 16); cout << "HO SV";
	gotoxy(34, 16); cout << "TEN SV";
	gotoxy(44, 16); cout << "P(0/1)";
	gotoxy(56, 16); cout << "SDT";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM SV";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA SV";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH SV LOP HT";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienDSSVmotlop()
{
	Normal(); system("cls");
	gotoxy(cot + 3, dong); SetColor(14); cout << "IN DANH SACH SINH VIEN 1 LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA LOP: " << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(13, 15); cout << char(194);
	gotoxy(30, 15); cout << char(194);
	gotoxy(43, 15); cout << char(194);
	gotoxy(50, 15); cout << char(194);

	gotoxy(13, 43); cout << char(193);
	gotoxy(30, 43); cout << char(193);
	gotoxy(43, 43); cout << char(193);
	gotoxy(50, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(13, i); cout << char(179);
		gotoxy(30, i); cout << char(179);
		gotoxy(43, i); cout << char(179);
		gotoxy(50, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(13, 17); cout << char(197);
	gotoxy(30, 17); cout << char(197);
	gotoxy(43, 17); cout << char(197);
	gotoxy(50, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(5, 16); cout << "MA SV";
	gotoxy(20, 16); cout << "HO SV";
	gotoxy(34, 16); cout << "TEN SV";
	gotoxy(44, 16); cout << "P(0/1)";
	gotoxy(56, 16); cout << "SDT";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "IN DANH SACH SV LOP";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F4"; gotoxy(80, 24); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 27, 29, 14);
	gotoxy(70, 28); cout << "UP/DOWN"; gotoxy(80, 28); cout << "CHUYEN TRANG";
}

void GiaoDienNhapMonHoc()
{
	Normal(); system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "THEM MON HOC" << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(15, 15); cout << char(194);
	gotoxy(40, 15); cout << char(194);
	gotoxy(53, 15); cout << char(194);

	gotoxy(15, 43); cout << char(193);
	gotoxy(40, 43); cout << char(193);
	gotoxy(53, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(15, i); cout << char(179);
		gotoxy(40, i); cout << char(179);
		gotoxy(53, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(15, 17); cout << char(197);
	gotoxy(40, 17); cout << char(197);
	gotoxy(53, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(6, 16); cout << "MA MH";
	gotoxy(25, 16); cout << "TEN MH";
	gotoxy(45, 16); cout << "STCLT";
	gotoxy(57, 16); cout << "STCTH";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM MH";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA MH";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH MH";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienXoaMonHoc()
{
	Normal(); system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "XOA MON HOC" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA MH: " << endl; cout << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(15, 15); cout << char(194);
	gotoxy(40, 15); cout << char(194);
	gotoxy(53, 15); cout << char(194);

	gotoxy(15, 43); cout << char(193);
	gotoxy(40, 43); cout << char(193);
	gotoxy(53, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(15, i); cout << char(179);
		gotoxy(40, i); cout << char(179);
		gotoxy(53, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(15, 17); cout << char(197);
	gotoxy(40, 17); cout << char(197);
	gotoxy(53, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(6, 16); cout << "MA MH";
	gotoxy(25, 16); cout << "TEN MH";
	gotoxy(45, 16); cout << "STCLT";
	gotoxy(57, 16); cout << "STCTH";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM MH";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA MH";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH MH";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
	gotoxy(3, 18);
}

void GiaoDienHieuChinhMonHoc()
{
	Normal(); system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "HIEU CHINH MON HOC" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA MH:";
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(15, 15); cout << char(194);
	gotoxy(40, 15); cout << char(194);
	gotoxy(53, 15); cout << char(194);

	gotoxy(15, 43); cout << char(193);
	gotoxy(40, 43); cout << char(193);
	gotoxy(53, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(15, i); cout << char(179);
		gotoxy(40, i); cout << char(179);
		gotoxy(53, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(15, 17); cout << char(197);
	gotoxy(40, 17); cout << char(197);
	gotoxy(53, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(6, 16); cout << "MA MH";
	gotoxy(25, 16); cout << "TEN MH";
	gotoxy(45, 16); cout << "STCLT";
	gotoxy(57, 16); cout << "STCTH";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM MH";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2"; gotoxy(80, 20); cout << "XOA MH";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH MH";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
	gotoxy(3, 18);
}

void GiaoDienDSMonHoc()
{
	Normal();
	system("cls");
	gotoxy(cot + 3, dong); SetColor(14); cout << "IN DANH SACH MON HOC" << endl; cout << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(15, 15); cout << char(194);
	gotoxy(40, 15); cout << char(194);
	gotoxy(53, 15); cout << char(194);

	gotoxy(15, 43); cout << char(193);
	gotoxy(40, 43); cout << char(193);
	gotoxy(53, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(15, i); cout << char(179);
		gotoxy(40, i); cout << char(179);
		gotoxy(53, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(15, 17); cout << char(197);
	gotoxy(40, 17); cout << char(197);
	gotoxy(53, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(6, 16); cout << "MA MH";
	gotoxy(25, 16); cout << "TEN MH";
	gotoxy(45, 16); cout << "STCLT";
	gotoxy(57, 16); cout << "STCTH";

	gotoxy(72, 24); cout << "F4"; gotoxy(80, 24); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 27, 29, 14);
	gotoxy(70, 28); cout << "UP/DOWN"; gotoxy(80, 28); cout << "CHUYEN TRANG";
	gotoxy(3, 18);
}

void GiaoDienNhapDiem()
{
	Normal(); system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "THEM DIEM MON HOC" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "NHAP MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA MON HOC : " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "LAN THI    : " << endl; cout << endl;

	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(7, 15); cout << char(194);
	gotoxy(22, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);
	gotoxy(58, 15); cout << char(194);

	gotoxy(7, 43); cout << char(193);
	gotoxy(22, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	gotoxy(58, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(7, i); cout << char(179);
		gotoxy(22, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(58, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(7, 17); cout << char(197);
	gotoxy(22, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(58, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(3, 16); cout << "STT";
	gotoxy(13, 16); cout << "MA SV";
	gotoxy(32, 16); cout << "HO SV";
	gotoxy(49, 16); cout << "TEN SV";
	gotoxy(60, 16); cout << "DIEM";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM DIEM SV";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH DIEM SV";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienHieuChinhDiem()
{
	Normal(); system("cls");
	gotoxy(cot + 10, dong); SetColor(14); cout << "HIEU CHINH DIEM MH" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "NHAP MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA MON HOC : " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "LAN THI    : ";
	gotoxy(30, wherey()); cout << "NHAP MA SV: ";
	cout << endl << endl;
	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(7, 15); cout << char(194);
	gotoxy(22, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);
	gotoxy(58, 15); cout << char(194);

	gotoxy(7, 43); cout << char(193);
	gotoxy(22, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	gotoxy(58, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(7, i); cout << char(179);
		gotoxy(22, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(58, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(7, 17); cout << char(197);
	gotoxy(22, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(58, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(3, 16); cout << "STT";
	gotoxy(13, 16); cout << "MA SV";
	gotoxy(32, 16); cout << "HO SV";
	gotoxy(49, 16); cout << "TEN SV";
	gotoxy(60, 16); cout << "DIEM";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "THEM DIEM SV";
	KeKhungVuong1Vien(70, 75, 19, 21, 14);
	gotoxy(72, 20); cout << "F2";
	KeKhungVuong1Vien(70, 75, 23, 25, 14);
	gotoxy(72, 24); cout << "F3"; gotoxy(80, 24); cout << "HIEU CHINH DIEM SV";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienInBangDiemMH()
{
	Normal(); system("cls");
	gotoxy(cot + 3, dong); SetColor(14); cout << "IN BANG DIEM MON HOC MOT LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "NHAP MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MA MON HOC : " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "LAN THI    : " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "BANG DIEM MON HOC" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "LOP: ";
	gotoxy(20, wherey()); cout << "LAN THI: " << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "MON HOC: " << endl; cout << endl;

	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(7, 15); cout << char(194);
	gotoxy(22, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);
	gotoxy(58, 15); cout << char(194);

	gotoxy(7, 43); cout << char(193);
	gotoxy(22, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	gotoxy(58, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(7, i); cout << char(179);
		gotoxy(22, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(58, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(7, 17); cout << char(197);
	gotoxy(22, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(58, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(3, 16); cout << "STT";
	gotoxy(13, 16); cout << "MA SV";
	gotoxy(32, 16); cout << "HO SV";
	gotoxy(49, 16); cout << "TEN SV";
	gotoxy(60, 16); cout << "DIEM";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "IN BANG DIEM MH";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienInBangDiemTB()
{
	Normal(); system("cls");
	gotoxy(cot + 3, dong); SetColor(14); cout << "IN BANG DIEM TB MOT LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "NHAP MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), 10); cout << "BANG DIEM TB MOT LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "LOP: ";
	gotoxy(20, wherey()); cout << "NAM HOC: " << endl; cout << endl;

	KeKhungVuong1Vien(1, 65, 15, 43, 14);
	//5 cai dau chia khung
	gotoxy(7, 15); cout << char(194);
	gotoxy(22, 15); cout << char(194);
	gotoxy(45, 15); cout << char(194);
	gotoxy(58, 15); cout << char(194);

	gotoxy(7, 43); cout << char(193);
	gotoxy(22, 43); cout << char(193);
	gotoxy(45, 43); cout << char(193);
	gotoxy(58, 43); cout << char(193);
	//cac duong doc
	for (int i = 16; i < 43; i++) {
		gotoxy(1, i); cout << char(179);
		gotoxy(7, i); cout << char(179);
		gotoxy(22, i); cout << char(179);
		gotoxy(45, i); cout << char(179);
		gotoxy(58, i); cout << char(179);
		gotoxy(65, i); cout << char(179);
	}
	//duong ngang chia stt, name....
	for (int i = 2; i < 65; i++) {
		gotoxy(i, 17); cout << char(196);
	}

	gotoxy(1, 17); cout << char(195);
	gotoxy(7, 17); cout << char(197);
	gotoxy(22, 17); cout << char(197);
	gotoxy(45, 17); cout << char(197);
	gotoxy(58, 17); cout << char(197);
	gotoxy(65, 17); cout << char(180);

	gotoxy(3, 16); cout << "STT";
	gotoxy(13, 16); cout << "MA SV";
	gotoxy(32, 16); cout << "HO SV";
	gotoxy(49, 16); cout << "TEN SV";
	gotoxy(60, 16); cout << "DIEM";

	KeKhungVuong1Vien(70, 75, 15, 17, 14);
	gotoxy(72, 16); cout << "F1"; gotoxy(80, 16); cout << "IN BANG DIEM TB";
	KeKhungVuong1Vien(70, 75, 27, 29, 14);
	gotoxy(72, 28); cout << "F4"; gotoxy(80, 28); cout << "THOAT";
	KeKhungVuong1Vien(68, 78, 31, 33, 14);
	gotoxy(70, 32); cout << "UP/DOWN"; gotoxy(80, 32); cout << "CHUYEN TRANG";
}

void GiaoDienInBangTongKet()
{
	Normal(); system("cls");
	gotoxy(cot + 3, dong); SetColor(14); cout << "IN BANG DIEM TONG KET	MOT LOP" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "NHAP MA LOP: " << endl; cout << endl;
	gotoxy(wherex(), 10); cout << "BANG DIEM TONG KET" << endl; cout << endl;
	gotoxy(wherex(), wherey()); cout << "LOP: ";
	gotoxy(20, wherey()); cout << "NAM HOC: " << endl; cout << endl;
	gotoxy(0, 16); cout << "STT";
	gotoxy(5, 16); cout << "MA SV";
	gotoxy(15, 16); cout << "HO TEN SV";
	gotoxy(35, 16);
	KeKhungVuong1Vien(120, 125, 1, 3, 14);
	gotoxy(122, 2); cout << "F1"; gotoxy(130, 2); cout << "IN BANG DIEM TK";
	KeKhungVuong1Vien(120, 125, 5, 7, 14);
	gotoxy(122, 6); cout << "F4"; gotoxy(130, 6); cout << "THOAT";
	KeKhungVuong1Vien(118, 128, 9, 11, 14);
	gotoxy(120, 10); cout << "UP/DOWN"; gotoxy(130, 10); cout << "CHUYEN TRANG";
}

//----------------------------------------------------------------------
void Run(DSLOP &dslop, PTRMONHOC &treemh);

void NhapLop(DSLOP &dslop, PTRMONHOC &treemh);
void XoaLop(DSLOP &dslop, PTRMONHOC &treemh);
void HieuChinhLop(DSLOP &dslop, PTRMONHOC &treemh);

void NhapSinhVien(DSLOP &dslop, PTRMONHOC &treemh);
void XoaSV(DSLOP &dslop, PTRMONHOC &treemh);
void HieuChinhSV(DSLOP &dslop, PTRMONHOC &treemh);

void NhapMonHoc(DSLOP &dslop, PTRMONHOC &treemh);
void XoaMonHoc(DSLOP &dslop, PTRMONHOC &treemh);
void HieuChinhMonHoc(DSLOP &dslop, PTRMONHOC &treemh);

void NhapDiemSV(DSLOP &dslop, PTRMONHOC &treemh);
void HieuChinhDiemSV(DSLOP &dslop, PTRMONHOC &treemh);
//----------------------------------------------------------------------
//Xu Ly
//Lop
int SearchMaLop(DSLOP &dslop, char *malop)
{
	for (int i = 0; i < dslop.n; i++)
	{
		if (_stricmp(dslop.nodes[i].MALOP, malop) == 0)
			return i;
	}
	return -1;
}

int SearchNienKhoa(DSLOP &dslop, int nienkhoa)
{
	for (int i = 0; i < dslop.n; i++)
	{
		if (dslop.nodes[i].namnhaphoc == nienkhoa)
			return i;
	}
	return -1;
}

void XuatDSLopTrang1(DSLOP &dslop)
{
	int dongxuat = 18;
	if (dslop.n > 25)
	{
		for (int i = 0; i < 25; i++)
		{
			if (dongxuat < 43)
			{
				gotoxy(3, dongxuat); cout << dslop.nodes[i].MALOP;
				gotoxy(22, wherey()); cout << dslop.nodes[i].TENLOP;
				gotoxy(47, wherey()); cout << dslop.nodes[i].namnhaphoc;
				dongxuat++;
			}
		}
	}
	else
	{
		for (int i = 0; i < dslop.n; i++)
		{
			gotoxy(3, dongxuat); cout << dslop.nodes[i].MALOP;
			gotoxy(22, wherey()); cout << dslop.nodes[i].TENLOP;
			gotoxy(47, wherey()); cout << dslop.nodes[i].namnhaphoc;
			dongxuat++;
		}
	}
}

void XuatDSLopTrang2(DSLOP &dslop, int &dongxuat)
{
	if (dslop.n > 25)
	{
		for (int i = 25; i < dslop.n; i++)
		{
			if (dongxuat < 43)
			{
				gotoxy(3, dongxuat); cout << dslop.nodes[i].MALOP;
				gotoxy(22, wherey()); cout << dslop.nodes[i].TENLOP;
				gotoxy(47, wherey()); cout << dslop.nodes[i].namnhaphoc;
				dongxuat++;
			}
		}
	}
}

void NhapLop(DSLOP &dslop, PTRMONHOC &treemh)
{
	LOP l; int dongnhap = 18;
	system("cls"); GiaoDienNhapLop(); Normal();
nhaplaimalop:
	if (dongnhap == 43) NhapLop(dslop, treemh);
	gotoxy(0, 45); cout << "                                       ";
	gotoxy(3, dongnhap); cout << "                 ";
	gotoxy(3, dongnhap); fflush(stdin); gets(l.MALOP);
	if (_stricmp(l.MALOP, "") == 0) goto nhaplaikey;
	char temp[11];
	ChuanHoaChuoi(l.MALOP, temp);
	if (SearchMaLop(dslop, temp) != -1)
	{
		gotoxy(0, 45); cout << "                                       ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP TRUNG, NHAP LAI!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}	
nhaplaitenlop:
	gotoxy(22, dongnhap); fflush(stdin); gets(l.TENLOP);
	if (_stricmp(l.TENLOP, "") == 0) goto nhaplaitenlop;
	gotoxy(47, dongnhap); cin >> l.namnhaphoc;
	l.ptrsv = NULL;
	dslop.nodes[dslop.n] = l; dslop.n++;
	dongnhap++;
	if (dslop.n == MAXLOP)
	{
		gotoxy(0, 45); cout << "                                         ";
		gotoxy(0, 45); SetColor(14); cout << "DANH SACH LOP DAY, DUNG NHAP!" << endl; _getch(); Normal(); return;
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) goto nhaplaimalop;
	else if (key == F2) XoaLop(dslop, treemh);
	else if (key == F3) HieuChinhLop(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienNhapLop(); Normal();
		dongnhap = 18;
		XuatDSLopTrang1(dslop);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienNhapLop(); Normal();
		dongnhap = 18;
		XuatDSLopTrang2(dslop, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HamXoaLop(DSLOP &dslop, int vitri)
{
	if (vitri == dslop.n - 1) dslop.n--;
	else
	{
		for (int i = vitri; i < dslop.n; i++)
		{
			dslop.nodes[i] = dslop.nodes[i + 1];
		}
		dslop.n--;
	}
}

void XoaLop(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienXoaLop(); Normal(); XuatDSLopTrang1(dslop);
	char malop[11]; int dongnhap = 18;
nhaplai:
	gotoxy(0, 45); cout << "                                            ";
	gotoxy(7, 4); cout << "                  ";
	gotoxy(7, 4); fflush(stdin); gets(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vitri = SearchMaLop(dslop, malop);
	if (vitri == -1)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplai;
	}
	PTRSV p = dslop.nodes[vitri].ptrsv;
	if (p != NULL)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "LOP DA CO SINH VIEN!" << endl; _getch(); Normal();
		goto nhaplai;
	}
	HamXoaLop(dslop, vitri); system("cls"); GiaoDienXoaLop(); Normal(); XuatDSLopTrang1(dslop);
	 nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapLop(dslop, treemh);
	else if (key == F2) XoaLop(dslop, treemh);
	else if (key == F3) HieuChinhLop(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienXoaLop(); Normal();
		XuatDSLopTrang1(dslop); goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienXoaLop(); Normal();
		dongnhap = 18;
		XuatDSLopTrang2(dslop, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HieuChinhLop(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienHieuChinhLop(); Normal(); XuatDSLopTrang1(dslop);
	goto nhaplaikey;
	char malopSua[11];
nhaplai:
	gotoxy(0, 45); cout << "                                           ";
	gotoxy(7, 4); cout << "             ";
	gotoxy(7, 4); fflush(stdin); get(malopSua);
	if (_stricmp(malopSua, "") == 0) goto nhaplaikey;
	int vitri = SearchMaLop(dslop, malopSua);
	gotoxy(0, 45); cout << "                                  ";
	if (vitri == -1)
	{
		gotoxy(0, 45); cout << "                                         ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplai;
	}
	else
	{
		int dongxuat = 18;
		for (int i = 0; i < dslop.n; i++)
		{
			if (_stricmp(dslop.nodes[i].MALOP, malopSua) == 0)
			{
				gotoxy(22, dongxuat); cout << "                       ";
			nhaplaitenlop:
				gotoxy(22, dongxuat); fflush(stdin); get(dslop.nodes[i].TENLOP);
				if (_stricmp(dslop.nodes[i].TENLOP, "") == 0) goto nhaplaitenlop;
				gotoxy(47, dongxuat); cout << "         ";
				gotoxy(47, dongxuat); fflush(stdin); cin >> dslop.nodes[i].namnhaphoc;
			}
			dongxuat++;
			if (dongxuat >= 43) dongxuat = 18;
		}
		system("cls"); GiaoDienHieuChinhLop(); Normal(); XuatDSLopTrang1(dslop);
	nhaplaikey:
		int key = keyPressed();
		if (key == F1) NhapLop(dslop, treemh);
		else if (key == F2) XoaLop(dslop, treemh);
		else if (key == F3) goto nhaplai;
		else if (key == F4) Run(dslop, treemh);
		else if (key == UpTrang)
		{
			system("cls"); GiaoDienHieuChinhLop(); Normal();
			XuatDSLopTrang1(dslop);
			goto nhaplaikey;
		}
		else if (key == DownTrang)
		{
			system("cls"); GiaoDienHieuChinhLop(); Normal(); dongxuat = 18;
			XuatDSLopTrang2(dslop, dongxuat);
			goto nhaplaikey;
		}
		else goto nhaplaikey;
	}
}

void XuatDSLopTheoNK(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienDSLop(); Normal();
	int nienkhoa;
NhapLai:
	gotoxy(0, 45); cout << "                                     ";
	gotoxy(10, 4); cout << "                                        ";
	gotoxy(10, 4); cin >> nienkhoa;
	if (SearchNienKhoa(dslop, nienkhoa) == -1)
	{
		gotoxy(0, 45); cout << "                                     ";
		gotoxy(0, 45); SetColor(14); cout << "KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto NhapLai;
	}
	else
	{
	xuattrang1:
		system("cls"); GiaoDienDSLop(); Normal();
		gotoxy(10, 4); cout << nienkhoa;
		int dongxuat = 18;
		if (dslop.n > 25)
		{
			for (int i = 0; i < 25; i++)
			{
				if (dongxuat < 43)
				{
					if (dslop.nodes[i].namnhaphoc = nienkhoa)
					{
						gotoxy(3, dongxuat); cout << dslop.nodes[i].MALOP;
						gotoxy(22, wherey()); cout << dslop.nodes[i].TENLOP;
						gotoxy(47, wherey()); cout << dslop.nodes[i].namnhaphoc;
						dongxuat++;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < dslop.n; i++)
			{
				if (dslop.nodes[i].namnhaphoc = nienkhoa)
				{
					gotoxy(3, dongxuat); cout << dslop.nodes[i].MALOP;
					gotoxy(22, wherey()); cout << dslop.nodes[i].TENLOP;
					gotoxy(47, wherey()); cout << dslop.nodes[i].namnhaphoc;
					dongxuat++;
				}
			}
		}
		goto nhaplaikey;
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) XuatDSLopTheoNK(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang) goto xuattrang1;
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienDSLop(); Normal();
		int dongxuat = 18; gotoxy(10, 4); cout << nienkhoa;
		if (dslop.n > 25)
		{
			for (int i = 25; i < dslop.n; i++)
			{
				if (dongxuat < 43)
				{
					if (dslop.nodes[i].namnhaphoc = nienkhoa)
					{
						gotoxy(3, dongxuat); cout << dslop.nodes[i].MALOP;
						gotoxy(22, wherey()); cout << dslop.nodes[i].TENLOP;
						gotoxy(47, wherey()); cout << dslop.nodes[i].namnhaphoc;
						dongxuat++;
					}
				}
			}
		}
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

//Sinh Vien
PTRSV SearchMaSV(DSLOP &dslop, char *masv)
{
	PTRSV p;
	for (int i = 0; i < dslop.n; i++)
	{
		for (p = dslop.nodes[i].ptrsv; p != NULL; p = p->next)
		{
			if (_stricmp(p->sinhvien.MASV, masv) == 0) return p;
		}
	}
	return NULL;
}

PTRSV SearchSDTSV(DSLOP &dslop, char *sdt)
{
	PTRSV p;
	for (int i = 0; i < dslop.n; i++)
	{
		for (p = dslop.nodes[i].ptrsv; p != NULL; p = p->next)
		{
			if (_stricmp(p->sinhvien.SODT, sdt) == 0) return p;
		}
	}
	return NULL;
}


void Insert_LastSV(PTRSV &Firstsv, SINHVIEN sv)
{
	PTRSV p = new NODESINHVIEN;
	p->sinhvien = sv;
	p->next = NULL;
	if (Firstsv == NULL) Firstsv = p;
	else
	{
		PTRSV Last;
		for (Last = Firstsv; Last->next != NULL; Last = Last->next);
		Last->next = p;
	}
}

int TongSoSV(PTRSV p)
{
	int siso = 0;
	for (PTRSV Firstsv = p; Firstsv != NULL; Firstsv = Firstsv->next)
	{
		siso++;
	}
	return siso;
}

void SapXepSV(DSLOP &dslop, int vitri)
{
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		for (PTRSV q = p->next; q != NULL; q = q->next)
		{
			if (_stricmp(p->sinhvien.TEN, q->sinhvien.TEN) > 0)
			{
				SINHVIEN sv = p->sinhvien;
				p->sinhvien = q->sinhvien;
				q->sinhvien = sv;
			}
			else if (_stricmp(p->sinhvien.TEN, q->sinhvien.TEN) == 0)
			{
				if (_stricmp(p->sinhvien.HO, q->sinhvien.HO) > 0)
				{
					SINHVIEN sv = p->sinhvien;
					p->sinhvien = q->sinhvien;
					q->sinhvien = sv;
				}
			}
		}
	}
}

void XuatSVTrang1(DSLOP &dslop, int vtlop)
{
	int dongnhap = 18; int dem = 0;
	for (PTRSV p = dslop.nodes[vtlop].ptrsv; p != NULL; p = p->next)
	{
		dem++;
		if (dem <= 25)
		{
			gotoxy(3, dongnhap); cout << p->sinhvien.MASV;
			gotoxy(15, dongnhap); cout << p->sinhvien.HO;
			gotoxy(32, dongnhap); cout << p->sinhvien.TEN;
			gotoxy(45, dongnhap); cout << PHAI[p->sinhvien.PHAI];
			gotoxy(52, dongnhap); cout << p->sinhvien.SODT;
			dongnhap++;
		}
	}
}

void XuatSVTrang2(DSLOP &dslop, int vtlop, int &dongnhap)
{
	int dem = 0;
	if (TongSoSV(dslop.nodes[vtlop].ptrsv) > 25)
	{
		for (PTRSV p = dslop.nodes[vtlop].ptrsv; p != NULL; p = p->next)
		{
			dem++;
			if (dem > 25)
			{
				gotoxy(3, dongnhap); cout << p->sinhvien.MASV;
				gotoxy(15, dongnhap); cout << p->sinhvien.HO;
				gotoxy(32, dongnhap); cout << p->sinhvien.TEN;
				gotoxy(45, dongnhap); cout << PHAI[p->sinhvien.PHAI];
				gotoxy(52, dongnhap); cout << p->sinhvien.SODT;
				dongnhap++;
			}
		}
	}
}

void NhapSinhVien(DSLOP &dslop, PTRMONHOC &treemh)
{
	char malop[11];  SINHVIEN sv;
	system("cls"); GiaoDienNhapSinhVien(); Normal(); int dongnhap = 18;
nhaplai:
	gotoxy(7, 4); cout << "                ";
	gotoxy(7, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtlop = SearchMaLop(dslop, malop);
	if (vtlop == -1)
	{
		gotoxy(0, 45); cout << "                                     ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplai;
	}
nhaplaimasv:
	if (dongnhap == 43) { system("cls"); GiaoDienNhapSinhVien(); Normal(); dongnhap = 18; gotoxy(7, 4); cout << malop; }
	gotoxy(0, 45); cout << "                                    " << endl;
	gotoxy(3, dongnhap); cout << "        " << endl;
	gotoxy(3, dongnhap); fflush(stdin); get(sv.MASV);
	if (_stricmp(sv.MASV, "") == 0) goto nhaplaikey;
	char temp[11];
	ChuanHoaChuoi(sv.MASV, temp);
	if (SearchMaSV(dslop, temp) != NULL)
	{
		gotoxy(0, 45); cout << "                                        ";
		gotoxy(0, 45); SetColor(14); cout << "MA SV BI TRUNG, NHAP LAI!" << endl; _getch(); Normal();
		goto nhaplaimasv;
	}
	else
	{
		gotoxy(0, 45); cout << "                                      " << endl;
	nhaplaiho:
		gotoxy(15, dongnhap); fflush(stdin); get(sv.HO);
		if (_stricmp(sv.HO, "") == 0) goto nhaplaiho;
	nhaplaiten:
		gotoxy(32, dongnhap); fflush(stdin); get(sv.TEN);
		if (_stricmp(sv.TEN, "") == 0) goto nhaplaiten;
	nhapphai:
		gotoxy(0, 45); cout << "                                       " << endl;
		gotoxy(45, dongnhap); cout << "   ";
		gotoxy(45, dongnhap); fflush(stdin); cin >> sv.PHAI;
		if (sv.PHAI < 0 || sv.PHAI > 1)
		{
			gotoxy(0, 45); cout << "                                         ";
			gotoxy(0, 45); SetColor(14); cout << "GIOI TINH KHONG PHU HOP!" << endl; _getch(); Normal();
			goto nhapphai;
		}
		gotoxy(45, dongnhap); cout << PHAI[sv.PHAI];
	nhaplaisdt:
		gotoxy(52, dongnhap); cout << "            ";
		gotoxy(52, dongnhap); fflush(stdin); get(sv.SODT);
		if (_stricmp(sv.SODT, "") == 0) goto nhaplaisdt;
		if (SearchSDTSV(dslop, sv.SODT) != NULL)
		{
			gotoxy(0, 45); cout << "                                        ";
			gotoxy(0, 45); SetColor(14); cout << "SDT SV BI TRUNG, NHAP LAI!" << endl; _getch(); Normal();
			goto nhaplaisdt;
		}
		sv.ptrdiem = NULL;
		Insert_LastSV(dslop.nodes[vtlop].ptrsv, sv);
		dongnhap++;
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1)
	{
		if (_stricmp(malop, "") == 0) NhapSinhVien(dslop, treemh);
		else goto nhaplaimasv;
	}
	else if (key == F2) XoaSV(dslop, treemh);
	else if (key == F3) HieuChinhSV(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienNhapSinhVien(); Normal(); gotoxy(7, 4); cout << malop;
		dongnhap = 18; int dem = 0;
		if (_stricmp(malop, "") == 0) goto nhaplaikey;
		XuatSVTrang1(dslop, vtlop);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienNhapSinhVien(); Normal(); gotoxy(7, 4); cout << malop;
		dongnhap = 18; int dem = 0;
		if (_stricmp(malop, "") == 0) goto nhaplaikey;
		XuatSVTrang2(dslop, vtlop, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void XuatSVMotLop(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienDSSVmotlop(); Normal();
	char malop[11];
nhaplai:
	int dongnhap = 18;
	gotoxy(0, 45); cout << "                                     " << endl;
	gotoxy(7, 4); cout << "             " << endl;
	gotoxy(7, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtlop = SearchMaLop(dslop, malop);
	if (vtlop == -1)
	{
		gotoxy(0, 45); cout << "                                          " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplai;
	}
	else
	{
		PTRSV p = dslop.nodes[vtlop].ptrsv;
		if (p == NULL)
		{
			gotoxy(0, 45); cout << "                                     " << endl;
			gotoxy(0, 45); SetColor(14); cout << "LOP KHONG CO DANH SACH SV!" << endl; _getch(); Normal();
			goto nhaplai;
		}
		else
		{
			SapXepSV(dslop, vtlop); int dem = 0;
			XuatSVTrang1(dslop, vtlop);
		}
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) XuatSVMotLop(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienDSSVmotlop(); Normal(); gotoxy(7, 4); cout << malop;
		dongnhap = 18; int dem = 0;
		if (_stricmp(malop, "") == 0) goto nhaplaikey;
		XuatSVTrang1(dslop, vtlop);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienDSSVmotlop(); Normal(); gotoxy(7, 4); cout << malop;
		dongnhap = 18; int dem = 0;
		if (_stricmp(malop, "") == 0) goto nhaplaikey;
		XuatSVTrang2(dslop, vtlop, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HamXoaSV(DSLOP &dslop, PTRSV p)
{
	for (int i = 0; i < dslop.n; i++)
	{
		if (dslop.nodes[i].ptrsv == NULL) return;
		if (dslop.nodes[i].ptrsv == p)
		{
			p = dslop.nodes[i].ptrsv;
			dslop.nodes[i].ptrsv = p->next;
			delete p;
		}
		PTRSV firstsv = dslop.nodes[i].ptrsv;
		while (firstsv != NULL)
		{
			if (firstsv->next != p)
			{
				firstsv = firstsv->next;
			}
			else
			{
				p = firstsv->next;
				firstsv->next = p->next;
				delete p;
			}
		}
	}
}

void XoaSV(DSLOP &dslop, PTRMONHOC &treemh)
{
	char malop[11]; char masv[11];
nhaplaimalop:
	system("cls"); GiaoDienXoaSinhVien(); Normal();
	int dongnhap = 4;
	gotoxy(0, 45); cout << "                                              " << endl;
	gotoxy(7, 4); cout << "                ";
	gotoxy(7, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtlop = SearchMaLop(dslop, malop);
	if (vtlop == -1)
	{
		gotoxy(0, 45); cout << "                                              " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
	else if (dslop.nodes[vtlop].ptrsv == NULL)
	{
		gotoxy(0, 45); cout << "                                          " << endl;
		gotoxy(0, 45); SetColor(14); cout << "LOP KHONG CO DANH SACH SV!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
	XuatSVTrang1(dslop, vtlop);
nhaplaimasv:
	gotoxy(0, 45); cout << "                                       " << endl;
	gotoxy(7, 6); cout << "              ";
	gotoxy(7, 6); fflush(stdin); get(masv);
	if (_stricmp(masv, "") == 0) goto nhaplaikey;
	PTRSV p = SearchMaSV(dslop, masv);
	if (p == NULL)
	{
		gotoxy(0, 45); cout << "                                       " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA SV KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimasv;
	}
	else
	{
		HamXoaSV(dslop, p);
		system("cls");
		GiaoDienXoaSinhVien(); Normal(); XuatSVTrang1(dslop, vtlop);
		gotoxy(7, 4); cout << malop;
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapSinhVien(dslop, treemh);
	else if (key == F2)
	{
		if (_stricmp(malop, "") == 0) XoaSV(dslop, treemh);
		else goto nhaplaimasv;
	}
	else if (key == F3) HieuChinhSV(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienXoaSinhVien(); Normal(); gotoxy(7, 4); cout << malop;
		dongnhap = 18; int dem = 0;
		XuatSVTrang1(dslop, vtlop);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienXoaSinhVien(); Normal(); gotoxy(7, 4); cout << malop;
		dongnhap = 18; int dem = 0;
		XuatSVTrang2(dslop, vtlop, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HieuChinhSV(DSLOP &dslop, PTRMONHOC &treemh)
{
	char malop[11]; char masvcansua[11];
nhaplaimalop:
	system("cls"); GiaoDienHieuChinhSinhVien(); Normal();
	gotoxy(0, 45); cout << "                                         " << endl;
	gotoxy(7, 4); cout << "                       ";
	gotoxy(7, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtlop = SearchMaLop(dslop, malop);
	if (vtlop == -1)
	{
		gotoxy(0, 45); cout << "                                         " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
	else if (dslop.nodes[vtlop].ptrsv == NULL)
	{
		gotoxy(0, 45); cout << "                                         " << endl;
		gotoxy(0, 45); SetColor(14); cout << "LOP KHONG CO DANH SACH SV!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
	XuatSVTrang1(dslop, vtlop); goto nhaplaikey;
nhaplaimasv:
	int dongnhap = 18;
	gotoxy(7, 6); cout << "           ";
	gotoxy(7, 6); fflush(stdin); get(masvcansua);
	if (_stricmp(masvcansua, "") == 0) goto nhaplaikey;
	for (PTRSV p = dslop.nodes[vtlop].ptrsv; p != NULL; p = p->next)
	{
		if (_stricmp(p->sinhvien.MASV, masvcansua) != 0)
		{
			gotoxy(0, 45); cout << "                                 " << endl;
			gotoxy(0, 45); SetColor(14); cout << "MA SV KHONG CO TRONG DANH SACH LOP NAY!" << endl; _getch(); Normal();
			goto nhaplaimasv;
		}
	}
	if (SearchMaSV(dslop, masvcansua) == NULL)
	{
		gotoxy(0, 45); cout << "                                 " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA SV KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimasv;
	}
	else
	{
		for (PTRSV p = dslop.nodes[vtlop].ptrsv; p != NULL; p = p->next)
		{
			if (_stricmp(p->sinhvien.MASV, masvcansua) == 0)
			{
				gotoxy(15, dongnhap); cout << "               ";
			nhaplaiho:
				gotoxy(15, dongnhap); fflush(stdin); get(p->sinhvien.HO);
				if (_stricmp(p->sinhvien.HO, "") == 0) goto nhaplaiho;
				gotoxy(32, dongnhap); cout << "           ";
			nhaplaiten:
				gotoxy(32, dongnhap); fflush(stdin); get(p->sinhvien.TEN);
				if (_stricmp(p->sinhvien.TEN, "") == 0) goto nhaplaiten;
				gotoxy(45, dongnhap); cout << "     ";
			nhaplaiphai:
				gotoxy(45, dongnhap); fflush(stdin); cin >> p->sinhvien.PHAI;
				if (p->sinhvien.PHAI < 0 || p->sinhvien.PHAI > 1) goto nhaplaiphai;
				gotoxy(45, dongnhap); cout << PHAI[p->sinhvien.PHAI];
				gotoxy(52, dongnhap); cout << "            ";
			nhaplaisdt:
				gotoxy(52, dongnhap); fflush(stdin); get(p->sinhvien.SODT);
				if (_stricmp(p->sinhvien.SODT, "") == 0) goto nhaplaisdt;
			}
			dongnhap++;
			if (dongnhap == 43) dongnhap = 18;
		}
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapSinhVien(dslop, treemh);
	else if (key == F2) XoaSV(dslop, treemh);
	else if (key == F3)
	{
		if (_stricmp(malop, "") == 0) HieuChinhSV(dslop, treemh);
		else goto nhaplaimasv;
	}
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienHieuChinhSinhVien(); Normal(); gotoxy(7, 4); cout << malop;
		XuatSVTrang1(dslop, vtlop); goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienXoaSinhVien(); Normal(); gotoxy(7, 4); cout << malop; dongnhap = 18;
		XuatSVTrang2(dslop, vtlop, dongnhap); goto nhaplaikey;
	}
	else goto nhaplaikey;
}

//Mon Hoc
void KhoiTao(PTRMONHOC &treemh){ treemh = NULL; }

void Insert_node(PTRMONHOC &treemh, MONHOC mh)
{
	if (treemh == NULL)
	{
		treemh = new NODEMONHOC;
		treemh->monhoc = mh;
		treemh->left = NULL;
		treemh->right = NULL;
	}
	else
	{
		if (_stricmp(mh.MAMH, treemh->monhoc.MAMH) < 0)
		{
			Insert_node(treemh->left, mh);
		}
		else if (_stricmp(mh.MAMH, treemh->monhoc.MAMH) > 0)
		{
			Insert_node(treemh->right, mh);
		}
	}
}

PTRMONHOC SearchMaMH(PTRMONHOC &treemh, char *mamh)
{
	PTRMONHOC p = treemh;
	while (p != NULL && (_stricmp(p->monhoc.MAMH, mamh) != 0))
	{
		if (_stricmp(mamh, p->monhoc.MAMH) < 0)
			p = p->left;
		else if (_stricmp(mamh, p->monhoc.MAMH) > 0)
			p = p->right;
	}
	return p;
}

int TongSoMH(PTRMONHOC &treemh)
{
	if (treemh == NULL)
	{
		return 0;
	}
	return 1 + TongSoMH(treemh->left) + TongSoMH(treemh->right);
}

void XuatMHTrang1(PTRMONHOC &treemh, int &dem)
{
	if (treemh != NULL)
	{
		dem++;
		if (dem <= 25)
		{
			gotoxy(3, wherey()); cout << treemh->monhoc.MAMH;
			gotoxy(17, wherey()); cout << treemh->monhoc.TENMH;
			gotoxy(42, wherey()); cout << treemh->monhoc.STCLT;
			gotoxy(55, wherey()); cout << treemh->monhoc.STCTH;
			cout << endl;
		}
		XuatMHTrang1(treemh->left, dem);
		XuatMHTrang1(treemh->right, dem);
	}
}

void XuatMHTrang2(PTRMONHOC &treemh, int &dem, int &dongxuat)
{
	if (treemh != NULL)
	{
		dem++;
		if (dem > 25)
		{
			gotoxy(3, dongxuat); cout << treemh->monhoc.MAMH;
			gotoxy(17, wherey()); cout << treemh->monhoc.TENMH;
			gotoxy(42, wherey()); cout << treemh->monhoc.STCLT;
			gotoxy(55, wherey()); cout << treemh->monhoc.STCTH;
			dongxuat++;
		}
		XuatMHTrang2(treemh->left, dem, dongxuat);
		XuatMHTrang2(treemh->right, dem, dongxuat);
	}
}

void NhapMonHoc(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienNhapMonHoc(); Normal();
	MONHOC mh; DIEMMONHOC diem; diem.LAN = 1; diem.DIEM = 0; int dongnhap = 18;
nhaplaimaMH:
	if (dongnhap == 43) { system("cls"); GiaoDienNhapMonHoc(); Normal(); dongnhap = 18; }
	gotoxy(0, 45); cout << "                           ";
	gotoxy(3, dongnhap); cout << "         " << endl;
	gotoxy(3, dongnhap); fflush(stdin); get(mh.MAMH);
	if (_stricmp(mh.MAMH, "") == 0) goto nhaplaikey;
	char temp[11];
	ChuanHoaChuoi(mh.MAMH, temp);
	if (SearchMaMH(treemh, temp) != NULL)
	{
		gotoxy(0, 45); cout << "                 " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA MON HOC BI TRUNG!" << endl; _getch(); Normal();
		goto nhaplaimaMH;
	}
	else
	{
		gotoxy(0, 45); cout << "                            " << endl;
	nhaplaiten:
		gotoxy(17, dongnhap); fflush(stdin); get(mh.TENMH);
		if (_stricmp(mh.TENMH, "") == 0) goto nhaplaiten;
		gotoxy(42, dongnhap); fflush(stdin); cin >> mh.STCLT;
		gotoxy(55, dongnhap); fflush(stdin); cin >> mh.STCTH;
		Insert_node(treemh, mh);
		dongnhap++;
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) goto nhaplaimaMH;
	else if (key == F2) XoaMonHoc(dslop, treemh);
	else if (key == F3) HieuChinhMonHoc(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		int dem = 0;
		system("cls"); GiaoDienNhapMonHoc(); Normal(); gotoxy(3, 18);
		XuatMHTrang1(treemh, dem);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		int dem = 0; dongnhap = 18;
		system("cls"); GiaoDienNhapMonHoc(); Normal(); gotoxy(3, 18);
		XuatMHTrang2(treemh, dem, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HamHieuChinhMonHoc(PTRMONHOC &treemh, char *mamh, int &dongxuat)
{
	if (treemh != NULL)
	{
		if (_stricmp(treemh->monhoc.MAMH, mamh) == 0)
		{
			gotoxy(17, dongxuat); cout << "                 ";
		nhaplaiten:
			gotoxy(17, wherey()); fflush(stdin); get(treemh->monhoc.TENMH);
			if (_stricmp(treemh->monhoc.TENMH, "") == 0) goto nhaplaiten;
			gotoxy(42, wherey() - 1); cout << "       ";
			gotoxy(42, wherey()); fflush(stdin); cin >> treemh->monhoc.STCLT;
			gotoxy(55, wherey() - 1); cout << "       ";
			gotoxy(55, wherey()); fflush(stdin); cin >> treemh->monhoc.STCTH;
		}
		dongxuat++;
		if (dongxuat == 43) dongxuat = 18;
		HamHieuChinhMonHoc(treemh->left, mamh, dongxuat);
		HamHieuChinhMonHoc(treemh->right, mamh, dongxuat);
	}
}

void HieuChinhMonHoc(DSLOP &dslop, PTRMONHOC &treemh)
{
	char mamh[11]; int dongnhap = 18; int dem = 0;
	system("cls"); GiaoDienHieuChinhMonHoc(); Normal(); XuatMHTrang1(treemh, dem);
nhaplaimaMH:
	gotoxy(7, 4); cout << "         " << endl;
	gotoxy(7, 4); fflush(stdin); get(mamh);
	if (_stricmp(mamh, "") == 0) goto nhaplaikey;
	PTRMONHOC p = SearchMaMH(treemh, mamh);
	if (p == NULL)
	{
		gotoxy(0, 45); cout << "                                         " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA MON HOC KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimaMH;
	}
	else
	{
		gotoxy(0, 45); cout << "                                        " << endl;
		dongnhap = 18;
		HamHieuChinhMonHoc(treemh, mamh, dongnhap);
		system("cls"); GiaoDienHieuChinhMonHoc(); Normal(); dem = 0; XuatMHTrang1(treemh, dem);
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapMonHoc(dslop, treemh);
	else if (key == F2) XoaMonHoc(dslop, treemh);
	else if (key == F3) goto nhaplaimaMH;
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		int dem = 0;
		system("cls"); GiaoDienHieuChinhMonHoc(); Normal(); gotoxy(3, 18);
		XuatMHTrang1(treemh, dem);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		int dem = 0; dongnhap = 18;
		system("cls"); GiaoDienHieuChinhMonHoc(); Normal(); gotoxy(3, 18);
		XuatMHTrang2(treemh, dem, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HamXoaMonHoc(PTRMONHOC &treemh, PTRMONHOC p)
{
	if (treemh == NULL) return;
	else if (_stricmp(treemh->monhoc.MAMH, p->monhoc.MAMH) > 0) HamXoaMonHoc(treemh->left, p);
	else if (_stricmp(treemh->monhoc.MAMH, p->monhoc.MAMH) < 0) HamXoaMonHoc(treemh->right, p);
	else if (_stricmp(treemh->monhoc.MAMH, p->monhoc.MAMH) == 0)
	{
		if (treemh->left == NULL)
		{
			treemh = treemh->right;
		}
		else if (treemh->right == NULL)
		{
			treemh = treemh->left;
		}
		else if (treemh->left != NULL && treemh->right != NULL)
		{
			PTRMONHOC s = treemh, q = s->left;
			// S la cha cua Q, Q la Node phai nhat cua cay con trai cua P
			if (q->right != NULL)
			{
				while (q->right != NULL)
				{
					s = q;
					q = q->right;
				}
				p->monhoc = q->monhoc;
				s->right = q->left;
			}
			else
			{
				p->monhoc = q->monhoc;
				s->left = q->left;
			}
			delete q;
		}
	}
}

void XoaMonHoc(DSLOP &dslop, PTRMONHOC &treemh)
{
	char mamh[11]; int dongnhap = 18; int dem = 0;
	system("cls"); GiaoDienXoaMonHoc(); Normal();; XuatMHTrang1(treemh, dem);
nhaplaimaMH:
	gotoxy(7, 4); cout << "         " << endl;
	gotoxy(7, 4); fflush(stdin); get(mamh);
	if (_stricmp(mamh, "") == 0) goto nhaplaikey;
	PTRMONHOC p = SearchMaMH(treemh, mamh);
	if (p == NULL)
	{
		gotoxy(0, 45); cout << "                                            " << endl;
		gotoxy(0, 45); SetColor(14); cout << "MA MON HOC KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimaMH;
	}
	else
	{
		gotoxy(0, 45); cout << "                                         " << endl;
		HamXoaMonHoc(treemh, p);
		system("cls"); GiaoDienXoaMonHoc(); Normal(); dem = 0; XuatMHTrang1(treemh, dem);
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapMonHoc(dslop, treemh);
	else if (key == F2) goto nhaplaimaMH;
	else if (key == F3) HieuChinhMonHoc(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		int dem = 0;
		system("cls"); GiaoDienXoaMonHoc(); Normal(); gotoxy(3, 18);
		XuatMHTrang1(treemh, dem);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		int dem = 0; dongnhap = 18;
		system("cls"); GiaoDienXoaMonHoc(); Normal();
		XuatMHTrang2(treemh, dem, dongnhap);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

int SearchMaMHDSTT(PTRMONHOC &treemh, MONHOC mh[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (_stricmp(mh[i].MAMH, treemh->monhoc.MAMH) == 0)
			return i;
	}
	return -1;
}

void DSTTMonHoc(PTRMONHOC &treemh, MONHOC mh[], int &n)
{
	if (treemh != NULL)
	{
		DSTTMonHoc(treemh->left, mh, n);
		if (SearchMaMHDSTT(treemh, mh, n) == -1) { mh[n] = treemh->monhoc; n++; }
		DSTTMonHoc(treemh->right, mh, n);
	}
}

void SapXepMH(MONHOC mh[], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (_stricmp(mh[i].TENMH, mh[j].TENMH) > 0)
			{
				MONHOC t = mh[i];
				mh[i] = mh[j];
				mh[j] = t;
			}
		}
	}
}

void XuatDSMHTrang1(MONHOC mh[], int n)
{
	int dongxuat = 18;
	if (n > 25)
	{
		for (int i = 0; i < 25; i++)
		{
			if (dongxuat < 43)
			{
				gotoxy(3, dongxuat); cout << mh[i].MAMH;
				gotoxy(17, wherey()); cout << mh[i].TENMH;
				gotoxy(42, wherey()); cout << mh[i].STCLT;
				gotoxy(55, wherey()); cout << mh[i].STCTH;
				dongxuat++;
			}
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (dongxuat < 43)
			{
				gotoxy(3, dongxuat); cout << mh[i].MAMH;
				gotoxy(17, wherey()); cout << mh[i].TENMH;
				gotoxy(42, wherey()); cout << mh[i].STCLT;
				gotoxy(55, wherey()); cout << mh[i].STCTH;
				dongxuat++;
			}
		}
	}
}

void XuatDSMHTrang2(MONHOC mh[], int n)
{
	int dongxuat = 18;
	if (n > 25)
	{
		for (int i = 25; i < n; i++)
		{
			if (dongxuat < 43)
			{
				gotoxy(3, dongxuat); cout << mh[i].MAMH;
				gotoxy(17, wherey()); cout << mh[i].TENMH;
				gotoxy(42, wherey()); cout << mh[i].STCLT;
				gotoxy(55, wherey()); cout << mh[i].STCTH;
				dongxuat++;
			}
		}
	}
}

void XuatDSMonHocTen(DSLOP &dslop, PTRMONHOC &treemh, MONHOC mh[], int n)
{
	system("cls"); GiaoDienDSMonHoc(); Normal();
	SapXepMH(mh, n);
	XuatDSMHTrang1(mh, n);
nhaplaikey:
	int key = keyPressed();
	if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienDSMonHoc(); Normal();
		XuatDSMHTrang1(mh, n);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienDSMonHoc(); Normal();
		XuatDSMHTrang2(mh, n);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

//Diem
void Insert_LastDiem(PTRDIEM &Firstd, DIEMMONHOC diem)
{
	PTRDIEM p = new NODEDIEM;
	p->diem = diem;
	p->next = NULL;
	if (Firstd == NULL) Firstd = p;
	else
	{
		PTRDIEM Last;
		for (Last = Firstd; Last->next != NULL; Last = Last->next);
		Last->next = p;
	}
}

int TongLanThimotSV(PTRDIEM p)
{
	int tongso = 0;
	for (PTRDIEM First = p; First != NULL; First = First->next)
	{
		tongso++;
	}
	return tongso;
}

PTRDIEM SearchMaMHvaLanthiTrongSV(PTRDIEM p, char *mamh, int lanthi)
{
	for (PTRDIEM q = p; q != NULL; q = q->next)
	{
		if (_stricmp(q->diem.MAMH, mamh) == 0 && q->diem.LAN == lanthi) { return q; }
	}
	return NULL;
}

PTRDIEM SearchDiemMHLanThi(PTRDIEM p, char *mamh, int lanthi)
{
	for (PTRDIEM q = p; q != NULL; q = q->next)
	{
		if (q->diem.LAN == lanthi && _stricmp(q->diem.MAMH, mamh) == 0 && q->diem.DIEM > 0 && q->diem.DIEM < 5) return q;
	}
	return NULL;
}

void XNhapDiemSVTrang1(DSLOP &dslop, int vitri, char *mamh, int lanthi)
{
	int dongxuat = 18; int stt = 0; int dem = 0;
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
		{
			if ((_stricmp(q->diem.MAMH, mamh) == 0) && (q->diem.LAN == lanthi))
			{
				if (q->diem.DIEM == 0 && dem < 25)
				{
					dem++;
					stt++; gotoxy(4, dongxuat); cout << stt;
					gotoxy(10, dongxuat); cout << p->sinhvien.MASV;
					gotoxy(25, dongxuat); cout << p->sinhvien.HO;
					gotoxy(48, dongxuat); cout << p->sinhvien.TEN;
					dongxuat++;
				}
				break;
			}
		}
	}
}

void XNhapDiemSVTrang2(DSLOP &dslop, int vitri, char *mamh, int lanthi)
{
	int dongxuat = 18; int stt = 0;
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		stt++;
		for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
		{
			if ((_stricmp(q->diem.MAMH, mamh) == 0) && (q->diem.LAN == lanthi))
			{
				if (q->diem.DIEM == 0)
				{
					gotoxy(4, dongxuat); cout << stt;
					gotoxy(10, dongxuat); cout << p->sinhvien.MASV;
					gotoxy(25, dongxuat); cout << p->sinhvien.HO;
					gotoxy(48, dongxuat); cout << p->sinhvien.TEN;
					dongxuat++;
				}
				break;
			}
		}
	}
}

void XuatDiemSVTrang1(DSLOP &dslop, int vitri, char *mamh, int lanthi)
{
	int dongxuat = 18; int stt = 0;
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
		{
			if ((_stricmp(q->diem.MAMH, mamh) == 0) && (q->diem.LAN == lanthi) && q->diem.DIEM > 0 && stt < 25)
			{
				stt++; gotoxy(4, dongxuat); cout << stt;
				gotoxy(10, dongxuat); cout << p->sinhvien.MASV;
				gotoxy(25, dongxuat); cout << p->sinhvien.HO;
				gotoxy(48, dongxuat); cout << p->sinhvien.TEN;
				gotoxy(60, dongxuat); cout << q->diem.DIEM;
				dongxuat++;
				break;
			}
		}
	}
}

void XuatDiemSVTrang2(DSLOP &dslop, int vitri, char *mamh, int lanthi)
{
	int dongxuat = 18; int stt = 0;
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		stt++;
		for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
		{
			if ((_stricmp(q->diem.MAMH, mamh) == 0) && (q->diem.LAN == lanthi) && q->diem.DIEM > 0 && stt > 25)
			{
				gotoxy(4, dongxuat); cout << stt;
				gotoxy(10, dongxuat); cout << p->sinhvien.MASV;
				gotoxy(25, dongxuat); cout << p->sinhvien.HO;
				gotoxy(48, dongxuat); cout << p->sinhvien.TEN;
				gotoxy(60, dongxuat); cout << q->diem.DIEM;
				dongxuat++;
				break;
			}
		}
	}
}


void NhapDiemSV(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienNhapDiem(); Normal();
	DIEMMONHOC diem; diem.LAN = 1; diem.DIEM = 0; char malop[11]; int dongnhap = 18;
nhaplaimalop:
	gotoxy(0, 45); cout << "                                                ";
	gotoxy(12, 4); cout << "                        ";
	gotoxy(12, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtrilop = SearchMaLop(dslop, malop);
	if (vtrilop == -1)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
nhaplaimamh:
	gotoxy(0, 45); cout << "                                                 ";
	gotoxy(12, 6); cout << "                     ";
	gotoxy(12, 6); fflush(stdin); get(diem.MAMH);
	if (_stricmp(diem.MAMH, "") == 0) goto nhaplaikey;
	if (SearchMaMH(treemh, diem.MAMH) == NULL)
	{
		gotoxy(0, 45); cout << "                                                        ";
		gotoxy(0, 45); SetColor(14); cout << "MA MON HOC KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimamh;
	}
	for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
	{
		if (p->sinhvien.ptrdiem == NULL)
		{
			Insert_LastDiem(p->sinhvien.ptrdiem, diem);
		}
		else
		{
			if (SearchMaMHvaLanthiTrongSV(p->sinhvien.ptrdiem, diem.MAMH, diem.LAN) == NULL) Insert_LastDiem(p->sinhvien.ptrdiem, diem);

		}
	}
nhaplailanthi:
	gotoxy(0, 45); cout << "                                            ";
	gotoxy(12, 8); cout << "                  ";
	gotoxy(12, 8); fflush(stdin); cin >> diem.LAN;
	if (diem.LAN <= 0 || diem.LAN > 2)
	{
		gotoxy(0, 45); cout << "                                                     ";
		gotoxy(0, 45); SetColor(14); cout << "LAN THI NHAP 1 || 2!" << endl; Normal(); _getch();
		goto nhaplailanthi;
	}
	else if (diem.LAN == 1)
	{
		XNhapDiemSVTrang1(dslop, vtrilop, diem.MAMH, diem.LAN);
		for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
		{
		nhapdiemlan1:
			for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
			{
				if ((_stricmp(q->diem.MAMH, diem.MAMH) == 0) && q->diem.LAN == diem.LAN && q->diem.DIEM == 0)
				{
				nhaplaidiemlan1:
					gotoxy(60, dongnhap); cout << "    ";
					gotoxy(60, dongnhap); fflush(stdin); cin >> q->diem.DIEM;
					if (q->diem.DIEM < 0 || q->diem.DIEM > 10) { goto nhaplaidiemlan1; }
					dongnhap++;
					break;
				}
			}
			if (dongnhap == 43)
			{
				dongnhap = 18;
				system("cls"); GiaoDienNhapDiem(); Normal();
				gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << diem.MAMH; gotoxy(12, 8); cout << diem.LAN;
				XNhapDiemSVTrang2(dslop, vtrilop, diem.MAMH, diem.LAN);
				goto nhapdiemlan1;
			}
		}
	}
	else if (diem.LAN == 2)
	{
		for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
		{
			if (SearchDiemMHLanThi(p->sinhvien.ptrdiem, diem.MAMH, 1) != NULL && SearchMaMHvaLanthiTrongSV(p->sinhvien.ptrdiem, diem.MAMH, diem.LAN) == NULL)
			{
				Insert_LastDiem(p->sinhvien.ptrdiem, diem);
			}
		}
		XNhapDiemSVTrang1(dslop, vtrilop, diem.MAMH, diem.LAN);
		for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
		{
		nhapdiemlan2:
			for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
			{
				if ((_stricmp(q->diem.MAMH, diem.MAMH) == 0) && q->diem.LAN == diem.LAN && q->diem.DIEM == 0)
				{
				nhaplaidiemlan2:
					gotoxy(60, dongnhap); cout << "    ";
					gotoxy(60, dongnhap); fflush(stdin); cin >> q->diem.DIEM;
					if (q->diem.DIEM < 0 || q->diem.DIEM > 10) { goto nhaplaidiemlan2; }
					dongnhap++;
					break;
				}
			}
			if (dongnhap == 43)
			{
				dongnhap = 18;
				system("cls"); GiaoDienNhapDiem(); Normal();
				gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << diem.MAMH; gotoxy(12, 8); cout << diem.LAN;
				XNhapDiemSVTrang2(dslop, vtrilop, diem.MAMH, diem.LAN);
				goto nhapdiemlan2;
			}
		}
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapDiemSV(dslop, treemh);
	else if (key == F3) HieuChinhDiemSV(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienNhapDiem(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << diem.MAMH; gotoxy(12, 8); cout << diem.LAN;
		XuatDiemSVTrang1(dslop, vtrilop, diem.MAMH, diem.LAN);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienNhapDiem(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << diem.MAMH; gotoxy(12, 8); cout << diem.LAN;
		XuatDiemSVTrang2(dslop, vtrilop, diem.MAMH, diem.LAN);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void HieuChinhDiemSV(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienHieuChinhDiem(); Normal();
	char malop[11]; char mamh[11]; int lanthi = 0; char masv[11];
nhaplaimalop:
	gotoxy(0, 45); cout << "                                                ";
	gotoxy(12, 4); cout << "                        ";
	gotoxy(12, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtrilop = SearchMaLop(dslop, malop);
	if (vtrilop == -1)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
nhaplaimamh:
	gotoxy(0, 45); cout << "                                                 ";
	gotoxy(12, 6); cout << "                     ";
	gotoxy(12, 6); fflush(stdin); get(mamh);
	if (_stricmp(mamh, "") == 0) goto nhaplaikey;
	if (SearchMaMH(treemh, mamh) == NULL)
	{
		gotoxy(0, 45); cout << "                                                        ";
		gotoxy(0, 45); SetColor(14); cout << "MA MON HOC KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimamh;
	}
nhaplailanthi:
	gotoxy(0, 45); cout << "                                            ";
	gotoxy(12, 8); cout << "      ";
	gotoxy(12, 8); fflush(stdin); cin >> lanthi;
	if (lanthi <= 0 || lanthi > 2)
	{
		gotoxy(0, 45); cout << "                                                     ";
		gotoxy(0, 45); SetColor(14); cout << "LAN THI NHAP 1 || 2!" << endl; Normal(); _getch();
		goto nhaplailanthi;
	}
	XuatDiemSVTrang1(dslop, vtrilop, mamh, lanthi);
nhaplaimasv:
	gotoxy(0, 45); cout << "                                                         ";
	gotoxy(41, 8); cout << "                  ";
	gotoxy(41, 8); fflush(stdin); get(masv);
	if (_stricmp(masv, "") == 0) goto nhaplaikey;
	if (SearchMaSV(dslop, masv) == NULL)
	{
		gotoxy(0, 45); cout << "                                                    ";
		gotoxy(0, 45); SetColor(14); cout << "MA SV KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimasv;
	}
	int dongxuat = 18;
	for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
	{
	hieuchinhdiem:
		if (_stricmp(p->sinhvien.MASV, masv) == 0)
		{
			for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
			{
				if ((_stricmp(q->diem.MAMH, mamh) == 0) && (q->diem.LAN == lanthi) && q->diem.DIEM > 0)
				{
				nhaplaidiem:
					gotoxy(60, dongxuat); cout << "   ";
					gotoxy(60, dongxuat); cin >> q->diem.DIEM;
					if (q->diem.DIEM < 0 || q->diem.DIEM > 10) { goto nhaplaidiem; }
					goto nhaplaikey;
				}
			}
		}
		dongxuat++;
		if (dongxuat == 43)
		{
			dongxuat = 17;
			system("cls"); GiaoDienHieuChinhDiem(); Normal();
			gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << mamh; gotoxy(12, 8); cout << lanthi; gotoxy(41, 8); cout << masv;
			XuatDiemSVTrang2(dslop, vtrilop, mamh, lanthi);
			goto hieuchinhdiem;
		}
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) NhapDiemSV(dslop, treemh);
	else if (key == F3) goto nhaplaimasv;
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienHieuChinhDiem(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << mamh; gotoxy(12, 8); cout << lanthi;
		XuatDiemSVTrang1(dslop, vtrilop, mamh, lanthi);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienHieuChinhDiem(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << mamh; gotoxy(12, 8); cout << lanthi;
		XuatDiemSVTrang2(dslop, vtrilop, mamh, lanthi);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

void XuatBangDiemMH(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienInBangDiemMH(); Normal();
	char malop[11]; char mamh[11]; int lanthi = 0;
nhaplaimalop:
	gotoxy(0, 45); cout << "                                                ";
	gotoxy(12, 4); cout << "                        ";
	gotoxy(12, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtrilop = SearchMaLop(dslop, malop);
	if (vtrilop == -1)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
nhaplaimamh:
	gotoxy(0, 45); cout << "                                                 ";
	gotoxy(12, 6); cout << "                     ";
	gotoxy(12, 6); fflush(stdin); get(mamh);
	if (_stricmp(mamh, "") == 0) goto nhaplaikey;
	PTRMONHOC t = SearchMaMH(treemh, mamh);
	if (t == NULL)
	{
		gotoxy(0, 45); cout << "                                                        ";
		gotoxy(0, 45); SetColor(14); cout << "MA MON HOC KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimamh;
	}
nhaplailanthi:
	gotoxy(0, 45); cout << "                                            ";
	gotoxy(12, 8); cout << "      ";
	gotoxy(12, 8); fflush(stdin); cin >> lanthi;
	if (lanthi <= 0 || lanthi > 2)
	{
		gotoxy(0, 45); cout << "                                                     ";
		gotoxy(0, 45); SetColor(14); cout << "LAN THI NHAP 1 || 2!" << endl; Normal(); _getch();
		goto nhaplailanthi;
	}
	gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
	gotoxy(29, wherey()); cout << lanthi << endl << endl;
	gotoxy(9, wherey()); cout << t->monhoc.TENMH << endl;
	int stt = 0; int dongxuat = 18;
	XuatDiemSVTrang1(dslop, vtrilop, mamh, lanthi);
nhaplaikey:
	int key = keyPressed();
	if (key == F1) XuatBangDiemMH(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienInBangDiemMH(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << mamh; gotoxy(12, 8); cout << lanthi;
		gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP; gotoxy(29, wherey()); cout << lanthi << endl << endl;
		gotoxy(9, wherey()); cout << t->monhoc.TENMH << endl;
		XuatDiemSVTrang1(dslop, vtrilop, mamh, lanthi);
		goto nhaplaikey;
	}
	else if (key == DownTrang)
	{
		system("cls"); GiaoDienInBangDiemMH(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(12, 6); cout << mamh; gotoxy(12, 8); cout << lanthi;
		gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP; gotoxy(29, wherey()); cout << lanthi << endl << endl;
		gotoxy(9, wherey()); cout << t->monhoc.TENMH << endl;
		XuatDiemSVTrang2(dslop, vtrilop, mamh, lanthi);
		goto nhaplaikey;
	}
	else goto nhaplaikey;
}

//--------------------------------------------------------------------------------------------------

PTRDIEM SearchDiem(PTRSV p, char *mamh, int lanthi, int &dem)
{
	for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
	{
		dem++;
		if (_strcmpi(q->diem.MAMH, mamh) == 0 && q->diem.LAN == lanthi) { return q; }
	}
	return NULL;
}

int TongSoTCofSV(DSLOP &dslop, int vtrilop, PTRMONHOC &treemh)
{
	int sumTC = 0;
	for (PTRDIEM d = dslop.nodes[vtrilop].ptrsv->sinhvien.ptrdiem; d != NULL; d = d->next)
	{
		PTRMONHOC t = SearchMaMH(treemh, d->diem.MAMH);
		if (d->diem.LAN == 1)
		{
			sumTC += t->monhoc.STCLT + t->monhoc.STCTH;
		}
	}
	return sumTC;
}

void XuatBangDiemTBtrang1(DSLOP &dslop, int vitri)
{
	int dongxuat = 18; int stt = 0;
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		stt++;
		if (stt <= 25)
		{
			gotoxy(4, dongxuat); cout << stt;
			gotoxy(10, dongxuat); cout << p->sinhvien.MASV;
			gotoxy(25, dongxuat); cout << p->sinhvien.HO;
			gotoxy(48, dongxuat); cout << p->sinhvien.TEN;
			dongxuat++;
		}
	}
}

void XuatBangDiemTBtrang2(DSLOP &dslop, int vtlop)
{
	int stt = 0; int dongxuat = 18;
	if (TongSoSV(dslop.nodes[vtlop].ptrsv) > 25)
	{
		for (PTRSV p = dslop.nodes[vtlop].ptrsv; p != NULL; p = p->next)
		{
			stt++;
			if (stt > 25)
			{
				gotoxy(4, dongxuat); cout << stt;
				gotoxy(10, dongxuat); cout << p->sinhvien.MASV;
				gotoxy(25, dongxuat); cout << p->sinhvien.HO;
				gotoxy(48, dongxuat); cout << p->sinhvien.TEN;
				dongxuat++;
			}
		}
	}
}

void XuatBangDiemTBMH(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienInBangDiemTB(); Normal();
	char malop[11];
nhaplaimalop:
	gotoxy(0, 45); cout << "                                                ";
	gotoxy(12, 4); cout << "                        ";
	gotoxy(12, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtrilop = SearchMaLop(dslop, malop);
	if (vtrilop == -1)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
	gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
	gotoxy(29, wherey()); cout << dslop.nodes[vtrilop].namnhaphoc;
	XuatBangDiemTBtrang1(dslop, vtrilop);
	float diemtb = 0; int dongxuat = 18;
diemtb:
	for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
	{
		int n = TongLanThimotSV(p->sinhvien.ptrdiem);
		int *danhdau = new int[n];
		for (int i = 1; i <= n; i++) { danhdau[i] = 0; }
		if (p->sinhvien.ptrdiem == NULL)
		{
			diemtb = 0;
			gotoxy(60, dongxuat); cout << diemtb;
		}
		else
		{
			for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
			{
				int dem1 = 0, dem2 = 0;
				PTRDIEM d1 = SearchDiem(p, q->diem.MAMH, 1, dem1);
				PTRDIEM d2 = SearchDiem(p, q->diem.MAMH, 2, dem2);
				PTRMONHOC t = SearchMaMH(treemh, q->diem.MAMH);
				if (d2 == NULL)
				{
					diemtb += (d1->diem.DIEM *(t->monhoc.STCLT + t->monhoc.STCTH)) / TongSoTCofSV(dslop, vtrilop, treemh);
				}
				else
				{
					if (danhdau[dem2] == 0 && danhdau[dem1] == 0)
					{
						danhdau[dem1] = 1; danhdau[dem2] = 1;
						if (d1->diem.DIEM > d2->diem.DIEM)
						{
							diemtb += (d1->diem.DIEM *(t->monhoc.STCLT + t->monhoc.STCTH)) / TongSoTCofSV(dslop, vtrilop, treemh);
						}
						else if (d1->diem.DIEM < d2->diem.DIEM)
						{
							diemtb += (d2->diem.DIEM *(t->monhoc.STCLT + t->monhoc.STCTH)) / TongSoTCofSV(dslop, vtrilop, treemh);
						}
						else if (d1->diem.DIEM == d2->diem.DIEM)
						{
							diemtb += (d1->diem.DIEM *(t->monhoc.STCLT + t->monhoc.STCTH)) / TongSoTCofSV(dslop, vtrilop, treemh);
						}
					}
				}

			}
			gotoxy(60, dongxuat); cout << setprecision(2) << diemtb;
			diemtb = 0;
			dongxuat++;
			if (dongxuat == 43)
			{
			nhaplainhan:
				int nhan = keyPressed();
				if (nhan == DownTrang)
				{
					system("cls"); GiaoDienInBangDiemTB(); Normal(); dongxuat = 18;
					gotoxy(12, 4); cout << malop; gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
					gotoxy(29, wherey()); cout << dslop.nodes[vtrilop].namnhaphoc;
					int dongnhap = 18;
					XuatBangDiemTBtrang2(dslop, vtrilop);
				}
				else goto nhaplainhan;
			}
		}
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) XuatBangDiemTBMH(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienInBangDiemTB(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
		gotoxy(29, wherey()); cout << dslop.nodes[vtrilop].namnhaphoc;
		XuatBangDiemTBtrang1(dslop, vtrilop); dongxuat = 18;
		goto diemtb;
	}
	else goto nhaplaikey;
}

void XuatBangDiemTongKettrang1(DSLOP &dslop, int vitri)
{
	int dongxuat = 18; int stt = 0;
	for (PTRSV p = dslop.nodes[vitri].ptrsv; p != NULL; p = p->next)
	{
		stt++;
		if (stt <= 25)
		{
			gotoxy(0, dongxuat); cout << stt;
			gotoxy(5, dongxuat); cout << p->sinhvien.MASV;
			gotoxy(15, dongxuat); cout << p->sinhvien.HO;
			gotoxy(27, dongxuat); cout << p->sinhvien.TEN;
			dongxuat++;
		}
	}
}

void XuatBangDiemTongKettrang2(DSLOP &dslop, int vtlop)
{
	int stt = 0; int dongxuat = 18;
	if (TongSoSV(dslop.nodes[vtlop].ptrsv) > 25)
	{
		for (PTRSV p = dslop.nodes[vtlop].ptrsv; p != NULL; p = p->next)
		{
			stt++;
			if (stt > 25)
			{
				gotoxy(0, dongxuat); cout << stt;
				gotoxy(5, dongxuat); cout << p->sinhvien.MASV;
				gotoxy(15, dongxuat); cout << p->sinhvien.HO;
				gotoxy(27, dongxuat); cout << p->sinhvien.TEN;
				dongxuat++;
			}
		}
	}
}

int VitriMaMH(PTRDIEM p, MONHOC mh[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (_stricmp(p->diem.MAMH, mh[i].MAMH) == 0) return i;
	}
	return -1;
}

void XuatBangDiemTongKet(DSLOP &dslop, PTRMONHOC &treemh)
{
	system("cls"); GiaoDienInBangTongKet(); Normal();
	char malop[11]; MONHOC mh[MAXLOP]; int nmh = 0;
	gotoxy(25, 16); DSTTMonHoc(treemh, mh, nmh);
	for (int i = 0; i < nmh; i++){ SetColor(14); gotoxy(34 + i * 10, 16); cout << mh[i].MAMH; } Normal();
nhaplaimalop:
	gotoxy(0, 45); cout << "                                                ";
	gotoxy(12, 4); cout << "                        ";
	gotoxy(12, 4); fflush(stdin); get(malop);
	if (_stricmp(malop, "") == 0) goto nhaplaikey;
	int vtrilop = SearchMaLop(dslop, malop);
	if (vtrilop == -1)
	{
		gotoxy(0, 45); cout << "                                            ";
		gotoxy(0, 45); SetColor(14); cout << "MA LOP KHONG CO TRONG DANH SACH!" << endl; _getch(); Normal();
		goto nhaplaimalop;
	}
	gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
	gotoxy(29, wherey()); cout << dslop.nodes[vtrilop].namnhaphoc;
bangtongket:
	XuatBangDiemTongKettrang1(dslop, vtrilop);
	int dongxuat = 18;
	for (PTRSV p = dslop.nodes[vtrilop].ptrsv; p != NULL; p = p->next)
	{
		int n = TongLanThimotSV(p->sinhvien.ptrdiem);
		int *danhdau = new int[n];
		for (int i = 1; i <= n; i++) { danhdau[i] = 0; }
		if (p->sinhvien.ptrdiem == NULL) { p = p->next; dongxuat++; }
		else
		{
			for (PTRDIEM q = p->sinhvien.ptrdiem; q != NULL; q = q->next)
			{
				int dem1 = 0, dem2 = 0;
				PTRDIEM d1 = SearchDiem(p, q->diem.MAMH, 1, dem1);
				PTRDIEM d2 = SearchDiem(p, q->diem.MAMH, 2, dem2);
				PTRMONHOC t = SearchMaMH(treemh, q->diem.MAMH);
				if (d2 == NULL)
				{
					int vitrimh = VitriMaMH(q, mh, nmh);
					gotoxy(34 + vitrimh * 10, dongxuat); cout << d1->diem.DIEM;
				}
				else
				{
					if (danhdau[dem2] == 0 && danhdau[dem1] == 0)
					{
						danhdau[dem1] = 1; danhdau[dem2] = 1;
						if (d1->diem.DIEM > d2->diem.DIEM)
						{
							int vitrimh = VitriMaMH(q, mh, nmh);
							gotoxy(34 + vitrimh * 10, dongxuat); cout << d1->diem.DIEM;
						}
						else if (d1->diem.DIEM < d2->diem.DIEM)
						{
							int vitrimh = VitriMaMH(q, mh, nmh);
							gotoxy(34 + vitrimh * 10, dongxuat); cout << d2->diem.DIEM;
						}
						else if (d1->diem.DIEM == d2->diem.DIEM)
						{
							int vitrimh = VitriMaMH(q, mh, nmh);
							gotoxy(34 + vitrimh * 10, dongxuat); cout << d1->diem.DIEM;
						}
					}
				}
			}
			dongxuat++;
			if (dongxuat == 43)
			{
			nhaplainhan:
				int nhan = keyPressed();
				if (nhan == DownTrang)
				{
					system("cls"); GiaoDienInBangTongKet(); Normal(); dongxuat = 18;
					gotoxy(12, 4); cout << malop; gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
					gotoxy(29, wherey()); cout << dslop.nodes[vtrilop].namnhaphoc;
					int dongnhap = 18;
					for (int i = 0; i < nmh; i++){ SetColor(14); gotoxy(34 + i * 10, 16); cout << mh[i].MAMH; } Normal();
					XuatBangDiemTongKettrang2(dslop, vtrilop);
				}
				else goto nhaplainhan;
			}
		}
	}
nhaplaikey:
	int key = keyPressed();
	if (key == F1) XuatBangDiemTongKet(dslop, treemh);
	else if (key == F4) Run(dslop, treemh);
	else if (key == UpTrang)
	{
		system("cls"); GiaoDienInBangTongKet(); Normal();
		gotoxy(12, 4); cout << malop; gotoxy(5, 12); cout << dslop.nodes[vtrilop].TENLOP;
		gotoxy(29, wherey()); cout << dslop.nodes[vtrilop].namnhaphoc;
		for (int i = 0; i < nmh; i++){ SetColor(14); gotoxy(34 + i * 10, 16); cout << mh[i].MAMH; } Normal();
		XuatBangDiemTongKettrang1(dslop, vtrilop); dongxuat = 18;
		goto bangtongket;
	}
	else goto nhaplaikey;
}

//File
const char *filePathLopSVDiem = "C:/Users/ANH TUAN/Desktop/DataLopSVDiem.txt";
const char *filePathMonHoc = "C:/Users/ANH TUAN/Desktop/DataMonHoc.txt";
fstream fileLopSVDiem;
fstream fileMonHoc;

void GhiFileLopSVDiem(DSLOP &dslop)
{
	fileLopSVDiem.open(filePathLopSVDiem, ios::out);
	if (!fileLopSVDiem)
	{
		gotoxy(0, 2); SetColor(14); cout << "KHONG THE MO FILE!"; Normal();
		return;
	}
	fileLopSVDiem.write((char *)&dslop.n, sizeof(int));
	for (int i = 0; i < dslop.n; i++)
	{
		fileLopSVDiem.write((char *)&dslop.nodes[i], sizeof(LOP));
		int siso = TongSoSV(dslop.nodes[i].ptrsv);
		fileLopSVDiem.write((char *)&siso, sizeof(int));
		if (siso > 0)
		{
			for (PTRSV Firstsv = dslop.nodes[i].ptrsv; Firstsv != NULL; Firstsv = Firstsv->next)
			{
				fileLopSVDiem.write((char *)&Firstsv->sinhvien, sizeof(SINHVIEN));
				int solt = TongLanThimotSV(Firstsv->sinhvien.ptrdiem);
				fileLopSVDiem.write((char *)&solt, sizeof(int));
				if (solt > 0)
				{
					for (PTRDIEM FirstD = Firstsv->sinhvien.ptrdiem; FirstD != NULL; FirstD = FirstD->next)
					{
						fileLopSVDiem.write((char *)&FirstD->diem, sizeof(DIEMMONHOC));
					}
				}
			}
		}
	}
	fileLopSVDiem.close();
}

void DocFileLopSVDiem(DSLOP &dslop)
{
	SINHVIEN sv; DIEMMONHOC diem; int siso = 0, solt = 0;
	fileLopSVDiem.open(filePathLopSVDiem, ios::in);
	if (!fileLopSVDiem)
	{
		gotoxy(0, 2); SetColor(14); cout << "KHONG THE MO FILE!"; Normal();
		return;
	}
	fileLopSVDiem.read((char *)&dslop.n, sizeof(int));
	for (int i = 0; i < dslop.n; i++)
	{
		fileLopSVDiem.read((char *)&dslop.nodes[i], sizeof(LOP));
		dslop.nodes[i].ptrsv = NULL;
		fileLopSVDiem.read((char *)&siso, sizeof(int));
		if (siso > 0)
		{
			for (int j = 0; j < siso; j++)
			{
				fileLopSVDiem.read((char *)&sv, sizeof(SINHVIEN));
				Insert_LastSV(dslop.nodes[i].ptrsv, sv);
				PTRSV p = SearchMaSV(dslop, sv.MASV);
				p->sinhvien.ptrdiem = NULL;
				fileLopSVDiem.read((char *)&solt, sizeof(int));
				if (solt > 0)
				{
					for (int k = 0; k < solt; k++)
					{
						fileLopSVDiem.read((char *)&diem, sizeof(DIEMMONHOC));
						Insert_LastDiem(p->sinhvien.ptrdiem, diem);
					}
				}
			}
		}
	}
	fileLopSVDiem.close();
}

void OpenFileMH()
{
	fileMonHoc.open(filePathMonHoc, ios::out);
	if (!fileMonHoc)
	{
		gotoxy(0, 2); SetColor(14); cout << "KHONG THE MO FILE!"; Normal();
		return;
	}
}

void GhiFileTongMonHoc(PTRMONHOC &treemh)
{
	int tongsoMH = TongSoMH(treemh);
	fileMonHoc.write((char *)&tongsoMH, sizeof(int));
}

void GhiFileMonHoc(PTRMONHOC &treemh)
{
	if (treemh != NULL)
	{
		fileMonHoc.write((char *)&treemh->monhoc, sizeof(MONHOC));
		GhiFileMonHoc(treemh->left);
		GhiFileMonHoc(treemh->right);
	}
}

void CloseFileMH()
{
	fileMonHoc.close();
}


void DocFileMonHoc(PTRMONHOC &treemh)
{

	MONHOC mh; int tongsoMH = 0;
	fileMonHoc.open(filePathMonHoc, ios::in);
	fileMonHoc.read((char *)&tongsoMH, sizeof(int));
	KhoiTao(treemh);
	if (tongsoMH > 0)
	{
		for (int i = 0; i < tongsoMH; i++)
		{
			fileMonHoc.read((char *)&mh, sizeof(MONHOC));
			Insert_node(treemh, mh);
		}
	}
	fileMonHoc.close();
}

//Chay CT
void Run(DSLOP &dslop, PTRMONHOC &treemh)
{
	MONHOC mh[MAXLOP]; int nMH = 0;
	int key1 = 0; int key2 = 0;
	int chon;
	while (1)
	{
		chon = MenuDongChinh(thucdonchinh);
		system("cls");
		switch (chon)
		{
		case 1:
			NhapLop(dslop, treemh);
			break;
		case 2:
			XuatDSLopTheoNK(dslop, treemh);
			break;
		case 3:
			NhapSinhVien(dslop, treemh);
			break;
		case 4:
			XuatSVMotLop(dslop, treemh);
			break;
		case 5:
			NhapMonHoc(dslop, treemh);
			break;
		case 6:
			DSTTMonHoc(treemh, mh, nMH);
			XuatDSMonHocTen(dslop, treemh, mh, nMH);
			break;
		case 7:
			NhapDiemSV(dslop, treemh);
			break;
		case 8:
			XuatBangDiemMH(dslop, treemh);
			break;
		case 9:
			XuatBangDiemTBMH(dslop, treemh);
			break;
		case 10:
			XuatBangDiemTongKet(dslop, treemh);
			break;
		case 11:
			Normal(); system("cls"); gotoxy(0, 2); SetColor(14); cout << "CHAP NHAN GHI FILE ?(F1: CO / F4: KHONG)";
		nhaplaikey1:
			key1 = keyPressed();
			if (key1 == F1)
			{
				GhiFileLopSVDiem(dslop);
				OpenFileMH();
				GhiFileTongMonHoc(treemh);
				GhiFileMonHoc(treemh);
				CloseFileMH();
			}
			else if (key1 == F4) Run(dslop, treemh);
			else goto nhaplaikey1;
			break;
		case 12:
			Normal(); system("cls"); gotoxy(0, 2); SetColor(14); cout << "CHAP NHAN DOC FILE ?(F1: CO / F4: KHONG)";
		nhaplaikey2:
			key2 = keyPressed();
			if (key2 == F1)
			{
				DocFileLopSVDiem(dslop);
				DocFileMonHoc(treemh);
			}
			else if (key2 == F4) Run(dslop, treemh);
			else goto nhaplaikey2;
			break;
		case 13: exit(0);
		default:
			break;
		}
		if (chon == so_itemchinh) break;
	}
}

int main()
{
	PTRMONHOC treemh;
	DSLOP dslop;

	KhoiTao(treemh);
	Run(dslop, treemh);

	system("pause");
	return 0;
}
