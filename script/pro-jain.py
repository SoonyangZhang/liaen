import os
import argparse
def mkdir(path):
    folder = os.path.exists(path)
    if not folder:    
        os.makedirs(path)
def ReafByteInfo(fileName,left,right):
    bytes=0
    for index, line in enumerate(open(fileName,'r')):
        lineArr = line.strip().split()
        time=float(lineArr[0])
        if time>right:
            break
        if time>=left:
            bytes=bytes+int(lineArr[3])
    return bytes
parser = argparse.ArgumentParser(description='manual to this script')
parser.add_argument('--algo', type=str, default ='olia')
args = parser.parse_args()
algo=args.algo
data_dir="data_process"
fileName1="%s_"+algo+"_1_owd.txt"
fileName2="%s_"+algo+"_2_owd.txt"
fileName3="%s_"+algo+"_3_owd.txt"
fileName4="%s_"+algo+"_4_owd.txt"
fileOutName=algo+"_fair"
out_path=data_dir+"/"
left=0.0
right=300.0
mkdir(out_path)
instance=[1,2,3,4,5,6,7,8]
fileOut=fileOutName+".txt"
fout=open(out_path+fileOut,'w')
for case in range(len(instance)):
    f1=fileName1%(str(instance[case]))
    f4=fileName4%(str(instance[case]))
    bytes1=ReafByteInfo(f1,left,right)
    bytes4=ReafByteInfo(f4,left,right)
    f2=fileName2%(str(instance[case]))
    bytes2=ReafByteInfo(f2,left,right)
    f3=fileName3%(str(instance[case]))
    bytes3=ReafByteInfo(f3,left,right)
    sum=bytes1+bytes4
    J1=1.0*(bytes2+sum)*(bytes2+sum)/(2.0*(bytes2*bytes2+sum*sum))
    R1=1.0*sum/(bytes2)
    J2=1.0*(bytes3+sum)*(bytes3+sum)/(2.0*(bytes3*bytes3+sum*sum))
    R2=1.0*sum/(bytes3)   
    fout.write(str(instance[case])+"\t"+str(J1)+"\t"+str(R1)+"\t"+str(J2)+"\t"+str(R2)+"\n")
fout.close()
