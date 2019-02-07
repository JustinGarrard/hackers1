# Hackers Project 1: Prathm Juneja, Justin Garrard, Phil Baumann, and Conor Nailos
Hackers in the Bazaar: Project 1
This project is an attempt to bridge the gap between the fun, exciting nature of retro hacking with modern technology that people today enjoy.
We've built a way to turn a RaspberryPi into a bluetooth receiver. Inspired by kids who want to use bluetooth headphones (i.e. gamers, airpods lol). This way, they can have fun hacking together something that actually comes to use for them. After the project is complete, any regular pair of headphones can be plugged into the Pi, making it completely wireless.

This is a super over-engineered solution, that also now includes LED lights that flash to music, but it was a ton of fun to make and actually could teach people a lot about the command line and linux in general.

Here's a simplified set of instructions on how you do it:
1. Flash the Raspbian OS onto your Pi.
2. Once running, go to the top right corner of the GUI, right click the Bluetooth symbol, and disable it. This thing will ruin your progress if you don't.
3. Run: sudo apt-get-install pulseaudio-module-bluetooth
4. Run: sudo apt-get install python-gobject
5. Run: sudo apt-get install bluez-tools
5. Now, we get to the fun part. The first major step is to start messing with (read: disabling) a bunch of the Bluetooth settings. Go to /etc/Bluetooth/main.conf and everytime you see something that indicates a timeout, replace that number with a 0. 
6. In that same file, add a line that says "Enable = Source, Sink, Media". This line is now directing your Bluetooth to act as a source and sink for music and audio connections. This is important because Bluetooth can be used for other things, such as connecting peripherals.
7. In that same file, find the "Class = " line. Change it to "Class = 0x0041C". This new instruction tells the Bluetooth device that it is sending over audio.
8. Go ahead and kill the pulseaudio service that automatically started running. Otherwise this will screw everything up. To do this, do "pulseaudio -k"
9. So, this pulseaudio thing we've installed. This is the only fairly high level code used in this. Essentially, pulse audio is what lets us play sound through the aux port. Programming this with low level commands would be agonizing. Instead, we make a few changes to it so that it works better for our purposes. Edit the file at /etc/pulse/dameon by putting a ";" mark before the "resample-method = speex-float-3" line. 
10. Essentially, we don't want resampling techniques to ruin the sound coming in from the Bluetooth device. This would be fine if we were simply resampling music stored on the device, but the latency of Bluetooth can be a serious problem here. So, after you've commented out that line, add this one: resample-method = trivial.
11. We're almost there. Next, run this command, that sets the volume to 100% on the aux port: amixer set Master 100% 
12. Great. Everything is done. Except the Bluetooth part. In this Git page, there is a shell script titled "Project01Bluetooth.sh". All you need to do is add that shell script to the file located at /etc/rc.local ; By doing, you will automatically run that script when the Pi starts. You can do this by either copying and pasting all of the code in that shell script into your rc.local file, or you can simply just put "sh ~/Project01Bluetooth.sh" in it, and save the Project01Bluetooth.sh file to your home directory. Either works.
13. Here's a brief explanation of what that script does:
      - First, it does the samething that forces the volume back to 100% on the aux port.
      - Then, it does some very basic Bluetooth stuff, like turning the chip on and then making it discoverable.
      - Here's the catch: the low-level Bluetooth library is broken. It's supposed to have a feature that allows you to prevent a       password being necessary, which would make the Pi headless. Unfortunately, that feature doesn't work unless the Pi has already connected to that device once. This would deafeat the purpose of everything. You would have to hook up the Pi to a keyboard and a monitor in order to connect to a new device.
      - Instead, we call something called bt-agent with a flag of NoInputNoOutput. This is a depricated tool that, while incompatible with a lot of new Bluetooth features, still works with the old low-level stuff. This thing does allow us to require no I/O devices. Thank God.
      
 That's all! Thanks for reading this!
