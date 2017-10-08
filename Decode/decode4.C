/////////////////////////////////////////////////////////////////////
//       source name : decode4                                     //
//       content     : decode no cluster by ch and or with cluster //
//       TFile       : BH1_1M_cluster.root                         //
//                     BH1_2M_cluster.root                         //
//                     BH1_4M_cluster.root                         //
//                     BH1_6M_cluster.root                         //
//                     BH1_8M_cluster.root                         //
//                     BH1_10M_cluster.root                        //
//                     BH1_12M_cluster.root                        //
//                     BH1_14M_cluster.root                        //
//                     BH1_16M_cluster.root                        //
//                     BH1_18M_cluster.root                        //
//                     BH1_20M_cluster.root                        //
//                     BH1_22M_cluster.root                        //
//                     BH1_24M_cluster.root                        //
//       Date        : 2017/8/24                                   //
//       Auther      : Suharu                                      //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>

#include <TApplication.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TTree.h>
#include <TFile.h>
#include <TSystem.h>
#include <TH1.h>
#include <TH2.h>
#include <RStringView.h>



using namespace std;


//  mask 
static const unsigned int frame_end = 0xfe00ffff;
static const unsigned int spill_end = 0x4e00ffff;

static const unsigned int data_mask = 0xffff;

static const unsigned int ch_mask   = 0xf;
static const unsigned int ch_shift  = 16;

const double ns_to_ms = 1000000;



struct dataCont{
  unsigned int data;
  unsigned int time;
  unsigned int ch;
};




bool TimeCompA(const dataCont& obj1,
	       const dataCont& obj2)
{
          return obj1.time < obj2.time;
}



// decode -------------------------------------------------------------------
void
decode(unsigned int data, dataCont& obj)
{
  unsigned int time_stamp = data & data_mask;
  unsigned int channel    = (data >> ch_shift) & ch_mask;

  obj.data = data;
  obj.time = time_stamp;
  obj.ch   = channel+1;

  if(data == frame_end) obj.ch = 99;
}




// transform_timestamp ------------------------------------------------------
void
transform_timestamp(unsigned int data, unsigned int &stamp)
{
  static int n_frame = 0;

  unsigned int time_stamp = 0x10000*n_frame*10 + (data & data_mask)*10;  // ns
  stamp = time_stamp;

  if(data == frame_end){
    ++n_frame;
    stamp = 0;
  }// frame_end

}// transform_timestamp




//chande_time : pre_ch_time to ch_time ---------------------------------------------
//void
//change_time(unsigned int ch_munber, double pre_time[11],double *corr_time[11])
//{
//       for(unsigned int i=0; i<11; ++i){
//               if(i == ch_munber-1){
//                       *corr_time[i] = pre_time[i];
//               }else{
////                       corr_time[i] = - pre_time[i];
//                       *corr_time[i] = -5 ; 
//               }
//       }
//}

//change_time(unsigned int ch_munber, double pre_time[11],double corr_time)
//{
//       corr_time = pre_time;
//       for(unsigned int i=0; i<11; ++i){
//               if(i != ch_munber-1){
////                       corr_time[i] = - pre_time[i];
//                       pre_time[i] = -5 ; 
//               }
//       }
//}


