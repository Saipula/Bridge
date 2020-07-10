// ---------------------------------------------------------------------------

#ifndef suitH
#define suitH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TForm2 : public TForm {
__published: // IDE-managed Components
	TRadioGroup *Suit;
	TBitBtn *BitBtn1;

private: // User declarations
public: // User declarations
	__fastcall TForm2(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
// ---------------------------------------------------------------------------
#endif
