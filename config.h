/* -===applyed patches===-  
     - alpha (transparency)
     - gaps
     - cool-autostart 
     - fullgaps
     - rotate stack 
     - always center
     - fibonacci      */

/* -===appearance===- */
static const unsigned int borderpx  = 2;        /* border pixel of windows   */
static const unsigned int gappx     = 15;       /* gaps between windows      */
static const unsigned int snap      = 3;        /* snap pixel                */
static const int showbar            = 1;        /* 0 means no bar            */
static const int topbar             = 1;        /* 0 means bottom bar        */
static const int vertpad            = 6;        /* vertical padding of bar   */
static const int sidepad            = 6;        /* horizontal padding of bar */
static const char *fonts[]          = { "Hack Nerd Font Mono:size=12" };
static const char dmenufont[]       = "Hack:size=12";
static const char col_gray1[]       = "#232627";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#7f8c8d";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#1b668f";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, OPAQUE, OPAQUE },
	[SchemeSel]  = { OPAQUE, OPAQUE, OPAQUE },
	/*[SchemeNorm] = { OPAQUE, baralpha, borderalpha },*/
	/*[SchemeSel]  = { OPAQUE, baralpha, borderalpha },*/
};

static const char *const autostart[] = {
	"sh", "-c", "/home/ghost/.config/erzengel/scripts/autostart.sh", NULL,
	NULL 
};

/* tagging */
static const char *tags[] = { "1" , "2", "3", "4", "5", "6", "7", };
/* static const char *tags[] = { "  " , "  ", "  ", "  ", "  ", "  ", "  ", }; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "steam",    NULL,       NULL,       1 << 8,       1,           -1 },
};


/* -===layouts===- */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[@]",      spiral  },     /* fibonacci layout */
	{ "><>",      NULL    },     /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[\\]",     dwindle },
	{ "[]=",      tile    },     /* first entry is default */
};

/* -===keydefinitions===- */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static char dmenumon[2] = "0";                                            // component of dmenucmd, manipulated in spawn()
// static const char *dmenucmd[] = { "/home/ghost/scripts/dmenu.sh", NULL }; // actually not needed, dmenu is set in ~/.confic/sxhkd/sxhkdrc-dwm 
static const char *termcmd[]  = { "st",        NULL };

/* -===keybindings===- */
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_n,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_r,      focusstack,     {.i =   +1 } },
	{ MODKEY,                       XK_t,      focusstack,     {.i =   -1 } },
	{ MODKEY,                       XK_d,      setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ ControlMask|ShiftMask,        XK_r,      setgaps,        {.i =  -5 } },
	{ ControlMask|ShiftMask,        XK_t,      setgaps,        {.i =  +5 } },
	{ ControlMask|ShiftMask,        XK_n,      setgaps,        {.i =   0 } },

	{ MODKEY,                       XK_g,      incnmaster,     {.i =  -1 } },
	{ MODKEY,                       XK_f,      incnmaster,     {.i =  +1 } }, 
	
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[4]} },
	{ ControlMask,                  XK_space,  setlayout,      {0} },
	{ ControlMask|ShiftMask,        XK_space,  togglefloating, {0} },
	
	{ MODKEY,                       XK_x,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

        /* ----------------------------------------------------------------------------- */
	/*{ MODKEY,                     XK_Return, zoom,           {0} },                */
	/*{ MODKEY,                     XK_t,      setlayout,      {.v = &layouts[0]} }, */
	/*{ MODKEY,                     XK_f,      setlayout,      {.v = &layouts[1]} }, */
	/*{ MODKEY,                     XK_Tab,    view,           {0} },                */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, 
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, 
	/*{ MODKEY,                     XK_0,      view,           {.ui = ~0 } },        */
	/*{ MODKEY|ShiftMask,           XK_0,      tag,            {.ui = ~0 } },        */
	/*{ MODKEY,                     XK_m,      setlayout,      {.v = &layouts[2]} }, */

	/* -- Key bindings for this command are configured in the custom SXHKD file ---- */
//	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = dmenucmd } },   //   This is just a dummy. The real thing is in sxhkdrc-dwm
	/*{ MODKEY,                     XK_Return, spawn,          {.v = termcmd } },    */
	/*{ MODKEY,                     XK_Up,     spawn,          {.v = upvol} },       */
	/*{ MODKEY,                     XK_Down,   spawn,          {.v = downvol} },     */
};

/* mouse button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* See LICENSE file for copyright and license details. */
