# Notification-Station
ESP8266, 32x8 Matrix display for clock and notifications

### Stage one - (Time digital)
1. [x] ~~HTML page to display time~~
2. [ ]	Read time from server
3. [ ]	Display time on display (digitally)

### Stage two - (Scrolling String)
1. [ ]	HTML update, to allow string/message entry.
2. [ ]	Write method to decipher %coding.
3. [ ]	Display string/message on display.

### Stage three - (Config file, back end)
1. [ ]	HTML update, to include settings
2. [ ]	Store and retrieve config setting from SPIFFS (JSON??)
3. [ ]	Allow more than one wifi setting to be stored and searched through.

### Stage four - (Fancy up time)
1. [ ]	HTML update, to choose time display method.
2. [ ]	Add time display choice to config file.
3. [ ]	Write scrolling written time function
4. [ ]	Make digital display number change animation. Would like to see the changing digit roll down off the display as the new digit rolls in from the top.
5. [ ]	New Year’s Eve count down timer, 10-1 followed by “Happy new year”.

### Stage five - (Alarm)
1. [ ]	HTML update, for alarm time/repeat.
2. [ ]	Thing that goes beep, to alert new notification
3. [ ]	Means to INPUT i.e.; Initiate snooze or cancel alarm, low target = 2x button, high target = time of flight sensor, hand far away for snooze, hand close for cancel.
4. [ ]	Display alarm

### Stage Six - (Notifications) displays instantly
1. [ ]	HTML update, for what to do on receiving notifications, beep once…. (need to think)
2. [ ]	Display notification.

### Stage Six - (Messages) needs input to displays
1. [ ]	HTML update, for what to do on receiving message, beep once…. (need to think)
2. [ ]	Display “message from” [sender] with the option to read() or cancel() using INPUTs