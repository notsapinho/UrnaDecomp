// vota::impl::CInformacaoThreadOperador (uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp).
// Target functions of this file, by slot of the vtable @1590108:
//   2     10581 CancelaHabilitacao          (here)     3     10580 IsAudioAtivado               (pending)
//   4     2683  Slot4                       (here)     5     10579 IsAudioAtivadoCadastro       (pending)
//   6     2683  IsAudioAtivadoMesario       (here)     7     10578 SetAudioAtivadoMesario       (here)
//   8     10577 GetTextoAudio               (here)     9     10576 IsBiometriaOperador          (here)
//   10    10574 IsBiometriaEleitor          (here)     11    10573 IsSemBiometria               (here)
//   12    10572 SetBiometriaOperador        (here)     13    10571 SetBiometriaEleitor          (here)
//   14    10570 LimpaBiometria              (here)     15    2587  GetEstadoBiometria           (here)
//   16    10569 GetTextoComparecimento      (pending)  17    10568 AgendaInspecao               (pending)
//   18    10567 GetDataHoraInspecao         (here)     19    10566 IsVotacaoBloqueadaPorHorario (pending)
//   20    10565 LimpaIdentidades            (here)     21    10564 SetIdentidadeDigitada        (pending)
//   22    10563 SetTipoIdentidadeDigitada   (pending)  27    10558 SetEleitorSemFoto            (here)
//   28    10557 SetFotoApresentada          (here)     29    10556 SetFotoNaoApresentada        (here)
//   30    10554 GetApresentacaoFotoEleitor  (here)
//   23-26 10562, 10561, 10560, 10559: GetIdentidadeDigitada, GetTipoIdentidadeDigitada, GetIdentidadeEleitor and
//         GetIdentidadePrincipalEleitor (here; records at lines 474, 484, 494 and 504, column 15)
// The names of slots 2 to 22 and 27 to 30 are chosen (iinformacaothreadoperador.h says from what). A member marked
// pending is defined in src/units/50-uenux2-cinformacaothreadoperador-pending.cpp until it is reconstructed.
// vota::TipoToStr (10586, record at line 40) and IInformacaoThreadOperador::GetInst (599, record at line 554) are not
// reconstructed, and their lines stay blank. The six records are the only lines the target fixes: the members run in
// slot order, as the target's function order has them, and the lines of slots 2 to 22 and 27 to 30 are a choice.

#include "app/vota/operador/comum/cinformacaothreadoperador.h"

#include "app/vota/euevotaerror.h"

// (original lines 28-36: content not recovered)
#line 37
// <stubs>
// f10586 · 837 B · unmatched · name unknown
// void f10586(i32) { ... }
// </stubs>

// (original lines 42-392: content not recovered)
#line 393
namespace vota::impl {

void CInformacaoThreadOperador::CancelaHabilitacao()
{
    m_audioAtivado = false;
    m_estadoBiometria = SemBiometria;
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::EleitorSemFoto;
    m_resultadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::SemErro;
}

bool CInformacaoThreadOperador::Slot4() const
{
    return m_audioAtivado;
}

bool CInformacaoThreadOperador::IsAudioAtivadoMesario() const
{
    return m_audioAtivado;
}

void CInformacaoThreadOperador::SetAudioAtivadoMesario(bool ativado)
{
    m_audioAtivado = ativado;
}

std::string CInformacaoThreadOperador::GetTextoAudio() const
{
    return m_audioAtivado ? "ÁUDIO ATIVADO" : " ";
}

bool CInformacaoThreadOperador::IsBiometriaOperador() const
{
    return m_estadoBiometria == BiometriaOperador;
}

bool CInformacaoThreadOperador::IsBiometriaEleitor() const
{
    return m_estadoBiometria == BiometriaEleitor;
}

bool CInformacaoThreadOperador::IsSemBiometria() const
{
    return m_estadoBiometria == SemBiometria;
}

void CInformacaoThreadOperador::SetBiometriaOperador()
{
    m_estadoBiometria = BiometriaOperador;
}

void CInformacaoThreadOperador::SetBiometriaEleitor()
{
    m_estadoBiometria = BiometriaEleitor;
}

void CInformacaoThreadOperador::LimpaBiometria()
{
    m_estadoBiometria = SemBiometria;
}

IInformacaoThreadOperador::EEstadoBiometria CInformacaoThreadOperador::GetEstadoBiometria() const
{
    return m_estadoBiometria;
}

api::CDateTime CInformacaoThreadOperador::GetDataHoraInspecao() const
{
    return m_dataHoraInspecao;
}

void CInformacaoThreadOperador::LimpaIdentidades()
{
    m_identidadeDigitada.reset();
    m_tipoIdentidadeDigitada.reset();
    m_identidadeEleitor.reset();
    m_identidadePrincipalEleitor.reset();
}

std::string CInformacaoThreadOperador::GetIdentidadeDigitada() const
{
    if (!m_identidadeDigitada) {
        throw CUeVotaError(EUE_VOTA_IDENTIDADE_DIGITADA_NAO_REGISTRADA, "Identidade não registrada");
    }
    return *m_identidadeDigitada;
}

// (original lines 479-480: content not recovered)
#line 481
ecourna::app::dados::ETipoIdentificadorEleitor CInformacaoThreadOperador::GetTipoIdentidadeDigitada() const
{
    if (!m_tipoIdentidadeDigitada) {
        throw CUeVotaError(EUE_VOTA_TIPO_IDENTIDADE_NAO_REGISTRADO, "Tipo de identidade não registrado");
    }
    return *m_tipoIdentidadeDigitada;
}

// (original lines 489-490: content not recovered)
#line 491
comum::md::CEleitorIdentidade CInformacaoThreadOperador::GetIdentidadeEleitor() const
{
    if (!m_identidadeEleitor) {
        throw CUeVotaError(EUE_VOTA_IDENTIDADE_ELEITOR_NAO_REGISTRADA, "Identidade não registrada");
    }
    return *m_identidadeEleitor;
}

// (original lines 499-500: content not recovered)
#line 501
comum::md::CEleitorIdentidade CInformacaoThreadOperador::GetIdentidadePrincipalEleitor() const
{
    if (!m_identidadePrincipalEleitor) {
        throw CUeVotaError(EUE_VOTA_IDENTIDADE_PRINCIPAL_NAO_REGISTRADA, "Identidade não registrada");
    }
    return *m_identidadePrincipalEleitor;
}

void CInformacaoThreadOperador::SetEleitorSemFoto()
{
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::EleitorSemFoto;
    m_resultadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::SemErro;
}

void CInformacaoThreadOperador::SetFotoApresentada()
{
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::Apresentada;
    m_resultadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::SemErro;
}

void CInformacaoThreadOperador::SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado)
{
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::NaoApresentadaPorErro;
    m_resultadoApresentacaoFoto = resultado;
}

ecourna::app::dados::CApresentacaoFotoEleitor CInformacaoThreadOperador::GetApresentacaoFotoEleitor() const
{
    return ecourna::app::dados::CApresentacaoFotoEleitor(m_estadoApresentacaoFoto, m_resultadoApresentacaoFoto);
}

} // namespace vota::impl

// <stubs>
// f599 · 4114 B · unmatched · name unknown
// ? f599() { ... }
// </stubs>
