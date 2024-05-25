import random
import time

start_time = time.time()

N = 10000000
acertos = 0

i = N
while i > 0:
    x = random.randint(0, 100)
    y = random.randint(0, 100)
    x = x/100
    y = y/100
     
    if(x * x + y * y <= 1):
        acertos = acertos + 1
    i = i - 1
   

print(4 * acertos/N)
print("%s seconds" % (time.time() - start_time))

    