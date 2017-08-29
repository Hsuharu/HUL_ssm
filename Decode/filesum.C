void histsum(){

TChain chain("h1");
TString fname;

for(Int_t i = 0;i  < 10;i++){
  fname = "root/file";fname += i;fname += ".root";
  chain.Add(fname);
}

chain.Merge("combined.root");

}

