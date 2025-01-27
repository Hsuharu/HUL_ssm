void busychange_eff_distribution(){

  int eff_i = 0;
  double eff;
  double efficiency[5][13];
  double entries[13];
  double entries_M[13];
  double entries_k[13];
  double trigger_entries[13];
  double alltrigger_entries[13];
  double average[13];
  int busy = 0;

busy = 30;
  ifstream ifs0(Form("./DAT/%d/entries_%d.dat",busy,busy));  
//  ifstream ifs1("./DAT/entries_110.dat");  
  while(ifs0 >> eff)
    {
        entries[eff_i] = eff;
        entries_M[eff_i] = entries[eff_i]/1000000;
        eff_i++;
    }

        eff_i=0;

  ifstream ifs10(Form("./DAT/%d/alltrigger_entries_%d.dat",busy,busy));  
  while(ifs10 >> eff)
    {
        entries[eff_i] = eff;
        entries_k[eff_i] = entries[eff_i]/1000;
        eff_i++;
    }

        eff_i=0;
//  ifstream ifs1(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  ifstream ifs1(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  while(ifs1 >> eff)
    {
        efficiency[0][eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

busy = 40;
  ifstream ifs2(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  while(ifs2 >> eff)
    {
        efficiency[1][eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

busy = 50;
  ifstream ifs3(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  while(ifs3 >> eff)
    {
        efficiency[2][eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

busy = 60;
  ifstream ifs4(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  while(ifs4 >> eff)
    {
        efficiency[3][eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

busy = 70;
  ifstream ifs5(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  while(ifs5 >> eff)
    {
        efficiency[4][eff_i] = eff;
        eff_i++;
    }


  int number = 13;//Number of channel

// TGraph---------------------------------------------------------------------
  TGraph *graph[10];
//  for(int i=0; i<11; ++i){
         graph[0] = new TGraph(number,&(entries_M[0]),&(efficiency[0][0]));
         graph[1] = new TGraph(number,&(entries_M[0]),&(efficiency[1][0]));
         graph[2] = new TGraph(number,&(entries_M[0]),&(efficiency[2][0]));
         graph[3] = new TGraph(number,&(entries_M[0]),&(efficiency[3][0]));
         graph[4] = new TGraph(number,&(entries_M[0]),&(efficiency[4][0]));
         graph[5] = new TGraph(number,&(entries_k[0]),&(efficiency[0][0]));
         graph[6] = new TGraph(number,&(entries_k[0]),&(efficiency[1][0]));
         graph[7] = new TGraph(number,&(entries_k[0]),&(efficiency[2][0]));
         graph[8] = new TGraph(number,&(entries_k[0]),&(efficiency[3][0]));
         graph[9] = new TGraph(number,&(entries_k[0]),&(efficiency[4][0]));
//  }

// TCanvas--------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
//        c1->DrawFrame(0,0.8,22,1,"Efficiency");

// Frame ---------------------------------------------------------------------
  TH1 *frame1=gPad->DrawFrame(0,0.88,30,1.00,"DAQ Efficiency");      
  gPad->SetGrid();
  frame1->GetXaxis()->SetTitle("Entries(M counts)");
  frame1->GetYaxis()->SetTitleOffset(1.2);
  frame1->GetYaxis()->SetTitle("Efficiency");

// Legend --------------------------------------------------------------------
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
          
        frame1->Draw();
        for(int i=0 ; i<5; i++){
        graph[i]->SetMarkerStyle(20);
        graph[i]->SetLineStyle(2);
        if(i<4){
                graph[i]->SetMarkerColor(i+1);
                graph[i]->SetLineColor(i+1);
        }else{
                graph[i]->SetMarkerColor(kMagenta);
                graph[i]->SetLineColor(kMagenta);
        }
        legend->AddEntry(graph[i],Form("%dmicrosec",30+i*10),"p");
        legend->Draw();
        graph[i]->Draw("lp");
         }

// TCanvas--------------------------------------------------------------------
  TCanvas *c2 = new TCanvas("c2","c2",800,700);

// Frame ---------------------------------------------------------------------
  TH1 *frame2=gPad->DrawFrame(0,0.88,3,1.00,"DAQ Efficiency ver.kcount");      
  gPad->SetGrid();
  frame2->GetXaxis()->SetTitle("Entries(k counts)");
  frame2->GetYaxis()->SetTitleOffset(1.2);
  frame2->GetYaxis()->SetTitle("Efficiency");

// Legend --------------------------------------------------------------------
  TLegend *legend2 = new TLegend(0.7,0.7,0.9,0.9);
          
        frame2->Draw();
        for(int i=5 ; i<10; i++){
        graph[i]->SetMarkerStyle(21);
        graph[i]->SetLineStyle(2);
        if(i<9){
                graph[i]->SetMarkerColor(i-4);
                graph[i]->SetLineColor(i-4);
        }else{
                graph[i]->SetMarkerColor(kMagenta);
                graph[i]->SetLineColor(kMagenta);
        }
        legend2->AddEntry(graph[i],Form("%dmicrosec",30+(i-5)*10),"p");
        legend2->Draw();
        graph[i]->Draw("lp");
         }


  c2->Print("Efficiency_Distribution_busychange_verk.pdf");
  
}
