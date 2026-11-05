# uenux2 vota state no landed file holds: vota::CSincronismoEleitor (app/vota/eleitor/csincronismoeleitor.{h,cpp}).
# Paths relative to src/uenux2. vota::CPedeDigital (app/vota/operador/confirmaidentidade/cpededigital.{h,cpp}) was this
# unit's too: its file is in unit 282's list now, after the files of the two classes whose GetInst its fn 5397 holds
# inlined (that fragment measures the order), and its matches (2739, 10469, 10466, 10467), their notes, its pending
# ProcessTick and the roots it needs went with it.
#
# Target functions matched:
#   vota::CSincronismoEleitor::StartState (slot 2)             7178
#   vota::CSincronismoEleitor::ProcessKey (slot 6)              7181
#   the exit destructors of s_inst and s_mutex                  7195, 7187
# CSincronismoEleitor's GetInst, statics and constructor are in csincronismoeleitor.cpp, the constructor out of line
# (csincronismoeleitor.h says why, and what is chosen): fn 4454, unit 197's FinalizaEleitor, holds them inlined and
# matches (unit 197's fragment); its srcloc-anchor names the statics, over which 7195 and 7187 match.
# No roots: CSincronismoEleitor's vptr store is in the link, inlined into FinalizaEleitor, so its vtable's stand-in
# went (the link without it moves no row into or out of match).
#
# Evidence:
# - CSincronismoEleitor::StartState posts 13 to the operator's queue (the queue's inline Post: Insert, fn 501, with
#   priority 1 and the queue's address in the message), sets m_pNextState, resets vota::CTelasVota's progress bar at
#   +180 to its +28 (api::CProgressBar::SetValor, fn 3667, with GetLimiteInferior) and shows the form at +172 (slot 2),
#   through ctelasvota.h's GetBarraSincronismo and GetTelaSincronismo. Insert of a temporary message gives the same
#   function (measured: both `4 over 43 rows`, every row a call's or an address's operand); Post is written, as for the
#   operador states' messages (fragment 152 has the case where only Post gives the target's frame).
# - CSincronismoEleitor::ProcessKey sets m_pNextState (+4) to this and, on the key 5 when
#   vota::impl::ISincronismoVotoEleitor::GetInst().Sincroniza() (slot 2) returns true, to vota::CFimVotoEleitor's
#   GetInst. It holds both GetInsts inlined, the interface's with its default instance and the state's with its
#   constructor, and calls the executable TU's has<T> and push<T> thunks (2741, 5398): fragment 241 writes those
#   classes, and its fragment has their evidence. The bare 5 is the key, as CPerguntaEleitorVotando::ProcessKey
#   (fragment 152) compares it; the `&&` in one if is a choice.
#
# Paths and lines. No record names CSincronismoEleitor: its file is chosen, the class's name in lower case under
# app/vota/eleitor/, where its vtable (@1534076) and typeinfo lie in the data between cfimvotoeleitor.cpp's record
# (1534048) and csincronismovotoeleitor.cpp's (1534132), in that directory's name order; the end of either neighbour's
# object fits the data too.
#
# Chosen, no evidence names them: every local's name, and the declaration order of the virtual members:
# CSincronismoEleitor, whose destructor is implicit, has StartState first, so that csincronismoeleitor.cpp emits its
# vtable (how-to step 3).
APP_VOTA_ESTADOS_SINCRONISMO_SRCS := src/app/vota/eleitor/csincronismoeleitor.cpp
UENUX2_SRCS += $(APP_VOTA_ESTADOS_SINCRONISMO_SRCS)
