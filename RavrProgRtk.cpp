// vim:ts=4 sts=0 sw=4

#include "RavrProgRtk.h"

#include <stdio.h>

//-----------------------------------------------------------------------------####
//Programmer TAB

void RProgApp::ProgrammerChanged(int i, void *v)
{
	prog = (Programmer*)v;
	printf("Programmer changed %i -> %s\n", i, (char*)prog->name());

	InterfaceCombo->Clear();

	if(prog) {
		progif = progif_list = prog->interface; //XXX
		for(ProgIF *i = progif; i; i = i->next) {
			InterfaceCombo->AddItem(i->name(),i); //XXX
		}
		Refresh(); //ports
	}else{
		progif = progif_list = 0;
	}

	if(progif) {
//		InterfaceChanged(0); //XXX
	}
}

//---------------------------------------------------------

void ProgCB(u32 total, u32 current, void *v)
{
	printf("CB --->  t %i c %i %X\n",total,current,(u32)(u64)v); //xx just shut gcc up....
//	return;

	if(!total) total = 1;
	RProgressBar *b = (RProgressBar*)v;
	if(b) {
		b->pmax = total;
		b->ppos = current;
		b->Draw();
	}
}

//---------------------------------------------------------

void RProgApp::InterfaceChanged(int i, void *v)
{
	printf("Interface changed %i\n",i);

	progif = (ProgIF*)v;


/*

	if(n < 0) {
		progif_list = progif = 0;
		return;
	}

	if(progif_list) {
		progif = progif_list->GetAt(n);
	}else{
		progif = 0;
		return;
	}*/

	progif->PCBvoid = (void*)flashprogress;
	progif->ProgressCallback = ProgCB;

	//Programming Clock
	int *up = progif->GetPClockList();
	PClockCombo->Clear();
	if(up) {
		up++;
		PClockCombo->AddItem("Default");
		while(*up) {
			RString s;
			s.ToDec(*up);
			PClockCombo->AddItem(s);
			up++;
		}
	}else{
		PClockCombo->AddItem("Not Available");
	}
	
	//Clock Generator
	up = progif->GetEClockList();
	EClockCombo->Clear();
	if(up) {
		up++;
		EClockCombo->AddItem("Default");
		while(*up) {
			RString s;
			s.ToDec(*up);
			EClockCombo->AddItem(s);
			up++;
		}
		EClockCombo->AddItem("Off");
	}else{
		EClockCombo->AddItem("Not Available");
	}

	//device list
	DeviceCombo->Clear();
	device = progif->GetDeviceList(); //device = auto;
	const char *dev = devname; //BUG -> AddItem selects first addition...
	for(Device *d = device; d; d = d->next) {
		//debug
		RString n,s = d->name;
		n.ToHex(d->signature);
		s += "  ";
		s += n;
		//s += "  " + n; //XXX buggy ?!
		n.ToHex(d->jtag_id);
		s += " -- ";
		s += n;
		//s += " -- " + n; //XXX
		DeviceCombo->AddItem(s); //XXX
		//*/

//		DeviceCombo->AddItem(d->name); //XXX
		if(d->name == dev) { //no need for strcmp, always points to the same buffer
			DeviceCombo->Select(d->i);
		}
	}
}

//-------------------------------------------------------------------

void RProgApp::PClockChanged(int i, void *v)
{
	printf("PClock changed %i\n",i);

//	progif->SetPClockI(i);
}

void RProgApp::ApplyP()
{
	printf("ApplyP\n");
/*
	if(progifc && progifc->GetPClockList()) {
		int f = progifc->ApplyPClock();
		QString s;
		s.setNum(f);
		s = "Default = " + s;
		ui.PClockCombo->setItemText(0,s);
		if(progifc->PSaved()) {
			ui.PClockCombo->setCurrentIndex(0); //XXX
		}
	}
*/
}

//-------------------------------------------------------------------

void RProgApp::EClockChanged(int i, void *v)
{
	printf("EClock changed %i\n",i);

//	progif->SetEClockI(i);
}

void RProgApp::ApplyE()
{
	printf("ApplyE\n");

/*	if(progifc && progifc->GetEClockList()) {
		int f = progifc->ApplyEClock();
		QString s;
		if(f) {
			s.setNum(f);
		}else{
			s = "OFF";
		}
		s = "Default = " + s;
		ui.EClockCombo->setItemText(0,s);
		if(progifc->PSaved()) {
			ui.EClockCombo->setCurrentIndex(0);
		}
	}
*/
}

//-------------------------------------------------------------------

