#!/bin/sh
set -eu

SEP='  ·  '

VOLUME="$(amixer -M sget Master | awk '{ match($0, /\[([0-9]+%)\]/, a) } END { print(a[1]) }')"

MPD_STATUS="$(mpc status 2> /dev/null | awk '
	NR==1 { song_name = $0 }
	NR==2 {
		status = ""
		if ($1 == "[playing]") {
			status = "▶"
		} else if ($1 == "[paused]") {
			status = "∥"
		}

		printf("   %s   %s  %s  %s", status, song_name, $4, $2)
	}
')"

STATUS="$MPD_STATUS $SEP $VOLUME $SEP $(date "+%a %d %b %I:%M") "

xsetroot -name "$STATUS"
