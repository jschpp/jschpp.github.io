---
layout: post
title:  "SSL and Proxy"
author: jschpp
date:   2016-01-18 17:26:00 +0100
sitemap:
  changefreq: 'never'
tags:
  - gatling
---
# tlsgatling
After thinking a bit about my server configuration I realized that using a reverse proxy kinda eliminates the pupose of using gatling in the first place -.-'

So I set out to install gatling with ssl enabled.

After searching for a bit I found [this message here][link]. The important part is this:

>This is how I did it:
>
>     ./config --prefix=/opt/diet no-dso 
>     make CC="diet -Os gcc -pipe -nostdinc"
>
>make install will then install to /opt/diet/lib, which is on my box a symlink to /opt/diet/lib-i386.

After another

    make install

I tried compiling `tlsgatling` again just to realize that I still hat the `openssl-devel` package installed. So after uninstalling that and symlinking 

    ln -s /opt/diet/lib/libcrypto.a /lib64/.
    ln -s /opt/diet/lib/libssl.a /lib64/.
	ln -s /opt/diet/include/openssl/ /usr/local/include/.

Compiling worked fine. Finally I have a working `tlsgatling`

**NOTE** I don't reccommend doing the above symlinks... I think that may break something &#12484;

Finally I moved tlsgatling to `/opt/diet/bin`

# certificate
For my certificate I used [letsencrypt][letsenc]. The HowTo tells me I need to do the following:

    ./letsencrypt-auto certonly --standalone -d jschpp.de -d www.jschpp.de

Which didn't work... I first needed to shutdown my webserver than I needed to disable my _special_ [firewall rules][firewall]. Or to be more specific I needed to add some rules to my firewall

    firewall-cmd --add-rule=http --zone=public
	firewall-cmd --add-rule=https --zone=public
    firewall-cmd --add-rule=http --permanent --zone=public
	firewall-cmd --add-rule=https --permanent --zone=public

(not sure if http is needed but I didn't care)

After running the `letsencrypt` command again I had my certificate. If I want to use it I need to concatenate the privkey.pem and cert.pem files

	cat /etc/letsencrypt/live/jschpp.de/privkey.pem /etc/letsencrypt/live/jschpp.de/cert.pem >server.pem
This file needs to be moved to `/var/www` and need to be change to world unreadable

	chmod o-r server.pem

I modified my `gatling.service` file to the following:
{% gist jschpp/48cfbc378ed09045397b %}

Now i can run

	systemctl daemon-reload && systemctl start gatling.service
and have a running ssl enabled webserver

[link]: http://news.gmane.org/find-root.php?message_id=20050225154211.GA12094%40codeblau.de
[letsenc]: https://letsencrypt.org/
[firewall]: https://www.jschpp.de/2015/12/05/cloudflare-firewall.html