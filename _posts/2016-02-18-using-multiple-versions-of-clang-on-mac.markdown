---
layout: post
title: "Using multiple versions of clang on Mac"
date: "2016-02-18 22:09:02 +0100"
---

After trying for what feels like the 100th time I finally found out how to switch from the default Mac `clang` v3.4 to the Mac Ports version 3.6

It's really simple:

{% highlight shell %}
sudo port install clang_select
sudo port select --set clang mp-clang-3.6
{% endhighlight %}

The above obviously only works if `clang-3.6` was previous installed.
