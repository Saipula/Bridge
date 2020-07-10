// ---------------------------------------------------------------------------

#ifndef MyClassesH
#define MyClassesH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <vector>
#include "suit.h"

// ---------------------------------------------------------------------------
enum SUIT // Масть
{
	// буби
	DIAMONDS,
	// червы
		HEARTS,
	// трефы
		CLUBS,
	// пики
		SPADES
};

struct Carta {
	SUIT Suit; // масть
	short Value; // значение карты от 6 до туза
	bool Visible; // Видимость карты
	TPicture *cartImg; // Рисунок карты

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

class Player { // Класс игрока
protected:
	TPicture *cartFon; // Рубашка карт

	bool Visible; // Видимость карт

	TCanvas *device;
	int imgW, imgH;

public:
	bool Hod;

	std::vector<Carta*>carts; // Лист карт

	TPoint *Start; // Координаты начала отрисовки карт    S

	// Конструктор
	Player(TCanvas *canv, TPoint Start, int W, int H, TPicture *cartFon);
	// Добавить карту
	void add(Carta *carta);
	// Отобразить карты
	void draw();
	// Метод при нажатии на экран
	Carta Click(Carta *carta, TPoint click);
	// Проверка есть ли чем ходить
	short proverka(Carta *carta);
	// Очистка места после удаления карты
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
	TPicture *cartFon; // Рубашка карт
	Carta *carts[36]; // Ящик с картами
	Carta cartNaStole; // Карта на столе
	TCanvas *device; // Полотно на котором рисуется всё
	int imgW, imgH; // Ширина и высота карт
	int IterCart; // Счётчик, для того чтобы "доставать" карты из колоды

	Player *pl1; // Игрок
	Bot *bot;

	void rand_cart(); // Перемешивание карт в колоде

public:
	bool End;

	Game(TImageList *list, TCanvas *canv);
	void show(); // Отображение карт
	void click(TPoint click); // Нажатие на карту
	bool Win(short i);
	void Hod(); // Ход противника
	void cleer();
};

#endif
