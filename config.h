/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 25;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "Cantarell:size=11" };
static const char dmenufont[]       = "Cantarell:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance  title       tags mask isfloating monitor */
	{ "Firefox",       NULL,     NULL,       1 << 0,   0,         -1 },
	{ "pinentry-qt",   NULL,     NULL,       0,        1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[]|",      deck }, /* https://dwm.suckless.org/patches/deck/dwm-deck-6.0.diff */
};

/* key definitions */
/* #define MODKEY Mod1Mask - Left Alt */
#define MODKEY Mod4Mask /* Windows Key */
#define XF86AudioLowerVolume   0x1008ff11
#define XF86AudioMute          0x1008ff12
#define XF86AudioRaiseVolume   0x1008ff13
#define XF86AudioPlay          0x1008ff14
#define XF86AudioPause         0x1008ff31
#define XF86Calculator         0x1008ff1d
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

#define CMD(X) static const char * X[] = { "/etc/dwm/cmds", #X, NULL };
CMD(dmenucmd)
CMD(terminal)
CMD(lock)
CMD(screenshot)
CMD(password)
CMD(audio_pause)
CMD(audio_next)
CMD(audio_prev)
CMD(audio_info)
CMD(vol_up)
CMD(vol_down)
CMD(vol_mute)
CMD(quitmenu)
CMD(notif_del)
CMD(notif_last)
CMD(notif_action)
CMD(log_time)

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
	{ "status-1", 1 },
	{ "status-2", 2 },
	{ "status-3", 3 },
	{ "status-4", 4 },
	{ "status-5", 5 },
	{ "status-6", 6 },
	{ "status-7", 7 },
	{ "status-8", 8 },
};
static const char *statuscmd[] = { "/etc/dwm/cmds", NULL, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lock } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshot } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = terminal } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_space,  spawn,          {.v = notif_del } },
	{ MODKEY,                       XK_grave,  spawn,          {.v = notif_last } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = notif_action } },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,         XK_apostrophe, spawn,          {.v = password } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = audio_prev } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = audio_pause } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = audio_next } },
	{ 0,                        XF86AudioPlay, spawn,          {.v = audio_pause } },
	{ 0,                       XF86AudioPause, spawn,          {.v = audio_pause } },
	{ MODKEY,                 XK_bracketright, spawn,          {.v = audio_info } },
	{ 0,                        XF86AudioMute, spawn,          {.v = vol_mute } },
	{ 0,                 XF86AudioRaiseVolume, spawn,          {.v = vol_up } },
	{ 0,                 XF86AudioLowerVolume, spawn,          {.v = vol_down } },
	{ 0,                       XF86Calculator, spawn,          {.v = log_time } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      spawn,          {.v = quitmenu } },
	//{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
