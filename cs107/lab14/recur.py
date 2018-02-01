def power(b, e):
        if e == 1:
                powertmp = b
        else:
                powertmp = b*power(b, e-1)
        return powertmp

print power(2, 8)
