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

void decode(unsigned int data, dataCont& obj);
void transform_timestamp(unsigned int data, unsigned int &stamp);

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

// BH1_ch1--------------------------------------------------------------------
void BH1_ch1(){
  // Binary file open
  fstream ifs("../Data/shot390825/ssm.dat",ios::binary | ios::out);
  // ROOT file create
  TFile fout(outfile_name.c_str(), "recreate");
        
    ifs.read((char*)&data, sizeof(unsigned int ));
}
