#include "Persisto.h"

static AEGP_PluginID	S_my_id				= 0;

static AEGP_Command		S_persisto_cmd 		= 0;

static SPBasicSuite		*sP					= NULL;

static A_Err
UpdateMenuHook(
	AEGP_GlobalRefcon		plugin_refconPV,		/* >> */
	AEGP_UpdateMenuRefcon	refconPV,				/* >> */
	AEGP_WindowType			active_window)			/* >> */
{
	A_Err 					err = A_Err_NONE;
	
	AEGP_SuiteHandler		suites(sP);
	
	if (S_persisto_cmd){
		err = suites.CommandSuite1()->AEGP_EnableCommand(S_persisto_cmd);
	} else {
		err = suites.CommandSuite1()->AEGP_DisableCommand(S_persisto_cmd);
	}
	return err;
}
			   
static A_Err
CommandHook(
	AEGP_GlobalRefcon	plugin_refconPV,		/* >> */
	AEGP_CommandRefcon	refconPV,				/* >> */
	AEGP_Command		command,				/* >> */
	AEGP_HookPriority	hook_priority,			/* >> */
	A_Boolean			already_handledB,		/* >> */
	A_Boolean			*handledPB)				/* << */
{
	A_Err 				err 	= A_Err_NONE, 
						err2 	= A_Err_NONE;

	if (S_persisto_cmd == command){
		try{
			AEGP_SuiteHandler		suites(sP);
			ERR2(suites.UtilitySuite3()->AEGP_ReportInfo(S_my_id, STR(StrID_AnchorMessage)));
		} catch (A_Err &thrown_err) {
			err = thrown_err;
		}
	}
	return err;
}

A_Err
EntryPointFunc(
	struct SPBasicSuite		*pica_basicP,			/* >> */
	A_long				 	major_versionL,			/* >> */		
	A_long					minor_versionL,			/* >> */		
	AEGP_PluginID			aegp_plugin_id,			/* >> */
	AEGP_GlobalRefcon		*global_refconP)		/* << */
{
	A_Err 			err		=	A_Err_NONE, 
					err2	=	A_Err_NONE;
	sP		=	pica_basicP;
	S_my_id	=	aegp_plugin_id;	

	AEGP_SuiteHandler	suites(sP);

	ERR(suites.CommandSuite1()->AEGP_GetUniqueCommand(&S_persisto_cmd));

	if (S_persisto_cmd){
		ERR(suites.CommandSuite1()->AEGP_InsertMenuCommand(	S_persisto_cmd, 
															STR(StrID_Menu_Item), 
															AEGP_Menu_FILE, 
//															AEGP_MENU_INSERT_SORTED));
															9));

		// Remove the Save As menu.
		// First remove the commands under the Save As menu.
		ERR(suites.CommandSuite1()->AEGP_RemoveMenuCommand(6));		// Save As...
		ERR(suites.CommandSuite1()->AEGP_RemoveMenuCommand(2166));	// Save a Copy...
		ERR(suites.CommandSuite1()->AEGP_RemoveMenuCommand(3785));	// Save a Copy As XML...
		ERR(suites.CommandSuite1()->AEGP_RemoveMenuCommand(4165));	// Save a Copy As 17.x...
		ERR(suites.CommandSuite1()->AEGP_RemoveMenuCommand(4164));	// Save a Copy As CC (16.x)...
		// Then remove the Save As menu item itself.
		ERR(suites.CommandSuite1()->AEGP_RemoveMenuCommand(3840));


		ERR(suites.RegisterSuite5()->AEGP_RegisterCommandHook(S_my_id,
																AEGP_HP_BeforeAE, 
																AEGP_Command_ALL, 
																CommandHook, 
																NULL));

		ERR(suites.RegisterSuite5()->AEGP_RegisterUpdateMenuHook(	S_my_id, 
																	UpdateMenuHook, 
																	NULL));
	}
	if (err){
		err2 = suites.UtilitySuite3()->AEGP_ReportInfo(S_my_id, STR(StrID_Error));
	}
	return err;
}
