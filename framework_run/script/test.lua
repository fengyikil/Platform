--测试c调用lua函数
function test_add(a,b)
 c = a+b
 print(c) 
 return a+b
end

function test_exit()
 print("lua exit")
 return 9
end

function test_run()
 print("lua run")
 return 12
end

--测试传递通讯指针
function test_commu(com)
  print(type(com))
  fk_test_commu(com)
  return 100
end

--测试通讯解包各函数
function test_commu_unpacking(com)

end


print("hello")
print("hello")
print("hello")
res,str1,str2= fk_test(7,8)
print(res)
print(str1)
print(str2)