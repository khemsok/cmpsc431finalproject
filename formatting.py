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

r = open('out1.txt', 'r')
w = open('out1_new.txt', 'w')
line_ = r.readlines()
for line in line_:
    x1, x2, x3, x4, x5, x6, x7 = line.split(',')
    w.write('Last Name: '+ x1 + '\n' + 'First Name: ' + x2 + '\n' + 'Date: ' + x3 + '\n' + 'Day: ' + x4 + '\n' + 'Time: ' + x5 + '\n' + 'Department: ' + x6 + '\n' + 'Role: ' + x7 + '\n' )
    
r.close()
w.close()

f = open('out2.txt','r')
lines = f.readlines()
f.close()
f = open('out2.txt', 'w')

for line in lines:
    if not "==>" in line:
        if not "Goodbye!\n" in line:
            if not "Welcome!\n" in line:
               f.write(line)

f.close()

r = open('out2.txt', 'r')
w = open('out2_new.txt', 'w')
line_ = r.readlines()
for line in line_:
    x1, x2, x3, x4, x5, x6, x7 = line.split(',')
    w.write('Department: '+ x1 + '\n' + 'Date: ' + x2 + '\n' + 'Day: ' + x3 + '\n' + 'Time: ' + x4 + '\n' + 'Role: ' + x5 + '\n' + 'Certificate: ' + x6 + '\n' + 'Staff needed: ' + x7 + '\n' )
    
r.close()
w.close()

f = open('out3.txt','r')
lines = f.readlines()
f.close()
f = open('out3.txt', 'w')

for line in lines:
    if not "==>" in line:
        if not "Goodbye!\n" in line:
            if not "Welcome!\n" in line:
               f.write(line)

f.close()

r = open('out3.txt', 'r')
w = open('out3_new.txt', 'w')
line_ = r.readlines()
for line in line_:
    x1, x2, x3, x4, x5, x6, x7 = line.split(',')
    w.write('Last Name: '+ x1 + '\n' + 'First Name: ' + x2 + '\n' + 'Department: ' + x3 + '\n' + 'Date: ' + x4 + '\n' + 'Day: ' + x5 + '\n' + 'Time: ' + x6 + '\n' + 'Phone Number: ' + x7 + '\n' )
    
r.close()
w.close()