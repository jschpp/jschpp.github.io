---
layout: post
title:  "Firewall settings for cloudflare"
author: jschpp
date: 2015-12-05 21:38:00 +0100
---
Since I am using cloudflare nobody exept them should access my server at port 80 or 443.

So I removed all rules granting access at those ports <del>and added the following script in my `crontab` file:</del>

Somehow putting it in crontab seems not to work right (I think the network is not yet up when the script is run).
So I created a systemd script to start this script...

{% gist jschpp/d882e83f6fa3d8201ce3 %}
