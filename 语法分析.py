#语法分析器#
key = {"auto","break","case","string","const","continue","default",

"do","double","else","enum","extern","float","for",

"goto","if","int","long","register","return","short",

"signed","static","sizeof","struct","switch","typedef","union",

"unsigned","void","volatile","while"}  #32个关键字

limiter = {'{','}','[',']','(',')',';','\'',':',',','"'}  #界符

basic_op = {'+', '-', '*', '/', '%','=','|','&','^','>','<','!'}  #基本的运算符

terminate = key|limiter|basic_op|{'id','digit'} ##语法分析的终结符
unterminate = {}
pro_left = []  ##文法产生式左部
pro_right = []  ##文法产生式右部
first_set = dict() ##fisrt集
follow_set = dict() ##follow集

def scanner(file_name):
    global unterminate, pro_left, pro_right,first_set
    my_file = open(file_name,'r')
    line = my_file.readline()
    unterminate = set(line.strip('\n').split(','))
    for u in unterminate:
        first_set[u]= set()
        follow_set[u] = set()
    for line in my_file.readlines():
        line = line.strip('\n').split(':=')
        tmp = line[0].replace('<','').replace('>','')
        pro_left.append(tmp.strip(" "))
        tmp = line[1].replace('<','#').replace('>','#').replace(' ','#')
        tmp = tmp.split('#')
        while '' in tmp:
            tmp.remove('')
        pro_right.append(tmp)
    my_file.close()
    


        
def first():
    global terminate, unterminate, pro_right,first_set
    not_ok = set()
    for i in range(0,len(pro_left)):
        first_set[pro_left[i]].add(pro_right[i][0])
        if pro_right[i][0] in unterminate:
            not_ok.add(pro_left[i])
    for key in not_ok:
        single_first(key)
    for key in first_set:
        print(str(key)+":"+str(first_set[key]))
        
def single_first(u): #求单个元素的first#
    global terminate, unterminate, first_set
    tag = 1
    for value in first_set[u]:
        if value in unterminate:
            tag = 0
            single_first(value)
            print("***"+str(value)+":"+str(first_set[value]))
            first_set[u] = first_set[u] - set([value])
            # print("***"+str(u)+":"+str(first_set[u]))
            first_set[u] = first_set[u] | first_set[value]
    if tag == 1:
        return
    
            
if __name__ == '__main__':
    scanner('1.txt')
    first()


