// emuration macro
// 2017/8/25(Fri)
// Suharu
//
//

void trigger_efficiency(){
  gBenchmark->Start("trigger_efficiency");
  TFile *file[13];
  TTree *tree[13];
  TString fout1[13];
  TCanvas *c[13];
  TH1D *hist[13][12];
  TRandom3 tran(std::time(0));

  double ms_time[13];
  double pre_ms_time[13];
  double delta_t[13];
  double ch_time[13][11];
  double trigger[13];
  double entries1[13];
  double entries2[13];
  double efficiency1[13];

  int color[]={1,2,7};
  int n[13];
  double max_bin[13]; 
  double max_value[13];
  int entries[13];

//  TFile *file = new TFile("../../../rootfile/BH1_1M_cluster.root");
///  TFile *file = new TFile("../../../rootfile/BH1_20M_cluster.root");


  fout1[0] = ("../DAT/Efficiency_1M.dat"); 
  pre_ms_time[0] = 0;
  for(int i=0; i<13; ++i){
          if(i==0){
                file[0] = new TFile("../../../rootfile/BH1_1M_cluster.root");
          }else{
                file[i] = new TFile(Form("../../../rootfile/BH1_%dM_cluster.root",2*i));
          } 
          tree[i] = (TTree*)file[i]->Get("tree");
          pre_ms_time[i] = 0;

          tree[i]->SetBranchAddress("ms_time",&ms_time[i]);
          tree[i]->SetBranchAddress("BH1_ch",&ch_time[i][0]);

        if(i==0){
               hist[i][0] = new TH1D(Form("BH1 or %dM",i+1),"",301000,-10,3000);
               hist[i][1] = new TH1D(Form("BH1 or %dM Trigger(1/10000)",i+1),"",301000,-10,3000);
//               hist[i][2] = new TH1D(Form("BH1 or %dM Trigger & mask(30micros)",i+1),"",301000,-10,3000);
               hist[i][2] = new TH1D(Form("BH1 or %dM Trigger & mask(110micros)",i+1),"",301000,-10,3000);
        }else{
               hist[i][0] = new TH1D(Form("BH1 or %dM",i*2),"",301000,-10,3000);
               hist[i][1] = new TH1D(Form("BH1 or %dM Trigger(1/10000)",i*2),"",301000,-10,3000);
//               hist[i][2] = new TH1D(Form("BH1 or %dM Trigger & mask(30micros)",i*2),"",301000,-10,3000);
               hist[i][2] = new TH1D(Form("BH1 or %dM Trigger & mask(110micros)",i*2),"",301000,-10,3000);
        }
          

   n[i] = tree[i]->GetEntries();
        for(int j=0; j<n[i]; ++j){
                tree[i]->GetEntry(j);
                if(ms_time[i]>0){
                        hist[i][0]->Fill(ms_time[i]);
                        //Trigger ----------------------
                        trigger[i] = tran.Rndm(); 
                        if(trigger[i]>0.9999){
                                hist[i][1]->Fill(ms_time[i]);
                                delta_t[i] = ms_time[i] - pre_ms_time[i];
//                                delta_t2 = ms_time - pre2_ms_time;
//                                if(delta_t[i]>0.03){ //30 microsec
                                if(delta_t[i]>0.11){ //110 microsec
                                        hist[i][2]->Fill(ms_time[i]);
                                }
//                                if(delta_t[i]<0.03){ //30 micrisec
                                if(delta_t[i]<0.11){ //110 microsec
                                        continue;
                                }
                                pre_ms_time[i] = ms_time[i];
                        }
                }
        }

        entries1[i] = hist[i][1]->GetEntries();
        entries2[i] = hist[i][2]->GetEntries();
        efficiency1[i] = entries2[i]/entries1[i];
        cout << efficiency1[i] << "" << endl;
 

        c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),1600,900);
        max_bin[i] = hist[i][0]->GetMaximumBin();
        max_value[i] = hist[i][0]->GetBinContent(max_bin[i]);

        for(int j=0; j<3; ++j){
      //        c1->cd(i+1);
              hist[i][j]->SetLineColor(color[j]);
              if(j==1){
                      hist[i][j]->Scale(max_value[i]/10,"");
              }
              if(j==2){
                      hist[i][j]->Scale(max_value[i]/10,"");
              }
              hist[i][j]->Draw("hist same");
        }

        if(i==0){
//                 fout1[i]= (Form("../DAT/Efficiency_%dM.dat",i+1));
                 c[i]->Print("Trigger_Efficiency_1M_110.pdf");
        }else{
//                 fout1[i]= (Form("../DAT/Efficiency_%dM.dat",2*i));
                 c[i]->Print(Form("Trigger_Efficiency_%dM_110.pdf",2*i));
        }

        entries[i] = hist[i][0]->GetEntries(); 
  }

// file.dat out --------------------------------------------------------------        
//  fout1[0] = ("../DAT/Efficiency.dat");
//  fout1[1] = ("../DAT/entries.dat");
//  fout1[2] = ("../DAT/trigger_entries.dat");
//  fout1[3] = ("../DAT/alltrigger_entries.dat");
  fout1[0] = ("../DAT/Efficiency_110.dat");
  fout1[1] = ("../DAT/entries_110.dat");
  fout1[2] = ("../DAT/trigger_entries_110.dat");
  fout1[3] = ("../DAT/alltrigger_entries_110.dat");
  ofstream fout_1(fout1[0].Data());
  ofstream fout_2(fout1[1].Data());
  ofstream fout_3(fout1[2].Data());
  ofstream fout_4(fout1[3].Data());
  for(int i=0;i<13;++i){
          fout_1 << efficiency1[i] << endl;
          fout_2 << entries[i] << endl;
          fout_3 << entries2[i] << endl;
          fout_4 << entries1[i] << endl;
         
  }  

   gBenchmark->Show("trigger_efficiency");
}
