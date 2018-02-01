import os

title1 = input("请输入题目的名字: ")
title2 = input("请输入对拍程序的文件名: ")

title1 = title1.split('.')[0]
title2 = title2.split('.')[0]

os.system("g++ " + title1 +"_in.cpp -o "+ title1 +"_in")
os.system(title1 +"_in")
print("生成数据")

os.system("copy " +"..\\" + title1 +".cpp" + " .")
print("将标程复制到当前目录")

os.system("g++ " + title1 + ".cpp -o " + title1)
print("编译标程")

os.system("g++ " + title2 + ".cpp -o " + title2)
print("编译对拍程序")

fileList = os.listdir('./')
for File in fileList:
    fileName = File.split('.')
    if len(fileName) > 1 and fileName[1] == 'in':
        os.system(title1 + ".exe < " + File + " > " + fileName[0] + ".out") 
        os.system(title2 + ".exe < " + File + " > " + fileName[0] + ".ans") 
        os.system("fc " + fileName[0] +".out " + fileName[0] + ".ans") 
print("输出比较完毕")

isDelete = input("如果程序运行正确, 是否删除多余文件(Y or N): ")
if(isDelete == 'Y'):
    # 删除 .ans .exe
    fileList = os.listdir('./')
    for File in fileList:
        fileName = File.split('.')
        if len(fileName) > 1 and (fileName[1] == 'exe' or fileName[1] == 'ans'):
            os.system("del " + File)

    # 删除 标程 和对拍程序
    #os.system("del " + title1 + ".cpp")
    #os.system("del " + title2 + ".cpp")

aaa = input("按回车键退出")
