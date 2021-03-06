#include "EveVisualizer.h"
#include "TApplication.h"
#include "VisualizationHelper.h"
#include "base/Vector3D.h"
#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "Data.h"
using Tomography::VisualizationHelper;
using Vec_t = Tracking::Vector3D<double>;
int main(int argc, char *argv[]) {
  TApplication *fApp = new TApplication("Test", NULL, NULL);
  Tomography::VisualizationHelper *v = new Tomography::VisualizationHelper;//::instance();
  // Vec_t pt(3.,4.,5.,10.);
  v->InitializeVisualizer();
  // v->Register(pt);
  v->Register("geom.gdml");
  TFile *fp = new TFile(argv[1], "r");
  TTree *tr = (TTree *)fp->Get(argv[2]);
  std::vector<Data *> *VectorOfDataObject = NULL;
  Vector3D *poca = NULL;
  tr->SetBranchAddress("VectorOfDataObject", &VectorOfDataObject);
  tr->SetBranchAddress("POCA", &poca);
  std::cout << "Total number of entries in the tree : " << tr->GetEntries() << std::endl;

  Vec_t tempPt;

  for (unsigned int j = 0; j < tr->GetEntries(); j++) {

    tr->GetEntry(j);
    //std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    for (unsigned int i = 0; i < VectorOfDataObject->size(); i++) {

      /*std::cout << "--------------------------------------" << std::endl;
      std::cout << "POCA : ";
      poca->Print();
      (*VectorOfDataObject)[i]->Print();*/
      tempPt.Set(poca->GetX()/10.,poca->GetY()/10.,poca->GetZ()/10.);
      v->Register(tempPt);
      
    }
  }

  double color =10;
  //Now tryig to register a voxel
  /*Vec_t voxDim(10.,10.,10.);
  Vec_t voxCenter(0.,0.,0.);
  v->Register(voxDim,voxCenter,5);*/
  
  v->Lock();
  // rev.CloseBins();

  v->Show();
  fApp->Run();

  return 0;
}
