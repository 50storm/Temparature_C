#include <stdio.h>
#include <string.h>
#define DEBUG 0
#define println()(printf("\n"))
/*  prototype functions */

struct temparature_type{
  int month;
  double day_avg;
  double day_max;
  double day_min;
  double month_max;
  double month_min;
};

int set_tempara_data(struct temparature_type *, char [] );
int main(int argc, const char * argv[]) {
  /*初期処理*/
  int flg_pg=0;

  //月別のファイル読み込み
  //char filename[]="tempara_2015.dat";
  char *filename="tempara_2015.dat";


  struct temparature_type tempara_data[1000];

  flg_pg=set_tempara_data( tempara_data, filename );


  return 0;
}

int set_tempara_data(struct temparature_type *tempara_data, char filename[] ){
  int k;
  char buf[1000];
  FILE* fp;
  
  fp = fopen(filename, "r");
  if(fp==NULL){
    printf("File does not exist.");
    return -1;

  }
  while (fgets(buf, 256, fp) != NULL) {
    int ret = sscanf(buf, "%d"  "%lf"  "%lf"
        "%lf"  "%lf"  "%lf", 
        &tempara_data[k].month, &tempara_data[k].day_avg, &tempara_data[k].day_max, 
        &tempara_data[k].day_min, &tempara_data[k].month_max, &tempara_data[k].month_min
        );//ok
    printf("%d\n",ret);//6

    k++;
  }

  for(k=0; k<12 ; k++){
    printf("debugging\t");
    printf("month=%d \t day_avg=%f \t day_max=%f \t day_min=%f \t month_max=%f \t month_min=%f ", 
    tempara_data[k].month , tempara_data[k].day_avg , tempara_data[k].day_max , tempara_data[k].day_min , tempara_data[k].month_max, tempara_data[k].month_min);
    println();
  }
  fclose(fp);
  return 0;
}
