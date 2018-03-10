# def A(n,m):
#     ret=1
#     while m!=0:
#         ret=ret*n
#         n-=1
#         m-=1
#     return ret
# def mul(n):
#     ret=1
#     while n!=1:
#         ret*=n
#         n-=1
#     return ret
# n,m=raw_input().split()
# n=int(n)
# m=int(m)
# print(mul(n)*(A(n+1,2)*A(n+3,m)+2*m*(n+1)*A(n+2,m-1)))
def mul(x, y):
    re = 1
    for i in range (x, y + 1):
        re = re * i
    return re

n, m = raw_input().split()
n = int(n); m = int(m)
print(mul(1,n+1)*mul(n+4-m,n+2)*(n*(n+3)+2*m))
