#!/usr/bin/env python
import time
import os
import subprocess ,signal
prefix_cmd="./waf --run 'scratch/couple-tree --mp=cp --it=%s --cc=%s --lo=%s'"
test_case=[1,4,5,6,7,8]
loss_rate=[0,10,20,30,40,50]
cc_name="lia"
for case in range(len(test_case)):
    inst=str(test_case[case]);
    for i in range(len(loss_rate)):
        cmd=prefix_cmd%(inst,cc_name,str(loss_rate[i]))
        process= subprocess.Popen(cmd,shell = True)
        while 1:
            time.sleep(1)
            ret=subprocess.Popen.poll(process)
            if ret is None:
                continue
            else:
                break
cc_name="olia"
for case in range(len(test_case)):
    inst=str(test_case[case]);
    for i in range(len(loss_rate)):
        cmd=prefix_cmd%(inst,cc_name,str(loss_rate[i]))
        process= subprocess.Popen(cmd,shell = True)
        while 1:
            time.sleep(1)
            ret=subprocess.Popen.poll(process)
            if ret is None:
                continue
            else:
                break
cc_name="liaen3"
for case in range(len(test_case)):
    inst=str(test_case[case]);
    for i in range(len(loss_rate)):
        cmd=prefix_cmd%(inst,cc_name,str(loss_rate[i]))
        process= subprocess.Popen(cmd,shell = True)
        while 1:
            time.sleep(1)
            ret=subprocess.Popen.poll(process)
            if ret is None:
                continue
            else:
                break
cc_name="mpveno"
for case in range(len(test_case)):
    inst=str(test_case[case]);
    for i in range(len(loss_rate)):
        cmd=prefix_cmd%(inst,cc_name,str(loss_rate[i]))
        process= subprocess.Popen(cmd,shell = True)
        while 1:
            time.sleep(1)
            ret=subprocess.Popen.poll(process)
            if ret is None:
                continue
            else:
                break
cc_name="mpwest"
for case in range(len(test_case)):
    inst=str(test_case[case]);
    for i in range(len(loss_rate)):
        cmd=prefix_cmd%(inst,cc_name,str(loss_rate[i]))
        process= subprocess.Popen(cmd,shell = True)
        while 1:
            time.sleep(1)
            ret=subprocess.Popen.poll(process)
            if ret is None:
                continue
            else:
                break

