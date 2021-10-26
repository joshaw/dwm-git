#!/bin/sh
set -eu

log() {
	echo "$(date) $*" >> /var/log/dwm/dwm_cmds.log
}

disconnect() {
	nohup "$@" > /dev/null 2>&1 &
}

status() {
	sh /etc/dwm/status.sh
}

quit_dwm() {
	#printf 'yes\nno\n' | dmenu -f -p "Quit dwm?" | grep -q 'yes' && killall dwm
	action="$(printf 'Lock\nSuspend\nLogout\nShutdown\n' | dmenu -p "Action")"
	log "$(echo "$action" | tr 'A-Z' 'a-z')"
	case "$action" in
		Lock) slock ;;
		Suspend) systemctl suspend && slock ;;
		Logout) killall dwm ;;
		Shutdown) systemctl poweroff ;;
	esac
}

lock_screen() {
	slock
	log "unlocked"
}

mpd_cmd() {
	mpc "$1" > /dev/null
}

screenshot() {
	#fname="$(date "+%Y%m%d-%H%M")"
	#fullname="$HOME/screenshots/screenshot_$fname.png"
	#maim -s -m 10 | tee "$fullname" | xclip -selection clipboard -t image/png
	#[ -s "$fullname" ] || rm -f "$fullname"
	scrot \
		--select \
		--silent \
		--freeze \
		--exec 'xclip -selection clipboard -t image/png -i "$f"' \
		"$HOME"'/screenshots/%Y-%m-%d_%H-%M-%S_$wx$h.png'
}

calendar() {
	EXPIRE="$((30 * 1000))"
	HEADER="$(date '+%a %d %b %Y')"
	BODY="$(cal --color=always |
		sed -e '1d' \
			-e '/^\s*$/d' \
			-e 's#\(.....\)$#<i>\1</i>#' \
			-e 's#'$(printf '\033\[7m')'#<u><i><b>#' \
			-e 's#'$(printf '\033\[27m')'#</b></i></u>#')"
	notify-send -t "$EXPIRE" "$HEADER" "<small><tt>$BODY</tt></small>"
}

status_mpd() {
	HEADER="$(mpc -f "%title%" current)"
	BODY="$(mpc -f "<small>from</small> %album%\n<small>by</small> %artist%" current)"
	notify-send "$HEADER" "$BODY"
}

status_net() {
	EXPIRE="$((30 * 1000))"
	BODY="$(networkctl status --lines 0; echo; networkctl --no-legend)"
	notify-send -t "$EXPIRE" "Network Status" "<small><tt>$BODY</tt></small>"
}

status_vol() {
	notify-send "Master Mixer" "$(amixer sget Master | grep '%')"
}

CMD="${1:-""}"

log "$CMD"
case "$CMD" in
	browser) disconnect firefox ;;
	lock) lock_screen ;;
	dmenu_run) dmenu_run ;;
	screenshot) screenshot ;;
	#terminal) disconnect rxvt-unicode ;;
	#terminal) disconnect xfce4-terminal ;;
	terminal) disconnect alacritty ;;
	password) disconnect python3 ~/bin/dmenu-keepassxc.py ;;
	calendar) calendar ;;

	audio_pause) mpd_cmd toggle ;;
	audio_next) mpd_cmd next ;;
	audio_prev) mpd_cmd prev ;;
	audio_info) disconnect python3 ~/bin/dmenu-mpd.py -i ;;

	#vol_up) pactl set-sink-volume "@DEFAULT_SINK@" "+5%" ;;
	#vol_down) pactl set-sink-volume "@DEFAULT_SINK@" "-5%" ;;
	#vol_mute) pactl set-sink-mute "@DEFAULT_SINK@" "toggle" ;;
	vol_up)   amixer --quiet set Master "2%+"; status ;;
	vol_down) amixer --quiet set Master "2%-"; status ;;
	vol_mute) amixer --quiet set Master "toggle"; status ;;

	status-mpd) status_mpd ;;
	status-vol) status_vol ;;
	status-net) status_net ;;
	status-date) calendar ;;

	quit) quit_dwm ;;
esac
