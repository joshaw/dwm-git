#!/bin/sh
set -eu

SEP='·'

MPD_STATUS="$(mpc status 2> /dev/null | awk '
	NR==1 { song_name = $0 }
	NR==2 {
		status = ""
		if ($1 == "[playing]") {
			status = "▶"
		} else if ($1 == "[paused]") {
			status = "∥"
		}

		printf("%s   %s  %s  %s", status, song_name, $4, $2)
	}
')"

VOLUME="$(amixer -M sget Master | awk '
	/%]/ {
		match($0, /\[([0-9]+%)\]/, a)
		if ($NF == "[off]")
			print("mute")
		else
			print(a[1])
		exit
	}')"

NETDEVS="$(networkctl list --json=pretty |
	jq --raw-output '[.Interfaces[] | select(.Name != "lo") | .Name] | join("/")'
)"

DATE="$(date "+%a %d %b %I:%M")"

STATUS="$(printf '   \x04%s   |\x03   %s   |\x02   %s   |\x01   %s' \
	"$MPD_STATUS" "$VOLUME" "$NETDEVS" "$DATE")"
STATUS="${STATUS//|/$SEP}"

xsetroot -name "$STATUS"
