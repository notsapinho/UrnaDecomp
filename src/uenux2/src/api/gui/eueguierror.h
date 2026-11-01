#pragma once

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

enum EUeGuiError {
    // the values are the codes api::CBmpConversor::VerticalFlip (target fn 3664) throws; the names are chosen from its
    // messages, "Dado de entrada nulo" and "Dimensões inválidas": no evidence names them
    EUE_GUI_VERTICALFLIP_DADO_NULO = 4900,
    EUE_GUI_VERTICALFLIP_DIMENSOES_INVALIDAS = 4901,
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
    // the value is the code api::CLedFieldMT::Draw (target fn 11050) throws; the name is chosen from its message,
    // "Operação desconhecida {}": no evidence names it
    EUE_GUI_LEDFIELDMT_OPERACAO_DESCONHECIDA = 4940,
    // the value is the code api::CMovie::CMovie (target fn 5526) throws; the name is chosen from its message, "Não
    // havia frames": no evidence names it
    EUE_GUI_MOVIE_SEM_FRAMES = 4943,
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
    // the value is the code api::IScreen::GetFontMetrics (target fn 8938) throws; the name is chosen from its message,
    // "Método não implementado": no evidence names it
    EUE_GUI_METODO_NAO_IMPLEMENTADO = 4982,
    // the value is the code api::CApplicationContextGuard's constructor throws (record capplicationcontextstack.cpp 45:15,
    // inlined into fn 676); the name is chosen from its message, "O contexto não pôde ser criado": no evidence names it
    EUE_GUI_APPLICATIONCONTEXTGUARD_CONTEXTO_NAO_CRIADO = 5013,
};

using CUeGuiError = ecourna::api::exception::CBaseError<EUeGuiError, ecourna::api::exception::SErrorLimits{4900, 5100}>;

} // namespace api
