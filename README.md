Sudabot
=======

Sudabot is an ircbot for Windows and Linux written in c++

Building
========

Linux

Build the executable by using the Makefile
```
$cd Sudabot/Sudabot
$make
```

Windows

Requires Visual c++ Redistribution 2012 x86

Build using Visual Studio or Visual c++ express

Configuring
=======

Edit sudabot.conf located in the executable directory.

example config: sudabot.conf
```
// Sudabot example config sudabot.conf

  server=irc.example.com                //server address
  port=6667                            //server port
  channel=#channelname                //this is the default channel the bot will join 
  nicks=sudabot                      //nick the bot will use
  use_passwd=true                   //irc server uses registration and the bot will attempt to identify itself to the nickserv
  passwd=password                   //password to be sent to NickServ
  alias=suda                        //!<alias> is used to acknowledge the bot 
                                    //PMing the bot will also work
  owner=ty                    //Your nick, this allows admin commands
  
  Welcome_msg="Welcome $user to $channel"  //Welcome message sent when user joins channel
  Welcome_enabled=true                     //enable/disable welcome message
  
```


Commands
=========


```
    !<alias> help 

```

Bot Admins
========

Bot Admins are given operator privileges when they join the channel, if the bot itself is a channel operator. This also allows the user access to bot admin commands.

adding bot admins
```
  !<alias> addadmin <nick>
```
removing bot admins
```
 !<alias> removeadmin <nick>
```





