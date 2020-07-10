object Form2: TForm2
  Left = 441
  Top = 207
  BorderIcons = [biMinimize, biMaximize]
  Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1084#1072#1089#1090#1100'!'
  ClientHeight = 191
  ClientWidth = 315
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object Suit: TRadioGroup
    Left = 0
    Top = 0
    Width = 315
    Height = 191
    Align = alClient
    ItemIndex = 0
    Items.Strings = (
      'DIAMONDS'
      'HEARTS'
      'CLUBS'
      'SPADES')
    TabOrder = 0
    ExplicitWidth = 417
    ExplicitHeight = 201
  end
  object BitBtn1: TBitBtn
    Left = 176
    Top = 80
    Width = 105
    Height = 41
    Kind = bkOK
    NumGlyphs = 2
    TabOrder = 1
  end
end
