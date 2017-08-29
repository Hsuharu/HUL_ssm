void eff_distribution(){

  int eff_i = 0;
  double eff;
  double efficiency[1][2];


  ifstream ifs0("./DAT/Efficiency_1M.dat");  
  while(ifs0 >> eff)
    {
        efficiency[eff_i][0] = eff;
        eff_i++;
    }

  eff_i = 0;
  ifstream ifs1("./DAT/Efficiency_20M.dat");  
  while(ifs1 >> eff)
    {
        efficiency[eff_i][1] = eff;
        eff_i++;
    }



  int number = 2;//Number of channel
  int  marker[] = {3,2,27,4,5,20,21,22,23,25,26};
  double spill[] = {1,20};

// TGraoh---------------------------------------------------------------------
  TGraph *graph;
//  for(int i=0; i<11; ++i){
         graph = new TGraph(number,&(spill[0]),&(efficiency[0][0]));
//  }

// TCanvas--------------------------------------------------------------------
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
//        c1->DrawFrame(0,0.8,22,1,"Efficiency");

// Frame ---------------------------------------------------------------------
  TH1 *frame=gPad->DrawFrame(0,0.8,22,1.01,"Efficiency");      
  gPad->SetGrid();
  frame->GetXaxis()->SetTitle("M/spill");
  frame->GetYaxis()->SetTitleOffset(1.2);
  frame->GetYaxis()->SetTitle("Efficiency(musk=30micros)");

// Legend --------------------------------------------------------------------
  TLegend *legend = new TLegend(0.7,0.8,0.9,0.9);
          
        frame->Draw();
        graph->SetMarkerStyle(20);
        graph->SetMarkerColor(marker[1]);
        legend->AddEntry(graph,"30microsec","p");
        legend->Draw();
        graph->Draw("p");
//  for(int i=0; i<11; ++i){
//         graph[i]->SetMarkerStyle(marker[i]);
//         graph[i]->Draw("p");
//  }
  c1->Print("Efficiency_Distribution.pdf");
}
