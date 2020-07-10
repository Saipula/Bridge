// ---------------------------------------------------------------------------

#pragma hdrstop

#include "MyClasses.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Game::Game(TImageList *list, TCanvas *canv) {
	device = canv;
	imgW = list->Width;
	imgH = list->Height;

	IterCart = 0;

	cartFon = new TPicture();
	list->GetBitmap(36, cartFon->Bitmap);

	pl1 = new Player(device, TPoint(100, 300), imgW, imgH, cartFon);
	bot = new Bot(device, TPoint(100, 0), imgW, imgH, cartFon);

	SUIT suit[4] = {DIAMONDS, HEARTS, CLUBS, SPADES};

	for (int i = 0; i < 36; i++) {
		TPicture *tmpPict = new TPicture();
		list->GetBitmap(i, tmpPict->Bitmap);
		carts[i] = new Carta(tmpPict, i / 4 + 6, suit[i % 4], false);
	}

	rand_cart();

	for (int i = 0; i < 6; i++, IterCart++) {
		pl1->add(carts[IterCart]);
	}

	for (int i = 0; i < 6; i++, IterCart++) {
		bot->add(carts[IterCart]);
	}

	cartNaStole = carts[IterCart];
	cartNaStole.Visible = true;
	IterCart++;

	End = false;
}

void Game::rand_cart() {
	for (int i = 0; i < 36; i++)
		std::swap(carts[i], carts[rand() % 36]);
}

void Game::show() {
	pl1->draw();
	bot->draw();
	device->Draw(550, 130, cartNaStole.cartImg->Graphic);

	if (IterCart < 36)
		device->Draw(650, 130, cartFon->Graphic);
	else {
		device->Pen->Color = clBtnFace;
		device->Brush->Color = clBtnFace;
		device->Rectangle(650, 130, imgW, imgH);
	}
}

void Game::click(TPoint click) {
	if (pl1->Hod) {
		cartNaStole = pl1->Click(new Carta(cartNaStole), click);

		if (cartNaStole.Value == 14) {
			if (pl1->proverka(new Carta(cartNaStole)) == 0 && IterCart < 36) {
				pl1->add(carts[IterCart]);
				IterCart++;

				pl1->Hod = false;
				bot->Hod = true;
			}
		}
		else if (cartNaStole.Value == 12 && cartNaStole.Suit == SPADES) {
			for (short i = 0; i < 5 && IterCart < 36; i++, IterCart++) {
				bot->add(carts[IterCart]);
			}
		}
		else if (cartNaStole.Value == 8) {
			for (short i = 0; i < 2 && IterCart < 36; i++, IterCart++) {
				bot->add(carts[IterCart]);
			}
		}
		else if (cartNaStole.Value == 6) {
			if (pl1->proverka(new Carta(cartNaStole)) == 0 && IterCart < 36) {
				pl1->add(carts[IterCart]);
				IterCart++;
			}
		}
		else if (cartNaStole.Value == 7) {
			if (IterCart < 36) {
				bot->add(carts[IterCart]);
				IterCart++;
				pl1->Hod = false;
				bot->Hod = true;
			}
		}
		else if (cartNaStole.Value == 11) {
			SUIT suit[4] = {DIAMONDS, HEARTS, CLUBS, SPADES};
			SUIT tmp;
			if (Form2->ShowModal() == mrOk) {
				tmp = suit[Form2->Suit->ItemIndex];
			}

			for (short i = 0; i < 36; i++) {
				if (carts[i]->Suit == tmp && carts[i]->Value == 11) {
					cartNaStole = carts[i];
					break;
				}
			}

			pl1->Hod = false;
			bot->Hod = true;
		}
		else {
			pl1->Hod = false;
			bot->Hod = true;
		}
	}
	show();
}

bool Game::Win(short i) {
	if (i == 1)
		if (bot->carts.size() == 0)
			return true;
		else if (i == 0)
			if (pl1->carts.size() == 0)
				return true;
	return false;
}

