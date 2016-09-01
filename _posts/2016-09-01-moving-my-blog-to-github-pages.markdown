---
layout: post
title: "Moving my Blog to github pages"
date: "2016-09-01 13:22:37 +0200"
---

At the moment I don't have time to administrate a root server even if it's just a VM.
So after canceling my server lease I decided to move my server to [github-pages][1].

Since I was already using [jekyll][2] it wasn't much of a chore. I just pushed my
already existing git repository in the new [jschpp.github.io][3] repo.

Then the only thing to do was telling github to use a custom domain and I was done.

The only negative at the moment is that github doesn't support ssl for custom domains
without wrapping [cloudflare][4] around it. Ah well maybe this will be fixed sometime soon
or I may just set up a new root server.

[1]: https://pages.github.com/
[2]: {{site.jekyll_url}}
[3]: {{ site.github.repository_url }}
[4]: https://konklone.com/post/github-pages-now-sorta-supports-https-so-use-it
