---
title: "A Simple Python Bounds Checker using Decorators"
date: 2022-10-17T20:55:56+01:00
tags: []
draft: false
---

### A bounds checker you say?

Every now and again you might need a bounds checker. I find that when you do, you need it a lot!
I thought there must be a simple way to minimise bloated code. Fear no more as Python decorators are here to save the day! 


```python
def bounds_checker(lower, upper):
    def wrap(func):
        def wrapped_f(*args):
            val = args[0]
            if val > upper:
                val = upper
                print(f"Set value is too high. Upper bound: {upper} set")

            elif val < lower:
                print(f"Set value is too low. Lower bound: {lower} set")
                val = lower
     
            func(val)
        return wrapped_f
    return wrap


@bounds_checker(0,200)
def set_value(value):
    print(value)      


set_value(300)
```

This outputs 

```
Set value is too high. Upper bound: 200 set
```

