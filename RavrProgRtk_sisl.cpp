// vim:ts=4 sts=0 sw=4
//Automatically generated from: RavrProgRtk.h
//Don't edit, all changes _will be lost_.

#include "RavrProgRtk.h"

//---class RProgApp : RApp
/*---Signals---
//---Slots-----
ProgrammerChanged(int,void*)
InterfaceChanged(int,void*)
PClockChanged(int,void*)
EClockChanged(int,void*)
ApplyP()
ApplyE()
Refresh()
Connect()
RefreshAVR()
DeviceChanged(int,void*)
ChipErase()
ReadFlash()
WriteFlash()
VerifyFlash()
SelectFlash()
ReadEeprom()
WriteEeprom()
VerifyEeprom()
SelectEeprom()
ReadFuse()
WriteFuse()
VerifyFuse()
DefaultFuse()
SelectFuseTab()
FuseChecked(bool)
FuseSelected(int)
FuseEdited()
FuseEditFinished(bool)
SelectConfigTab()
//-----------*/
//------------------------------
//---Start of connector stubs---

void RProgApp_ProgrammerChanged_i_v(void *ths, void **ppv)	{ ((RProgApp*)ths)->ProgrammerChanged((int)(uptr)ppv[0],(void*)(uptr)ppv[1]); }
void RProgApp_InterfaceChanged_i_v(void *ths, void **ppv)	{ ((RProgApp*)ths)->InterfaceChanged((int)(uptr)ppv[0],(void*)(uptr)ppv[1]); }
void RProgApp_PClockChanged_i_v(void *ths, void **ppv)	{ ((RProgApp*)ths)->PClockChanged((int)(uptr)ppv[0],(void*)(uptr)ppv[1]); }
void RProgApp_EClockChanged_i_v(void *ths, void **ppv)	{ ((RProgApp*)ths)->EClockChanged((int)(uptr)ppv[0],(void*)(uptr)ppv[1]); }
void RProgApp_ApplyP(void *ths, void **ppv)	{ ((RProgApp*)ths)->ApplyP(); }
void RProgApp_ApplyE(void *ths, void **ppv)	{ ((RProgApp*)ths)->ApplyE(); }
void RProgApp_Refresh(void *ths, void **ppv)	{ ((RProgApp*)ths)->Refresh(); }
void RProgApp_Connect(void *ths, void **ppv)	{ ((RProgApp*)ths)->Connect(); }
void RProgApp_RefreshAVR(void *ths, void **ppv)	{ ((RProgApp*)ths)->RefreshAVR(); }
void RProgApp_DeviceChanged_i_v(void *ths, void **ppv)	{ ((RProgApp*)ths)->DeviceChanged((int)(uptr)ppv[0],(void*)(uptr)ppv[1]); }
void RProgApp_ChipErase(void *ths, void **ppv)	{ ((RProgApp*)ths)->ChipErase(); }
void RProgApp_ReadFlash(void *ths, void **ppv)	{ ((RProgApp*)ths)->ReadFlash(); }
void RProgApp_WriteFlash(void *ths, void **ppv)	{ ((RProgApp*)ths)->WriteFlash(); }
void RProgApp_VerifyFlash(void *ths, void **ppv)	{ ((RProgApp*)ths)->VerifyFlash(); }
void RProgApp_SelectFlash(void *ths, void **ppv)	{ ((RProgApp*)ths)->SelectFlash(); }
void RProgApp_ReadEeprom(void *ths, void **ppv)	{ ((RProgApp*)ths)->ReadEeprom(); }
void RProgApp_WriteEeprom(void *ths, void **ppv)	{ ((RProgApp*)ths)->WriteEeprom(); }
void RProgApp_VerifyEeprom(void *ths, void **ppv)	{ ((RProgApp*)ths)->VerifyEeprom(); }
void RProgApp_SelectEeprom(void *ths, void **ppv)	{ ((RProgApp*)ths)->SelectEeprom(); }
void RProgApp_ReadFuse(void *ths, void **ppv)	{ ((RProgApp*)ths)->ReadFuse(); }
void RProgApp_WriteFuse(void *ths, void **ppv)	{ ((RProgApp*)ths)->WriteFuse(); }
void RProgApp_VerifyFuse(void *ths, void **ppv)	{ ((RProgApp*)ths)->VerifyFuse(); }
void RProgApp_DefaultFuse(void *ths, void **ppv)	{ ((RProgApp*)ths)->DefaultFuse(); }
void RProgApp_SelectFuseTab(void *ths, void **ppv)	{ ((RProgApp*)ths)->SelectFuseTab(); }
void RProgApp_FuseChecked_b(void *ths, void **ppv)	{ ((RProgApp*)ths)->FuseChecked((bool)(uptr)ppv[0]); }
void RProgApp_FuseSelected_i(void *ths, void **ppv)	{ ((RProgApp*)ths)->FuseSelected((int)(uptr)ppv[0]); }
void RProgApp_FuseEdited(void *ths, void **ppv)	{ ((RProgApp*)ths)->FuseEdited(); }
void RProgApp_FuseEditFinished_b(void *ths, void **ppv)	{ ((RProgApp*)ths)->FuseEditFinished((bool)(uptr)ppv[0]); }
void RProgApp_SelectConfigTab(void *ths, void **ppv)	{ ((RProgApp*)ths)->SelectConfigTab(); }

