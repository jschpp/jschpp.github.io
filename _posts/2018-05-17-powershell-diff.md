---
layout: post
title: "Powershell Diff"
date: "2018-05-17 17:36:00 +0200"
---
Comparing Objects can be done by using `Compare-Object` in Powershell. Problem arise when you start comparing text files.

The `Compare-Object` Cmdlet in Powershell works wonderfully when comparing simple Powershell Objects.

```powershell
λ  Compare-Object $a $b -IncludeEqual

InputObject                                                                           SideIndicator
-----------                                                                           -------------
CN=inherittest2,OU=SubOU1,OU=User1,OU=InheritTest,OU=Testumgebung,,DC=test,DC=invalid =>
CN=inherittest1,OU=User1,OU=InheritTest,OU=Testumgebung,DC=test,DC=invalid            <=
```

The problem with this appears when comparing text files:

```powershell
λ  Compare-Object $(gc a.txt) $(gc b.txt) -IncludeEqual

InputObject SideIndicator
----------- -------------
a           ==
b           ==
d           ==
x           =>
c           <=
```

This tells me there is a difference but not where.

Searching the mighty internet brought me [this][mightyinternet]:

>Special-purpose file comparison tools have lots of tricks to compare files efficiently and logically, but PowerShell does let you implement a basic file comparison through a special trick – realizing that the Get-Content cmdlet tags its output objects with the line number they came from.

Which helps immensely. So I wrote a quick and dirty side-by-comparison for files:

{% gist jschpp/004e40d1821b3de15f09016aaee0e2d6 file-diff-ps1 %}

With this the above comparison looks like this:

```powershell
λ  C:\Users\jschpp\Desktop\diff.ps1 a.txt b.txt

Line Left Right
---- ---- -----
3    c    x
```


[mightyinternet]: http://www.leeholmes.com/blog/2013/11/29/using-powershell-to-compare-diff-files/
