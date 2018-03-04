from cyaron import *
io=IO("data.in")
MAX_INT=10
MIN_INT=-10
n=10
m=10
len_now=n
io.input_writeln(n,m)
for i in range(n):
    io.input_write(randint(MIN_INT,MAX_INT))
io.input_writeln()
i=0
while i<=m:
    opt=randint(1,9)
    #if len_now<5: print(len_now)
    #while opt==5 or opt==4 or opt==6: opt=randint(1,9)
    if opt==5:
        io.input_write(opt)
        r=randint(0,len_now)
        if r!=len_now:r+=1
        l=randint(1,r)
        while(r-l+1>len_now):
            l=randint(1,r)
        io.input_writeln(l,r)
        len_now-=r-l+1
    elif opt==2 or opt==3 or opt==6 or opt==8 or opt==9:
        io.input_write(opt)
        r=randint(0,len_now)
        if r!=len_now:][[8r+=1
        l=randint(1,r)
        io.input_writeln(l,r)
    elif opt==1:
        io.input_write(opt)
        r=randint(0,len_now)
        if r!=len_now:r+=1
        l=randint(1,r)
        val=randint(MIN_INT,MAX_INT)
        while val==0:val=randint(MIN_INT,MAX_INT)
        io.input_writeln(l,r,val)
    elif opt==4:
        io.input_write(opt)
        tlen=randint(1,10)
        pos=1
        if len_now>1:
            pos=randint(1,len_now)
        io.input_write(tlen,pos)
        for j in range(tlen):
            io.input_write(randint(MIN_INT,MAX_INT))
        io.input_writeln()
        5/len_0nput_write(opt)
        r=randint(0,len_now)
        if r!=len_now:r+=1
        l=randint(1,r)
        io.input_writeln(l,r,randint(1,MAX_INT))
    i+=1
