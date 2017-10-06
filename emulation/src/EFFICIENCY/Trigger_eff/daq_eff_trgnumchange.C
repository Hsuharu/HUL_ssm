// emuration macro
// 2017/10/6(Fri)
// Suharu
// Final Change 
//

void daq_eff_trgnumchange(){
        gBenchmark->Start("daq_eff_trgnumchange");
        TFile *file;
        TTree *tree;
        TString fout1[4];
        TCanvas *c[4];
        TCanvas *c14;
        TH1D *hist[4][12];
        TRandom3 tran(std::time(0));

        double ms_time;
        double pre_ms_time;
        double delta_t[4];
        //  double ch_time[11];
        double trigger[4];
        double entries1[4];
        double entries2[4];
        //  double efficiency1[10][13];
        double efficiency[10][4];
        double eff[10];
        double efficiency1[4];
        double count[4];
        double sum[4];
        double average[4];
        double number_of_bin[4];
        int busy = 30; //micro sec
        double  busy_ms  = 0.030; //ms 


        int color[]={1,2,7};
        int n;
        double max_bin[4]; 
        double max_value[4];
        int entries[4];

        //  TFile *file = new TFile("../../../rootfile/BH1_1M_cluster.root");
        ///  TFile *file = new TFile("../../../rootfile/BH1_20M_cluster.root");


        file = new TFile(Form("../../../rootfile/BH1_%dM_cluster.root",18));
        tree = (TTree*)file->Get("tree");

        tree->SetBranchAddress("ms_time",&ms_time);
        //   tree->SetBranchAddress("BH1_ch",&ch_time[0]);


        n = tree->GetEntries();

        for(int i=0; i<4; ++i){
                hist[i][0] = new TH1D(Form("BH1_or_%dM_%d",18,i+1),"",301000,-10,3000);
                hist[i][1] = new TH1D(Form("BH1_or_%dM_Trigger(1/%d)",18,2500*(i+1)),"",301000,-10,3000);
                hist[i][2] = new TH1D(Form("BH1_or_%dM_Trigger(1/%d)&mask(%dmicros)",18,2500*(i+1),busy),"",301000,-10,3000);
                //hist[i][3] = new TH1D(Form("BH1_or_%dM_delta_t(1/%d_%dmicros)",18,2500*(i+1),busy),"",2500,0,25);

                for(int s=0; s<10; ++s){
                        pre_ms_time = 0;
                        hist[i][0]->Reset();
                        hist[i][1]->Reset();
                        hist[i][2]->Reset();

                        for(int j=0; j<n; ++j){
                                tree->GetEntry(j);
                                if(ms_time>0){
                                        hist[i][0]->Fill(ms_time);
                                        //Trigger ----------------------
                                        trigger[i] = tran.Rndm(); 
                                        if(trigger[i]<0.0001*(i+1)){
                                                hist[i][1]->Fill(ms_time);
                                                delta_t[i] = ms_time - pre_ms_time;
                                                //hist[i][3]->Fill(delta_t[i]);
                                                //delta_t2 = ms_time - pre2_ms_time;
                                                if(delta_t[i]>busy_ms){ 
                                                        hist[i][2]->Fill(ms_time);
                                                }
                                                if(delta_t[i]<busy_ms){ 
                                                        continue;
                                                }
                                                pre_ms_time = ms_time;
                                        }
                                }
                        }

                        // Calculation ---------------------------------------------------------------
                        count[i]=0;
                        sum[i] = 0;
                        number_of_bin[i]=0;

                        for(int j=0; j<200000; ++j){
                                count[i] = hist[i][2]->GetBinContent(j+60000);
                                sum[i] = sum[i] + count[i];
                                ++number_of_bin[i];
                        }

                        average[i] = sum[i] / number_of_bin[i];

                        entries1[i] = hist[i][1]->GetEntries();
                        entries2[i] = hist[i][2]->GetEntries();
                        efficiency[s][i] = entries2[i]/entries1[i];
                        eff[i] = efficiency[s][i] + eff[i];
                        cout << efficiency[s][i] << "" << endl;


                        //c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),1600,900);
                        //max_bin[i] = hist[i][0]->GetMaximumBin();
                        //max_value[i] = hist[i][0]->GetBinContent(max_bin[i]);
                        //
                        //for(int j=0; j<3; ++j){
                        //      hist[i][j]->SetLineColor(color[j]);
                        //      if(j==1){
                        //              hist[i][j]->Scale(max_value[i]/10,"");
                        //      }
                        //      if(j==2){
                        //              hist[i][j]->Scale(max_value[i]/10,"");
                        //      }
                        //      hist[i][j]->GetXaxis()->SetTitle("[ms]");
                        //      hist[i][j]->GetYaxis()->SetTitleOffset(1.2);
                        //      hist[i][j]->GetYaxis()->SetTitle("[counts/10micro sec]");
                        //      hist[i][j]->Draw("hist same");
                        //}
//
//
//                        c[i]->Print(Form("./%d/DAQ_Efficiency_%dM_trgnum%dk.pdf",busy,18,2*(i+1)));

                        entries[i] = hist[i][0]->GetEntries(); 
                }
                efficiency1[i] = eff[i]/10;
                cout << efficiency1[i] << "" << endl;
        }

        for(int i=0; i<4;i++){
                c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),1600,900);
                max_bin[i] = hist[i][0]->GetMaximumBin();
                max_value[i] = hist[i][0]->GetBinContent(max_bin[i]);

                for(int j=0; j<3; ++j){
                        hist[i][j]->SetLineColor(color[j]);
                        if(j==1){
                                hist[i][j]->Scale(max_value[i]/10,"");
                        }
                        if(j==2){
                                hist[i][j]->Scale(max_value[i]/10,"");
                        }
                        hist[i][j]->GetXaxis()->SetTitle("[ms]");
                        hist[i][j]->GetYaxis()->SetTitleOffset(1.2);
                        hist[i][j]->GetYaxis()->SetTitle("[counts/10micro sec]");
                        hist[i][j]->Draw("hist same");
                }

        }

        // file.dat out --------------------------------------------------------------        
        fout1[0] = (Form("../DAT/%d/daq_Efficiency_%d.dat",busy,busy        ));
        fout1[1] = (Form("../DAT/%d/daq_entries_%d.dat",busy,busy           ));
        fout1[2] = (Form("../DAT/%d/daq_trigger_entries_%d.dat",busy,busy   ));
        fout1[3] = (Form("../DAT/%d/daq_alltrigger_entries_%d.dat",busy,busy));
        fout1[4] = (Form("../DAT/%d/daq_average_%d.dat",busy,busy           ));
        ofstream fout_1(fout1[0].Data());
        ofstream fout_2(fout1[1].Data());
        ofstream fout_3(fout1[2].Data());
        ofstream fout_4(fout1[3].Data());
        ofstream fout_5(fout1[4].Data());
        for(int i=0;i<4;++i){
                fout_1 << efficiency1[i] << endl;
                fout_2 << entries[i] << endl;
                fout_3 << entries2[i] << endl;
                fout_4 << entries1[i] << endl;
                fout_5 << average[i] << endl;

        }

        gBenchmark->Show("daq_eff_trgnumchange");
}
