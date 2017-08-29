void BH1orhist() {
        TFile *file1 = new TFile("./decode2.root");
        TFile *file2 = new TFile("./decode2_hyp.root");
        TTree *tree1 = (TTree*)file1->Get("tree");
        TTree *tree2 = (TTree*)file2->Get("tree");

        double ms_time1;
        double ms_time2;
        
        tree1->SetBranchAddress("ms_time",&ms_time1);
        tree2->SetBranchAddress("ms_time",&ms_time2);
        
        TH1D *hist1 = new TH1D("hist1","",300000,0,3000);
        TH1D *hist2 = new TH1D("hist2","",300000,0,3000);
        
        int n1 = tree1->GetEntries();
                for(int i=0;i<n1; ++i){
                        tree1->GetEntry(i);
                        hist1->Fill(ms_time1);
                }

        int n2 = tree2->GetEntries();
                for(int i=0;i<n2; ++i){
                        tree2->GetEntry(i);
                        hist2->Fill(ms_time2);
                }
        TCanvas *c1 = new TCanvas("c1","c1",800,700); 
                hist1->Draw();

        TCanvas *c2 = new TCanvas("c2","c2",800,700); 
                hist2->Draw();

//        TCanvas *c3 = new TCanvas("c3","c3",800,700); 
//                hist2-hist1->Draw();
}

