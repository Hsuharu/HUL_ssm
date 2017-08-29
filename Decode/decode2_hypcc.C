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





// main fanction ------------------------------------------------------------
void decode2(){
//TFile and Tree
//  TFile f("decode2.root","recreate");
//  TTree t1("t1","decode2");
//  t1->


//hist -----------------------
  TH1D *hist[20];
  for(int i=0;i<12 ; ++i){
         hist[i] = new TH1D(Form("BH1_ch_or decode%d",i+1),"",300000,0,3000); 
  }


  std::ifstream fs("../Data/shot390825/ssm.dat");//1M/spill
//  std::ifstream fs("../Data/shot390825/ssm.dat",std::ios::binary | std::ios::in);//1M/spill
//  ifstream fs("../Data/shot391511/ssm.dat",ios::binary | ios::in);//20M/spill
  
//dataCont define
  std::vector<dataCont> data_list;
  double prev_time = 0;

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
        
                unsigned int time;
                transform_timestamp((*itr).data, time);

                if(time !=0 ){
                       double ms_time = time/ns_to_ms;
                       hist[0] -> Fill(ms_time);
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
     for(int i=0; i<1; ++i){
     TCanvas *c[i];
     c[i] =  new TCanvas(Form("c%d",i+1),"",1000,900);
     hist[i]->Draw();
     }
  fs.close();

}

  int main(int argc, char** argv){
        TROOT root("GUI","GUI");

        TApplication theApp("App",&argc,argv);

        decode2();

        theApp.Run();

        return 0;
  }

