void M_par_spill() 
{
  int ratio_i;
  int ave_i;
  int max_i;
  char check[256];
  double max;
  double ave;
  double rat;
  double maximum[2][11];
  double average[2][11];
  double ratio[2][11];

  ifstream ifs0("./maximum_1M_clusterkai.dat");  
  while(ifs0.getline(check,256))
    {
      stringstream st0;
      st0<<check;
      if(strlen(check)==0) continue;
	
      else
       {
	      st0 >> max;
        maximum[0][max_i] = max;
        max_i++;
       }
      }

  ifstream ifs1("./average_1M_clusterkai.dat");  
  while(ifs1.getline(check,256))
    {
      stringstream st1;
      st1<<check;
      if(strlen(check)==0) continue;
	
      else
       {
	      st1 >> ave;
        average[0][ave_i] = ave;
        ave_i++;
       }
      }

  ifstream ifs2("./ratio_1M_clusterkai.dat");  
  while(ifs2.getline(check,256))
    {
      stringstream st2;
      st2<<check;
      if(strlen(check)==0) continue;
	
      else
       {
	      st2 >> rat;
        ratio[0][ratio_i] = rat;
        ratio_i++;
       }
      }
  ratio_i = 0;
  ave_i = 0;
  max_i = 0;
  ifstream ifs3("./maximum_20M_clusterkai.dat");  
  while(ifs3.getline(check,256))
    {
      stringstream st3;
      st3<<check;
      if(strlen(check)==0) continue;
	
      else
       {
	      st3 >> max;
        maximum[1][max_i] = max;
        max_i++;
       }
      }

  ifstream ifs4("./average_20M_clusterkai.dat");  
  while(ifs4.getline(check,256))
    {
      stringstream st4;
      st4<<check;
      if(strlen(check)==0) continue;
	
      else
       {
	      st4 >> ave;
        average[1][ave_i] = ave;
        ave_i++;
       }
      }

  ifstream ifs5("./ratio_20M_clusterkai.dat");  
  while(ifs5.getline(check,256))
    {
      stringstream st5;
      st5<<check;
      if(strlen(check)==0) continue;
	
      else
       {
	      st5 >> rat;
        ratio[1][ratio_i] = rat;
        ratio_i++;
       }
      }

  double ch[11][2];    

  for(int i=0; i<2;i++){
        for(int j=0; j<11; ++j){
                ch[j][i] = ratio[i][j];
        }
  }

  int number = 2;//Number of channel
  double M_spill[] = {1,20};
  TGraph *hist[11];
  for(int i=0; i<11; ++i){
          hist[i] = new TGraph(number,M_spill,&ch[i][0]);
  }
//          hist[ 0] = new TGraph(number,M_spill,&ch[0][0]);
//          hist[ 1] = new TGraph(number,M_spill,&ch[1][0]);
//          hist[ 2] = new TGraph(number,M_spill,&ch[2][0]);
//          hist[ 3] = new TGraph(number,M_spill,&ch[3][0]);
//          hist[ 4] = new TGraph(number,M_spill,&ch[4][0]);
//          hist[ 5] = new TGraph(number,M_spill,&ch[5][0]);
//          hist[ 6] = new TGraph(number,M_spill,&ch[6][0]);
//          hist[ 7] = new TGraph(number,M_spill,&ch[7][0]);
//          hist[ 8] = new TGraph(number,M_spill,&ch[8][0]);
//          hist[ 9] = new TGraph(number,M_spill,&ch[9][0]);
//          hist[10] = new TGraph(number,M_spill,&ch[10][0]);
  
  TCanvas *c1 = new TCanvas("c1","c1",800,700);
  hist[0]->Draw();
  for(int i=1; i<11; ++i){
          hist[i]->Draw("sames");
  }

}

