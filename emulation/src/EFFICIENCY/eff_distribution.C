void eff_distribution(){

  int eff_i = 0;
  double eff;
  double efficiency[5][13];
  double entries[13];
  double entries_M[13];
  double trigger_entries[13];
  double alltrigger_entries[13];
  double average[13];
  int busy = 0;

busy = 30;
  ifstream ifs0(Form("./DAT/%d/entries.dat",busy));  
//  ifstream ifs1("./DAT/entries_110.dat");  
  while(ifs0 >> eff)
    {
        entries[eff_i] = eff;
        entries_M[eff_i] = entries[eff_i]/1000000;
        eff_i++;
    }

        eff_i=0;
//  ifstream ifs1(Form("./DAT/%d/Efficiency_%d.dat",busy,busy));  
  ifstream ifs1(Form("./DAT/%d/Efficiency.dat",busy));  
  while(ifs1 >> eff)
    {
        efficiency[0][eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

  ifstream ifs2(Form("./DAT/%d/trigger_entries.dat",busy));  
//  ifstream ifs3("./DAT/alltrigger_entries_110.dat");  
  while(ifs2 >> eff)
    {
        trigger_entries[eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

  ifstream ifs3(Form("./DAT/%d/alltrigger_entries.dat",busy));  
//  ifstream ifs3("./DAT/alltrigger_entries_110.dat");  
  while(ifs3 >> eff)
    {
        alltrigger_entries[eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

  ifstream ifs4(Form("./DAT/%d/average.dat",busy));  
//  ifstream ifs4("./DAT/average_110.dat");  
  while(ifs4 >> eff)
    {
        average[eff_i] = exp(-3*eff);
//        average[eff_i] = exp(-11*eff);
        eff_i++;
    }

  int number = 13;//Number of channel
  int  marker[] = {3,2,27,4,5,20,21,22,23,25,26};

// TGraph---------------------------------------------------------------------
  TGraph *graph[4];
//  for(int i=0; i<11; ++i){
         graph[0] = new TGraph(number,&(entries_M[0]),&(efficiency[0][0]));
         graph[1] = new TGraph(number,&(entries_M[0]),&(trigger_entries[0]));
         graph[2] = new TGraph(number,&(entries_M[0]),&(alltrigger_entries[0]));
         graph[3] = new TGraph(number,&(entries_M[0]),&(average[0]));
//  }

// TGraph---------------------------------------------------------------------
  TF1 *poi = new TF1("poi","exp(-3*[0]*x)",0,30);
  poi->SetParameter(0,0.001);
// TCanvas--------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
//        c1->DrawFrame(0,0.8,22,1,"Efficiency");

// Frame ---------------------------------------------------------------------
  TH1 *frame1=gPad->DrawFrame(0,0.95,30,1.00,"DAQ Efficiency");      
  gPad->SetGrid();
  frame1->GetXaxis()->SetTitle("Entries(M counts)");
  frame1->GetYaxis()->SetTitleOffset(1.2);
  frame1->GetYaxis()->SetTitle(Form("Efficiency(musk=%dmicros)",busy));

// Legend --------------------------------------------------------------------
  TLegend *legend = new TLegend(0.7,0.8,0.9,0.9);
          
// Draw ----------------------------------------------------------------------
        frame1->Draw();
        legend->AddEntry(graph[3],"Poisson","p");
        legend->AddEntry(graph[0],Form("%dmicrosec",busy),"p");
        legend->Draw();
        graph[0]->SetMarkerStyle(20);
        graph[3]->SetMarkerStyle(2);
        graph[3]->Fit("poi");
        graph[0]->Draw("p");
        graph[3]->Draw("p");
//        poi->Draw("same");

//  for(int i=0; i<11; ++i){
//         graph[i]->SetMarkerStyle(marker[i]);
//         graph[i]->Draw("p");
//  }

//  int color[]={1,2,7};
//  TCanvas *c2 = new TCanvas("c2","c2",800,700);
//  TH1 *frame2=gPad->DrawFrame(0,0,30,2700,"Trigger entries");      
//  gPad->SetGrid();
//  frame2->GetXaxis()->SetTitle("Entries(M counts)");
//  frame2->GetYaxis()->SetTitleOffset(1.2);
//  frame2->GetYaxis()->SetTitle(Form("Trigger counts(musk=%dmicros)",busy));
////  frame2->GetYaxis()->SetTitle("Trigger counts(musk=110micros)");
//  frame2->Draw();
//  graph[1]->SetMarkerStyle(20);
//  graph[1]->SetMarkerColor(4);
//  graph[2]->SetMarkerStyle(20);
//  graph[2]->SetMarkerColor(2);
//  graph[1]->Draw("p");
//  graph[2]->Draw("p");

//  c2->Print(Form("Trigger_Entries_%d.pdf",busy));
  c1->Print(Form("poisson_Efficiency_Distribution_%d.pdf",busy));
 // c2->Print("Trigger_Entries_110.pdf");
  
}
