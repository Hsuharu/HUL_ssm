void test(){
  TFile *file = new TFile("../../rootfile/BH1_or_1M.root");
  TTree *tree = (TTree*)file->Get("tree");

  double ms_time;
  double count;
  double sum; 
  double number_of_bin;
  int axis = 2;


  tree->SetBranchAddress("ms_time",&ms_time);

  TH1D *hist = new TH1D("hist","",300000,0,3000);

  int n = tree->GetEntries();
        for(int i=0; i<n; ++i){
                tree->GetEntry(i);
                hist->Fill(ms_time);
        }
  double max_bin = hist->GetMaximumBin();
  double max_value = hist->GetBinContent(max_bin);
  double averageofcount;// = hist->GetMean(axis); 
 
  for(int i=0; i<300000; i++){
        count = hist->GetBinContent(i);
//        cout << count << "" <<endl;
        if(count > 3){
                sum = sum + count;
                ++number_of_bin;
//                cout << number_of_bin << "" <<endl;
        } 
  }

  averageofcount = sum/number_of_bin;

  cout<< max_bin << "" << endl;
  cout<< max_value << "" << endl;
  cout<< averageofcount << "" << endl;

  TCanvas *c1 = new TCanvas("c1","c1",800,700);
        hist->Draw();
}
