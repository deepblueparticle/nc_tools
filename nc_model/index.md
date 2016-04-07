---
layout: page
title: nc_model - GCode to model
permalink: /nc_model/
---

Create a 3d model representing the GCode toolpath removed from a stock model.

```
$ nc_model --help
nc_model:
  -h [ --help ]         display this help and exit
  --stock arg           Stock model file
  --tool arg            Default tool
```


Given a GCode program as standard input:

```
$ cat profile.ngc 
g0 z1
   x-2 y-2

g1 z-5 f50
   x0  y0
   x10 y0
   x10 y10
   x0  y10
   x0  y0
```

And an .off model of the stock (here generated by the [nc_stock]({{ site.baseurl }}/nc_stock/) utility)

```
$ nc_stock --box -x10 -y10 -z-10 > stock.off
```

The nc_model command can be used to remove material from the stock. The simple gcode progam given does not specify a
tool change, so the inital tool is specified manually. The tool geometry is defined in the [nc_tools.conf]({{ site.baseurl }}/nc_tools.conf/) file.

```
$ nc_model --stock stock.off --tool 1 < profile.ngc > model.off
$ nc_backplot --model model.off < profile.ngc
```


![resulting model]({{ site.baseurl }}/assets/nc_model.png)