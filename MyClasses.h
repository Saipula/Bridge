// ---------------------------------------------------------------------------

#ifndef MyClassesH
#define MyClassesH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <vector>
#include "suit.h"

// ---------------------------------------------------------------------------
enum SUIT // �����
{
	// ����
	DIAMONDS,
	// �����
		HEARTS,
	// �����
		CLUBS,
	// ����
		SPADES
};

struct Carta {
	SUIT Suit; // �����
	short Value; // �������� ����� �� 6 �� ����
	bool Visible; // ��������� �����
	TPicture *cartImg; // ������� �����

	Carta(TPicture *cartImg, short Value, SUIT Suit, bool Visible) {
		this->cartImg = cartImg;
		this->Value = Value;
		this->Suit = Suit;
		this->Visible = Visible;
	}

	Carta(Carta *carta) {
		this->cartImg = carta->cartImg;
		this->Value = carta->Value;
		this->Suit = carta->Suit;
		this->Visible = carta->Visible;
	}

	Carta() {
	}
};

class Player { // ����� ������
protected:
	TPicture *cartFon; // ������� ����

	bool Visible; // ��������� ����

	TCanvas *device;
	int imgW, imgH;

public:
	bool Hod;

	std::vector<Carta*>carts; // ���� ����

	TPoint *Start; // ���������� ������ ��������� ����    S

	// �����������
	Player(TCanvas *canv, TPoint Start, int W, int H, TPicture *cartFon);
	// �������� �����
	void add(Carta *carta);
	// ���������� �����
	void draw();
	// ����� ��� ������� �� �����
	Carta Click(Carta *carta, TPoint click);
	// �������� ���� �� ��� ������
	short proverka(Carta *carta);
	// ������� ����� ����� �������� �����
	void clear();
};

class Bot : public Player {
public:
	Bot(TCanvas *canv, TPoint Start, int W, int H, TPicture *cartFon)
		: Player(canv, Start, W, H, cartFon) {
		Visible = false;
		Hod = false;
	}
	Carta hod(Carta *carta);
};

class Game {
	TPicture *cartFon; // ������� ����
	Carta *carts[36]; // ���� � �������
	Carta cartNaStole; // ����� �� �����
	TCanvas *device; // ������� �� ������� �������� ��
	int imgW, imgH; // ������ � ������ ����
	int IterCart; // �������, ��� ���� ����� "���������" ����� �� ������

	Player *pl1; // �����
	Bot *bot;

	void rand_cart(); // ������������� ���� � ������

public:
	bool End;

	Game(TImageList *list, TCanvas *canv);
	void show(); // ����������� ����
	void click(TPoint click); // ������� �� �����
	bool Win(short i);
	void Hod(); // ��� ����������
	void cleer();
};

#endif
