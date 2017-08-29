

void ratio_20M(){
  TFile *file = new TFile("../../rootfile/BH1_20M.root");
  TTree *tree = (TTree*)file->Get("tree");

  double ms_time;
  double ch_time[11];
  double ch[11];

  tree->SetBranchAddress("ms_time",&ms_time);
  tree->SetBranchAddress("BH1_ch",ch_time);

  TH1D *hist[12];
  hist[0] =new TH1D("BH1 or","BH1 or",300000,0,3000);
  for(int i=1; i<12; ++i){
        hist[i] = new TH1D(Form("BH1 ch%d",i),Form("BH1 ch%d",i),300000,0,3000);

  }
// hist ----------------------------------------------------------------------
  int n = tree->GetEntries();
  for(int i=0; i<n; ++i){
        tree->GetEntry(i);
        hist[0]->Fill(ms_time);
        for(int j=1; j<12; ++j){
                if(ch_time[j-1]>0){
                        hist[j]->Fill(ch_time[j-1]);
                }
        }
  }
  

  double count[12];
  double sum[12]; 
  double number_of_bin[12];
  double max_bin[12]; 
  double max_value[12];
  double average_of_count[12];// = hist->GetMean(axis); 
//  double diff[12];
  double ratio[12];

   for(int i=0; i<12; ++i){
        max_bin[i] = hist[i]->GetMaximumBin();
        max_value[i] = hist[i]->GetBinContent(max_bin[i]);
        ch[i]=i;
   }

// Calculation ---------------------------------------------------------------
   for(int i=0; i<200000; ++i){
        for(int j=0; j<12; ++j){
                count[j] = hist[j]->GetBinContent(i+60000);
                        sum[j] = sum[j] + count[j];
                        ++number_of_bin[j];
        }

   }

   cout << number_of_bin[0] << "" << endl;

   for(int j=0; j<12; ++j){
        average_of_count[j] = sum[j]/number_of_bin[j];// = hist->GetMean(axis); 
//        diff[j] = max_value[j] - average_of_count[j];
        ratio[j] = max_value[j] / average_of_count[j];
        cout << "maximun:" << max_value[j] << " average:" << average_of_count[j] << " ratio:" << ratio[j] << endl;
   }
        

// TGraph --------------------------------------------------------------------
  int number_of_ch = 12;//include  BH1_or 
  
  TGraph *ch_ratio;
  ch_ratio = new TGraph(number_of_ch, ch,ratio);
  TGraph *ch_ave;
  ch_ave = new TGraph(number_of_ch, ch, average_of_count);
  TGraph *ch_max;
  ch_max = new TGraph(number_of_ch, ch, max_value);

// file.dat out --------------------------------------------------------------        
  TString fout1 = ("maximum.dat");
  ofstream fout_1(fout1.Data());
  TString fout2 = ("average.dat");
  ofstream fout_2(fout2.Data());
//  TString fout3 = ("diff.dat");
//  ofstream fout_3(fout3.Data());
  TString fout3 = ("ratio.dat");
  ofstream fout_3(fout3.Data());
  for(int i=1; i<12; ++i){
      fout_1 << max_value[i] << endl;
      fout_2 << average_of_count[i] << endl;
//      fout_3 << diff[i] << endl;
      fout_3 << ratio[i] << endl;
  }
   

  TCanvas *c1 = new TCanvas("c1","c1",1600,900);
  c1->Divide(4,3);
  for(int i=0; i<12; ++i){
        c1->cd(i+1);
        hist[i]->Draw();
  }

  TCanvas *c2 = new TCanvas("c2","c2",800,700);
       ch_ratio->Draw();
//  c2->Divide(3,1);
//        c2->cd(1);
//        ch_ratio->Draw();
//        c2->cd(2);
//        ch_ave->Draw();
//        c2->cd(3);
//        ch_max->Draw();


 c1->Print("spillstructure.pdf");
 c2->Print("ratio_distribution.pdf");


}

