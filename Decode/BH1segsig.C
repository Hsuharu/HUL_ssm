//  mask 用　///
static const unsigned int frame_end = 0xfe00ffff;
static const unsigned int spill_end = 0x4e00ffff;

//  static const unsigned int data_mask = 0xffff;
static const unsigned int data_mask = 0xdd;

static const unsigned int ch_mask   = 0xf;
static const unsigned int ch_shift  = 16;

// Dataを詰める用　//
struct dataCont{
  unsigned int data;
  unsigned int time;
  unsigned int ch;
};

//  bool型
bool TimeCompA(const dataCont& obj1,
	       const dataCont& obj2)
{
  return obj1.time < obj2.time;
}


void decode(unsigned int data, dataCont& obj);
void transform_timestamp(unsigned int data, unsigned int &stamp);

//  BHisegsig ----------------------------------------------------------------
void BH1segsig(){

  fs = fstream("../Data/shot390825/ssm.dat",ios::binary | ios::out);

  // ROOT file create
  TFile fout(outfile_name.c_str(), "recreate");


  std::string basename[] = {"Waveform (count)", "Waveform (rate)", "Time interval", "Time interval (1#mus)"};
  std::string range[] = {"", " 2000ms range",
			 " 500ms range-1", " 500ms range-2", " 500ms range-3", " 500ms range-4"};

  std::string xtitle[] = {"Time from flattop [ms]", "Time from flattop [ms]",
			  "Time Interval [#mus]", "Time interval [ns]"};
  std::string ytitle[] = {Form("Counts/%0.1f#mus", bin_size), "MHz",
			  "Counts", "Counts"};

  int n_bin = 300000;
  int x_min = 0;
  int x_max = 3000;

  TH1D *hist[sizeHist];
      std::string tmpname = basename[0] + range[0];
      hist[0] = new TH1D(BH1_ch1), tmpname.c_str(),
			       n_bin, x_min, x_max);

}

//  decode -------------------------------------------------------------------
void
decode(unsigned int data, dataCont& obj)
{
  unsigned int time_stamp = data & data_mask;  // dataが検出器のものかspillend等のものか判断するためにmask
  unsigned int channel    = (data >> ch_shift) & ch_mask; //dataのchについての情報があるところまでshiftして、chがわかるようにmaskする

  obj.data = data;         //structでできたobjにdataからの情報を入れる
  obj.time = time_stamp;
  obj.ch   = channel+1;

  if(data == frame_end) obj.ch = 99;
} // decode

//  transform_timestamp ------------------------------------------------------
void
transform_timestamp(unsigned int data, unsigned int &stamp)
{
  static int n_frame = 0;

  unsigned int time_stamp = 0x10000*n_frame*10 + (data & data_mask)*10;  // ns
  stamp = time_stamp;

  if(data == frame_end){
    ++n_frame;
    stamp = 0;
  }//  frame_end

}//  transform_timestamp
