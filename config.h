/* See LICENSE file for copyright and license details. */
#define TERMINAL "Alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 2;       	/* snap pixel */
static const unsigned int gappih    = 8;       	/* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       	/* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static int showsystray        = 0;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;     /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= False;               /* False means bottom tab bar */

// static const char *fonts[]          = { "monospace:size=12" };
// static const char dmenufont[]       = "monospace:size=12";
static const char *fonts[]          = { "Hack Nerd Font:size=12" };
static const char dmenufont[]       = "Hack Nerd Font:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_red[]         = "#770000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	// [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	// [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	// [SchemeTitle]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeTitle]  = { col_gray1, col_gray1,  col_gray2  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
//const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
//const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd1[] = {"alacritty", "--class", "spterm", NULL };
const char *spcmd2[] = {"alacritty", "--class", "spfm", "-e", "lf", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",    	spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
// static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask   isfloating   monitor */
	{ "Gimp",	    NULL,	      NULL,		    1 << 5,		  0,	        -1 },
  { "TelegramDesktop", NULL,NULL,		    1 << 3,		  0,	        -1 },
	{ "Peazip",	  NULL,	      NULL,		    0,		      1,	        -1 },
	{ "Arandr",	  NULL,	      NULL,		    0,		      1,	        -1 },
	{ "SimpleScreenRecorder", NULL,NULL,	0,		      1,	        -1 },
	{ "Galculator",NULL,NULL,	0,		      1,	        -1 },
	{ "Yad",	    NULL,	      NULL,		    0,		      1,	        -1 },
	{ "Firefox",  NULL,	      NULL,		    1 << 1,		0,	 -1 },
	{ NULL,		"spterm", NULL,		SPTAG(0),	1,	 -1 },
	{ NULL,		"spfm",	  NULL,		SPTAG(1),	1,	 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include "shiftview.c"
// #include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
/*0*/	{ "[]=",   tile },    /* first entry is default */
/*1*/	{ "TTT",   bstack },
/*2*/	{ "===",   bstackhoriz },
/*3*/	{ "[M]",   monocle },
/*4*/	{ "[@]",   spiral },
/*5*/	{ "[\\]",  dwindle },
/*6*/	{ "H[]",   deck },
/*7*/	{ "HHH",   grid },
/*8*/	{ "###",   nrowgrid },
/*9*/	{ "---",   horizgrid },
/*10*/	{ ":::",   gaplessgrid },
/*11*/	{ "|M|",   centeredmaster },
/*12*/	{ ">M>",   centeredfloatingmaster },
/*13*/	{ "><>",   NULL }, /* no layout function means floating behavior */
/*14*/	{ NULL,    NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
// static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
#include <X11/XF86keysym.h>


#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
 	/* volume and brightness */
    	{ 0,  XF86XK_AudioMute,           spawn, SHCMD("amixer -q -D pulse sset Master toggle") },
    	{ 0,  XF86XK_AudioRaiseVolume,    spawn, SHCMD("amixer -q -D pulse sset Master 5%+") },
    	{ 0,  XF86XK_AudioLowerVolume,    spawn, SHCMD("amixer -q -D pulse sset Master 5%-") },
    	{ 0,  XF86XK_AudioMute,           spawn, SHCMD("changevolume toggle") },
    	{ 0,  XF86XK_AudioRaiseVolume,    spawn, SHCMD("changevolume up") },
    	{ 0,  XF86XK_AudioLowerVolume,    spawn, SHCMD("changevolume down") },
    	{ 0,  XF86XK_MonBrightnessUp,     spawn, SHCMD("brightnessctl set +10") },
    	{ 0,  XF86XK_MonBrightnessDown,   spawn, SHCMD("brightnessctl set 10-") },

	{ MODKEY|ShiftMask,            	XK_f,	spawn, SHCMD("$FMGR") },
  { MODKEY,				        XK_y,         spawn, SHCMD("xcpc") },
  { MODKEY,               XK_BackSpace, spawn, SHCMD("slock") },
  { MODKEY,		            XK_apostrophe,spawn, SHCMD("galculator") },
  { MODKEY,				        XK_p,         spawn, SHCMD("arandr") },
  // { MODKEY|ShiftMask,	XK_r,        spawn,	    SHCMD(TERMINAL " -c float-st -g 95x28 -e gotop") },
  // { MODKEY,			      XK_F11,		spawn,		SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
  { MODKEY|ControlMask,   XK_Return,    spawn,		SHCMD("$TERMINAL -e runtmux") },


  // Screenshot
  { 0,			       XK_Print,	    spawn,		SHCMD("maim ~/Pictures/pic-full-$(date '+%y%m%d-%H%M-%S').png && notify-send '🖼️ Screenshot saved'") },
  { MODKEY|ShiftMask,	 	          XK_s,      spawn,	   SHCMD("maim -s | xclip -selection clipboard -t image/png && notify-send '📋 Screenshot area copied to clipboard'") },
  { ControlMask,                  XK_Print,  spawn,    SHCMD("maim | xclip -selection clipboard -t image/png && notify-send '📋 Screenshot copied to clipboard'") },
  { ShiftMask,                    XK_Print,  spawn,    SHCMD("maimpick") },


	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
    	{ MODKEY|ShiftMask,             XK_b,      togglesystray,  {0} },
	{ MODKEY|ControlMask,           XK_w,      tabmode,        {-1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_n,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_n,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,	                XK_space, zoom,           {0} },
	{ MODKEY,              		XK_z,      incrgaps,       {.i = +3 } },
	{ MODKEY,    			XK_x,      incrgaps,       {.i = -3 } },
	{ MODKEY,    			XK_a,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,    		XK_a,      defaultgaps,    {0} },
  { MODKEY,			                  XK_i,		   shiftview,	     { .i = -1 } },
	{ MODKEY,			                  XK_o,	     shiftview,	     { .i = 1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,             		XK_g,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY,             		XK_u,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY,             		XK_f,      setlayout,      {.v = &layouts[13]} },
	{ MODKEY,                       XK_semicolon,  setlayout,  {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,     moveresizeedge, {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,   moveresizeedge, {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,   moveresizeedge, {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,  moveresizeedge, {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,     moveresizeedge, {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,   moveresizeedge, {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,   moveresizeedge, {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,  moveresizeedge, {.v = "R"} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,           	XK_Return, togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_e,	   togglescratch,  {.ui = 1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, //quit
	{ MODKEY|ControlMask,           XK_q,      quit,           {1} }, //restart
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

