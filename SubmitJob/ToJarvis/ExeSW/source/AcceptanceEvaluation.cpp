
#include "MyHead.h"

void check_acceptance(Double_t X[],Double_t dir[],Double_t theta,Bool_t &accepted_event) {
    Double_t X_detector[3];

    propagate(X,dir,theta,X_detector,h_layer);
    if( fabs(X_detector[0])<Ldet/2 && fabs(X_detector[1])<Ldet/2 )
        accepted_event = true;
    else
        accepted_event = false;
}

void propagate(Double_t X[],Double_t dir[],Double_t theta,Double_t X_detector[],const Double_t h_layer) {
    Double_t dz = fabs(X[2] - h_layer);
    Double_t r = dz/dir[2];

    X_detector[0] = X[0] + r*dir[0];
    X_detector[1] = X[1] + r*dir[1];
    X_detector[2] = h_layer;
}

Double_t Get_Telescope_Analysical_Acceptance(Double_t _l, Double_t _a1, Double_t _b1, Double_t _a2, Double_t _b2) {

  //l: distance from planes                                                                                                       
  //a1,b1: sides of upper squares                                                                                                 
  //a2,b2: sides of lower squares   

  Double_t a = 0.5*(_a1+_a2);
  Double_t b = 0.5*(_b1+_b2);
  Double_t c = 0.5*(_a1-_a2);
  Double_t d = 0.5*(_b1-_b2);
  Double_t a2 = pow(a,2);
  Double_t b2 = pow(b,2);
  Double_t c2 = pow(c,2);
  Double_t d2 = pow(d,2);
  Double_t l2 = pow(_l,2);

  Double_t G = 0;
  
  G += l2 * log( (l2+a2+d2)/(l2+a2+b2) * (l2+c2+b2)/(l2+c2+d2) );
  G += 2*a*sqrt(l2+b2)*atan( a/sqrt(l2+a2) );
  G += 2*b*sqrt(l2+a2)*atan( b/sqrt(l2+b2) );
  G += 2*c*sqrt(l2+d2)*atan( c/sqrt(l2+d2) );
  G += 2*d*sqrt(l2+c2)*atan( d/sqrt(l2+c2) );
  G -= 2*a*sqrt(l2+d2)*atan( a/sqrt(l2+d2) );
  G -= 2*b*sqrt(l2+c2)*atan( b/sqrt(l2+c2) );
  G -= 2*c*sqrt(l2+b2)*atan( c/sqrt(l2+b2) );
  G -= 2*d*sqrt(l2+a2)*atan( d/sqrt(l2+a2) );

  return G;
  
}

Double_t Get_Acceptance(Double_t ratio) {
    return TMath::Pi()*TMath::Power(Ldet,2)*ratio;
}
