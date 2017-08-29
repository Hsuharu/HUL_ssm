void eff_distribution(){

  int eff_i = 0;
  double eff;
  double efficiency[13];
  double entries[13];
  double entries_M[13];
  double trigger_entries[13];
  double alltrigger_entries[13];

//  ifstream ifs0("./DAT/Efficiency.dat");  
  ifstream ifs0("./DAT/Efficiency_110.dat");  
  while(ifs0 >> eff)
    {
        efficiency[eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

//  ifstream ifs1("./DAT/entries.dat");  
  ifstream ifs1("./DAT/entries_110.dat");  
  while(ifs1 >> eff)
    {
        entries[eff_i] = eff;
        entries_M[eff_i] = entries[eff_i]/1000000;
        eff_i++;
    }

        eff_i=0;

//  ifstream ifs2("./DAT/trigger_entries.dat");  
  ifstream ifs2("./DAT/trigger_entries_110.dat");  
  while(ifs2 >> eff)
    {
        trigger_entries[eff_i] = eff;
        eff_i++;
    }

        eff_i=0;

//  ifstream ifs3("./DAT/alltrigger_entries.dat");  
  ifstream ifs3("./DAT/alltrigger_entries_110.dat");  
  while(ifs3 >> eff)
    {
        alltrigger_entries[eff_i] = eff;
        eff_i++;
    }

  int number = 13;//Number of channel
  int  marker[] = {3,2,27,4,5,20,21,22,23,25,26};

// TGraoh---------------------------------------------------------------------
  TGraph *graph[3];
//  for(int i=0; i<11; ++i){
         graph[0] = new TGraph(number,&(entries_M[0]),&(efficiency[0]));
         graph[1] = new TGraph(number,&(entries_M[0]),&(trigger_entries[0]));
         graph[2] = new TGraph(number,&(entries_M[0]),&(alltrigger_entries[0]));
//  }

// TCanvas--------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
//        c1->DrawFrame(0,0.8,22,1,"Efficiency");

// Frame ---------------------------------------------------------------------
  TH1 *frame1=gPad->DrawFrame(0,0.85,30,1.00,"Efficiency");      
  gPad->SetGrid();
  frame1->GetXaxis()->SetTitle("Entries(M counts)");
  frame1->GetYaxis()->SetTitleOffset(1.2);
//  frame1->GetYaxis()->SetTitle("Efficiency(musk=30micros)");
  frame1->GetYaxis()->SetTitle("Efficiency(musk=110micros)");

// Legend --------------------------------------------------------------------
  TLegend *legend = new TLegend(0.7,0.8,0.9,0.9);
          
        frame1->Draw();
        graph[0]->SetMarkerStyle(20);
        graph[0]->SetMarkerColor(1);
//        legend->AddEntry(graph[0],"30microsec","p");
        legend->AddEntry(graph[0],"110microsec","p");
        legend->Draw();
        graph[0]->Draw("p");

//  for(int i=0; i<11; ++i){
//         graph[i]->SetMarkerStyle(marker[i]);
//         graph[i]->Draw("p");
//  }

  int color[]={1,2,7};
  TCanvas *c2 = new TCanvas("c2","c2",800,700);
  TH1 *frame2=gPad->DrawFrame(0,0,30,2700,"Trigger entries");      
  gPad->SetGrid();
  frame2->GetXaxis()->SetTitle("Entries(M counts)");
  frame2->GetYaxis()->SetTitleOffset(1.2);
//  frame2->GetYaxis()->SetTitle("Trigger counts(musk=30micros)");
  frame2->GetYaxis()->SetTitle("Trigger counts(musk=110micros)");
  frame2->Draw();
  graph[1]->SetMarkerStyle(20);
  graph[1]->SetMarkerColor(4);
  graph[2]->SetMarkerStyle(20);
  graph[2]->SetMarkerColor(2);
  graph[1]->Draw("p");
  graph[2]->Draw("p");

//  c1->Print("Efficiency_Distribution_30.pdf");
//  c2->Print("Trigger_Entries_30.pdf");
  c1->Print("Efficiency_Distribution_110.pdf");
  c2->Print("Trigger_Entries_110.pdf");
  
}
