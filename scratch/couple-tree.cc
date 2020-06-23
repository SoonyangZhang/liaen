/** Network topology
 *       n0            n1             n2
 *        |            |              |
 *        | l0         | l2           |l4
 *        |            |              |
 *        n3---l1------n4-----l3-----n5
 *        |            |              |    
 *        |  l5        |  l6          |l7
 *        |            |              |
 *        n6           n7             n8
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/traffic-control-module.h"
#include "ns3/dqc-module.h"
#include "couple_cc_manager.h"
#include "couple_cc_source.h"
#include "ns3/log.h"
#include<stdio.h>
#include<iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <memory>
using namespace ns3;
using namespace dqc;
using namespace std;
NS_LOG_COMPONENT_DEFINE ("couple-tree");

uint32_t checkTimes;
double avgQueueSize;

// The times
double global_start_time;
double global_stop_time;
double sink_start_time;
double sink_stop_time;
double client_start_time;
double client_stop_time;
typedef struct
{
uint64_t bps;
uint32_t msDelay;
uint32_t msQdelay;	
}link_config_t;
link_config_t TreeTopoLinks1[]={
[0]={100*1000000,5,60},
[1]={100*1000000,5,60},
[2]={100*1000000,10,60},
[3]={5*1000000,10,60},
[4]={100*1000000,10,60},
[5]={100*1000000,5,60},
[6]={100*1000000,10,60},
[7]={100*1000000,10,60},
};
link_config_t TreeTopoLinks2[]={
[0]={100*1000000,5,90},
[1]={100*1000000,5,90},
[2]={100*1000000,10,90},
[3]={5*1000000,10,90},
[4]={100*1000000,10,90},
[5]={100*1000000,5,90},
[6]={100*1000000,10,90},
[7]={100*1000000,10,90},
};
link_config_t TreeTopoLinks3[]={
[0]={100*1000000,5,100},
[1]={100*1000000,5,100},
[2]={100*1000000,10,100},
[3]={5*1000000,10,100},
[4]={100*1000000,10,100},
[5]={100*1000000,15,100},
[6]={100*1000000,20,100},
[7]={100*1000000,20,100},
};
link_config_t TreeTopoLinks4[]={
[0]={100*1000000,5,150},
[1]={100*1000000,5,150},
[2]={100*1000000,10,150},
[3]={5*1000000,10,150},
[4]={100*1000000,10,150},
[5]={100*1000000,15,150},
[6]={100*1000000,20,150},
[7]={100*1000000,20,150},
};
link_config_t TreeTopoLinks5[]={
[0]={100*1000000,5,140},
[1]={100*1000000,5,140},
[2]={100*1000000,10,140},
[3]={6*1000000,10,140},
[4]={100*1000000,10,140},
[5]={100*1000000,25,140},
[6]={100*1000000,30,140},
[7]={100*1000000,30,140},
};
link_config_t TreeTopoLinks6[]={
[0]={100*1000000,5,180},
[1]={100*1000000,5,180},
[2]={100*1000000,10,180},
[3]={6*1000000,10,180},
[4]={100*1000000,10,180},
[5]={100*1000000,35,180},
[6]={100*1000000,40,180},
[7]={100*1000000,40,180},
};
link_config_t TreeTopoLinks7[]={
[0]={100*1000000,5,160},
[1]={100*1000000,5,160},
[2]={100*1000000,10,160},
[3]={8*1000000,10,160},
[4]={100*1000000,10,160},
[5]={100*1000000,25,160},
[6]={100*1000000,30,160},
[7]={100*1000000,40,160},
};
link_config_t TreeTopoLinks8[]={
[0]={100*1000000,5,200},
[1]={100*1000000,5,200},
[2]={100*1000000,10,200},
[3]={8*1000000,10,200},
[4]={100*1000000,10,200},
[5]={100*1000000,35,200},
[6]={100*1000000,40,200},
[7]={100*1000000,50,200},
};
const uint32_t TOPO_DEFAULT_BW     = 5000000;    // in bps: 3Mbps
const uint32_t TOPO_DEFAULT_PDELAY =      10;    // in ms:   100ms
const uint32_t TOPO_DEFAULT_QDELAY =     150;    // in ms:  300ms
static void InstallDqc( dqc::CongestionControlType cc_type,
                        Ptr<Node> sender,
                        Ptr<Node> receiver,
						uint16_t send_port,
                        uint16_t recv_port,
                        float startTime,
                        float stopTime,
						DqcTrace *trace,
                        uint32_t max_bps=0,uint32_t cid=0,uint32_t emucons=1)
{
    Ptr<DqcSender> sendApp = CreateObject<DqcSender> (cc_type);
	Ptr<DqcReceiver> recvApp = CreateObject<DqcReceiver>();
   	sender->AddApplication (sendApp);
    receiver->AddApplication (recvApp);
	if(cid){
		sendApp->SetCongestionId(cid);
	}
	sendApp->SetNumEmulatedConnections(emucons);
    Ptr<Ipv4> ipv4 = receiver->GetObject<Ipv4> ();
	Ipv4Address receiverIp = ipv4->GetAddress (1, 0).GetLocal ();
	recvApp->Bind(recv_port);
	sendApp->Bind(send_port);
	sendApp->ConfigurePeer(receiverIp,recv_port);
    sendApp->SetStartTime (Seconds (startTime));
    sendApp->SetStopTime (Seconds (stopTime));
    recvApp->SetStartTime (Seconds (startTime));
    recvApp->SetStopTime (Seconds (stopTime));
    if(max_bps>0){
        sendApp->SetMaxBandwidth(max_bps);
    }
	if(trace){
		sendApp->SetBwTraceFuc(MakeCallback(&DqcTrace::OnBw,trace));
		recvApp->SetOwdTraceFuc(MakeCallback(&DqcTrace::OnOwd,trace));
	}	
}
static double simDuration=300;
uint16_t sendPort=5432;
uint16_t recvPort=5000;
float appStart=0.0;
float appStop=simDuration;
int main (int argc, char *argv[]){
    LogComponentEnable("dqcsender",LOG_LEVEL_ALL);
    LogComponentEnable("proto_connection",LOG_LEVEL_ALL);
	LogComponentEnable("lia_enhance3",LOG_LEVEL_ALL);
	CommandLine cmd;
    std::string instance=std::string("1");
    std::string cc_tmp("mbbr");
	std::string loss_str("0");
	std::string mpcoup("cp");
    cmd.AddValue ("it", "instacne", instance);
	cmd.AddValue ("cc", "cctype", cc_tmp);
	cmd.AddValue ("lo", "loss",loss_str);
	cmd.AddValue ("mp", "couple",mpcoup);
    cmd.Parse (argc, argv);
    int loss_integer=std::stoi(loss_str);
    double loss_rate=loss_integer*1.0/1000;
	std::cout<<"l "<<loss_rate<<std::endl;
	bool couple=false;
	if(mpcoup==std::string("se")){
		couple=false;
	}else if(mpcoup==std::string("cp")){
		couple=true;
	}else{
		couple=true;
	}
	if(loss_integer>0){
	Config::SetDefault ("ns3::RateErrorModel::ErrorRate", DoubleValue (loss_rate));
	Config::SetDefault ("ns3::RateErrorModel::ErrorUnit", StringValue ("ERROR_UNIT_PACKET"));
	Config::SetDefault ("ns3::BurstErrorModel::ErrorRate", DoubleValue (loss_rate));
	Config::SetDefault ("ns3::BurstErrorModel::BurstSize", StringValue ("ns3::UniformRandomVariable[Min=1|Max=3]"));
	}
    std::string cc_name;
	if(loss_integer>0){
		cc_name="_tree"+cc_tmp+"l"+std::to_string(loss_integer)+"_";
	}else{
		cc_name="_tree"+cc_tmp+"_";
	}
	link_config_t *topo=TreeTopoLinks1;
    int total_links=sizeof(TreeTopoLinks1)/sizeof(TreeTopoLinks1[0]);
    if(instance==std::string("1")){
		topo=TreeTopoLinks1;
    }else if(instance==std::string("2")){
        topo=TreeTopoLinks2;
    }else if(instance==std::string("3")){
        topo=TreeTopoLinks3;
    }else if(instance==std::string("4")){
        topo=TreeTopoLinks4;
    }else if(instance==std::string("5")){
        topo=TreeTopoLinks5;
    }else if(instance==std::string("6")){
        topo=TreeTopoLinks6;
    }else if(instance==std::string("7")){
        topo=TreeTopoLinks7;
    }else if(instance==std::string("8")){
        topo=TreeTopoLinks8;
    }else{
        topo=TreeTopoLinks1;
    }
  NodeContainer c;
  c.Create (9);
  Names::Add ( "N0", c.Get (0));
  Names::Add ( "N1", c.Get (1));
  Names::Add ( "N2", c.Get (2));
  Names::Add ( "N3", c.Get (3));
  Names::Add ( "N4", c.Get (4));
  Names::Add ( "N5", c.Get (5));
  Names::Add ( "N6", c.Get (6));
  Names::Add ( "N7", c.Get (7));
  Names::Add ( "N8", c.Get (8));
  
  NodeContainer linkToNodes[8];
  int i=0;
  linkToNodes[i] = NodeContainer (c.Get (0), c.Get (3));
  i++;
  linkToNodes[i]= NodeContainer (c.Get (3), c.Get (4));
  i++;
  linkToNodes[i] = NodeContainer (c.Get (1), c.Get (4));
  i++;
  linkToNodes[i] = NodeContainer (c.Get (4), c.Get (5));
  i++;
  linkToNodes[i] = NodeContainer (c.Get (2), c.Get (5));
  i++;
  linkToNodes[i] = NodeContainer (c.Get (3), c.Get (6));
  i++;
  linkToNodes[i] = NodeContainer (c.Get (4), c.Get (7));
  i++;
  linkToNodes[i] = NodeContainer (c.Get (5), c.Get (8));
  
  link_config_t *config=topo;
  uint32_t bufSize=0;

  InternetStackHelper internet;
  internet.Install (c);

  NS_LOG_INFO ("Build topology");
  NetDeviceContainer devices_loss;
  int p=0;
  int loss_link=1;
  {
      for(i=0;i<total_links;i++){
        PointToPointHelper p2p;
        TrafficControlHelper tch;
        bufSize =config[i].bps * config[i].msQdelay/8000;
        p2p.SetQueue ("ns3::DropTailQueue",
                    "Mode", StringValue ("QUEUE_MODE_BYTES"),
                    "MaxBytes", UintegerValue (bufSize));
        p2p.SetDeviceAttribute ("DataRate", DataRateValue(DataRate (config[i].bps)));
        p2p.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (config[i].msDelay)));
        NetDeviceContainer devices = p2p.Install (linkToNodes[i]);
        Ipv4AddressHelper ipv4;
        std::string ip="10.0."+std::to_string(p)+".0";
        p++;
        ipv4.SetBase (ip.c_str(), "255.255.255.0");
        ipv4.Assign (devices);
        tch.Uninstall (devices);
        if(loss_link==i){
            devices_loss=devices;
        }
      }
  }

    if(loss_integer>0){
	std::string errorModelType = "ns3::RateErrorModel";
  	ObjectFactory factory;
  	factory.SetTypeId (errorModelType);
  	Ptr<ErrorModel> em = factory.Create<ErrorModel> ();
	devices_loss.Get (1)->SetAttribute ("ReceiveErrorModel", PointerValue (em));		
	}
    Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  
  
   	dqc::CongestionControlType cc=kBBR;
	if(cc_tmp==std::string("mbbr")){
		cc=kCoupleBBR;
	}else if(cc_tmp==std::string("lpbbr")){
		cc=kLpBBR;
		couple=true;
	}else if(cc_tmp==std::string("lpbbrno")){
		cc=kLpBBRNo;
		couple=false;
	}else if(cc_tmp==std::string("dwc")){
		cc=kDwcBytes;
		couple=true;
	}else if(cc_tmp==std::string("wvegas")){
		cc=kWvegas;
		couple=true;
	}else if(cc_tmp==std::string("westen")){
		cc=kWestwoodEnhance;
		couple=false;
	}else if(cc_tmp==std::string("mpwest")){
		cc=kMpWest;
		couple=true;
	}else if(cc_tmp==std::string("mpveno")){
		cc=kMpVeno;
		couple=true;
	}else if(cc_tmp==std::string("balia")){
		cc=kBalia;
		couple=true;
	}else if(cc_tmp==std::string("lia")){
		cc=kLiaBytes;
		couple=true;
	}else if(cc_tmp==std::string("liaen")){
		cc=kLiaEnhance;
	}else if(cc_tmp==std::string("liaen2")){
		cc=kLiaEnhance2;
	}else if(cc_tmp==std::string("liaen3")){
		cc=kLiaEnhance3;
	}else if(cc_tmp==std::string("olia")){
		cc=kOlia;
		couple=true;
	}else if(cc_tmp==std::string("vegas")){
		cc=kVegas;
		couple=false;
	}else if(cc_tmp==std::string("reno")){
		cc=kRenoBytes;
		couple=false;
	}else if(cc_tmp==std::string("cubic")){
		cc=kCubicBytes;
		couple=false;
	}else{
		cc=kBBR;
		couple=false;
	}

  std::unique_ptr<dqc::CoupleSource> source;
  dqc::CoupleManager *manager=dqc::CoupleManager::Instance();
	if(couple){
		source.reset(new dqc::CoupleSource());
		source->RegsterMonitorCongestionId(1);
		source->RegsterMonitorCongestionId(4);	
		manager->RegisterSource(source.get());
	}
	if(!couple){
		std::cout<<"seperate "<<std::endl;
	}
	std::cout<<cc_tmp<<std::endl;
  	uint32_t max_bps=0;
	int test_pair=1;
	uint32_t cc_id=1;


	DqcTrace trace1;
	std::string log=instance+cc_name+std::to_string(test_pair);
	trace1.Log(log,DqcTraceEnable::E_DQC_OWD|DqcTraceEnable::E_DQC_BW);
    InstallDqc(cc,c.Get(0),c.Get(2),sendPort,recvPort,appStart,appStop,&trace1,max_bps,cc_id);
	test_pair++;
	sendPort++;
	recvPort++;
	cc_id++;

	DqcTrace trace2;
	log=instance+cc_name+std::to_string(test_pair);
	trace2.Log(log,DqcTraceEnable::E_DQC_OWD|DqcTraceEnable::E_DQC_BW);
    InstallDqc(kRenoBytes,c.Get(1),c.Get(2),sendPort,recvPort,appStart,appStop,&trace2,max_bps,cc_id);
	test_pair++;
	sendPort++;
	recvPort++;
	cc_id++;


	DqcTrace trace3;
	log=instance+cc_name+std::to_string(test_pair);
	trace3.Log(log,DqcTraceEnable::E_DQC_OWD|DqcTraceEnable::E_DQC_BW);
	InstallDqc(kRenoBytes,c.Get(7),c.Get(8),sendPort,recvPort,appStart,appStop,&trace3,max_bps,cc_id);
	test_pair++;
	sendPort++;
	recvPort++;
	cc_id++;


	DqcTrace trace4;
	log=instance+cc_name+std::to_string(test_pair);
	trace4.Log(log,DqcTraceEnable::E_DQC_OWD|DqcTraceEnable::E_DQC_BW);
	InstallDqc(cc,c.Get(6),c.Get(8),sendPort,recvPort,appStart,appStop,&trace4,max_bps,cc_id);
	test_pair++;
	sendPort++;
	recvPort++;
	cc_id++;



    Simulator::Stop (Seconds(simDuration));
    Simulator::Run ();
    Simulator::Destroy();
	manager->Destructor();
}

