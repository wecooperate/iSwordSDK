//******************************************************************************
/*++
	FileName:		iSword.h
	Description:

--*/
//******************************************************************************
#ifndef __iSword_h_6591dbbe_85d3_457a_9064_49b24f9ca005__
#define __iSword_h_6591dbbe_85d3_457a_9064_49b24f9ca005__
//******************************************************************************
enum emAPIIndex {
	emAPIQuickBegin,
	emAPITerminateProcess,
	emAPIDeleteFile,
	emAPIQuickEnd,

	emAPIProcessBegin = 100,
	emAPIProcessEnd,

	emAPIFileBegin = 200,
	emAPIFileEnd,

	emAPIRegBegin = 300,
	emAPIRegEnd,

	emAPIMax,
};
//******************************************************************************
#endif
