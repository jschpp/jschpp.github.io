---
layout: post
title:  "Github mirror"
author: jschpp
date:   2016-02-12 00:09:00 +0100
sitemap:
  changefreq: 'never'
tags:
  - git
---
Since I didn't want to loose the data for this site in case of spontaneous breakage I added a Github mirror.

For this to work a found a post at [stackowerflow][stackowerflow] which reccommend doing the following
{% highlight shell %}
cd /path/to/blog.git
git remote add --mirror=push github git@github.com:user/repo.git # the =push part is new
{% endhighlight %}
and then adding a `git push --quiet github` to my `blog.git/hooks/post-receive` hook


[stackowerflow]: http://stackoverflow.com/q/11370239/343867
