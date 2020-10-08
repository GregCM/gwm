/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;       /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 1;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "ProFont:size=11" };
static const char dmenufont[]       = "ProFont:size=11";

/* 8 normal colors */
static const char col_black1[]      = "#000000";/*0: BLACK*/
static const char col_redbl1[]      = "#180808";/*0.5: RED-BLACK*/
static const char col_red1[]        = "#d41500";/*1: RED*/
static const char col_green1[]      = "#19c948";/*2: GREEN*/
static const char col_yellow1[]     = "#d6b800";/*3: YELLOW*/
static const char col_blue1[]       = "#5101d0";/*4: BLUE*/
static const char col_magenta1[]    = "#8101a3";/*5: MAGENTA*/
static const char col_cyan1[]       = "#25cba2";/*6: CYAN*/
static const char col_gray1[]       = "#dfc1c1";/*7: GRAY*/

/* 8 bright colors */
static const char col_black2[]      = "#927272";/*8: gray*/
static const char col_redbl2[]      = "#3c2121";/*8.5: red-gray*/
static const char col_red2[]        = "#ff5b5b";/*9: red*/
static const char col_green2[]      = "#59ff59";/*10: green*/
static const char col_yellow2[]     = "#ffff59";/*11: yellow*/
static const char col_blue2[]       = "#5c5cff";/*12: blue*/
static const char col_magenta2[]    = "#ff41ff";/*13: magenta*/
static const char col_cyan2[]       = "#5cd8d8";/*14: cyan*/
static const char col_white1[]      = "#fdf3f3";/*15: white*/

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white1, col_redbl1, col_white1},
	[SchemeSel]  = { col_black1, col_blue1,  col_blue1},
};

/* start some nice programs */
static const char *const autostart[] = {
	"st", "-e", "ranger", NULL,
	"st", "-e", "gtop", NULL,
    /* TODO Neofetch should be run here:*/
	"st", NULL,
    /* Redshift at night w/screen-dim = 40% */
    "redshift", "-b", "1.0:0.4", "-l", "29.75:-95.36", NULL,
    /* Bucklespring keyboard sound effects,
     * mutable by ScrollLock x2 */
    "buckle", NULL,
    "xrandr", "--output","DP1","--auto", "--left-of", "eDP1", NULL,
    "xrandr", "--output","HDMI1","--auto", "--left-of", "DP1", NULL,
    "xwallpaper", "--stretch", "/home/greg/Pictures/wallpaper.jpg", NULL,
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
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */ static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
	{ "|C|",      centeredmaster },
	{ ">C>",      centeredfloatingmaster },
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_redbl2, "-nf", col_white1, "-sb", col_blue2, "-sf", col_black1, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "selfrestart.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_x,      transfer,       {0} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, /*tile*/
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} }, /*floating*/
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, /*monocle*/
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[3]} }, /*spiral*/
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[4]} }, /*dwindle*/
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[5]} }, /*centered-master*/
	{ MODKEY|ShiftMask,             XK_c,      setlayout,      {.v = &layouts[6]} }, /*centered-floating master*/
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, /* move to monitor left of current*/
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } }, /* move to monitor right of current*/
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, /* move tag one monitor to the left*/
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, /* move tag one monitor to the right*/
    { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
 	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = +1 } }, /* + */
 	{ MODKEY,                       XK_equal,  setgaps,        {.i = 0  } }, /* = */

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY,                       XK_Escape, quit,           {0} },
    { MODKEY|ShiftMask,             XK_Escape, self_restart,   {0} },

	{ 0,		    XK_Print,                  spawn,		   SHCMD("scrot $HOME/Pictures/`date +%Y-%m-%d_%H:%M:%S`.png") },
	{ 0,            XF86XK_MonBrightnessUp,	   spawn,		   SHCMD("xbacklight -inc 7.5") },
	{ 0,            XF86XK_MonBrightnessDown,  spawn,		   SHCMD("xbacklight -dec 7.5") },
	{ 0,            XF86XK_AudioMute,		   spawn,		   SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
	{ 0,            XF86XK_AudioRaiseVolume,   spawn,		   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%") },
	{ 0,            XF86XK_AudioLowerVolume,   spawn,		   SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%") }
,
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

