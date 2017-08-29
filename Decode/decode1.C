#include <iostream>
#include <fstream>
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

//decode fanction ------------------------------------------------------------
void decode1(){
//   gBenchmark->Start("decode1");
//  mask 
static const unsigned int frame_end = 0xfe00ffff;
static const unsigned int spill_end = 0x4e00ffff;

static const unsigned int data_mask = 0xffff;

static const unsigned int ch_mask   = 0xf;
static const unsigned int ch_shift  = 16;


  unsigned int data;
  unsigned int stamp;
//  unsigned int i;
//  unsigned int j;
  static int n_frame = 0;
  const double ns_to_ms   = 1000000;
//  std::vector<dataCont> data_list;

//TFile and Tree
//  TFile f("decode1.root","recreate");
//  TTree t1("t1","decode1");
//  t1->

//hist -----------------------
  TH1D *hist[20];
  for(int i=0;i<12 ; ++i){
  hist[i] = new TH1D(Form("BH1 ch%d",i+1),"",300000,0,3000); 
  }

  ifstream fs("../Data/shot390825/ssm.dat",ios::binary | ios::in);
  
//Binary file scan  -----------------------
  while(!fs.eof()){
  fs.read((char*)&data, sizeof(unsigned int ));
  if(data == spill_end) continue;
    unsigned int time_stamp = data & data_mask;
    unsigned int channel = (data >> ch_shift) & ch_mask;
    unsigned int ch = channel +1; 

    if(data == frame_end){
    ch   =  99;
       ++n_frame;
       stamp = 0;
    }

    if(data != frame_end){
     time_stamp = 0x10000*n_frame*10 + time_stamp*10;  // ns
     stamp = time_stamp; 
     double ms_time = stamp/ns_to_ms;

//each ch hist fill --------------------------
        if(ch < 12 ){
                hist[ch-1]->Fill(ms_time);
        }
        hist[11]->Fill(ms_time); // or
    } 
   }
//   TCanvas *c1 = new TCanvas("c1","c1",800,700);
//   c1->Divide(4,3);
//   for(int i=0; i<11; ++i){
//   c1->cd(i+1);
//   hist[i]->SetLineColor(4);
//   hist[i]->Draw();
//   }
     for(int i=0; i<12; ++i){
     TCanvas *c[i];
     c[i] =  new TCanvas(Form("c%d",i+1),"",1200,1000);
     hist[i]->Draw();
     }
  fs.close();
//   gBenchmark->Show("decode1");

}

  int main(int argc, char** argv){
        TROOT root("GUI","GUI");

        TApplication theApp("App",&argc,argv);

        decode1();

        theApp.Run();

        return 0;
  }