void Game::Hod() {
	if (bot->Hod) {
		short prov = bot->proverka(new Carta(cartNaStole));

		if (prov == 0 && cartNaStole.Value != 6) {
			if (IterCart > 35) {
				End = true;
				show();
				return;
			}
			bot->add(carts[IterCart]);
			IterCart++;

			pl1->Hod = true;
			bot->Hod = false;
			show();
			return;
		}

		cartNaStole = bot->hod(new Carta(cartNaStole));
		cartNaStole.Visible = true;

		if (cartNaStole.Value == 14) {
			if (prov == 0 && IterCart < 36) {
				bot->add(carts[IterCart]);
				IterCart++;

				pl1->Hod = true;
				bot->Hod = false;
			}
		}
		else if (cartNaStole.Value == 12 && cartNaStole.Suit == SPADES) {
			for (short i = 0; i < 5 && IterCart < 36; i++, IterCart++) {
				pl1->add(carts[IterCart]);
			}
		}
		else if (cartNaStole.Value == 8) {
			for (short i = 0; i < 2 && IterCart < 36; i++, IterCart++) {
				pl1->add(carts[IterCart]);
			}
		}
		else if (cartNaStole.Value == 6) {
			if (prov == 0 && IterCart < 36) {
				bot->add(carts[IterCart]);
				IterCart++;
			}
		}
		else if (cartNaStole.Value == 7) {
			if (IterCart < 36) {
				pl1->add(carts[IterCart]);
				IterCart++;
				pl1->Hod = true;
				bot->Hod = false;
			}
		}
		else if (cartNaStole.Value == 11) {
			SUIT suit[4] = {DIAMONDS, HEARTS, CLUBS, SPADES};
			SUIT tmp = suit[rand() % 4];
			for (short i = 0; i < 36; i++) {
				if (carts[i]->Suit == tmp && carts[i]->Value == 11) {
					cartNaStole = carts[i];
					break;
				}
			}

			pl1->Hod = true;
			bot->Hod = false;
		}
		else {
			pl1->Hod = true;
			bot->Hod = false;
		}
	}

	else if (pl1->Hod) {
		short prov = pl1->proverka(new Carta(cartNaStole));
		if (prov == 2) {

		}
		else if (prov == 0 && IterCart < 36) {
			if (IterCart > 35) {
				End = true;
				show();
				return;
			}

			pl1->add(carts[IterCart]);
			IterCart++;

			pl1->Hod = false;
			bot->Hod = true;
		}
		show();
	}
	show();
}

void Game::cleer() {
	bot->clear();
	pl1->clear();
}

Carta Bot::hod(Carta *carta) {
	for (int i = 0; i < carts.size(); i++) {
		if ((carts[i]->Suit == carta->Suit) ||
			(carts[i]->Value == carta->Value)) {
			clear();
			Carta *tmp = new Carta(carts[i]);
			carts.erase(carts.begin() + i);
			return tmp;
		}
	}
	return carta;
}

Player::Player(TCanvas *canv, TPoint Start, int W, int H, TPicture *cartFon) {
	device = canv;
	this->cartFon = cartFon;
	this->Start = new TPoint(Start.x, Start.y);
	imgW = W;
	imgH = H;
	Visible = true;
	Hod = true;
}

void Player::add(Carta *carta) {
	carta->Visible = Visible;
	carts.push_back(carta);
}

void Player::draw() {
	for (int i = 0; i < carts.size(); i++) {
		if (carts[i]->Visible)
			device->Draw(Start->x + i * imgW, Start->y,
			carts[i]->cartImg->Graphic);
		else
			device->Draw(Start->x + i * imgW, Start->y, cartFon->Graphic);
	}
}

Carta Player::Click(Carta *carta, TPoint click) {
	if (click.y < Start->y || click.y > Start->y + imgH)
		return carta;
	if (click.x < Start->x || click.x > Start->x + imgW * carts.size())
		return carta;

	for (int i = 0; i < carts.size(); i++) {
		if (i == (click.x - Start->x) / imgW) {
			if ((carts[i]->Suit == carta->Suit) ||
				(carts[i]->Value == carta->Value)) {
				clear();
				Carta *tmp = new Carta(carts[i]);
				carts.erase(carts.begin() + i);
				return tmp;
			}
		}
	}
	return carta;
}

void Player::clear() {
	device->Pen->Color = clBtnFace;
	device->Brush->Color = clBtnFace;
	device->Rectangle(Start->x, Start->y, Start->x * carts.size() * imgW,
		Start->y + imgH);
}

short Player::proverka(Carta *carta) {
	if (carts.size() == 0)
		return 2;
	for (int i = 0; i < carts.size(); i++) {
		if ((carts[i]->Suit == carta->Suit) ||
			(carts[i]->Value == carta->Value))
			return 1;
	}
	return 0;
}
