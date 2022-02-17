// vim:ts=4 sts=0 sw=4

#include "../Rtk-gui/RtkAll.h"

#include <stdio.h>

//-----------------------------------------------


int RMain()
{
	RApp app;

	app.wnd = new RMainWindow(60,50,600,460); //XXX
	app.wnd->Create();
	app.wnd->SetText("Avr Config Viewer");
	app.wnd->SetAlignment(AL_H);

//----------------------

	RConfig r;
	RSBox *rsb;
	RTreeNode *p,*x;
	RTreeView *tv;

	rsb = new RSBox(app.wnd);
	rsb->frame = F_DOWN;
	tv = new RTreeView(rsb);
	rsb->Setup(10,10);
#ifdef _WIN32
	p = r.ReadRcf("c:/RavrProgParts/ATmega328.rcf");
#else
	p = r.ReadRcf("../RavrProgParts/ATmega328.rcf");
#endif
	tv->SetTree(p);

//----------------------

	x = p->GetNode("INTERRUPTS");
	if(x) for(x = x->child; x; x = x->next) {
		RString s = x->line;
		s.Replace(',','_');
		s.Replace(' ','_');
		s.Merge('_');
		s.Term();
		s.ToUpper();
		s+= "_vect";
	}

//----------------------

	RString s,t;

	//x = p->GetNode("ADMIN/SIGNATURE");
	x = p->GetNode("STK500/IspEnterProgMode/timeout");
	if(x) {
		s = x->line;
		t.SplitL(s,'=');
		printf("--- %s --- %s ---\n\n",t.GetStr(),s.GetStr());
	}else{
		printf("x=0\n");
	}
	

//----------------------

	app.Run();
}

