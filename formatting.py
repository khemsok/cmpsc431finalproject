f = open('out1.txt','r')
lines = f.readlines()
f.close()
f = open('out1.txt', 'w')

for line in lines:
    if not "==>" in line:
        if not "Goodbye!\n" in line:
            if not "Welcome!\n" in line:
               f.write(line)

f.close()

data = []
r = open('out1.txt', 'r')
w = open('out1_new.txt', 'w')
line_ = r.readlines()
for line in line_:
    x1, x2, x3, x4, x5, x6, x7 = line.split(',')
    w.write('First Name: '+ x1 + '\n' + 'Last Name: ' + x2 + '\n' + 'Date: ' + x3 + '\n' + 'Day: ' + x4 + '\n' + 'Time: ' + x5 + '\n' + 'Department: ' + x6 + '\n' + 'Role: ' + x7 + '\n' )
    
