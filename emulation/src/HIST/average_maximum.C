void average_maximum() {

  int maximum_i = 0;
  int ave_i = 0;
  double rat;
  double ave;
//  double ratio[11][2];
//  double average[11][2];
  double maximum[11][13];
  double average[11][13];
 

//1M ----------------------------------------------
  ifstream ifs0("./DAT/maximum_1M_cluster.dat");  
  while(ifs0>>rat)
    {
        maximum[maximum_i][0] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//20M ----------------------------------------------
  ifstream ifs1("./DAT/maximum_20M_cluster.dat");  
  while(ifs1>>rat)
    {
        maximum[maximum_i][10] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//2M ----------------------------------------------
  ifstream ifs2("./DAT/maximum_2M_cluster.dat");  
  while(ifs2>>rat)
    {
        maximum[maximum_i][1] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//4M ----------------------------------------------
  ifstream ifs3("./DAT/maximum_4M_cluster.dat");  
  while(ifs3>>rat)
    {
        maximum[maximum_i][2] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//6M ----------------------------------------------
  ifstream ifs4("./DAT/maximum_6M_cluster.dat");  
  while(ifs4>>rat)
    {
        maximum[maximum_i][3] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//8M ----------------------------------------------
  ifstream ifs5("./DAT/maximum_8M_cluster.dat");  
  while(ifs5>>rat)
    {
        maximum[maximum_i][4] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//10M ----------------------------------------------
  ifstream ifs6("./DAT/maximum_10M_cluster.dat");  
  while(ifs6>>rat)
    {
        maximum[maximum_i][5] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//12M ----------------------------------------------
  ifstream ifs7("./DAT/maximum_12M_cluster.dat");  
  while(ifs7>>rat)
    {
        maximum[maximum_i][6] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//14M ----------------------------------------------
  ifstream ifs8("./DAT/maximum_14M_cluster.dat");  
  while(ifs8>>rat)
    {
        maximum[maximum_i][7] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//16M ----------------------------------------------
  ifstream ifs9("./DAT/maximum_16M_cluster.dat");  
  while(ifs9>>rat)
    {
        maximum[maximum_i][8] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//18M ----------------------------------------------
  ifstream ifs10("./DAT/maximum_18M_cluster.dat");  
  while(ifs10>>rat)
    {
        maximum[maximum_i][9] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//22M ----------------------------------------------
  ifstream ifs11("./DAT/maximum_22M_cluster.dat");  
  while(ifs11>>rat)
    {
        maximum[maximum_i][11] = rat;
        maximum_i++;
    }

    maximum_i = 0;

//24M ----------------------------------------------
  ifstream ifs12("./DAT/maximum_24M_cluster.dat");  
  while(ifs12>>rat)
    {
        maximum[maximum_i][12] = rat;
        maximum_i++;
    }

///***************** average ****************
//1M ----------------------------------------------
  ifstream ifs13("./DAT/average_1M_cluster.dat");  
  while(ifs13>>ave)
    {
        average[ave_i][0] = ave;
        ave_i++;
    }

    ave_i = 0;

//20M ----------------------------------------------
  ifstream ifs14("./DAT/average_20M_cluster.dat");  
  while(ifs14>>ave)
    {
        average[ave_i][10] = ave;
        ave_i++;
    }

    ave_i = 0;

//2M ----------------------------------------------
  ifstream ifs15("./DAT/average_2M_cluster.dat");  
  while(ifs15>>ave)
    {
        average[ave_i][1] = ave;
        ave_i++;
    }

    ave_i = 0;

//4M ----------------------------------------------
  ifstream ifs16("./DAT/average_4M_cluster.dat");  
  while(ifs16>>ave)
    {
        average[ave_i][2] = ave;
        ave_i++;
    }

    ave_i = 0;

//6M ----------------------------------------------
  ifstream ifs17("./DAT/average_6M_cluster.dat");  
  while(ifs17>>ave)
    {
        average[ave_i][3] = ave;
        ave_i++;
    }

    ave_i = 0;

//8M ----------------------------------------------
  ifstream ifs18("./DAT/average_8M_cluster.dat");  
  while(ifs18>>ave)
    {
        average[ave_i][4] = ave;
        ave_i++;
    }

    ave_i = 0;

//10M ----------------------------------------------
  ifstream ifs19("./DAT/average_10M_cluster.dat");  
  while(ifs19>>ave)
    {
        average[ave_i][5] = ave;
        ave_i++;
    }

    ave_i = 0;

//12M ----------------------------------------------
  ifstream ifs20("./DAT/average_12M_cluster.dat");  
  while(ifs20>>ave)
    {
        average[ave_i][6] = ave;
        ave_i++;
    }

    ave_i = 0;

//14M ----------------------------------------------
  ifstream ifs21("./DAT/average_14M_cluster.dat");  
  while(ifs21>>ave)
    {
        average[ave_i][7] = ave;
        ave_i++;
    }

    ave_i = 0;

//16M ----------------------------------------------
  ifstream ifs22("./DAT/average_16M_cluster.dat");  
  while(ifs22>>ave)
    {
        average[ave_i][8] = ave;
        ave_i++;
    }

    ave_i = 0;

//18M ----------------------------------------------
  ifstream ifs23("./DAT/average_18M_cluster.dat");  
  while(ifs23>>ave)
    {
        average[ave_i][9] = ave;
        ave_i++;
    }

    ave_i = 0;

//22M ----------------------------------------------
  ifstream ifs24("./DAT/average_22M_cluster.dat");  
  while(ifs24>>ave)
    {
        average[ave_i][11] = ave;
        ave_i++;
    }

    ave_i = 0;

//24M ----------------------------------------------
  ifstream ifs25("./DAT/average_24M_cluster.dat");  
  while(ifs25>>ave)
    {
        average[ave_i][12] = ave;
        ave_i++;
    }

//  int number = 2;//Number of channel
  int number = 13;//Number of channel
  int marker[] = {3,2,27,4,5,20,21,22,23,25,26};
  double spill[] = {1,2,4,6,8,10,12,14,16,18,20,22,24};
  TGraph *graph[11];
  TGraph *graph2[11];

  // Legend ---------------------------------------------------------------------
  TLegend *legend = new TLegend(0.905,0.55,0.975,0.9);
  
  for(int i=0; i<11; ++i){
         graph[i] = new TGraph(number,&(average[i][0]),&(maximum[i][0]));
         graph2[i] = new TGraph(number,&(spill[0]),&(maximum[i][0]));
  }

  TCanvas *c1 = new TCanvas("c1","c1",1600,900);
  TH1 *frame = gPad->DrawFrame(0,0,38,150,"Maximum by average");
          gPad->SetGrid();
          frame->GetXaxis()->SetTitle("Average[counts/10misrosec]");
          frame->GetYaxis()->SetTitleOffset(1.2);
          frame->GetYaxis()->SetTitle("Maximum[counts/10misrosec]");

  for(int i=0; i<11; ++i){
//         graph[i]->SetMarkerStyle(marker[i]);
         graph[i]->SetMarkerStyle(i+20);
//         graph[i]->SetMarkerColor(i+1);
         graph[i]->SetLineStyle(2);
//         graph[i]->SetLineColor(i+1);
         if(i==9){
                 graph[i]->SetMarkerColor(12);
                 graph[i]->SetLineColor(12);
         }
         legend->AddEntry(graph[i],Form("ch%d",i+1),"p");
         legend->Draw();
         graph[i]->Draw("p");
  }

  TLegend *legend2 = new TLegend(0.905,0.55,0.975,0.9);
  //  legend-> SetNColumns(2);
  

  TCanvas *c2 = new TCanvas("c2","c2",1600,900);

//Frame1 ----------------------------------------------------------------------
  TH1 *frame1;
          frame1 = gPad->DrawFrame(0,0,25,150,"Ratio");      
          gPad->SetGrid();
          frame1->GetXaxis()->SetTitle("M/spill");
          frame1->GetYaxis()->SetTitleOffset(1.2);
          frame1->GetYaxis()->SetTitle("Max [counts/10microsec]");
        
          for(int i=0; i<11; ++i){
//                        graph[i]->SetMarkerStyle(style[i]);
                        graph2[i]->SetMarkerStyle(i+20);
                        graph2[i]->SetMarkerColor(i+1);
                        graph2[i]->SetLineStyle(2);
                        graph2[i]->SetLineColor(i+1);
                        if(i==9){
                                graph2[i]->SetMarkerColor(12);
                                graph2[i]->SetLineColor(12);
                        }
                        legend2->AddEntry(graph[i],Form("ch%d",i+1),"p");
                        legend2->Draw();
                        graph2[i]->Draw("lp");
//                        graph[i]->Draw("p");
          }
  c1->Print("average_maximum.pdf");
  c2->Print("Mparspill_maximum.pdf");
}
