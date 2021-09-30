---
layout: post
title: "Setting up an IP retrieval service"
date: 2021-09-30 15:13
author: Johannes Schöpp
tags: ["linux", "nginx"]
summary: 
---

I sometimes need to retrieve the external IP address of a server and most of the
time I'll use an external service like `ident.me` to do this for me.

But since I'm not a big friend of using external stuff for a service I myself
can provide, today I sought a way to host such a service myself.

<!--more-->

## First idea: Setting up a small application to do the retrieval for me

My first idea was to write a small web app to do the IP retrieval for me.

Since I always wanted to use rust to do this. So I had a look around and found
[actix}(<https://actix.rs/>).

Actix is a web framework written in rust and can be used to write web
applications in rust.

After a bit of stumbling aroung I settled on the following app:

```rust
use actix_web::{web, HttpRequest, App, HttpServer, Responder};

async fn root(req: HttpRequest) -> impl Responder {
    let connection_info = req.connection_info();
    let info = connection_info.realip_remote_addr().unwrap_or("");
    info.to_string()
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .route("/", web::get().to(root))
    })
    .bind(("127.0.0.1", 8080))?
    .run()
    .await
}
```

The above code is the example code from the actix website which was minimally
modified to return `realip_remote_addr` instead of `Hello world`

I tried it and it did pretty much what I wanted it to do.

```bash
curl http://127.0.0.1:8080
127.0.0.1:52530
```

### Setting up nginx

Soo now I have an app which will tell me the IP of the caller. All I need to do
now is setting up nginx to handle the external connections and maybe do ssl.

```nginx
server {
    listen 80;
    name id.testserver.tld;

    location / {
        proxy_pass http://127.0.0.1:8080;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    }
}
```

Note: I could've used `$remote_addr` instead of `$proxy_add_x_forwarded_for` but
since nginx autofills `$proxy_add_x_forwarded_for` with `$remote_addr` when the
proxy address is not set `$proxy_add_x_forwarded_for` contained the information
I needed plus extra information should I need it 😄

The above worked splendid and so I thought myself done 👍

But wait... can't I just use nginx to do the return?

## Second idea: Handle everything in nginx

Sooo... nginx can return values with a status code if you tell it to. And since
the only thing I did in my first idea was getting the info from nginx and
parsing it in rust which then returned the parsed info back to nginx I could
just use nginx for everything.

```nginx
server {
    listen 80;
    name id.testserver.tld;

    location / {
        default_type text/plain;
        return 200 $proxy_add_x_forwarded_for;
    }
}
```

That worked. So I didn't need the rust middleman at all. Nice xD

The final config looked like this:

```nginx
server {
    listen 80;
    name id4.testserver.tld;

    location / {
        default_type application/json;
        return 200 '{"ip":"$proxy_add_x_forwarded_for"}';
    }
}

server {
    listen [::]:80 ipv6only=on;
    name id6.testserver.tld;

    location / {
        default_type application/json;
        return 200 '{"ip":"$proxy_add_x_forwarded_for"}';        
    }
}
```

As you can see I opted for a JSON object as return value since that made parsing
on the client side more comfortable when using powershell.

As you can also see I set up to servers. One for IPv4 and one for IPv6 which
will help when calling the API since I can specify which external address I
want.

Now I only needed to setup letsencrypt and I was done.
