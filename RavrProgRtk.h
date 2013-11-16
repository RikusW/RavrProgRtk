// vim:ts=4 sts=0 sw=4

#include "../Rtk/RtkAll.h"
#include "../RavrProg/RavrProg.h"

class RProgApp : public RApp
{
public:
	RProgApp() {};
	~RProgApp() { DINIT(); };

	SISL(2);

	void Setup();

	//Programmer TAB
	SLOT(ProgrammerChanged)(int,void*);
	SLOT(InterfaceChanged)(int,void*);
	SLOT(PClockChanged)(int,void*);
	SLOT(EClockChanged)(int,void*);
	SLOT(ApplyP)();
	SLOT(ApplyE)();
	SLOT(Refresh)();
	SLOT(Connect)();
	SLOT(RefreshAVR)();
	SLOT(DeviceChanged)(int,void*);

	//Flash TAB
	SLOT(ChipErase)();

	SLOT(ReadFlash)();
	SLOT(WriteFlash)();
	SLOT(VerifyFlash)();
	SLOT(SelectFlash)();

	SLOT(ReadEeprom)();
	SLOT(WriteEeprom)();
	SLOT(VerifyEeprom)();
	SLOT(SelectEeprom)();

	//Fuse TAB
	SLOT(ReadFuse)();
	SLOT(WriteFuse)();
	SLOT(VerifyFuse)();
	SLOT(DefaultFuse)();
	SLOT(SelectFuseTab)();
	SLOT(FuseChecked)(bool);
	SLOT(FuseSelected)(int);
	SLOT(FuseEdited)();
	SLOT(FuseEditFinished)(bool);
	void SetupFuseBox(RContainer *c, Device *d);
	void UpdateFuseBox();
	void SetFuseEdit();



	SLOT(SelectConfigTab)();

	bool Enter();
	bool Leave();

	//Variables
	Programmer *prog_list;
	Programmer *prog; //selected programmer
	ProgIF *progif_list;
	ProgIF *progif;  //selected if
	ProgIF *progifc; //connected if
	Device *device;

	u8 bAuto,bIgnore;

	bool ign;
	const char *devname;

	RComboBox *InterfaceCombo;
	RComboBox *DeviceCombo;
	RComboBox *PClockCombo;
	RComboBox *EClockCombo;
	RComboBox *PortCombo;

	RButton *ConnectButton;

	RContainer *fusebox;
	RHexBox *fuseedit;
	REditBox *flashedit;
	REditBox *eepromedit;
	RProgressBar *flashprogress;
};


