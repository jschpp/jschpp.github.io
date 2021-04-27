---
layout: post
title: Building a C# PowerShell Module 1
date: 2020-07-19 13:59
author: Johannes Schöpp
tags: [powershell, c#, learningbydoing]
summary: In this series I will talk about how I started building binary
PowerShell modules
---
For my work I needed a way to parse the debug log files of our DNS Server.

A quick search revealed a [module by virot][1] which can do that.
So I've tried it and it worked - kind of...

The problem here was that I needed to parse a __big__ log file. And as comfortable
as using virots module was it simply wasn't fast enough. It used around 4 Gigs
of RAM and hogged all the CPU it could get.

My solution for that problem was simply porting his code to C#.

## Porting PowerShell to C&#35;

First I needed to create a new C# Module. Using Microsoft's Visual Studio makes
that a pretty easy task. Simply create a new Class Library targeting NetStandard.
I named my new Module `DNSDebugLogHandler`

You want to target Net Standard if your module should work in PowerShell version 5
as well as 7. If you don't care about your module running in PowerShell version 5
you can target Net Core. For an overview which .Net version is supported by
PowerShell 7 have a look at the [PowerShell Changelog][2]

In this series I need to have PowerShell 5 support so I will only add remarks how
to handle PowerShell 7 only modules and won't go deeper on this topic.

### Creating a CmdLet

A PowerShell CmdLet is a class inheriting from either `System.Management.Automation.Cmdlet`
of `System.Management.Automation.PSCmdlet`. To use those superclasses I needed to
first add [`PowerShellStandard.Library`][3] to my project. If I wanted to create
a version 7 only module I would need `System.Management.Automation` instead.

I added the `PowerShellStandard.Library` by right clicking on Dependencies in my
new DNSDebugLogHandler project and selecting <TODO: add correct>. After that I
used the search to add the `PowerShellStandard.Library`.

I can now use the `System.Management.Automation` namespace. First I need to add
it to my `DnsDebugLogHandler.cs` file with `using System.Management.Automation;`
after that my DnsDebugLogHandler class can inherit.

[1]: https://github.com/virot/DNSLogModule
[2]: https://github.com/PowerShell/PowerShell/blob/master/CHANGELOG/7.0.md
[3]: https://github.com/PowerShell/PowerShellStandard
