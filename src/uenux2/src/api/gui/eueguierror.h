#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeGuiError {
    // the values are the codes api::CBmpConversor::VerticalFlip (target fn 3664) throws; the names are chosen from its
    // messages, "Dado de entrada nulo" and "Dimensões inválidas": no evidence names them
    EUE_GUI_VERTICALFLIP_DADO_NULO = 4900,
    EUE_GUI_VERTICALFLIP_DIMENSOES_INVALIDAS = 4901,
    // the code api::CBmpConversor::CreateBitmapHeader throws (record cbmpconversor.cpp 122:15) is not in the target's code;
    // read as docs/reference/facts/reading.md R1 reads such a record, binaryen inlined the function into its one caller,
    // fn 10967, and folded the constant argument the test reads, the test and the throw with it. The value is chosen, the
    // gap in CBmpConversor's run (4900, 4901, 4903), and so is the name, from the message chosen for the throw, "Numero
    // de cores nao suportado", a literal no target function loads (R1 again)
    EUE_GUI_CREATEBITMAPHEADER_CORES_NAO_SUPORTADAS = 4902,
    // the value is the code api::CBmpConversor::InvertColors (target fn 3663) throws; the name is chosen from its message,
    // "Dado de entrada nulo": no evidence names it
    EUE_GUI_INVERTCOLORS_DADO_NULO = 4903,
    // the value is the code api::CFixedImage::CFixedImage(const std::string &) (target fn 2246) throws; the name is chosen
    // from its message, "Nome do arquivo vazio": no evidence names it
    EUE_GUI_FIXEDIMAGE_NOME_VAZIO = 4913,
    // the value is the code api::CFormBuilder::GetLabeledKeyPos (target fn 5544) throws; the name is chosen from its
    // message, "Alinhamento desconhecido ({})": no evidence names it
    EUE_GUI_GETLABELEDKEYPOS_ALINHAMENTO_DESCONHECIDO = 4914,
    // the values are the codes api::CFramedText::MaskText (target fn 2780) and api::CGrayedFramedText::MaskText (target fn
    // 5534) throw; the names are chosen from their message, "Texto [" + text + "] eh grande demais": no evidence names
    // them
    EUE_GUI_FRAMEDTEXT_TEXTO_GRANDE_DEMAIS = 4917,
    EUE_GUI_GRAYEDFRAMEDTEXT_TEXTO_GRANDE_DEMAIS = 4918,
    // the value is the code api::CImageFieldUpdate's constructor throws (record cimagefieldupdate.cpp 32:15, inlined into
    // fn 3059); the name is chosen from its message, "Campo estava com a imagem nula": no evidence names it
    EUE_GUI_IMAGEFIELDUPDATE_IMAGEM_NULA = 4921,
    // the value is the code api::CDSImageField's constructor throws (record cdsimagefield.cpp 29:15, inlined into fn 502);
    // the name is chosen from its message, "A fonte de dados não pode ser nula": no evidence names it
    EUE_GUI_DSIMAGEFIELD_FONTE_NULA = 4923,
    // the value is the code api::CMenuItem::SetSearchText (target fn 3655) throws; the name is chosen from its message,
    // "Texto de busca repetido [" + text + "]!": no evidence names it
    EUE_GUI_MENUITEM_BUSCA_REPETIDA = 4929,
    // the values are the codes api::CInteractiveFormBuilder::AddLabeledInputControl (target fn 653) throws: 4936 in its
    // lambda over a key (record cinteractiveformbuilder.cpp 76:23), 4937 past three keys (86:15); the names are chosen
    // from their messages, "Tecla de controle não suportada '{}'" and "O número máximo de teclas suportado é {}": no
    // evidence names them
    EUE_GUI_INTERACTIVEFORMBUILDER_TECLA_NAO_SUPORTADA = 4936,
    EUE_GUI_INTERACTIVEFORMBUILDER_MAXIMO_DE_TECLAS = 4937,
    // the value is the code api::CLedFieldMT::Draw (target fn 11050) throws; the name is chosen from its message,
    // "Operação desconhecida {}": no evidence names it
    EUE_GUI_LEDFIELDMT_OPERACAO_DESCONHECIDA = 4940,
    // the value is the code api::CMovie::CMovie (target fn 5526) throws; the name is chosen from its message, "Não
    // havia frames": no evidence names it
    EUE_GUI_MOVIE_SEM_FRAMES = 4943,
    // the values are the codes api::CProgressBar's constructor throws (records cprogressbar.cpp 52:15, 58:15 and 67:15,
    // inlined into target fn 5545); the names are chosen from their messages, "Limite inferior ({}) >= limite superior
    // ({})", "Largura da barra ({}) não comporta a margem ({})" and "Altura da barra ({}) não comporta a margem ({})": no
    // evidence names them
    EUE_GUI_PROGRESSBAR_LIMITES_INVALIDOS = 4944,
    EUE_GUI_PROGRESSBAR_LARGURA_INSUFICIENTE = 4945,
    EUE_GUI_PROGRESSBAR_ALTURA_INSUFICIENTE = 4946,
    // the value is the code api::CQRCodeGuard's constructor (target fn 5502) throws; the name is chosen from its message,
    // "Não foi possível criar o QR code": no evidence names it
    EUE_GUI_QRCODEGUARD_FALHA_AO_CRIAR = 4947,
    // the value is the code api::CQRCodeImage::MontaImagem throws (record cqrcodeimage.cpp 36:15, inlined into fn 10967);
    // the name is chosen from its message, "A largura do qrcode ({}) superou o espaço disponível ({})": no evidence names it
    EUE_GUI_QRCODEIMAGE_LARGURA_EXCEDIDA = 4948,
    // 4949 and 4951: the codes api::CQRCodeImagePaper::MontaImagem throws (records cqrcodeimagepaper.cpp 35:15 and
    // 49:15, held inlined by fn 2772); the names are chosen from their messages, "Criação de QRCode com texto vazio."
    // and "A largura do qrcode ({}) superou o espaço disponível ({})". 4950: its throw at 38:15, whose test binaryen
    // folded with the width every caller passes; the value is chosen (the gap between the two), and so is the name,
    // from the message chosen for it, "Criação de QRCode com largura 0.", the one literal of that sense no function
    // loads. No evidence names them.
    EUE_GUI_QRCODEIMAGEPAPER_TEXTO_VAZIO = 4949,
    EUE_GUI_QRCODEIMAGEPAPER_LARGURA_ZERO = 4950,
    EUE_GUI_QRCODEIMAGEPAPER_LARGURA_EXCEDIDA = 4951,
    // the value is the code api::CTextBox's constructor throws (record ctextbox.cpp 41:15, inlined into fn 11805); the name
    // is chosen from its message, the same as 4963's: no evidence names it
    EUE_GUI_TEXTBOX_POSICAO_INICIAL_INVALIDA = 4961,
    // the value is the code api::CTextBox::Draw (target fn 10958) throws; the name is chosen from its message, "Status
    // indefinido": no evidence names it
    EUE_GUI_TEXTBOX_STATUS_INDEFINIDO = 4962,
    // the value is the code api::CTextBox::Move (target fn 10957) throws; the name is chosen from its message, "A
    // posição da caixa não pode ter x < 3 ou y < 1.": no evidence names it
    EUE_GUI_TEXTBOX_POSICAO_INVALIDA = 4963,
    // the value is the code api::CTextField::CTextField (target fn 1918) throws; the name is chosen from its message,
    // "Campo estava com o texto nulo", as 4972's was: no evidence names it
    EUE_GUI_TEXTFIELD_TEXTO_NULO = 4964,
    // the values are the codes api::CTextFieldBlinking's constructor throws (records ctextfieldblinking.cpp 39:15 and 42:15,
    // inlined into fn 1265); the names are chosen from its messages, "Campo estava com o texto nulo" and "As cores estavam
    // iguais": no evidence names them
    EUE_GUI_TEXTFIELDBLINKING_TEXTO_NULO = 4965,
    EUE_GUI_TEXTFIELDBLINKING_CORES_IGUAIS = 4966,
    // the values are the codes api::CTextFieldDoubleLine's constructor (target fn 3659) throws; the names are chosen from
    // its messages, "Campo estava com o texto nulo" and "maxX menor que a posição x da linha 1" (and "... linha 2"): no
    // evidence names them
    EUE_GUI_TEXTFIELDDOUBLELINE_TEXTO_NULO = 4967,
    EUE_GUI_TEXTFIELDDOUBLELINE_MAXX_MENOR_LINHA1 = 4968,
    EUE_GUI_TEXTFIELDDOUBLELINE_MAXX_MENOR_LINHA2 = 4969,
    // the value is the code api::CTextFieldMT::CTextFieldMT (target fn 1262) throws; the name is chosen from its message,
    // "Campo estava com o texto nulo": no evidence names it
    EUE_GUI_TEXTFIELDMT_TEXTO_NULO = 4970,
    EUE_GUI_TEXTFIELDMULTILINE_TEXTO_NULO = 4972,
    // the value is the code api::CTextFieldPaper::CTextFieldPaper (target fn 2771) throws; the name is chosen from its
    // message, "Campo estava com o texto nulo": no evidence names it
    EUE_GUI_TEXTFIELDPAPER_TEXTO_NULO = 4973,
    // the value is the code api::CTextFieldUpdate::CTextFieldUpdate (target fn 3658) throws; the name is chosen from its
    // message, "Campo estava com o texto nulo": no evidence names it
    EUE_GUI_TEXTFIELDUPDATE_TEXTO_NULO = 4974,
    // the value is the code api::CTextRectField's constructor throws (record ctextrectfield.cpp 51:15, inlined into
    // fn 5546); the name is chosen from its message, "Campo estava com o texto nulo": no evidence names it
    EUE_GUI_TEXTRECTFIELD_TEXTO_NULO = 4976,
    // the value is the code api::CTextSource's constructor throws (record ctextsource.h 37:19, inlined into fn 10740);
    // the name is chosen from its message, "Texto nulo": no evidence names it
    EUE_GUI_TEXTSOURCE_TEXTO_NULO = 4977,
    // the value is the code api::IForm<IScreen>::FindFieldAs<CTextField> (target fn 1721, record iform.h 142:23)
    // throws; the name is chosen from its message, "Campo encontrado, mas não é do tipo solicitado: ": no evidence
    // names it
    EUE_GUI_FINDFIELDAS_TIPO_INVALIDO = 4978,
    // the value is the code api::IScreen::GetFontMetrics (target fn 8938) throws; the name is chosen from its message,
    // "Método não implementado": no evidence names it
    EUE_GUI_METODO_NAO_IMPLEMENTADO = 4982,
    // the value is the code api::CApplicationContextGuard's constructor throws (record capplicationcontextstack.cpp 45:15,
    // inlined into fn 676); the name is chosen from its message, "O contexto não pôde ser criado": no evidence names it
    EUE_GUI_APPLICATIONCONTEXTGUARD_CONTEXTO_NAO_CRIADO = 5013,
    // the values are the codes api::CInputMenuField::AddItem (target fn 1693) throws (records cinputmenufield.cpp
    // 320:15 and 339:15); the names are chosen from their messages, "Um CInputMenuField não comporta mais que 99 itens"
    // and "Item de menu não cabe na tela [" + text + "]": no evidence names them
    EUE_GUI_INPUTMENUFIELD_MAXIMO_ITENS = 4933,
    EUE_GUI_INPUTMENUFIELD_ITEM_NAO_CABE = 4934,
};

using CUeGuiError = ecourna::api::exception::CBaseError<EUeGuiError, ecourna::api::exception::SErrorLimits{4900, 5100}>;

} // namespace api