//---End of connector stubs---
//----------------------------
//---Start of SiSl Data-------

SiSlLink sil_RProgApp[30] =
{
	{ "ProgrammerChanged(int,void*)", RProgApp_ProgrammerChanged_i_v },
	{ "InterfaceChanged(int,void*)", RProgApp_InterfaceChanged_i_v },
	{ "PClockChanged(int,void*)", RProgApp_PClockChanged_i_v },
	{ "EClockChanged(int,void*)", RProgApp_EClockChanged_i_v },
	{ "ApplyP()", RProgApp_ApplyP },
	{ "ApplyE()", RProgApp_ApplyE },
	{ "Refresh()", RProgApp_Refresh },
	{ "Connect()", RProgApp_Connect },
	{ "RefreshAVR()", RProgApp_RefreshAVR },
	{ "DeviceChanged(int,void*)", RProgApp_DeviceChanged_i_v },
	{ "ChipErase()", RProgApp_ChipErase },
	{ "ReadFlash()", RProgApp_ReadFlash },
	{ "WriteFlash()", RProgApp_WriteFlash },
	{ "VerifyFlash()", RProgApp_VerifyFlash },
	{ "SelectFlash()", RProgApp_SelectFlash },
	{ "ReadEeprom()", RProgApp_ReadEeprom },
	{ "WriteEeprom()", RProgApp_WriteEeprom },
	{ "VerifyEeprom()", RProgApp_VerifyEeprom },
	{ "SelectEeprom()", RProgApp_SelectEeprom },
	{ "ReadFuse()", RProgApp_ReadFuse },
	{ "WriteFuse()", RProgApp_WriteFuse },
	{ "VerifyFuse()", RProgApp_VerifyFuse },
	{ "DefaultFuse()", RProgApp_DefaultFuse },
	{ "SelectFuseTab()", RProgApp_SelectFuseTab },
	{ "FuseChecked(bool)", RProgApp_FuseChecked_b },
	{ "FuseSelected(int)", RProgApp_FuseSelected_i },
	{ "FuseEdited()", RProgApp_FuseEdited },
	{ "FuseEditFinished(bool)", RProgApp_FuseEditFinished_b },
	{ "SelectConfigTab()", RProgApp_SelectConfigTab },
	{ 0,0 }
};

SiSlData sd_RProgApp = { 0, "RProgApp", 0, 0, sil_RProgApp };

SiSlData *RProgApp::SiSl_GetSD()
{
	if(!sd_RProgApp.up) {
		sd_RProgApp.up = RApp::SiSl_GetSD();
	}
	return &sd_RProgApp;
}

SiSlTN tn_RProgApp = { 0, "RProgApp", 0, 29 };
const char *RProgApp::GetTypeName(SiSlTN **tn)
{
	if(tn) {
		if(!tn_RProgApp.up) {
			RApp::GetTypeName(&tn_RProgApp.up);
		}
		*tn = &tn_RProgApp;
	}
	return tn_RProgApp.name;
}

//---End of SiSl Data-----------
//------------------------------
//----Start of signal stubs-----

//-----End of signal stubs------
//------------------------------
//done with class RProgApp : RApp

