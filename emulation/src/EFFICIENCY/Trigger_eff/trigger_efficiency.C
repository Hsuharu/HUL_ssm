// emuration macro
// 2017/8/25(Fri)
// Suharu
// Finalt Change 2017/09/29
//

void trigger_efficiency(){
	gBenchmark->Start("trigger_efficiency");
	TFile *file[13];
	TTree *tree[13];
	TString fout1[13];
	TCanvas *c[13];
	TCanvas *c14;
	TH1D *hist[13][12];
	TRandom3 tran(std::time(0));

	double ms_time[13];
	double pre_ms_time[13];
	double delta_t[13];
	double ch_time[13][12];
	double trigger[13];
	double entries1[13];
	double entries2[13];
	//  double efficiency1[10][13];
  int loop = 10;
  double d_loop = 10;
  double efficiency[10][13];
  double eff[13];
	double efficiency1[13];
	double count[13];
	double sum[13];
	double average[13];
	double number_of_bin[13];
	int busy = 60; //micro sec
	double  busy_ms  = 0.060; //ms 


	int color[]={1,2,7};
	int n[13];
	double max_bin[13]; 
	double max_value[13];
	int entries[13];

	//  TFile *file = new TFile("../../../rootfile/BH1_1M_cluster.root");
	///  TFile *file = new TFile("../../../rootfile/BH1_20M_cluster.root");


	pre_ms_time[0] = 0;
	for(int i=0; i<13; ++i){
		if(i==0){
			file[0] = new TFile("../../../rootfile/BH1_1M_cluster.root");
		}else{
			file[i] = new TFile(Form("../../../rootfile/BH1_%dM_cluster.root",2*i));
		} 
		tree[i] = (TTree*)file[i]->Get("tree");

		tree[i]->SetBranchAddress("ms_time",&ms_time[i]);
		tree[i]->SetBranchAddress("BH1_ch",&ch_time[i][0]);

		if(i==0){
			hist[i][0] = new TH1D(Form("BH1_or_%dM",i+1),"",301000,-10,3000);
			hist[i][1] = new TH1D(Form("BH1_or_%dM_Trigger(1/10000)",i+1),"",301000,-10,3000);
			hist[i][2] = new TH1D(Form("BH1_or_%dM_Trigger&mask(%dmicros)",i+1,busy),"",301000,-10,3000);
			hist[i][3] = new TH1D(Form("BH1_or_%dM_delta_t(%dmicros)",i+1,busy),"",101000,-10,1000);
		}else{
			hist[i][0] = new TH1D(Form("BH1_or_%dM",i*2),"",301000,-10,3000);
			hist[i][1] = new TH1D(Form("BH1_or_%dM_Trigger(1/10000)",i*2),"",301000,-10,3000);
			hist[i][2] = new TH1D(Form("BH1_or_%dM_Trigger&mask(%dmicros)",i*2,busy),"",301000,-10,3000);
			hist[i][3] = new TH1D(Form("BH1_or_%dM_delta_t(%dmicros)",i*2,busy),"",2500,0,25);
		}


		n[i] = tree[i]->GetEntries();

		for(int s=0; s<loop; ++s){
			pre_ms_time[i] = 0;
			hist[i][0]->Reset();
			hist[i][1]->Reset();
			hist[i][2]->Reset();
			hist[i][3]->Reset();

			for(int j=0; j<n[i]; ++j){
				tree[i]->GetEntry(j);
				if(ms_time[i]>0){
					hist[i][0]->Fill(ms_time[i]);
					//Trigger ----------------------
					trigger[i] = tran.Rndm(); 
					if(trigger[i]>0.9999){
						hist[i][1]->Fill(ms_time[i]);
						delta_t[i] = ms_time[i] - pre_ms_time[i];
						hist[i][3]->Fill(delta_t[i]);
						//                                delta_t2 = ms_time - pre2_ms_time;
						if(delta_t[i]>busy_ms){ 
							hist[i][2]->Fill(ms_time[i]);
						}
						if(delta_t[i]<busy_ms){ 
							continue;
						}
						pre_ms_time[i] = ms_time[i];
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

			// Draw -------------------------------------------------------------------
			//        c[i] = new TCanvas(Form("c%d",i+1),Form("c%d",i+1),1600,900);
			////        c[i]->Divide(2,1);
			//        max_bin[i] = hist[i][0]->GetMaximumBin();
			//        max_value[i] = hist[i][0]->GetBinContent(max_bin[i]);
			//
			////        c[i]->cd(1);
			//        for(int j=0; j<3; ++j){
			//              hist[i][j]->SetLineColor(color[j]);
			//              if(j==1){
			//                      hist[i][j]->Scale(max_value[i]/10,"");
			//              }
			//              if(j==2){
			//                      hist[i][j]->Scale(max_value[i]/10,"");
			//              }
			//              hist[i][j]->GetXaxis()->SetTitle("[ms]");
			//              hist[i][j]->GetYaxis()->SetTitleOffset(1.2);
			//              hist[i][j]->GetYaxis()->SetTitle("[counts/10micro sec]");
			//              hist[i][j]->Draw("hist same");
			//        }
			//        
			//
			//        if(i==0){
			////                 fout1[i]= (Form("../DAT/Efficiency_%dM.dat",i+1));
			//                 c[i]->Print(Form("./%d/Trigger_Efficiency_1M_%d.pdf",busy,busy));
			//        }else{
			////                 fout1[i]= (Form("../DAT/Efficiency_%dM.dat",2*i));
			//                 c[i]->Print(Form("./%d/Trigger_Efficiency_%dM_%d.pdf",busy,2*i,busy));
			//        }
			//
			entries[i] = hist[i][0]->GetEntries(); 
		}
		efficiency1[i] = eff[i]/d_loop;
		cout << efficiency1[i] << "" << endl;
	}
	//
	//        c14 = new TCanvas("c14","c14",1600,900);
	//        c14->Divide(5,3);
	//  for(int i=0; i<13;i++){
	//        c14->cd(i+1);
	//              hist[i][3]->GetXaxis()->SetTitle("[ms]");
	//              hist[i][3]->GetYaxis()->SetTitleOffset(1.2);
	//              hist[i][3]->GetYaxis()->SetTitle("counts");
	//              hist[i][3]->Draw();
	//  }

	// file.dat out --------------------------------------------------------------        
	fout1[0] = (Form("../DAT/%d/Efficiency_%d.dat",busy,busy        ));
	fout1[1] = (Form("../DAT/%d/entries_%d.dat",busy,busy           ));
	fout1[2] = (Form("../DAT/%d/trigger_entries_%d.dat",busy,busy   ));
	fout1[3] = (Form("../DAT/%d/alltrigger_entries_%d.dat",busy,busy));
	fout1[4] = (Form("../DAT/%d/average_%d.dat",busy,busy           ));
	ofstream fout_1(fout1[0].Data());
	ofstream fout_2(fout1[1].Data());
	ofstream fout_3(fout1[2].Data());
	ofstream fout_4(fout1[3].Data());
	ofstream fout_5(fout1[4].Data());
	for(int i=0;i<13;++i){
		fout_1 << efficiency1[i] << endl;
		fout_2 << entries[i] << endl;
		fout_3 << entries2[i] << endl;
		fout_4 << entries1[i] << endl;
		fout_5 << average[i] << endl;

	}  

	gBenchmark->Show("trigger_efficiency");
}