// ************ main fanction ************* 
void decode4(){
//TFile and Tree
  TFile f("../emulation/rootfile/BH1_1M_cluster.root","recreate");
  TTree tree("tree","BH1_1M");//1M
///  TFile f("../emulation/rootfile/BH1_2M_cluster.root","recreate");
///  TTree tree("tree","BH1_2M");//2M
///  TFile f("../emulation/rootfile/BH1_4M_cluster.root","recreate");
///  TTree tree("tree","BH1_4M");//3M
///  TFile f("../emulation/rootfile/BH1_6M_cluster.root","recreate");
///  TTree tree("tree","BH1_6M");//6M
///  TFile f("../emulation/rootfile/BH1_8M_cluster.root","recreate");
///  TTree tree("tree","BH1_8M");//8M
///  TFile f("../emulation/rootfile/BH1_10M_cluster.root","recreate");
///  TTree tree("tree","BH1_10M");//10M
///  TFile f("../emulation/rootfile/BH1_12M_cluster.root","recreate");
///  TTree tree("tree","BH1_12M");//12M
///  TFile f("../emulation/rootfile/BH1_14M_cluster.root","recreate");
///  TTree tree("tree","BH1_14M");//12M
///  TFile f("../emulation/rootfile/BH1_16M_cluster.root","recreate");
///  TTree tree("tree","BH1_16M");//17M
///  TFile f("../emulation/rootfile/BH1_18M_cluster.root","recreate");
///  TTree tree("tree","BH1_18M");//17M
///  TFile f("../emulation/rootfile/BH1_20M_cluster.root","recreate");
///  TTree tree("tree","BH1_20M");//20M
///  TFile f("../emulation/rootfile/BH1_22M_cluster.root","recreate");
///  TTree tree("tree","BH1_22M");//17M
///  TFile f("../emulation/rootfile/BH1_24M_cluster.root","recreate");
///  TTree tree("tree","BH1_24M");//17M
  

//hist ---------------------------------------- 
  TH1D *hist[20];
  hist[0] = new TH1D("BH1 or","",301000,-10,3000); 
  for(int i=1; i<12 ; ++i){
         hist[i] = new TH1D(Form("BH1 ch%d",i),"",301000,-10,3000); 
  }


  std::ifstream fs("../Shot_Data/shot390825/ssm.dat");//1M/spill
///  std::ifstream fs("../Shot_Data/shot390941/ssm.dat");//2M/spill
///  std::ifstream fs("../Shot_Data/shot390992/ssm.dat");//4M/spill
///  std::ifstream fs("../Shot_Data/shot391040/ssm.dat");//6M/spill
///  std::ifstream fs("../Shot_Data/shot391097/ssm.dat");//8M/spill
///  std::ifstream fs("../Shot_Data/shot391194/ssm.dat");//10M/spill
///  std::ifstream fs("../Shot_Data/shot391246/ssm.dat");//12M/spill
///  std::ifstream fs("../Shot_Data/shot391301/ssm.dat");//14M/spill
///  std::ifstream fs("../Shot_Data/shot391376/ssm.dat");//16M/spill
///  std::ifstream fs("../Shot_Data/shot391437/ssm.dat");//18M/spill
///  std::ifstream fs("../Shot_Data/shot391511/ssm.dat");//20M/spill
///  std::ifstream fs("../Shot_Data/shot391578/ssm.dat");//22M/spill
///  std::ifstream fs("../Shot_Data/shot391651/ssm.dat");//24M/spill
  
//dataCont define
  std::vector<dataCont> data_list;
  double prev_time = 0;
  unsigned int time;
  unsigned int ch;
  double ms_time;
  double ch_time[11];
//  double pre_ch_time[11];
  double s;
//  double ch[10];
  tree.Branch("BH1_ch",&ch_time,"ch_time[11]/D");
  tree.Branch("ms_time",&ms_time,"ms_time/D");

//Binary file scan  -----------------------
  while(!fs.eof()){
  unsigned int data;
  fs.read((char*)&data, sizeof(unsigned int ));

        if(data == spill_end) continue;
                dataCont tmp_data;
                decode(data, tmp_data);
                data_list.push_back(tmp_data);

        if(data != frame_end) continue;
                
     // frame end ---------------------------

        // iterator difine ---------------------------
        std::vector<dataCont>::iterator itr = data_list.begin();
        // SORT!!! ---------------------------
        std::partial_sort(data_list.begin(), data_list.end()-1,
		            data_list.end(),
		            TimeCompA // sort fanction 
		            );


        //Crastering = Double segment through cut

        for(; itr!=data_list.end(); ++itr){
               bool flag_cluster = false;
               if((*itr).data != frame_end){
        	              dataCont& curr = *itr;     //continuous data define
        	              dataCont& next = *(itr+1);

        	              if(true
        	                      && (next.time - curr.time) < 2 // 2 = 20 ns -> one clock 
        	                      && (next.ch-1 == curr.ch || next.ch+1 == curr.ch) // Next to each other ch
        	              ){
        	                      flag_cluster = true;
        	              }// if it is cluster -> flag_cluster is true
                }// cluster check! 
        
                transform_timestamp((*itr).data, time);
                ch = (*itr).ch;
                
                if(time !=0 ){
                        ms_time = time/ns_to_ms;
                        hist[0] -> Fill(ms_time);
                        if(ch<12){
                                hist[ch]->Fill(ms_time);
//                                pre_ch_time[ch-1] = ms_time;
//                                pre_ch_time[ch-1] = ms_time;
//                                change_time(ch,pre_ch_time[11],ch_time);
                                       for(unsigned int i=0; i<11; ++i){
                                               if(i == ch-1){
                                                       ch_time[i] = ms_time;
                                               }else{
                                                       ch_time[i] = -5 ; 
                                               }
                                       }
                        }        
                        tree.Fill();
                }

                if(flag_cluster){
                       ++itr;
                       transform_timestamp((*itr).data, time);
                       ch = (*itr).ch;
                         if(time !=0 ){
                                 if(ch<12){
                                         hist[ch]->Fill(ms_time);
                                                for(unsigned int i=0; i<11; ++i){
                                                        if(i == ch-1){
                                                                ch_time[i] = ms_time;
                                                        }else{
                                                                ch_time[i] = -5 ; 
                                                        }
                                                }
                                 }        
                        ms_time = -5;         
                        hist[0] -> Fill(ms_time);
                        tree.Fill();
                        }// if it is cluster sig. -> next data is skipped 
                }//flag_cluster 
        }//for (itr) 



        data_list.clear();

   }//While !fs.eof() 

  fs.close();
  f.Write();
  f.Close();
}

  int main(int argc, char** argv){
        TROOT root("GUI","GUI");

//        TApplication theApp("App",&argc,argv);

        decode4();

//        theApp.Run();

        return 0;
  }
