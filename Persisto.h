#include "AEConfig.h"
#ifdef AE_OS_WIN
	#define VC_EXTRALEAN
	#include <io.h>
	#include <fcntl.h>
	#include <windows.h>
	#include <stddef.h>
	#include <windowsx.h>
	#include <commctrl.h>
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

#include "entry.h"
#include "AE_GeneralPlug.h"
#include "AEGP_SuiteHandler.h"
#include "AE_Macros.h"
#include "Persisto_Strings.h"
#include "String_Utils.h"

#define DEFAULT_FUZZINESS 3.286

typedef struct {
	A_u_long		index;
	A_char			str[256];
} TableString;

// This entry point is exported through the PiPL (.r file)
extern "C" DllExport AEGP_PluginInitFuncPrototype EntryPointFunc;
