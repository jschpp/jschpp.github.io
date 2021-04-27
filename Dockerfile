FROM ruby:2

RUN gem install bundler
RUN mkdir -p /root/jschpp
WORKDIR /root/jschpp/
COPY Gemfile* .

ENV BUNDLE_GEMFILE=/root/jschpp/Gemfile \
    BUNDLE_JOBS=2 \
    BUNDLE_PATH=/bundle

RUN bundle install --with jekyll_plugins

COPY * .

RUN bundle exec jekyll serve -D -P 8080 -w

EXPOSE 8080