inline bool ignore_arg(double real,double imag,int x,int y){
  if(x>400||y>400) return true;
  if(real*real+imag*imag<0.5){
    return true;
  }
  return false;
}
