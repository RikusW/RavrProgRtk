
#include "RFile.h"
#include "RString.h"
#include "RTreeView.h"


class AvrPart
{
	AvrPart() {};
	~AvrPart() {};


	RString name,core,speed,osccal;
	u32 signature;
	bool toggle_pin;

	u32 flash_size,flash_page;
	u32 eep_size,eep_page;
	u32 iram_size,iram_start;
	u32 eram_size,eram_start;

	u32 rww_start,rww_stop; 
	u32 nrww_start,nrww_stop; 
	RString boot_sizes;

	RTreeNode *irq; //XXX

	u32 ocd_rev,ocd_reg,ocd_id,ocd_upper_io;
	RString ocd_read,ocd_write,ocd_eread,ocd_ewrite;
	RString ocd_eepi,ocd_flashi;

	RTreeNode *modules; //XXX
};
