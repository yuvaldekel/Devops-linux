import time

start = time.perf_counter()
for i in range(1000000):
    pass
end = time.perf_counter()

print(f'{float(end - start):.8f}')