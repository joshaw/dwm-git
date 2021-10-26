#!/bin/sh
set -eu

MPD="$(mpc status 2> /dev/null | awk '
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

NETDEVS="$(networkctl list --json=short |
	jq --raw-output '
		[.Interfaces[] | select(.OperationalState == "routable") | .Name] |
			join("/")
	'
)"

CHIP="coretemp-isa-0000"
TEMP="$(sensors -j "$CHIP" |
	jq --raw-output --arg chip "$CHIP" '.[$chip]["Package id 0"].temp1_input')°C"

read -r min1 min5 min15 _ < /proc/loadavg
LOAD="$(printf '%s/%s/%s' "$min1" "$min5" "$min15")"

DATE="$(date '+%a %d %b %I:%M')"

S="$(printf '\6   %s   ·\5   %s   ·\4   %s   ·\3   %s   ·\2   %s   ·\1   %s' \
            "$MPD"     "$VOLUME"  "$NETDEVS" "$TEMP"    "$LOAD"    "$DATE")"

exec xsetroot -name "$S"
