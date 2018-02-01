def swap(arr, e1, e2):
        swaptmp = arr[e1]
        arr[e1] = arr[e2]
        arr[e2] = swaptmp

def max(arr):
        s = arr[0]
        for k in arr:
                if arr[k] > s:
                        s = arr[k]
        return s

x = [1, 2, 3, 4, 5]
y = [55, 44, 33, 22, 11]

print x
swap(x,1,2)
print x
print max(y)
