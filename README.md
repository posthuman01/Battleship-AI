Battleship-AI
=============

IRC based Battleship game to encourage programming basic AI clients.

Authors: CaptSullivan, debus

Contributors:


Get Started:
------------

Clone (optional fork) repo to your local machine. Next, edit your Interface/config.cfg file to include settings for your bot.

You may override any of the default settings you want by placing them in the OVERRIDES section of the config file, an example config is:

```
[DEFAULT]
host=irc.freenode.net
port=6667
nick=SEX_ROBOT
channel=#battleship_testing

[OVERRIDES]
nick=your_nickname
channel=#alternat_channel
```

 Then compile the AI and execute interface.py as:

```
./interface.py ./ai
```

An example makefile is included so by running 'make' you will compile the Sample C++ ai.



Contact Us:
-----------

Submit issues here or attempt to contact us in #battleship or #battleship_testing on freenode.net
