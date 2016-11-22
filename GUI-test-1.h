/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  GENERATE                         1       /* callback function: GenerateWaveform */
#define  GENERATE_COMMANDBUTTON           2       /* control type: command, callback function: (none) */
#define  GENERATE_PREDEFINED_PATH         3       /* control type: listBox, callback function: path */

#define  PANEL                            2
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: run */
#define  PANEL_LED                        3       /* control type: LED, callback function: (none) */
#define  PANEL_NUMERIC                    4       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU2                    3
#define  MENUBAR_MENU3                    4
#define  MENUBAR_MENU4                    5


     /* Callback Prototypes: */

int  CVICALLBACK GenerateWaveform(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK path(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
