/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "FontAwesome:size=11", "Cantarell:size=11" };

static const char col_fg_norm[] = "#c5c8c6";
static const char col_bg_norm[] = "#1d1f21";
static const char col_fg_sel[]  = "#1d1f21";
static const char col_bg_sel[]  = "#81a2be";
static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { col_fg_norm, col_bg_norm, col_bg_norm },
	[SchemeSel]  = { col_fg_sel,  col_bg_sel,  col_bg_sel  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance  title       tags mask isfloating monitor */
	{ "pinentry-qt",   NULL,     NULL,       0,        1,         -1 },
	{ "zoom",          NULL,     NULL,       0,        1,         -1 },
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
#define XF86AudioMicMute       0x1008ffb2
#define XF86AudioMute          0x1008ff12
#define XF86AudioNext          0x1008ff17
#define XF86AudioPause         0x1008ff31
#define XF86AudioPlay          0x1008ff14
#define XF86AudioPrev          0x1008ff16
#define XF86AudioRaiseVolume   0x1008ff13
#define XF86Calculator         0x1008ff1d
#define XF86MonBrightnessDown  0x1008ff03
#define XF86MonBrightnessUp    0x1008ff02

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

#define CMD(X) static const char * X[] = { "wm-cmds", #X, NULL };
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
CMD(vol_mic_mute)
CMD(brightness_up)
CMD(brightness_down)
CMD(quitmenu)
CMD(notif_del)
CMD(notif_last)
CMD(notif_action)
CMD(log_time)

/* commands spawned when clicking statusbar, the mouse button pressed is exported as BUTTON */
static const StatusCmd statuscmds[] = {
	{ "1", 1 },
	{ "2", 2 },
	{ "3", 3 },
	{ "4", 4 },
	{ "5", 5 },
	{ "6", 6 },
	{ "7", 7 },
	{ "8", 8 },
	{ "9", 9 },
	{ "10", 10 },
	{ "11", 11 },
	{ "12", 12 },
	{ "13", 13 },
	{ "14", 14 },
	{ "15", 15 },
	{ "16", 16 },
};
static const char *statuscmd[] = { "wm-status", NULL, NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */

	{ 0,                        XF86AudioMute, spawn,          {.v = vol_mute } },
	{ 0,                        XF86AudioNext, spawn,          {.v = audio_next } },
	{ 0,                        XF86AudioPlay, spawn,          {.v = audio_pause } },
	{ 0,                        XF86AudioPrev, spawn,          {.v = audio_prev } },
	{ 0,                       XF86AudioPause, spawn,          {.v = audio_pause } },
	{ 0,                       XF86Calculator, spawn,          {.v = log_time } },
	{ 0,                     XF86AudioMicMute, spawn,          {.v = vol_mic_mute } },
	{ 0,                  XF86MonBrightnessUp, spawn,          {.v = brightness_up } },
	{ 0,                 XF86AudioLowerVolume, spawn,          {.v = vol_down } },
	{ 0,                 XF86AudioRaiseVolume, spawn,          {.v = vol_up } },
	{ 0,                XF86MonBrightnessDown, spawn,          {.v = brightness_down } },
	{ MODKEY,                       XK_F7,     spawn,          {.v = audio_prev } },
	{ MODKEY,                       XK_F8,     spawn,          {.v = audio_pause } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = audio_next } },
	{ MODKEY,                       XK_a,      spawn,          {.v = audio_info } },
	{ MODKEY,                       XK_grave,  spawn,          {.v = notif_last } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshot } },
	{ MODKEY|ControlMask,           XK_space,  spawn,          {.v = notif_del } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = terminal } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = notif_action } },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = quitmenu } },
	{ MODKEY|ShiftMask|ControlMask, XK_l,      spawn,          {.v = lock } },
	{ MODKEY|ShiftMask|ControlMask, XK_p,      spawn,          {.v = password } },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */

/*
 * Mouse buttons
 *    1: left click
 *    2: middle click
 *    3: right click
 *    4: scroll up
 *    5: scroll down
 *    8: "back" button
 *    9: "forward" button
 */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkLtSymbol,          0,              Button4,        focusstack,     {.i = +1 } },
	{ ClkLtSymbol,          0,              Button5,        focusstack,     {.i = -1 } },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

	{ ClkStatusText,        0,              Button1,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button3,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button4,        spawn,          {.v = statuscmd } },
	{ ClkStatusText,        0,              Button5,        spawn,          {.v = statuscmd } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
