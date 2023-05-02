/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 10;       /* vertical padding of bar */
static const int sidepad            = 10;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char norBG[]           = "#232627";
static const char norFG[]           = "#7f8c8d";
static const char norBD[]           = "#31363b";
static const char selFG[]           = "#eff0f1";
static const char selBG[]           = "#1b668f";
static const char selBD[]           = "#1b668f";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { norFG,     norBG,     norBD },
	[SchemeSel]  = { selFG,     selBG,     selBD },
};

static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
	"setxkbmap", "de", "neo", NULL,
	"sh", "-c", "picom", "--experimental-backends", NULL,
	"dwmblocks", NULL,
	"dunst", NULL,
	"xset", "r", "rate", "250", "30", NULL,
	"xset", "s", "off", "-dpms", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Nitrogen", NULL,       NULL,       0,            1,           -1 },
//	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "|H|",      NULL },    /* no layout function means floating behavior */
	{ "<0>",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
//static const char *dmenucmd[] = { "dmenu_run", "-x", "10", "-y", "10", "-z", "1900", NULL };
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *screenshot []  = { "flameshot", "gui", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_F7,     spawn,          SHCMD("pactl set-sink-volume 1 -10% ; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_F8,     spawn,          SHCMD("pactl set-sink-volume 1 +10% ; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,                       XK_F9,     spawn,          {.v = browser } },
	{ MODKEY,                       XK_F12,    spawn,          {.v = screenshot } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_r,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_t,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_n,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_d,      setmfact,       {.f = +0.05} },
//	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_x,      killclient,     {0} },
	{ MODKEY|ALTKEY,                XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ALTKEY,                XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ALTKEY,                XK_m,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
//	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ALTKEY,                XK_comma,  setgaps,        {.i = -1 } },
	{ MODKEY|ALTKEY,                XK_period, setgaps,        {.i = +1 } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_period, setgaps,        {.i = 10 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
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

