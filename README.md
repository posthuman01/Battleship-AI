Battleship-AI
=============

IRC based Battleship game to encourage programming basic AI clients.

Authors: CaptSullivan, debus

Contributors:


Get Started:
------------

Download interface.py, procIO.py, the irc folder, the config_manage folder, and a sample AI. Then copy the contents of example_config.cfg to ~/.battleshipAI. Override any of the default settings you want by placin them in the OVERRIDES section, an example config is:
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



Contact Us:
-----------

Submit issues here or attempt to contact us in #battleship or #battleship_testing on freenode.net
