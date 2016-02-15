---
layout: post
title: "Strange OAB problems"
date: "2016-02-15 16:52:24 +0100"
---
We recently had some strange problems with the Outlook Offline Address Book (OAB)

# Scenario
My company has two domains management.contoso.com and name.contoso.com. Both of those are fully functional separated Active directories with an Exchange infrastructure.

My User has this setting:
| username  | domain     | exchange active |
|-----------|------------|-----------------|
| user      | management | yes             |
| user_name | name       | yes             |

But only the user_name@name.contoso.com is set up in Outlook. The user@management.contoso.com mailbox exists due to historical reasons.

# Problem
After sending an email to user2@management.contoso.com the following happens:
```text
Diagnostic information for administrators:

Generating server: exchange.name.contoso.com
IMCEAEX-_O=FIRST_ADMINISTRATIVE_GROUP_OF_MANAGEMENT_CONTOSO_COM=Recipients_cn=user2@name.contoso.com
#550 5.1.1 RESOLVER.ADR.ExRecipNotFound; not found ##
```
Where `user2` is the internal username of user2 in management.contoso.com...

Well thats a problem. Apparently Outlook looks up user2 in the management.contoso.com even if the management.contoso.com account isn't set up in Outlook. It seems enough that the Exchange account exists in the first place.

After trying some stuff we narrowed it down to the OAB

# Solution...ish
This little script deactivates the automatic download of the OAB and deletes the local copies of it.
{% gist jschpp/68686a6b7bd604b56666 %}

The Problem with this is that you can still manually download it.
