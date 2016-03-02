---
layout: post
title: "Providing ssl cert chain with letsencrypt"
date: "2016-03-02 14:08:20 +0100"
---

I've written how to setup [letsencrypt][letsenc] with gatling in [a previous post][ssl-proxy]. I've made a mistake there I needed to correct.

The part in need of correcting is this one:

>After running the `letsencrypt` command again I had my certificate. If I want to use it I need to concatenate the privkey.pem and cert.pem files
>
>     cat /etc/letsencrypt/live/jschpp.de/privkey.pem /etc/letsencrypt/live/jschpp.de/cert.pem >server.pem
>

After testing my servers SSL connection I stumbled upon a problem. My certificate chain was not fully sent.
That's not that big of a problem since most modern browsers just load the chain from I don't know where. But I wanted to change that.

I found this [mail][mail] which detailed pretty much the same problem.

First instead of just using the `privkey.pem` and `cert.pem` to generate the `server.pem` the following is done:

```
cat privkey.pem cert.pem chain.pem > server.pem
```

After that the new pem file can be copied and chmodded as described in [the previous post][ssl-proxy].

Second: I don't know why but `tlsgatling` searches for a file named "www.example.net.pem" or in my case "www.jschpp.de.pem". As stated in the mail a simple symlink solves that problem

```
ln -s server.pem www.jschpp.de.pem
```

Now my cert chain is complete and [ssllabs][ssllabs] gives me an "A" rating ^^

[letsenc]: https://letsencrypt.org/
[ssl-proxy]: https://www.jschpp.de/2016/01/18/ssl-and-proxy.html
[mail]: http://permalink.gmane.org/gmane.comp.web.gatling/302
[ssllabs]: https://www.ssllabs.com/ssltest/analyze.html?d=jschpp.de