void RProgApp::Refresh()
{
	printf("Refresh\n");

	if(!prog) {
		return;
	}

	bool done = false;
	RString s;
	const char *c;
	PortCombo->Clear();
    for(u32 i = 0; (c = prog->port->GetPort(i)); i++) {
		s = c;
        PortCombo->AddItem(c);
		if(!done)
#ifdef WIN32		
		if(s.Contains("COM3")) { // add code to detect proper port...
#else
		if(s.Contains("ACM") || s.Contains("USB") || s.Contains("usb")) {
#endif		
		    PortCombo->Select(i);
			done = true;
		}
    }
}

//-------------------------------------------------------------------

void RProgApp::Connect()
{
	printf("Connect\n");

	if(progifc) {
		puts("Disconnecting");
		progifc->Disconnect();

		if(bAuto) {
			DeviceCombo->Select(0);
			device = progifc->SetDevice(0);
			bAuto = false;
		}
		progifc = 0;

		ProgrammerCombo->Enable();
		InterfaceCombo->Enable();
//		PClockCombo->ItemText(0,"Default");
		ApplyPButton->Disable();
//		EClockCombo->ItemText(0,"Default");
		ApplyEButton->Disable();
		PortCombo->Enable();
		RefreshButton->Enable();
		RefreshAVRButton->Disable();
		ConnectButton->SetText("Connect");

/*		SigEdit->Text("");
		SerialEdit->Text("");
		OsccalCombo->clear();
		pushButton_Refresh_AVR->Disable();
		lineEdit_Fuses->Text("");*/
		DeviceCombo->Enable();
	}else{
		if(!progif) {
			puts("RavrProgQt::Connect progif == 0");
			return;
		}
//		QString n,s = PortCombo->currentText();
//		QString n,s = PortCombo->currentText();
//		char c[300];
//		strcpy(c,s.toAscii().constData());
//		printf("Connecting to ->%s\n",c);

		if(progif->Connect(PortCombo->text)) { //XXX
//		if(progif->Connect(c)) {
			progifc = progif;
			puts("connect OK");
			ConnectButton->SetText("Disconnect");
			ProgrammerCombo->Disable();
			InterfaceCombo->Disable();
			ApplyPButton->Enable();
			ApplyEButton->Enable();
			PortCombo->Disable();
			RefreshButton->Disable();
			RefreshAVRButton->Enable();
			DeviceCombo->Disable();

			ApplyP();
			ApplyE();
			RefreshAVR();
		}else{
			puts("connect fail");
		}
	}
}

//-------------------------------------------------------------------

void RProgApp::RefreshAVR()
{
	printf("RefreshAVR\n");

	//auto detect avr
	int i = DeviceCombo->GetIndex();
	if(!i || bAuto) {
		bAuto = true;
		device = progifc->SetDevice(0);
		DeviceCombo->Select(device->i);
	}else{
		device = progifc->SetDevice(i); //??? whats this for ???
	}
}

//-------------------------------------------------------------------

void RProgApp::DeviceChanged(int i, void *v)
{
	printf("Device changed %i\n",i);
	
	if(i < 0) { // ignore -1 sent by clear
		ign = true;
		return;
	}
	if(ign) { //ignore 0 after -1
		ign = false;
		return;
	}

	if(!bAuto) {
		device = progif->GetDevice(i);
		devname = device->name;
	}
	printf("Device changed %i  %s\n",i, device ? device->name : "xx");
}

//Programmer TAB
//-----------------------------------------------------------------------------####
//Flash TAB

void RProgApp::ChipErase()
{
	printf("Chip Erase\n");
	if(Enter()) {
		progifc->ChipErase();
	}
	Leave();
}

//---------------------------------------------------------

void RProgApp::ReadFlash()
{
	printf("Read Flash\n");


//	QFileDialog dlg;
//	QString s = dlg.getSaveFileName(this);

	if(flashedit->text[0] == 0) { //XXX  Replace with RString
		printf("Reading Flash Cancelled\n");
		return;
	}
	char c[300];
	strcpy(c,flashedit->text); //required ??? replace with RString
	printf("Reading Flash: %s\n",c);

	if(Enter()) {
		progifc->ReadFlash(c);
	}
	Leave();
//XXX	flashprogress->setValue(0);
	flashprogress->Sl_Move(0);
}

//---------------------------------------------------------

void RProgApp::WriteFlash()
{
	printf("Write Flash\n");

	if(flashedit->text[0] == 0) { //XXX  Replace with RString
	//	QFileDialog dlg;
	//	s = dlg.getOpenFileName(this);
	//	if(s == "") {
			printf("Writing Flash Cancelled\n");
			return;
	//	}
	}
	char c[300];
	strcpy(c,flashedit->text); //required ??? replace with RString
	printf("Writing Flash %s\n",c);

	if(Enter()) {
/*		if(ui.checkBox_Erase->checkState()) {
			progifc->ChipErase();
		}
		progifc->WriteFlash(c);
		if(ui.checkBox_Verify->checkState()) {
			progifc->VerifyFlash(c);
		}*/
	}
	Leave();
	flashprogress->Sl_Move(0);
}

//---------------------------------------------------------

void RProgApp::VerifyFlash()
{
	printf("Verify Flash\n");

	if(flashedit->text[0] == 0) { //XXX  Replace with RString
	//	QFileDialog dlg;
	//	s = dlg.getOpenFileName(this);
	//	if(s == "") {
			printf("Verifying Flash Cancelled\n");
			return;
	//	}
	}
	char c[300];
	strcpy(c,flashedit->text); //required ??? replace with RString
	printf("Verifying Flash %s\n",c);

	if(Enter()) {
		progifc->VerifyFlash(c);
	}
	Leave();
	flashprogress->Sl_Move(0);
}

//---------------------------------------------------------

void RProgApp::SelectFlash()
{
	printf("Select Flash\n");
/*
	QFileDialog dlg;
	QString s = dlg.getOpenFileName(this);
	if(s == "") {
		printf("Selecting Flash File Cancelled\n");
		return;
	}
	ui.lineEdit_Flash->setText(s);
	char c[300];
	strcpy(c,s.toAscii().constData());
	printf("Selecting Flash File: %s\n",c);
*/
}

//-----------------------------------------------------------------------------

void RProgApp::ReadEeprom()
{
	printf("Read Eeprom\n");

//	QFileDialog dlg;
//	QString s = dlg.getSaveFileName(this);

	if(eepromedit->text[0] == 0) { //XXX  Replace with RString
		printf("Reading Eeprom Cancelled\n");
		return;
	}
	char c[300];
	strcpy(c,eepromedit->text); //required ??? replace with RString
	printf("Reading Eeprom: %s\n",c);

	if(Enter()) {
		progifc->ReadEeprom(c);
	}
	Leave();
	flashprogress->Sl_Move(0);

}

//---------------------------------------------------------

void RProgApp::WriteEeprom()
{
	printf("Write Eeprom\n");

	if(eepromedit->text[0] == 0) { //XXX  Replace with RString
	//	QFileDialog dlg;
	//	s = dlg.getOpenFileName(this);
	//	if(s == "") {
			printf("Writing Eeprom Cancelled\n");
			return;
	//	}
	}
	char c[300];
	strcpy(c,eepromedit->text); //required ??? replace with RString
	printf("Writing Eeprom %s\n",c);

	if(Enter()) {
/*		progifc->WriteEeprom(c);
		if(ui.checkBox_Verify->checkState()) {
			progifc->VerifyEeprom(c);
		}*/
	}
	Leave();
	flashprogress->Sl_Move(0);
}

//---------------------------------------------------------

void RProgApp::VerifyEeprom()
{
	printf("Verify Eeprom\n");

	if(eepromedit->text[0] == 0) { //XXX  Replace with RString
		printf("Verifying Eeprom Cancelled\n");
		return;
	}
	char c[300];
	strcpy(c,eepromedit->text); //required ??? replace with RString
	printf("Verifying Eeprom %s\n",c);

	if(Enter()) {
		progifc->VerifyEeprom(c);
	}
	Leave();
	flashprogress->Sl_Move(0);
}

//---------------------------------------------------------

void RProgApp::SelectEeprom()
{
	printf("SelectEeprom\n");
/*
	QFileDialog dlg;
	QString s = dlg.getOpenFileName(this);
	if(s == "") {
		printf("Selecting Eeprom Cancelled\n");
		return;
	}
	ui.lineEdit_Eeprom->setText(s);
	const char *c = s.toAscii().constData();
	printf("Selecting Eeprom File: %s\n",c);
*/
}

//Flash TAB
//-----------------------------------------------------------------------------####
//Fuse TAB

void RProgApp::SelectFuseTab()
{
	printf("Select Fuse\n");

	if(!device) {
		return;
	}

	if(!device->config) {
		device->Load();
	}

	RContainer *rc = (RContainer*)Rtk_GetUPTR();
	SetupFuseBox(rc,device);
	ReadFuse();

	//XXX bug, need to fix ReCalc()
	rc->ReCalc(true);
	rc->ReCalc(true);

	return;
}

//---------------------------------------------------------

void RProgApp::ReadFuse()
{
	printf("Read Fuse\n");

	if(Enter()) {
		puts("Reading Fuses");
		progifc->ReadFuses();
	}
	Leave();

	UpdateFuseBox();
	SetFuseEdit();
}

//---------------------------------------------------------

void RProgApp::WriteFuse()
{
	printf("Write Fuse\n");

	if(Enter()) {
		puts("Writing Fuses");
//		progifc->WriteFuses(); uncomment when code is tested
	}
	Leave();
}

//---------------------------------------------------------

void RProgApp::VerifyFuse()
{
	printf("Verify Fuse\n");

	if(Enter()) {
		puts("Verifying Fuses");
		progifc->VerifyFuses();
	}
	Leave();
}

//---------------------------------------------------------

void RProgApp::DefaultFuse()
{
	if(device) {
		device->SetDefaultFuses();
		UpdateFuseBox();
		SetFuseEdit();
	}
}

//---------------------------------------------------------

void RProgApp::FuseChecked(bool b)
{
	if(bIgnore) {
		return;
	}
	AvrFuse *f = (AvrFuse*)Rtk_GetUPTR();
	if(f) {
		f->Set(b); // true == checked
		SetFuseEdit();
	}else{
		printf("FuseChecked Invalid pointer\n");
	}
}

//---------------------------------------------------------

void RProgApp::FuseSelected(int i)
{
	if(bIgnore) {
		return;
	}
	AvrFuse *f = (AvrFuse*)Rtk_GetUPTR();
	if(f) {
		f->Select(i);
		SetFuseEdit();
	}else{
		printf("FuseSelected Invalid pointer\n");
	}
}

//---------------------------------------------------------

void RProgApp::FuseEdited()
{
	u8 fuses[32];
	u8 bytes[4];

	puts("fuseedit edited");

	if(bIgnore) {
		return;
	}

	fuseedit->GetBytes(bytes); //XXX... fix it ???
	fuses[0] = bytes[3];
	fuses[1] = bytes[2];
	fuses[2] = bytes[1];
	fuses[3] = bytes[0];
	device->SetFuseBuf(fuses);

//	int i = ui.lineEdit_Fuses->cursorPosition();
	UpdateFuseBox();
//	ui.lineEdit_Fuses->setCursorPosition(i);

//	const char *c = s.toAscii().constData();
//	printf("---%s---\n",s.toAscii().constData());
}

//---------------------------------------------------------

void RProgApp::FuseEditFinished(bool b) //lost focus so set reserved fuses to 1
{
	if(!b) {
		puts("hexbox lost focus");
//	int i = ui.lineEdit_Fuses->cursorPosition();
	SetFuseEdit(); //reset invalid fuses
//	ui.lineEdit_Fuses->setCursorPosition(i);
	}else{
		puts("hexbox got focus");
	}
}

//---------------------------------------------------------

const char *tohex = "0123456789ABCDEF";

void RProgApp::SetFuseEdit()
{
//	char buf[100];
//	char *s = buf;

	u8 fuses[32];
//	u8 u = 
	device->GetFuseBuf(fuses);

//	printf("---%02X %02X %02X %02X--- %i ---\n",fuses[0],fuses[1],fuses[2],fuses[3],u); //XXX debug

	u8 bytes[4];
	bytes[0] = fuses[3];
	bytes[1] = fuses[2];
	bytes[2] = fuses[1];
	bytes[3] = fuses[0];
	fuseedit->SetBytes(bytes);

/*	//mega/tiny
	do{
		u--;
		*s++ = tohex[fuses[u]>>4];
		*s++ = tohex[fuses[u]&0xF];
		*s++ = ' ';
	}while(u);
	*--s = 0; //s.chop(1);

	puts(buf);

	fuseedit->SetText(buf);
	fuseedit->Draw(); //XXX bad bad bad....*/
	//seedit->SetText("123409881234089124buf");
}

//---------------------------------------------------------

void RProgApp::SetupFuseBox(RContainer *rc, Device *d)
{
	bIgnore = true; //???
	rc->Clear();

	RControl *r;
	AvrFuse *f = d->GetFuses();
	for(f = f ? f->child : 0; f; f = f->next) {
		if(!f->mask) {
			r = new RLabel(rc);
			r->SetText((const char *)f->name);
		}else
		if(f->child) {
//			r = new RLabel(rc);
			RComboBox *cb = new RComboBox(rc);
			cb->Connect("Si_IndexChanged(int,void*)",this,"FuseSelected(int)",f);
			cb->user = f;
//			cb->setMaxVisibleItems(28);
			cb->SetAlignment(AL_STRETCHH);
			for(AvrFuse *n = f->child; n; n = n->next) {
				cb->AddItem(n->name);
			}
		}else{
			RCheckBox *cb = new RCheckBox(rc);
			cb->Connect("Si_Checkd(bool)",this,"FuseChecked(bool)",f);
			cb->user = f;
			r = cb;
			r->SetText((const char *)f->name);
		}
		r->SetAlignment(AL_STRETCHH);
	}
	bIgnore = false;
}

//---------------------------------------------------------

RDrawer *GetDrawer(u32 d); //XXX bad... remove later

void RProgApp::UpdateFuseBox()
{
	bIgnore = true;

	for(RControl *c = fusebox->child; c; c = c->next) {
		if(c->Inherits("RCheckBox")) {
			AvrFuse *f = (AvrFuse*)c->user;
			RCheckBox *cb = (RCheckBox*)c;
			if(f->Get()) {
				cb->Sl_Check();
			}else{
				cb->Sl_UnCheck();
			}
		}else
		if(c->Inherits("RComboBox")) {
			AvrFuse *f = (AvrFuse*)c->user;
			RComboBox *cb = (RComboBox*)c;
			cb->Select(f->GetSelect());
		}
	}
	bIgnore = false;
}

//Fuse TAB
//-----------------------------------------------------------------------------####
//Config tab

void RProgApp::SelectConfigTab()
{
	printf("Select Fuse\n");

	if(!device) {
		return;
	}

	if(!device->config) {
		device->Load();
	}

	RTreeView *tv = (RTreeView*)Rtk_GetUPTR();
	tv->SetTree(device->config);
}

//-----------------------------------------------------------------------------####

bool RProgApp::Enter()
{
	printf("Entering programming mode: ");

	if(!progifc) {
		puts("NOT CONNECTED");
		return false;
	}

	if(progifc->Enter()) {
		puts("OK");
		return true;
	}else{
		puts("FAILED");
		return false;
	}
}

//---------------------------------------------------------

bool RProgApp::Leave()
{
	printf("Leaving  Programming mode: ");

	if(!progifc) {
		puts("NOT CONNECTED");
		return false;
	}

	if(progifc->Leave()) {
		puts("OK");
		return true;
	}else{
		puts("FAILED");
		return false;
	}
}


//-----------------------------------------------------------------------------####
//-----------------------------------------------------------------------------####
//Setup

void RProgApp::Setup()
{
	wnd = new RMainWindow(60,50,600,600); //XXX
	wnd->Create();
	wnd->SetText("RavrProgRtk");
	wnd->SetAlignment(AL_V);
	wnd->x_mgn = 4;
	wnd->y_mgn = 4;
	wnd->spacing = 8;

	RSBox *rsb;
	RContainer *sv;


//XXX XXX
/*	RConfig rcf;
	RTreeNode *stp; // delete at end ? XXX
#ifdef WIN32
	stp = rcf.ReadRcf("c:/RavrProgParts/ATmega328.rcf");
#else
	stp = rcf.ReadRcf("../RavrProgParts/ATmega328.rcf");
#endif*/

//---------------------------------------------------------
// Tab control

	RTabControl *tc = new RTabControl(wnd);
	tc->SetText("TabControl");
	tc->x_weight = 10;
	tc->y_weight = 10;
	tc->x_mgn = tc->y_mgn = 4;
	tc->SetAlignment(AL_V | AL_STRETCHH | AL_STRETCHV);// | AL_FITH | AL_FITV);
	//((RTabControl*)tc)->rrb->SetWeight(2,1,-1,0);

//---------------------------------------------------------

	RTBox *rt;
	RHVBox *hv;
	RButton *b;
	RLabel *rl,*l;
	REditBox *eb;
	RComboBox *c;


	progifc = 0;
	progif = 0;
	prog = 0;
	device = 0;
	bAuto = false;
	bIgnore = false;
	ign = false;
	devname = "xx";

//-----------------------------------------------------------------------------####
//Programmer TAB

	int y=0;
	rt = new RTBox(tc,5,13);
	rt->SetText("Programmer");
	rt->frame = F_DOWN;
	rt->spacing = 8;
//	rt->SetAlignment(AL_STRETCHH | AL_STRETCHV);


	l = new RLabel(rt); l->SetText("Select Programmer:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("programmer combo"); rt->SetPos(2,y++,3);
	c->Connect("Si_IndexChanged(int,void*)",this,"ProgrammerChanged(int,void*)");
	c->SetAlignment(AL_STRETCHH);
	RComboBox *cb = c;
	ProgrammerCombo = c;


	l = new RLabel(rt); l->SetText("Select Interface:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("interface combo"); rt->SetPos(2,y++,3);
	c->Connect("Si_IndexChanged(int,void*)",this,"InterfaceChanged(int,void*)");
	c->SetAlignment(AL_STRETCHH);
	InterfaceCombo = c;

/*
	c->AddItem("Interface 1");
	c->AddItem("Interface 2");
	c->AddItem("Interface 3");

	c->Clear();
	c->AddItem("Interface A");
	c->AddItem("Interface B");
	c->AddItem("Interface C");*/


	l = new RLabel(rt); l->SetText("Programming Clock:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("clock combo"); rt->SetPos(2,y,2);
	c->Connect("Si_IndexChanged(int,void*)",this,"PClockChanged(int,void*)");
	c->SetAlignment(AL_STRETCHH);
	c->AddItem("100 000");
	c->AddItem("200 000");
	c->AddItem("300 000");
	PClockCombo = c;
	b = new RButton(rt); b->SetText("Apply"); rt->SetPos(4,y++);
	b->Connect("Si_Clicked(int)",this,"ApplyP()");
	ApplyPButton = b;
	b->Disable();


	l = new RLabel(rt); l->SetText("Clock Generator:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("clock gen combo"); rt->SetPos(2,y,2);
	c->Connect("Si_IndexChanged(int,void*)",this,"EClockChanged(int,void*)");
	c->SetAlignment(AL_STRETCHH);
	c->AddItem("4000");
	c->AddItem("5000");
	c->AddItem("6000");
	EClockCombo = c;
	b = new RButton(rt); b->SetText("Apply"); rt->SetPos(4,y++);
	b->Connect("Si_Clicked(int)",this,"ApplyE()");
	ApplyEButton = b;
	b->Disable();


	l = new RLabel(rt); l->SetText("Select Port:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("port select combo"); rt->SetPos(2,y,2);
	c->SetAlignment(AL_STRETCHH);
	PortCombo = c;
/*#ifdef WIN32
	c->AddItem("COM1"); //temp until RCom is enumeration is done
	c->AddItem("COM2");
	c->AddItem("COM3");
	c->AddItem("COM4");
	c->AddItem("COM5");
	c->AddItem("COM6");
#else
	c->AddItem("/dev/ttyACM0");
	c->AddItem("/dev/ttyACM1");
	c->AddItem("/dev/ttyACM2");
	c->AddItem("/dev/ttyACM3");
	c->AddItem("/dev/ttyS0");
	c->AddItem("/dev/ttyS1");
	c->AddItem("/dev/ttyS2");
	c->AddItem("/dev/ttyS3");
#endif*/
	b = new RButton(rt); b->SetText("Refresh"); rt->SetPos(4,y++);
	b->Connect("Si_Clicked(int)",this,"Refresh()");
	RefreshButton = b;


	b = new RButton(rt); b->SetText("Connect"); rt->SetPos(0,y++,5);
	b->Connect("Si_Clicked(int)",this,"Connect()");
	b->SetAlignment(AL_STRETCHH);
	ConnectButton = b;



	l = new RLabel(rt); l->SetText("---"); l->Sl_Hide(); rt->SetPos(0,y++,2);
	l = new RLabel(rt); l->SetText("Device Information"); rt->SetPos(0,y++,5);
	l->SetAlignment(AL_STRETCHH);

	l = new RLabel(rt); l->SetText("Select Device:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("device combo"); rt->SetPos(2,y++,3);
	c->Connect("Si_IndexChanged(int,void*)",this,"DeviceChanged(int,void*)");
	c->SetAlignment(AL_STRETCHH);
	c->AddItem("AUTO");
	c->AddItem("ATmega 1");
	c->AddItem("ATmega 2");
	c->AddItem("ATmega 3");
	DeviceCombo = c;

	l = new RLabel(rt); l->SetText("Signature + JTAG ID:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	eb = new REditBox(rt); eb->SetText("sig box"); rt->SetPos(2,y++,3);
	eb->SetAlignment(AL_STRETCHH);

	l = new RLabel(rt); l->SetText("AVR Serial Number:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	eb = new REditBox(rt); eb->SetText("serial box"); rt->SetPos(2,y++,3);
	eb->SetAlignment(AL_STRETCHH);

	l = new RLabel(rt); l->SetText("Osccal Values:"); rt->SetPos(0,y,2);
	l->SetAlignment(AL_STRETCHH);
	c = new RComboBox(rt); c->SetText("osccal combo"); rt->SetPos(2,y,2);
	c->SetAlignment(AL_STRETCHH);
	c->AddItem("osccal 1");
	c->AddItem("osccal 2");
	b = new RButton(rt); b->SetText("Refresh"); rt->SetPos(4,y++);
	b->Connect("Si_Clicked(int)",this,"RefreshAVR()");
	RefreshAVRButton = b;
	b->Disable();


	b = new RButton(rt); b->SetText("Spacer1"); b->Sl_Hide(); rt->SetPos(0,y);
	b = new RButton(rt); b->SetText("Spacer2"); b->Sl_Hide(); rt->SetPos(1,y);
	b = new RButton(rt); b->SetText("Spacer3"); b->Sl_Hide(); rt->SetPos(2,y);
	b = new RButton(rt); b->SetText("Spacer4"); b->Sl_Hide(); rt->SetPos(3,y);
	b = new RButton(rt); b->SetText("Spacer5"); b->Sl_Hide(); rt->SetPos(4,y++);

//---------------------------------------------------------
//Flash Tab

	y=0;
	rt = new RTBox(tc,4,9);
	rt->SetText("Flash");
	rt->frame = F_DOWN;
	rt->spacing = 8;
//	rt->SetAlignment(AL_STRETCHH | AL_STRETCHV);

	b = new RButton(rt); b->SetText("Chip Erase"); rt->SetPos(0,y++,4);
	b->Connect("Si_Clicked(int)",this,"ChipErase()");
	b->SetAlignment(AL_STRETCHH);

	RCheckBox *cc;
	cc = new RCheckBox(rt); cc->SetText("Erase before writing flash"); rt->SetPos(0,y,2);
	cc->SetAlignment(AL_STRETCHH); cc->Sl_Check();
	cc = new RCheckBox(rt); cc->SetText("Verify after writing flash"); rt->SetPos(2,y++,2);
	cc->SetAlignment(AL_STRETCHH); cc->Sl_Check();

	rl = new RLabel(rt); rl->SetText("Flash"); rt->SetPos(0,y++,1);
	eb = new REditBox(rt); eb->SetText("--flpath--"); rt->SetPos(0,y++,4); eb->SetAlignment(AL_STRETCHH);
	flashedit = eb;
	b = new RButton(rt); b->SetText("Read"); rt->SetPos(0,y);
	b->Connect("Si_Clicked(int)",this,"ReadFlash()");
	b = new RButton(rt); b->SetText("Write"); rt->SetPos(1,y);
	b->Connect("Si_Clicked(int)",this,"WriteFlash()");
	b = new RButton(rt); b->SetText("Verify"); rt->SetPos(2,y);
	b->Connect("Si_Clicked(int)",this,"VerifyFlash()");
	b = new RButton(rt); b->SetText("Set File"); rt->SetPos(3,y++);
	b->Connect("Si_Clicked(int)",this,"SelectFlash()");

	rl = new RLabel(rt); rl->SetText("Eeprom"); rt->SetPos(0,y++,1);
	eb = new REditBox(rt); eb->SetText("--eepath--"); rt->SetPos(0,y++,4); eb->SetAlignment(AL_STRETCHH);
	eepromedit = eb;
	b = new RButton(rt); b->SetText("Read"); rt->SetPos(0,y);
	b->Connect("Si_Clicked(int)",this,"ReadEeprom()");
	b = new RButton(rt); b->SetText("Write"); rt->SetPos(1,y);
	b->Connect("Si_Clicked(int)",this,"WriteEeprom()");
	b = new RButton(rt); b->SetText("Verify"); rt->SetPos(2,y);
	b->Connect("Si_Clicked(int)",this,"VerifyEeprom()");
	b = new RButton(rt); b->SetText("Set File"); rt->SetPos(3,y++);
	b->Connect("Si_Clicked(int)",this,"SelectEeprom()");

	RProgressBar *pb = new RProgressBar(rt); rt->SetPos(0,y++,4);
	pb->SetAlignment(AL_STRETCHH);
	flashprogress = pb;
	//InterfaceCombo->Select(0); //	InterfaceChanged(0); // pointer bugfix...
//*/

//---------------------------------------------------------
//Fuse TAB

	hv = new RHVBox(tc);
	hv->SetText("Fuses");
//	hv->frame = F_DOWN;
//	hv->x_mgn = hv->y_mgn = 0;	
	hv->spacing = 4;
	hv->SetAlignment(AL_STRETCHH | AL_STRETCHV | AL_V | AL_LEFT);
/*
	RHVBox *hv2 = new RHVBox(hv);
	tc->ConnectTab("Fuses","Si_Checked()",this,"SelectFuseTab()",hv2);
	hv2->SetAlignment(AL_STRETCHH | AL_STRETCHV | AL_V | AL_LEFT);
	hv2->frame = F_DOWN;
	RControl *r;
	r = new RCheckBox(hv2); r->SetText("Acheck1");r->SetAlignment(AL_STRETCHH);
*/

	rsb = new RSBox(hv);
	sv = new RScrollView(rsb);
	rsb->Setup(10,10);
	rsb->frame = F_DOWN;
	sv->SetAlignment(AL_STRETCHH | AL_STRETCHV | AL_V | AL_LEFT);
	sv->spacing = 0;
	sv->frame = F_DOWN;
	tc->ConnectTab("Fuses","Si_Checked()",this,"SelectFuseTab()",sv);
	fusebox = sv;

//	RControl *r;
//	RContainer *rc = sv;
//	r = new RCheckBox(rc); r->SetText("Acheck1");r->SetAlignment(AL_STRETCHH);
/*
	r = new RCheckBox(rc); r->SetText("Acheck2");r->SetAlignment(AL_STRETCHH);
	r = new RCheckBox(rc); r->SetText("Acheck3");r->SetAlignment(AL_STRETCHH);
	r = new RCheckBox(rc); r->SetText("Acheck4");r->SetAlignment(AL_STRETCHH);

*/

	rt = new RTBox(hv,4,2);
	rt->SetText("Programming");
	rt->frame = F_DOWN;
	rt->spacing = 8;
	rt->SetAlignment(AL_STRETCHH | AL_STRETCHV);

	rl = new RLabel(rt); rl->SetText("Fuses:"); rt->SetPos(0,0);
	RHexBox *hb = new RHexBox(rt); hb->SetText("00 00 00 11"); rt->SetPos(1,0,3,1); hb->SetAlignment(AL_STRETCHH);
	fuseedit = hb; hb->bIns = 0;
	hb->Connect("Si_SetText(char*)",this,"FuseEdited()");
	hb->Connect("Si_Focus(bool)",this,"FuseEditFinished(bool)");


	y = 1;
	b = new RButton(rt); b->SetText("Read"); rt->SetPos(0,y);
	b->Connect("Si_Clicked(int)",this,"ReadFuse()");
	b = new RButton(rt); b->SetText("Write"); rt->SetPos(1,y);
	b->Connect("Si_Clicked(int)",this,"WriteFuse()");
	b = new RButton(rt); b->SetText("Verify"); rt->SetPos(2,y);
	b->Connect("Si_Clicked(int)",this,"VerifyFuse()");
	b = new RButton(rt); b->SetText("Default"); rt->SetPos(3,y);
	b->Connect("Si_Clicked(int)",this,"DefaultFuse()");


//---------------------------------------------------------

	hv = new RHVBox(tc);
	hv->SetText("Config");
	hv->SetAlignment(AL_STRETCHH | AL_STRETCHV | AL_V | AL_LEFT);

	RTreeView *tv;

	rsb = new RSBox(hv);
	rsb->x_mgn = rsb->y_mgn = 4;
	rsb->SetText("Config File");
	rsb->frame = F_DOWN;
	rsb->SetAlignment(AL_STRETCHH | AL_STRETCHV);
	tv = new RTreeView(rsb);
	rsb->Setup(10,10);
//	tv->SetTree(stp);

	RTreeNode *tn;//,*tnc; //XXX
	tn  = new RTreeNode(0); //XXX
	new RTreeNode(tn); //XXX
	tv->SetTree(tn);

	tc->ConnectTab("Config","Si_Checked()",this,"SelectConfigTab()",tv);

//---------------------------------------------------------

	eb = new REditBox(wnd);
	eb->SetAlignment(AL_STRETCHH | AL_STRETCHV);

//---------------------------------------------------------

	prog_list = GetProgrammerList();
	for(Programmer *p = prog_list; p; p = p->next) {
		cb->AddItem((char*)p->name(),p);
	}
//	cb->Select(prog_list->next->next->next);
//	cb->Select(6);
//---------------------------------------------------------
}

//Setup
//-----------------------------------------------------------------------------####

//int RMain()
int main()
{
	RProgApp app;
	app.Setup();
	app.Run();
	return 0;
}

//-----------------------------------------------------------------------------####


