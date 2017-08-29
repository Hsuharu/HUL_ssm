#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include<functional>
#include<algorithm>
#include"gzfilter.hh"

#include"TFile.h"
#include"TH1.h"
#include"TCanvas.h"
#include"TAxis.h"
#include"TString.h"

#include"analyzer.hh"


/// mask 用　///
// 関数内部でのみ使用可能
static const unsigned int frame_end = 0xfe00ffff;
static const unsigned int spill_end = 0x4e00ffff;

static const unsigned int data_mask = 0xffff;

static const unsigned int ch_mask   = 0xf;
static const unsigned int ch_shift  = 16;

// Dataを詰める用　//
struct dataCont{
  unsigned int data;
  unsigned int time;
  unsigned int ch;
};

// bool型＝
bool TimeCompA(const dataCont& obj1,
	       const dataCont& obj2)
{
  return obj1.time < obj2.time;
}

void decode(unsigned int data, dataCont& obj);
void transform_timestamp(unsigned int data, unsigned int &stamp);

void SetTitle(TH1* hist, const char* xtitle, const char* ytitle);

// Instance -------------------------------------------------------------
int
main(int argc, char** argv)
{
  if(argc == 1){
    std::cout << "#D : Usage\n";
    std::cout << " analyzer [data path] [rootfile path]" << std::endl;;
  }

  std::string infile_path  = argv[1];
  std::string outfile_path = argv[2];

  std::string infile_name  = infile_path  + "/ssm.dat.gz";
  std::string outfile_name = outfile_path + "/analys.root";

  std::ifstream ifs_org(infile_name.c_str());

  if(!ifs_org.is_open()){
    std::cerr << "#E: no such file " << infile_name << std::endl;
    return -1;
  }

  h_Utility::igzfilter ifs(ifs_org);

  std::cout << "#D: Start analysis " << std::endl;

  // ROOT file create
  TFile fout(outfile_name.c_str(), "recreate");


  std::string basename[] = {"Waveform (count)", "Waveform (rate)", "Time interval", "Time interval (1#mus)"};
  std::string range[] = {"", " 2000ms range",
			 " 500ms range-1", " 500ms range-2", " 500ms range-3", " 500ms range-4"};

  std::string xtitle[] = {"Time from flattop [ms]", "Time from flattop [ms]",
			  "Time Interval [#mus]", "Time interval [ns]"};
  std::string ytitle[] = {Form("Counts/%0.1f#mus", bin_size), "MHz",
			  "Counts", "Counts"};

  int n_bin[6][4] = {{nbin_total, nbin_total, nbin_tint, nbin_tint_1u},
		     {nbin_spill, nbin_spill, nbin_tint, nbin_tint_1u},
		     {nbin_div,   nbin_div,   nbin_tint, nbin_tint_1u},
		     {nbin_div,   nbin_div,   nbin_tint, nbin_tint_1u},
		     {nbin_div,   nbin_div,   nbin_tint, nbin_tint_1u},
		     {nbin_div,   nbin_div,   nbin_tint, nbin_tint_1u}
  };

  int x_min[6][4] = {{xmin_total,      xmin_total,       xmin_tint, xmin_tint_1u},
		     {xmin_spill,      xmin_spill,       xmin_tint, xmin_tint_1u},
		     {xmin_spill+0,    xmin_spill+0,     xmin_tint, xmin_tint_1u},
		     {xmin_spill+500,  xmin_spill+500,   xmin_tint, xmin_tint_1u},
		     {xmin_spill+1000, xmin_spill+1000,  xmin_tint, xmin_tint_1u},
		     {xmin_spill+1500, xmin_spill+1500,  xmin_tint, xmin_tint_1u}
  };

  int x_max[6][4] = {{xmax_total,      xmax_total,     xmax_tint, xmax_tint_1u},
		     {xmax_spill,      xmax_spill,     xmax_tint, xmax_tint_1u},
		     {xmin_spill+div_size+0,    xmin_spill+div_size+0,     xmax_tint, xmax_tint_1u},
		     {xmin_spill+div_size+500,  xmin_spill+div_size+500,   xmax_tint, xmax_tint_1u},
		     {xmin_spill+div_size+1000, xmin_spill+div_size+1000,  xmax_tint, xmax_tint_1u},
		     {xmin_spill+div_size+1500, xmin_spill+div_size+1500,  xmax_tint, xmax_tint_1u}
  };

  TH1D *hist[sizeHist];
  for(int i = 0; i<6; ++i){
    for(int j = 0; j<4; ++j){
      std::string tmpname = basename[j] + range[i];
      hist[4*i + j] = new TH1D(Form("h_%d_%d",i,j), tmpname.c_str(),
			       n_bin[i][j], x_min[i][j], x_max[i][j]
			 );
      SetTitle(hist[4*i+j], xtitle[j].c_str(), ytitle[j].c_str());
    }// for(j)
  }// for(i)

  // Decode/Analyze ----------------------------------------------------
  std::vector<dataCont> data_list;
  double prev_time = 0;
  while(!ifs.eof()){
    unsigned int data;
    ifs.read((char*)&data, sizeof(unsigned int ));

    if(data == spill_end) continue;

    dataCont tmp_data;
    decode(data, tmp_data);
    data_list.push_back(tmp_data);
    if(data != frame_end) continue;

    // frame end ---------------------------
    std::vector<dataCont>::iterator itr = data_list.begin();
    std::partial_sort(data_list.begin(), data_list.end()-1,
		      data_list.end(),
		      TimeCompA
		      );

    for(; itr!=data_list.end(); ++itr){
      bool flag_cluster = false;
      if((*itr).data != frame_end){
	dataCont& curr = *itr;
	dataCont& next = *(itr+1);

	if(true
	   && (next.time - curr.time) < 2
	   && (next.ch-1 == curr.ch || next.ch+1 == curr.ch)
	   ){
	  flag_cluster = true;
	}// if
      }// valid data

      unsigned int time;
      transform_timestamp((*itr).data, time);


      if(time != 0){
	double ms_time = time/ns_to_ms;
	hist[i_wf_count]->Fill(ms_time);

	double curr_time = (double)time;
	hist[i_tint]->Fill((curr_time - prev_time)/ns_to_us);
	hist[i_tint_1u]->Fill(curr_time - prev_time);

	if(xmin_spill < ms_time && ms_time < xmax_spill){
	  hist[i_wf2000_count]->Fill(ms_time);
	  hist[i_tint2000]->Fill((curr_time - prev_time)/ns_to_us);
	  hist[i_tint2000_1u]->Fill(curr_time - prev_time);

	  int index = (int)((ms_time - xmin_spill)/div_size);
	  hist[i_wf500_1_count + 4*index]->Fill(ms_time);
	  hist[i_tint500_1  +4*index]->Fill((curr_time - prev_time)/ns_to_us);
	  hist[i_tint500_1_1u +4*index]->Fill(curr_time - prev_time);
	}// spill

	prev_time = curr_time;
      }

      if(flag_cluster) ++itr;
    }// for(itr)

    data_list.clear();

  }// while

  // count to rate
  for(int i = 0; i<nbin_total; ++i){
    hist[i_wf_rate]->SetBinContent(i+1, hist[i_wf_count]->GetBinContent(i+1)*count_to_mhz);
    hist[i_wf2000_rate]->SetBinContent(i+1, hist[i_wf2000_count]->GetBinContent(i+1)*count_to_mhz);
    hist[i_wf500_1_rate]->SetBinContent(i+1, hist[i_wf500_1_count]->GetBinContent(i+1)*count_to_mhz);
    hist[i_wf500_2_rate]->SetBinContent(i+1, hist[i_wf500_2_count]->GetBinContent(i+1)*count_to_mhz);
    hist[i_wf500_3_rate]->SetBinContent(i+1, hist[i_wf500_3_count]->GetBinContent(i+1)*count_to_mhz);
    hist[i_wf500_4_rate]->SetBinContent(i+1, hist[i_wf500_4_count]->GetBinContent(i+1)*count_to_mhz);
  }

  double n_particle = hist[i_wf_count]->GetEntries()/1000000.; // M/spill
  std::cout << std::fixed << std::setprecision(2);
  std::cout << "n_particle "  << n_particle << " M/spill"<< std::endl;
  std::ofstream ofs("last_rate.txt");
  ofs << std::fixed << std::setprecision(2);
  ofs << "n_particle "  << n_particle << " M/spill"<< std::endl;
  ofs.close();

  fout.Write();
  fout.Close();

  std::cout << "#D: End of analysis" << std::endl;

  return 0;
}// main

