require("elua_hello") 

function handleMesg(commu)
printf("Say: %s\n", "hello world")  
messagebox("Test","mesg")
print("lua print:")

print(fk_comu_getId(commu))
print(fk_comu_getInt(commu,0))
print(fk_comu_getInt(commu,4))
print(fk_comu_getInt(commu,8))

  len = fk_comu_getLen(commu)
  fk_comu_out(commu,len)
return 8;
end