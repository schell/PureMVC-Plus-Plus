#! /bin/bash
osascript -e '
	tell application "System Events"
		if exists process "Terminal" then
		else
			tell application "Terminal" to run
		end if	
		try
			tell application "Terminal" to close front window
		end try
		tell application "Terminal" to do script with command "cd /Users/schell/Code/PureMVC-Plus-Plus/example/opengl/; ./opengl"
		set frontmost of process "Terminal" to true
	end tell'