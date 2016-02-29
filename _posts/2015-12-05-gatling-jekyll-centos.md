---
layout: post
title:  "Setting up this Blog Part 1"
author: jschpp
date: 2015-12-05 22:17:00 +0100
---
How to set up a blog with gatling, Jekyll and CentOS Part 1.

* * *

Table of contents:

* This list will contain the toc (it doesn't matter what you write here)
{:toc}

* * *

# Intro
I wanted to try blogging again. So I checked for software I could use. I absolutely hate Wordpress and Co because it's simply to much stuff for just posting a random article or two. While searching for a simple blogging software I looked at one of my favorite blogs namely [fefes blog][fefe]. He is using a <del>non disclosed</del> C program to format his Blog and then publishes it with his own brand of web server. **EDIT:** Source Code for fefes blog can be found [here][fefesource].

In my search for a *simple* blog software I found [Jekyll][jekyll]. I liked it because it generates static files which can be hosted by about anything and is highly customizable without messing around with this dreadful php stuff.

So all I needed now was a web server. I didn't want apache because apache is bloated. I tried configuring nginx and broke it twice I think. After contemplating just hacking my own in GO I looked again to fefe and found that while his blog software is not published his web servers are. He has written two different web servers [gatling][gatling] and [fnord][fnord]. While the latter is no longer developed further the former is. So I decided on gatling.

Everything further presumes you have the normal building tools installed.

Installing gatling proved more difficult then I envisioned. Yes one can run `make && make install` but somehow just running it naively produces error messages. Well thank god I sometimes listen when everything screams **RTFM** at me. So... RTFM? let's have a look if there is a readme file:
{% highlight shell %}
[root@localhost gatling-0.13]# ll README*
-rw-r--r--. 1 1000 users  265  7. Okt 2003  README
-rw-r--r--. 1 1000 users  899  8. Apr 2008  README.antidos
-rw-r--r--. 1 1000 users  581 10. Okt 2003  README.bindbench
-rw-r--r--. 1 1000 users  699  2. Jun 2009  README.cgi
-rw-r--r--. 1 1000 users  406  9. Okt 2003  README.forkbench
-rw-r--r--. 1 1000 users 2773  2. Jun 2009  README.ftp
-rw-r--r--. 1 1000 users  605 31. Okt 2005  README.htaccess
-rw-r--r--. 1 1000 users 1007  2. Jun 2009  README.http
-rw-r--r--. 1 1000 users 2308  2. Jun 2009  README.httpbench
-rw-r--r--. 1 1000 users 1243 23. Okt 2003  README.manymapbench
-rw-r--r--. 1 1000 users 1152 11. Nov 2003  README.mmapbench
-rw-r--r--. 1 1000 users 1470 14. Jan 2004  README.performance
-rw-r--r--. 1 1000 users 1176  9. Jan 2010  README.php
-rw-r--r--. 1 1000 users  949 19. Aug 2011  README.polarssl
-rw-r--r--. 1 1000 users 2226  7. Jan 2004  README.prefetch
-rw-r--r--. 1 1000 users 1315  9. Jan 2010  README.proxy
-rw-r--r--. 1 1000 users  912 17. Mai 2005  README.redirect
-rw-r--r--. 1 1000 users 1724 23. Mär 2010  README.tls
{% endhighlight %}
Well then... README tells me I need `libowfat`. Let's install that first:

Going to [fefe's libowfat page][fat] tells me I also should use `diet libc`...

# diet libc

Get it from [here][diet] either using cvs or download the `tar` ball.  
After extracting it `cd` to the directory and `make`. Many Many lines of `gcc` output later it's finished.
The README tells me I need to run `install bin-x86_64/diet /usr/local/bin` to use it.
`make install` yields some errors which I ignore. Maybe everything works allright.  
That was all that was necessary to install diet libc.

# libowfat
Get it from [here][fat] again either using cvs or download the `tar` ball.  
Here a simple `make && make install` does the trick.

# gatling
Finally I can install `gatling`
{% highlight shell %}
[root@localhost gatling-0.13]# make
[...]
ssl.c:9:25: schwerwiegender Fehler: openssl/ssl.h: Datei oder Verzeichnis nicht gefunden
 #include <openssl/ssl.h>
                         ^
Kompilierung beendet.
make: *** [ssl.o] Fehler 1
{% endhighlight %}
Hmm this is not working therefore: `yum install openssl openssl-devel openssl-static`. Again:
{% highlight shell %}
[root@localhost gatling-0.13]# make
pssl.c:9:29: schwerwiegender Fehler: polarssl/havege.h: Datei oder Verzeichnis nicht gefunden
 #include <polarssl/havege.h>
                             ^
Kompilierung beendet.
make: *** [pssl.o] Fehler 1
{% endhighlight %}
Ok. Dammn it all to hell I don't need ssl support. I use cloudflare which does my ssl for me. Futhermore nobody except cloudflare can access my web server. Have a look [here][cloudflare] for my firewall script which ensures this.

Finally I have a gatling binary. Yay^^

A quick `cp gatling /usr/bin/` later I can run my server by calling `gatling`.

# CentOS (systemd)
Now that I have my gatling binary I need to run it at startup. I could add a line in my cron file but I wanted to make it right...ish. CentOS uses systemd and [fefe's strong dislike][dislike] (warning his blog is in german) notwithstanding I wanted to use it to start and stop my sever. After reading the man page for systemd I came up with the following:
{% gist jschpp/34fe6794e22d45e1c810%}
Yes it's not that nice and kinda hackish but it works.

# Interim Conclusion
At this point I have a running webserver which can be started by typing `systemctl start gatling`. Now all I have to do is set up a jekyll website and a git repository so I can modify said website from everywhere. Provided everywhere has a git client and a text editor.

This concludes part 1 have a look [here][part2] for part 2.


[dislike]: https://blog.fefe.de/?q=systemd
[gatling]: https://www.fefe.de/gatling/
[fefe]: https://blog.fefe.de/
[jekyll]: {{site.jekyll_url}}
[fnord]: https://www.fefe.de/fnord/
[fat]: https://www.fefe.de/libowfat/
[diet]: https://www.fefe.de/dietlibc/
[cloudflare]: {% post_url 2015-12-05-cloudflare-firewall %}
[part2]: {{site.baseurl}}/nyp
[fefesource]: https://erdgeist.org/cvsweb/Fefe/blog/