// decode -------------------------------------------------------------------
void
decode(unsigned int data, dataCont& obj)
{
  unsigned int time_stamp = data & data_mask;  // dataが検出器のものかspillend等のものか判断するためにmask
  unsigned int channel    = (data >> ch_shift) & ch_mask; //dataのchについての情報があるところまでshiftして、chがわかるようにmaskする

  obj.data = data;         //structでできたobjにdataからの情報を入れる
  obj.time = time_stamp;
  obj.ch   = channel+1;

  if(data == frame_end) obj.ch = 99;
}

// transform_timestamp ------------------------------------------------------
void
transform_timestamp(unsigned int data, unsigned int &stamp)
{
  static int n_frame = 0;

  unsigned int time_stamp = 0x10000*n_frame*10 + (data & data_mask)*10;  // ns
  stamp = time_stamp;

  if(data == frame_end){
    ++n_frame;
    stamp = 0;
  }// frame_end

}// transform_timestamp


// SetTitle ------------------------------------------------------------------
void
SetTitle(TH1* hist, const char* xtitle, const char* ytitle)
{
  hist->GetXaxis()->SetTitle(xtitle);
  hist->GetXaxis()->CenterTitle();
  hist->GetYaxis()->SetTitle(ytitle);
  hist->GetYaxis()->CenterTitle();
}
