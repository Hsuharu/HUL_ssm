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





// ************ main fanction ************* 
void decode2(){
//TFile and Tree
  TFile f("BH1_1M.root","recreate");
//  TFile f("BH1_or_20M.root","recreate");
  TTree tree("tree","BH1_ssl");
  

//hist ---------------------------------------- 
  TH1D *hist[20];
  hist[0] = new TH1D("BH1 or","",300000,0,3000); 
  for(int i=1;i<12 ; ++i){
         hist[i] = new TH1D(Form("BH1 ch%d",i),"",300000,0,3000); 
  }


  std::ifstream fs("../Data/shot390825/ssm.dat");//1M/spill
//  std::ifstream fs("../Data/shot390825/ssm.dat",std::ios::binary | std::ios::in);//1M/spill
//  std::ifstream fs("../Data/shot391511/ssm.dat");//20M/spill
  
//dataCont define
  std::vector<dataCont> data_list;
  double prev_time = 0;
  unsigned int time;
  double ms_time;
  unsigned int ch;
  double s;
//  double ch[10];
  tree.Branch("ms_time",&ms_time,"ms_time/D");
//  tree.Branch("ch",&ms_time,"ch[10]/D");
//  tree.Branch("ch1",&ch1_ms,"ch1/D");
//  tree.Branch("ch2",&ch2_ms,"ch2/D");
//  tree.Branch("ch3",&ch3_ms,"ch3/D");
//  tree.Branch("ch4",&ch4_ms,"ch4/D");
//  tree.Branch("ch5",&ch5_ms,"ch5/D");
//  tree.Branch("ch6",&ch6_ms,"ch6/D");
//  tree.Branch("ch7",&ch7_ms,"ch7/D");
//  tree.Branch("ch8",&ch8_ms,"ch8/D");
//  tree.Branch("ch9",&ch9_ms,"ch9/D");
//  tree.Branch("ch10",&ch10_ms,"ch10/D");
//  tree.Branch("ch11",&ch11_ms,"ch11/D");

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
                        }        
                        tree.Fill();
                        cout << s << "" << endl;
                        ++s;
                }

                if(flag_cluster) ++itr; // if it is cluster sig. -> next data is skipped 
        }//for (itr) 



        data_list.clear();

   }//While !fs.eof() 




//   TCanvas *c1 = new TCanvas("c1","c1",800,700);
//   c1->Divide(4,3);
//   for(int i=0; i<11; ++i){
//   c1->cd(i+1);
//   hist[i]->SetLineColor(4);
//   hist[i]->Draw();
//   }
//     for(int i=0; i<1; ++i){
//     TCanvas *c[i];
//     c[i] =  new TCanvas(Form("c%d",i+1),"",1000,900);
//     hist[i]->Draw();
//     }
  fs.close();
  f.Write();
  f.Close();

}

  int main(int argc, char** argv){
        TROOT root("GUI","GUI");

//        TApplication theApp("App",&argc,argv);

        decode2();

//        theApp.Run();

        return 0;
  }

