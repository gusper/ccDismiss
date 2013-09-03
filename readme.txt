This is code I wrote back in 2008. Highly doubtful it'll be of use to anyone anymore (i.e., if it is, I hope it's not because they're still using a Motorola Q nowadays). Below is the description I used on my blog back when I last released an update of it in August 2008.

---

If you have a Motorola Q (I’ve seen it on the original Q as well as the newer Q9m by Verizon), then you’ve probably seen that dialog that comes up when your battery has been fully charged. It’s title is “Main Battery” and all it tells you is “Charge Complete.” If you’re not a fan of that dialog, then you might find it useful to have this little (30k executable) tool running on your phone as its only job is closing out that useless (in my opinion) window five seconds after it has appeared. It will relieve you of having to hit extra buttons after a full charge just to see your home screen. This is especially for you if your phone locks automatically. The scenario that made me grumpy enough to spend the couple hours it took to create this (testing is taking much longer) starts with me charging my phone next to my bed when I go to sleep. When I wake up, I like to take a quick glance at my phone to see the stuff I have on my home screen. Instead, I’d see the “Charge Complete” dialog which I wasn’t able to dismiss until I unlocked the phone which requires another extra five key presses in my case plus another to dismiss the dialog. With ccDismiss now, I hit any key and my home screen will appear. If I want to interact with it, then I have to unlock it of course but I’m now not forced to unlock it if I just wanted to take a quick look.

HOW DOES IT WORK?
For it to do its thing, you must have it running at all times so I’ve just gone ahead and copied the executable to my phones StartUp folder (\Windows\StartUp) so it automatically runs whenever I restart my phone. Instead of just polling non-stop to see if the much-loved window is up, it registers itself to get notified whenever there’s a change of battery state. Once it receives notification of such a change, it waits five seconds and starts looking to see if the dialog has appeared. If it finds it, it immediately closes it out.

WHAT DEVICES DOES IT WORK ON?
I’ve only tested it on a Motorola Q9m. I’m fairly certain it’ll run on an original Motorola Q as well as it’s developed against the Windows Mobile 5 SDK so it should be fully backwards compatible. Also, I don’t know if other Verizon phones (I’ve had a Motorola Q9h from AT&T and it didn’t have this wonderful dialog) also have this great feature but if you have one that does, you might want to give it a try. If anyone tries it with any phone other than the Motorola Q9m, I’d appreciate it if you let me know so I can keep track of which phones it works on and which it doesn’t. Just shoot me a mail at gus <over at> gusperez <dot> com.

SYSTEM REQUIREMENTS:
Windows Mobile 5 or 6 – Smartphone Edition (not sure if it would just work on a “Professional” edition but might be worth a try if you have one). This is a native Win32 (for WM5) C++ application so it really shouldn’t require much else.

INSTALLATION INSTRUCTIONS: 
Unzip the ccDismiss.zip file. Copy the ccdismiss.exe file to your phone using ActiveSync or the Windows Mobile Device Center on Vista. You likely want it to run automatically all the time so copy it to your \Windows\StartUp folder. The first time the program gets run on your device, you’ll get a security warning. You shouldn’t see it again any subsequent times though.

QUALITY STATE:
I’ve been running it for months as have plenty of other folks at this point and I haven’t had any reports of problems so far. Seems pretty stable so far.
