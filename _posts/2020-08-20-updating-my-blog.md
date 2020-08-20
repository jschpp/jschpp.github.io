---
layout: post
title: Updating my blog
date: "2020-08-20 21:25:00 +0200"
author: jschpp
---
Well it's finally that time of the decade again where I touch my blog xD

Since I converted to using jekyll in 2015 I more or less used the same configuration without changing much behind the scenes.

It is now 2020 and I couldn't simply run `jekyll serve` on my blog anymore without jekyll telling me that my config is not correct and I should update it.

## Updating jekyll

Since jekyll now depends on bundler and dependencies aren't handled via the `_config.yml` file anymore I needed to add all needed file to my repository.

I solved that by running `jekyll new . --force` in the root of my blog folder. (Disclaimer: You may want to switch branches beforehand to test everything in peace^^)

After that I deleted the following new default files

```
index.markdown
about.markdown
```

I then renamed the newly created `_config.yml` file and restored my old `_config.yml` via `git checkout HEAD -- _config.yml`

The mayor difference between the old (I can't remember which version was current in 2015) and the new jekyll version is the usage of a `Gemfile`

In the olden days gems would be added in jekyll using the `gem` section in the `_config.yml` this looked like this:

```yaml
gems:
  - jekyll-gist
  - jekyll-paginate
  - jekyll-mentions
```

The newer Version looks like this:

```yaml
plugins:
  - jekyll-gist
  - jekyll-paginate
  - jekyll-mentions
```

as you can see the simply replacing `gems` with `plugins` is all you need to do here.

Next I needed to modify my `Gemfile`

My `Gemfile` at time of writing looks like this:

```ruby
source "https://rubygems.org"

gem "minima", "~> 2.5"

gem "github-pages", group: :jekyll_plugins
group :jekyll_plugins do
  gem "jekyll-feed"
  gem "jekyll-gist"
  gem "jekyll-paginate"
  gem "jekyll-mentions"
end

# Windows and JRuby does not include zoneinfo files, so bundle the tzinfo-data gem
# and associated library.
platforms :mingw, :x64_mingw, :mswin, :jruby do
  gem "tzinfo", "~> 1.2"
  gem "tzinfo-data"
end

# Performance-booster for watching directories on Windows
gem "wdm", "~> 0.1.1", :platforms => [:mingw, :x64_mingw, :mswin]
```

I added all my jekyll plugins and told it to use the `github-pages` gem instead of the plain `jekyll` gem.

## Other Changes

### Handling Comments

First off I desperately need to get rid of disqus... I didn't like how "bloated" it was and I wasn't a big fan of using it anyway.

I instead wanted to use utterances.

#### utteranc.es

In 2019 I stumbled over [utterances][utter] while reading the blog of the wonderful @mczerniawski.
I quite liked the minimalist theme and possibility of using github to host my comments since I was already using github pages to host everything else.

The config of utterances is quite simple. You only visit https://utteranc.es/ answer the questions given to you in the form and copy the source code snippet to the bottom of your post layout html file.

Then you all you need to do is add the utterances app to your github repo as described on the page.

You can find my post layout [here][postlayout]

### Pagination

Somehow my pagination broke. I don't know why but I "solved" it by copying the pagination example code from the jekyll website.

## Final words

All changes can be found [here][changes]


[utter]: https://utteranc.es/
[postlayout]: https://github.com/jschpp/jschpp.github.io/blob/21d9d641023da288b317057f9f0daae28df4f642/_layouts/post.html
[changes]: https://github.com/jschpp/jschpp.github.io/commit/21d9d641023da288b317057f9f0daae28df4f642
