// emuration macro
// 2017/8/25(Fri)
// Suharu
//
//

void trigger_efficiency(){
   gBenchmark->Start("trigger_efficiency");
  TFile *file = new TFile("../../../rootfile/BH1_20M_cluster.root");
///  TFile *file = new TFile("../../../rootfile/BH1_20M_cluster.root");
  TTree *tree = (TTree*)file->Get("tree");

  double ms_time;
  double pre_ms_time = 0;
//  double pre2_ms_time = 0;
  double delta_t;
//  double delta_t2;
  double ch_time[11];
  double trigger;
  double entries1;
  double entries2;
//  double entries3;
  double efficiency1;
//  double efficiency2;


  tree->SetBranchAddress("ms_time",&ms_time);
  tree->SetBranchAddress("BH1_ch",&ch_time);

  TH1D *hist[12];
  hist[0] = new TH1D("BH1 or","",301000,-10,3000);
  hist[1] = new TH1D("BH1 or_Trigger(1/10000)","",301000,-10,3000);
  hist[2] = new TH1D("BH1 or_Trigger & mask(30micros)","",301000,-10,3000);
//  hist[3] = new TH1D("BH1 or_Trigger & mask false","",301000,-10,3000);

  TRandom3 tran(std::time(0));
  int n = tree->GetEntries();
        for(int i=0; i<n; ++i){
                tree->GetEntry(i);
                if(ms_time>0){
                        hist[0]->Fill(ms_time);
                        //Trigger ----------------------
                        trigger = tran.Rndm(); 
                        if(trigger>0.9999){
                                hist[1]->Fill(ms_time);
                                delta_t = ms_time - pre_ms_time;
//                                delta_t2 = ms_time - pre2_ms_time;
                                if(delta_t>0.03){
                                        hist[2]->Fill(ms_time);
                                }
                                if(delta_t<0.03){
                                        continue;
                                }
                                pre_ms_time = ms_time;
                        }
                }
        }

        entries1 = hist[1]->GetEntries();
        entries2 = hist[2]->GetEntries();
//        entries3 = hist[3]->GetEntries();
        efficiency1 = entries2/entries1;
//        efficiency2 = entries3/entries1;
        cout << efficiency1 << "" << endl;
//        cout << efficiency2 << "" << endl;
 
  TCanvas *c1 = new TCanvas("c1","c1",1600,900);
//  c1->Divide(1,3);
  int color[]={1,2,7};
  for(int i=0; i<3; ++i){
//        c1->cd(i+1);
        hist[i]->SetLineColor(color[i]);
        hist[i]->Draw("same");
  }

// file.dat out --------------------------------------------------------------        
  TString fout1 = ("../DAT/Efficiency_20M.dat");
  ofstream fout_1(fout1.Data());
      fout_1 << efficiency1 << endl;

///  TString fout2 = ("../DAT/Efficiency_20M.dat");
///  ofstream fout_2(fout2.Data());
///      fout_2 << efficiency1 << endl;

   c1->Print("Trigger_Efficiency_20M.pdf");
///   c1->Print("Trigger_Efficiency_20M.pdf");

   gBenchmark->Show("trigger_efficiency");
}
