#include "Persisto.h"

TableString		g_strs[StrID_NUMTYPES] = {
	StrID_NONE,						"",
	StrID_Menu_Item,				"Anchor Save As",
	StrID_Section_Key,				"AnchorPlugin",
	StrID_AnchorMessage,			"Anchor Save As invoked.",
	/*
	StrID_Value_Key_1,				"Fuzziness",
	StrID_Value_Key_2,				"Cliche Du Jour",
	StrID_DefaultString,			"Default",
	StrID_NewValueAdded,			"New value added!",
	StrID_ValueExisted,				"Value already existed",
	StrID_DifferentValueSet,		"Different value found than expected!",
	*/
	StrID_Error,					"Problems encountered while registering menu command."
};

char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}