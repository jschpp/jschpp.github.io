---
layout: post
title: "Adding Disqus to my blog"
date: "2016-02-29 16:57:00 +0100"
---

Since I use [jekyll][jekyll] to generate this blog I don't have a simple comment function.

So I decided on using [Disqus][disqus] for comments. Integrating it is quite simple:

# 1. Set up Disqus
Follow [this FAQ article][faq1].
Then use the "Universal Code" and embed it into your pages layout

# 2. Embed Disqus
In my case I wanted Disqus at the bottom of every post I wrote. So I modified my post.html:

{% gist jschpp/0b268cab449bab19dd26 %}

Of course `>>DISQUSSHORTNAME<<` was modified to the shortname of this blog.

[This FAQ][faq2] recommended adding `comments true` to the YAML Front Matter of post.html

That didn't work in my case. Instead I added

```yaml
defaults:
  -
    scope:
      path: ""
      type: "posts"
    values:
      comments: true
```
to my \_config.yaml

That's it.

[faq1]: https://help.disqus.com/customer/en/portal/articles/466182-publisher-quick-start-guide
[faq2]: https://help.disqus.com/customer/portal/articles/472138-jekyll-installation-instructions
[jekyll]: {{site.jekyll_url}}
