---
layout: post
title:  "Reverse Proxy with Go"
author: jschpp
date:   2015-12-09 14:56:00 +0100
categories: announcements
sitemap:
  changefreq: 'never'
tags:
  - golang
  - go
  - programming
  - server
---

My server is up and running. Just one small problem.

gatling doesn't use the x-forwarded-for header. Meaning my logs are all like this:

	Dec  7 05:46:20 olymp gatling[595]: accept 6 162.158.88.123 28934 1 http
	Dec  7 05:46:21 olymp gatling[595]: accept 7 162.158.89.150 54272 2 http
	Dec  7 05:46:21 olymp gatling[595]: accept 8 162.158.89.124 36349 3 http
	Dec  7 05:47:09 olymp gatling[595]: accept 6 162.158.88.123 63005 1 http
	Dec  7 08:02:30 olymp gatling[595]: accept 6 162.158.88.123 34684 1 http
	Dec  7 08:02:30 olymp gatling[595]: accept 7 162.158.89.150 41954 2 http
	Dec  7 08:02:32 olymp gatling[595]: accept 8 162.158.88.123 40501 3 http
	Dec  7 08:05:11 olymp gatling[595]: accept 6 162.158.88.123 27187 1 http
	Dec  7 08:05:15 olymp gatling[595]: accept 7 162.158.88.123 34394 2 http
	Dec  7 08:05:18 olymp gatling[595]: accept 8 162.158.88.123 14323 3 http
	Dec  7 08:05:57 olymp gatling[595]: accept 6 162.158.88.123 32043 2 http
	Dec  7 08:06:35 olymp gatling[595]: accept 6 162.158.88.123 17267 2 http
	Dec  7 08:06:48 olymp gatling[595]: accept 7 162.158.88.123 20461 3 http
	Dec  7 09:28:25 olymp gatling[595]: accept 6 162.158.88.123 62468 1 http
	Dec  7 09:33:29 olymp gatling[595]: accept 6 162.158.88.123 59867 1 http
	Dec  7 09:33:33 olymp gatling[595]: accept 7 162.158.88.123 26975 2 http
	Dec  7 09:39:11 olymp gatling[595]: accept 6 162.158.88.123 53588 1 http
	Dec  7 09:39:12 olymp gatling[595]: accept 6 162.158.88.123 52731 1 http
	Dec  7 10:33:48 olymp gatling[595]: accept 6 162.158.88.123 22197 1 http
	Dec  7 10:33:48 olymp gatling[595]: accept 7 162.158.89.150 15470 2 http
	Dec  7 11:57:11 olymp gatling[595]: accept 6 162.158.89.152 34205 1 http


As one can see there is an awful lot of traffic from cloudflare but nothing else.

# Solution:

This small gist:
{% gist jschpp/bba4bba9f71651ed0071 %}

Running gatling in link-lokal mode on port 81 and this small go tool enables me to log the right ip address.