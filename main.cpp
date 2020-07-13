// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "MyClasses.h"
#include <ctime>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
Game *game;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
	srand(time(NULL));
	game = new Game(ImageList, this->Canvas, Image1->Picture);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::RestClick(TObject *Sender) {
	game->cleer();
	game = new Game(ImageList, this->Canvas, Image1->Picture);
	Timer1->Enabled = true;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y) {
	if (Button == mbLeft)
		game->click(TPoint(X, Y));
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender) {
	if (game->End) {
		Timer1->Enabled = false;
		ShowMessage("Нет ходов, игра окончена!");
		RestClick(Sender);
	}

	if (game->Win(0)) {
		Timer1->Enabled = false;
		ShowMessage("Вы победили!");
		RestClick(Sender);
	}
	else if (game->Win(1)) {
		Timer1->Enabled = false;
		ShowMessage("Бот победил!");
		RestClick(Sender);
	}

	game->Hod();
}
// ---------------------------------------------------------------------------

